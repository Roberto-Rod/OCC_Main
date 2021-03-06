//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.IO.Serial.Socket/UdpSocket.cs $
// $Revision: 3786 $
// $Date: 2021-04-20 16:33:31 +0000 (Tue, 20 Apr 2021) $
// $Author: maettu_this $
// ------------------------------------------------------------------------------------------------
// MKY Version 1.0.30
// ------------------------------------------------------------------------------------------------
// See release notes for product version details.
// See SVN change log for file revision details.
// Author(s): Matthias Klaey
// ------------------------------------------------------------------------------------------------
// Copyright © 2007-2021 Matthias Kläy.
// All rights reserved.
// ------------------------------------------------------------------------------------------------
// This source code is licensed under the GNU LGPL.
// See http://www.gnu.org/licenses/lgpl.html for license details.
//==================================================================================================

#region Configuration
//==================================================================================================
// Configuration
//==================================================================================================

#if (DEBUG)

	// Enable debugging of state:
////#define DEBUG_STATE

	// Enable debugging of threads:
////#define DEBUG_THREADS

#endif // DEBUG

#endregion

#region Using
//==================================================================================================
// Using
//==================================================================================================

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
//// "System.Net" as well as "ALAZ.SystemEx.NetEx" are explicitly used for more obvious distinction.
//// "System.Net.Sockets" as well.
using System.Threading;

using MKY.Collections.Generic;
using MKY.Contracts;
using MKY.Diagnostics;
using MKY.Net;
using MKY.Net.Sockets;

#endregion

namespace MKY.IO.Serial.Socket
{
	/// <remarks>
	/// This class is implemented using partial classes separating sending/receiving functionality.
	/// </remarks>
	public partial class UdpSocket : DisposableBase, IIOProvider
	{
		#region Types
		//==========================================================================================
		// Types
		//==========================================================================================

		private enum SocketState
		{
			Opening,
			Opened,
			Closing,
			Closed,
			Error
		}

		private class AsyncReceiveState
		{
			public System.Net.Sockets.UdpClient Socket                   { get; protected set; }
		////public int                          LocalPort                { get; protected set; } <= Commented-out to prevent FxCopy message CA1811
		////public System.Net.IPAddress         LocalFilter              { get; protected set; } <= "AvoidUncalledPrivateCode" (Microsoft.Performance).
			public uint                         LocalFilterIPv4MaskBytes { get; protected set; }

		////public AsyncReceiveState(System.Net.Sockets.UdpClient socket, int localPort, System.Net.IPAddress localFilter, uint localFilterIPv4MaskBytes)
			public AsyncReceiveState(System.Net.Sockets.UdpClient socket, uint localFilterIPv4MaskBytes)
			{
				Socket                   = socket;
			////LocalPort                = localPort;
			////LocalFilter              = localFilter;
				LocalFilterIPv4MaskBytes = localFilterIPv4MaskBytes;
			}
		}

		#endregion

		#region Constants
		//==========================================================================================
		// Constants
		//==========================================================================================

		private const int SendQueueFixedCapacity      = SocketEx.SendBufferSizeDefault;
		private const int ReceiveQueueInitialCapacity = SocketEx.ReceiveBufferSizeDefault;

		private const int ThreadWaitTimeout = 500; // Enough time to let the threads join...

		private const string Undefined = "(undefined)"; // Lower case same as "localhost".

		#endregion

		#region Fields
		//==========================================================================================
		// Fields
		//==========================================================================================

		/// <summary>
		/// A dedicated event helper to allow discarding exceptions when object got disposed.
		/// </summary>
		private EventHelper.Item eventHelper = EventHelper.CreateItem(typeof(UdpSocket).FullName);

		private int instanceId;
		private UdpSocketType socketType;

		private IPHostEx remoteHost;
		private int remotePort;
		private IPNetworkInterfaceEx localInterface;
		private int localPort;
		private IPFilterEx localFilter;

		private UdpServerSendMode serverSendMode;

		private SocketState state = SocketState.Closed;
		private object stateSyncObj = new object();

		private System.Net.Sockets.UdpClient socket;
		private object socketSyncObj = new object();
		private object dataEventSyncObj = new object();

		private Queue<byte> sendQueue = new Queue<byte>(SendQueueFixedCapacity);
		private bool sendThreadRunFlag;
		private AutoResetEvent sendThreadEvent;
		private Thread sendThread;
		private object sendThreadSyncObj = new object();

		/// <remarks>
		/// Async receiving. The capacity is set large enough to reduce the number of resizing
		/// operations while adding items.
		/// </remarks>
		private Queue<Pair<byte, System.Net.IPEndPoint>> receiveQueue = new Queue<Pair<byte, System.Net.IPEndPoint>>(ReceiveQueueInitialCapacity);
		private bool receiveThreadRunFlag;
		private AutoResetEvent receiveThreadEvent;
		private Thread receiveThread;
		private object receiveThreadSyncObj = new object();

		#endregion

		#region Events
		//==========================================================================================
		// Events
		//==========================================================================================

		/// <summary></summary>
		public event EventHandler<EventArgs<DateTime>> IOChanged;

		/// <summary></summary>
		public event EventHandler<EventArgs<DateTime>> IOControlChanged;

		/// <summary></summary>
		public event EventHandler<IOWarningEventArgs> IOWarning;

		/// <summary></summary>
		public event EventHandler<IOErrorEventArgs> IOError;

		/// <summary></summary>
		[CallingContract(IsNeverMainThread = true, IsAlwaysSequential = true)]
		public event EventHandler<DataReceivedEventArgs> DataReceived;

		/// <summary></summary>
		[CallingContract(IsNeverMainThread = true, IsAlwaysSequential = true)]
		public event EventHandler<DataSentEventArgs> DataSent;

		#endregion

		#region Object Lifetime
		//==========================================================================================
		// Object Lifetime
		//==========================================================================================

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.Client"/>.</summary>
		/// <remarks>The local IP network interface is defaulted to <see cref="System.Net.IPAddress.Any"/> or <see cref="System.Net.IPAddress.IPv6Any"/>.</remarks>
		/// <remarks>The local IP address filter is set to the remote IP address.</remarks>
		/// <exception cref="ArgumentException"><paramref name="remoteHost"/> is <see cref="IPHost.Explicit"/>.</exception>
		public UdpSocket(IPHost remoteHost, int remotePort)
			: this((IPHostEx)remoteHost, remotePort)
		{
		}

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.Client"/>.</summary>
		/// <remarks>The local IP network interface is defaulted to <see cref="System.Net.IPAddress.Any"/> or <see cref="System.Net.IPAddress.IPv6Any"/>.</remarks>
		/// <remarks>The local IP address filter is set to the remote IP address.</remarks>
		/// <exception cref="ArgumentNullException"><paramref name="remoteHost"/> is <c>null</c>.</exception>
		public UdpSocket(IPHostEx remoteHost, int remotePort)
			: this(SocketBase.NextInstanceId, remoteHost, remotePort, IPAddressEx.GetAnyOfFamily(remoteHost.Address))
		{
		}

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.Client"/>.</summary>
		/// <remarks>The local IP network interface is defaulted to <see cref="System.Net.IPAddress.Any"/> or <see cref="System.Net.IPAddress.IPv6Any"/>.</remarks>
		/// <remarks>The local IP address filter is set to the remote IP address.</remarks>
		/// <exception cref="ArgumentException"><paramref name="remoteHost"/> is <see cref="IPHost.Explicit"/>.</exception>
		public UdpSocket(int instanceId, IPHost remoteHost, int remotePort)
			: this(instanceId, (IPHostEx)remoteHost, remotePort)
		{
		}

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.Client"/>.</summary>
		/// <remarks>The local IP network interface is defaulted to <see cref="System.Net.IPAddress.Any"/> or <see cref="System.Net.IPAddress.IPv6Any"/>.</remarks>
		/// <remarks>The local IP address filter is set to the remote IP address.</remarks>
		/// <exception cref="ArgumentNullException"><paramref name="remoteHost"/> is <c>null</c>.</exception>
		public UdpSocket(int instanceId, IPHostEx remoteHost, int remotePort)
			: this(instanceId, remoteHost, remotePort, IPAddressEx.GetAnyOfFamily(remoteHost.Address))
		{
		}

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.Client"/>.</summary>
		/// <remarks>The local IP address filter is set to the remote IP address.</remarks>
		/// <exception cref="ArgumentException"><paramref name="remoteHost"/> is <see cref="IPHost.Explicit"/>.</exception>
		/// <exception cref="ArgumentException"><paramref name="localInterface"/> is <see cref="IPNetworkInterface.Explicit"/>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="remoteHost"/> and <paramref name="localInterface"/>.</exception>
		public UdpSocket(IPHost remoteHost, int remotePort, IPNetworkInterface localInterface)
			: this((IPHostEx)remoteHost, remotePort, (IPNetworkInterfaceEx)localInterface)
		{
		}

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.Client"/>.</summary>
		/// <remarks>The local IP address filter is set to the remote IP address.</remarks>
		/// <exception cref="ArgumentNullException"><paramref name="remoteHost"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="remoteHost"/> and <paramref name="localInterface"/>.</exception>
		public UdpSocket(IPHostEx remoteHost, int remotePort, IPNetworkInterfaceEx localInterface)
			: this(SocketBase.NextInstanceId, remoteHost, remotePort, localInterface)
		{
		}

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.Client"/>.</summary>
		/// <remarks>The local IP address filter is set to the remote IP address.</remarks>
		/// <exception cref="ArgumentException"><paramref name="remoteHost"/> is <see cref="IPHost.Explicit"/>.</exception>
		/// <exception cref="ArgumentException"><paramref name="localInterface"/> is <see cref="IPNetworkInterface.Explicit"/>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="remoteHost"/> and <paramref name="localInterface"/>.</exception>
		public UdpSocket(int instanceId, IPHost remoteHost, int remotePort, IPNetworkInterface localInterface)
			: this(instanceId, (IPHostEx)remoteHost, remotePort, (IPNetworkInterfaceEx)localInterface)
		{
		}

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.Client"/>.</summary>
		/// <remarks>The local IP address filter is set to the remote IP address.</remarks>
		/// <exception cref="ArgumentNullException"><paramref name="remoteHost"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="remoteHost"/> and <paramref name="localInterface"/>.</exception>
		public UdpSocket(int instanceId, IPHostEx remoteHost, int remotePort, IPNetworkInterfaceEx localInterface)
			: this(instanceId, UdpSocketType.Client, remoteHost, remotePort, localInterface, 0, (System.Net.IPAddress)remoteHost)
		{
		}

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.Server"/>.</summary>
		/// <exception cref="ArgumentException"><paramref name="localInterface"/> is <see cref="IPNetworkInterface.Explicit"/>.</exception>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public UdpSocket(IPNetworkInterface localInterface, int localPort, UdpServerSendMode serverSendMode = UdpServerSendMode.MostRecent)
			: this((IPNetworkInterfaceEx)localInterface, localPort, serverSendMode)
		{
		}

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.Server"/>.</summary>
		/// <exception cref="ArgumentNullException"><paramref name="localInterface"/> is <c>null</c>.</exception>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public UdpSocket(IPNetworkInterfaceEx localInterface, int localPort, UdpServerSendMode serverSendMode = UdpServerSendMode.MostRecent)
			: this(SocketBase.NextInstanceId, localInterface, localPort, IPAddressEx.GetAnyOfFamily(localInterface.Address), serverSendMode)
		{
		}

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.Server"/>.</summary>
		/// <exception cref="ArgumentException"><paramref name="localInterface"/> is <see cref="IPNetworkInterface.Explicit"/>.</exception>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public UdpSocket(int instanceId, IPNetworkInterface localInterface, int localPort, UdpServerSendMode serverSendMode = UdpServerSendMode.MostRecent)
			: this(instanceId, (IPNetworkInterfaceEx)localInterface, localPort, serverSendMode)
		{
		}

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.Server"/>.</summary>
		/// <exception cref="ArgumentNullException"><paramref name="localInterface"/> is <c>null</c>.</exception>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public UdpSocket(int instanceId, IPNetworkInterfaceEx localInterface, int localPort, UdpServerSendMode serverSendMode = UdpServerSendMode.MostRecent)
			: this(instanceId, UdpSocketType.Server, IPAddressEx.GetNoneOfFamily(localInterface), 0, localInterface, localPort, IPAddressEx.GetAnyOfFamily(localInterface.Address), serverSendMode)
		{
		}

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.Server"/>.</summary>
		/// <exception cref="ArgumentException"><paramref name="localInterface"/> is <see cref="IPNetworkInterface.Explicit"/>.</exception>
		/// <exception cref="ArgumentException"><paramref name="localFilter"/> is <see cref="IPFilter.Explicit"/>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="localInterface"/> and <paramref name="localFilter"/>.</exception>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public UdpSocket(IPNetworkInterface localInterface, int localPort, IPFilter localFilter, UdpServerSendMode serverSendMode = UdpServerSendMode.MostRecent)
			: this((IPNetworkInterfaceEx)localInterface, localPort, (IPFilterEx)localFilter, serverSendMode)
		{
		}

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.Server"/>.</summary>
		/// <exception cref="ArgumentNullException"><paramref name="localInterface"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentNullException"><paramref name="localFilter"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="localInterface"/> and <paramref name="localFilter"/>.</exception>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public UdpSocket(IPNetworkInterfaceEx localInterface, int localPort, IPFilterEx localFilter, UdpServerSendMode serverSendMode = UdpServerSendMode.MostRecent)
			: this(SocketBase.NextInstanceId, localInterface, localPort, localFilter, serverSendMode)
		{
		}

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.Server"/>.</summary>
		/// <exception cref="ArgumentException"><paramref name="localInterface"/> is <see cref="IPNetworkInterface.Explicit"/>.</exception>
		/// <exception cref="ArgumentException"><paramref name="localFilter"/> is <see cref="IPFilter.Explicit"/>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="localInterface"/> and <paramref name="localFilter"/>.</exception>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public UdpSocket(int instanceId, IPNetworkInterface localInterface, int localPort, IPFilter localFilter, UdpServerSendMode serverSendMode = UdpServerSendMode.MostRecent)
			: this(instanceId, (IPNetworkInterfaceEx)localInterface, localPort, (IPFilterEx)localFilter, serverSendMode)
		{
		}

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.Server"/>.</summary>
		/// <exception cref="ArgumentNullException"><paramref name="localInterface"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentNullException"><paramref name="localFilter"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="localInterface"/> and <paramref name="localFilter"/>.</exception>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public UdpSocket(int instanceId, IPNetworkInterfaceEx localInterface, int localPort, IPFilterEx localFilter, UdpServerSendMode serverSendMode = UdpServerSendMode.MostRecent)
			: this(instanceId, UdpSocketType.Server, IPAddressEx.GetNoneOfFamily(localInterface), 0, localInterface, localPort, localFilter, serverSendMode)
		{
		}

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.PairSocket"/>.</summary>
		/// <remarks>The local IP address filter is set to the remote IP address.</remarks>
		/// <exception cref="ArgumentException"><paramref name="remoteHost"/> is <see cref="IPHost.Explicit"/>.</exception>
		/// <exception cref="ArgumentException"><paramref name="localInterface"/> is <see cref="IPNetworkInterface.Explicit"/>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="remoteHost"/> and <paramref name="localInterface"/>.</exception>
		public UdpSocket(IPHost remoteHost, int remotePort, IPNetworkInterface localInterface, int localPort)
			: this((IPHostEx)remoteHost, remotePort, (IPNetworkInterfaceEx)localInterface, localPort)
		{
		}

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.PairSocket"/>.</summary>
		/// <remarks>The local IP address filter is set to the remote IP address.</remarks>
		/// <exception cref="ArgumentNullException"><paramref name="remoteHost"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentNullException"><paramref name="localInterface"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="remoteHost"/> and <paramref name="localInterface"/>.</exception>
		public UdpSocket(IPHostEx remoteHost, int remotePort, IPNetworkInterfaceEx localInterface, int localPort)
			: this(SocketBase.NextInstanceId, remoteHost, remotePort, localInterface, localPort)
		{
		}

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.PairSocket"/>.</summary>
		/// <remarks>The local IP address filter is set to the remote IP address.</remarks>
		/// <exception cref="ArgumentException"><paramref name="remoteHost"/> is <see cref="IPHost.Explicit"/>.</exception>
		/// <exception cref="ArgumentException"><paramref name="localInterface"/> is <see cref="IPNetworkInterface.Explicit"/>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="remoteHost"/> and <paramref name="localInterface"/>.</exception>
		public UdpSocket(int instanceId, IPHost remoteHost, int remotePort, IPNetworkInterface localInterface, int localPort)
			: this(instanceId, (IPHostEx)remoteHost, remotePort, (IPNetworkInterfaceEx)localInterface, localPort)
		{
		}

		/// <summary>Creates a UDP/IP socket of type <see cref="UdpSocketType.PairSocket"/>.</summary>
		/// <remarks>The local IP address filter is set to the remote IP address.</remarks>
		/// <exception cref="ArgumentNullException"><paramref name="remoteHost"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentNullException"><paramref name="localInterface"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="remoteHost"/> and <paramref name="localInterface"/>.</exception>
		public UdpSocket(int instanceId, IPHostEx remoteHost, int remotePort, IPNetworkInterfaceEx localInterface, int localPort)
			: this(instanceId, UdpSocketType.PairSocket, remoteHost, remotePort, localInterface, localPort, (System.Net.IPAddress)remoteHost)
		{
		}

		/// <summary>Creates a UDP/IP socket of the given type.</summary>
		/// <remarks>The local IP address filter is defaulted to <see cref="System.Net.IPAddress.Any"/> or <see cref="System.Net.IPAddress.IPv6Any"/>.</remarks>
		/// <exception cref="ArgumentException"><paramref name="remoteHost"/> is <see cref="IPHost.Explicit"/>.</exception>
		/// <exception cref="ArgumentException"><paramref name="localInterface"/> is <see cref="IPNetworkInterface.Explicit"/>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="remoteHost"/> and <paramref name="localInterface"/>.</exception>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public UdpSocket(UdpSocketType socketType, IPHost remoteHost, int remotePort, IPNetworkInterface localInterface, int localPort, UdpServerSendMode serverSendMode = UdpServerSendMode.MostRecent)
			: this(socketType, (IPHostEx)remoteHost, remotePort, (IPNetworkInterfaceEx)localInterface, localPort, serverSendMode)
		{
		}

		/// <summary>Creates a UDP/IP socket of the given type.</summary>
		/// <remarks>The local IP address filter is defaulted to <see cref="System.Net.IPAddress.Any"/> or <see cref="System.Net.IPAddress.IPv6Any"/>.</remarks>
		/// <exception cref="ArgumentNullException"><paramref name="remoteHost"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentNullException"><paramref name="localInterface"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="remoteHost"/> and <paramref name="localInterface"/>.</exception>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public UdpSocket(UdpSocketType socketType, IPHostEx remoteHost, int remotePort, IPNetworkInterfaceEx localInterface, int localPort, UdpServerSendMode serverSendMode = UdpServerSendMode.MostRecent)
			: this(SocketBase.NextInstanceId, socketType, remoteHost, remotePort, localInterface, localPort, serverSendMode)
		{
		}

		/// <summary>Creates a UDP/IP socket of the given type.</summary>
		/// <remarks>The local IP address filter is defaulted to <see cref="System.Net.IPAddress.Any"/> or <see cref="System.Net.IPAddress.IPv6Any"/>.</remarks>
		/// <exception cref="ArgumentException"><paramref name="remoteHost"/> is <see cref="IPHost.Explicit"/>.</exception>
		/// <exception cref="ArgumentException"><paramref name="localInterface"/> is <see cref="IPNetworkInterface.Explicit"/>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="remoteHost"/> and <paramref name="localInterface"/>.</exception>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public UdpSocket(int instanceId, UdpSocketType socketType, IPHost remoteHost, int remotePort, IPNetworkInterface localInterface, int localPort, UdpServerSendMode serverSendMode = UdpServerSendMode.MostRecent)
			: this(instanceId, socketType, (IPHostEx)remoteHost, remotePort, (IPNetworkInterfaceEx)localInterface, localPort, serverSendMode)
		{
		}

		/// <summary>Creates a UDP/IP socket of the given type.</summary>
		/// <remarks>The local IP address filter is defaulted to <see cref="System.Net.IPAddress.Any"/> or <see cref="System.Net.IPAddress.IPv6Any"/>.</remarks>
		/// <exception cref="ArgumentNullException"><paramref name="remoteHost"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentNullException"><paramref name="localInterface"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="remoteHost"/> and <paramref name="localInterface"/>.</exception>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public UdpSocket(int instanceId, UdpSocketType socketType, IPHostEx remoteHost, int remotePort, IPNetworkInterfaceEx localInterface, int localPort, UdpServerSendMode serverSendMode = UdpServerSendMode.MostRecent)
			: this(instanceId, socketType, remoteHost, remotePort, localInterface, localPort, IPAddressEx.GetAnyOfFamily(remoteHost.Address), serverSendMode)
		{
		}

		/// <summary>Creates a UDP/IP socket of the given type.</summary>
		/// <exception cref="ArgumentException"><paramref name="remoteHost"/> is <see cref="IPHost.Explicit"/>.</exception>
		/// <exception cref="ArgumentException"><paramref name="localInterface"/> is <see cref="IPNetworkInterface.Explicit"/>.</exception>
		/// <exception cref="ArgumentException"><paramref name="localFilter"/> is <see cref="IPFilter.Explicit"/>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="remoteHost"/> and <paramref name="localInterface"/> or <paramref name="localFilter"/>.</exception>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public UdpSocket(UdpSocketType socketType, IPHost remoteHost, int remotePort, IPNetworkInterface localInterface, int localPort, IPFilter localFilter, UdpServerSendMode serverSendMode = UdpServerSendMode.MostRecent)
			: this(socketType, (IPHostEx)remoteHost, remotePort, (IPNetworkInterfaceEx)localInterface, localPort, (IPFilterEx)localFilter, serverSendMode)
		{
		}

		/// <summary>Creates a UDP/IP socket of the given type.</summary>
		/// <exception cref="ArgumentNullException"><paramref name="remoteHost"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentNullException"><paramref name="localInterface"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentNullException"><paramref name="localFilter"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="remoteHost"/> and <paramref name="localInterface"/> or <paramref name="localFilter"/>.</exception>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public UdpSocket(UdpSocketType socketType, IPHostEx remoteHost, int remotePort, IPNetworkInterfaceEx localInterface, int localPort, IPFilterEx localFilter, UdpServerSendMode serverSendMode = UdpServerSendMode.MostRecent)
			: this(SocketBase.NextInstanceId, socketType, remoteHost, remotePort, localInterface, localPort, localFilter, serverSendMode)
		{
		}

		/// <summary>Creates a UDP/IP socket of the given type.</summary>
		/// <exception cref="ArgumentException"><paramref name="remoteHost"/> is <see cref="IPHost.Explicit"/>.</exception>
		/// <exception cref="ArgumentException"><paramref name="localInterface"/> is <see cref="IPNetworkInterface.Explicit"/>.</exception>
		/// <exception cref="ArgumentException"><paramref name="localFilter"/> is <see cref="IPFilter.Explicit"/>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="remoteHost"/> and <paramref name="localInterface"/> or <paramref name="localFilter"/>.</exception>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public UdpSocket(int instanceId, UdpSocketType socketType, IPHost remoteHost, int remotePort, IPNetworkInterface localInterface, int localPort, IPFilter localFilter, UdpServerSendMode serverSendMode = UdpServerSendMode.MostRecent)
			: this(instanceId, socketType, (IPHostEx)remoteHost, remotePort, (IPNetworkInterfaceEx)localInterface, localPort, (IPFilterEx)localFilter, serverSendMode)
		{
		}

		/// <summary>Creates a UDP/IP socket of the given type.</summary>
		/// <exception cref="ArgumentNullException"><paramref name="remoteHost"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentNullException"><paramref name="localInterface"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentNullException"><paramref name="localFilter"/> is <c>null</c>.</exception>
		/// <exception cref="ArgumentException">Mismatching <see cref="System.Net.Sockets.AddressFamily"/> of <paramref name="remoteHost"/> and <paramref name="localInterface"/> or <paramref name="localFilter"/>.</exception>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public UdpSocket(int instanceId, UdpSocketType socketType, IPHostEx remoteHost, int remotePort, IPNetworkInterfaceEx localInterface, int localPort, IPFilterEx localFilter, UdpServerSendMode serverSendMode = UdpServerSendMode.MostRecent)
		{
			// Assert by-reference arguments:

			if (remoteHost     == null) throw (new ArgumentNullException("remoteHost",     MessageHelper.InvalidExecutionPreamble + Environment.NewLine + Environment.NewLine + MessageHelper.SubmitBug));
			if (localInterface == null) throw (new ArgumentNullException("localInterface", MessageHelper.InvalidExecutionPreamble + Environment.NewLine + Environment.NewLine + MessageHelper.SubmitBug));
			if (localFilter    == null) throw (new ArgumentNullException("localFilter",    MessageHelper.InvalidExecutionPreamble + Environment.NewLine + Environment.NewLine + MessageHelper.SubmitBug));

			// All arguments are defined!

			if (remoteHost.Address.AddressFamily != localInterface.Address.AddressFamily) // Do not prepend/append 'SubmitBug' as an application could rely and the error message.
				throw (new ArgumentException(string.Format(CultureInfo.CurrentCulture, "Mismatching address families! Remote host is {0} while local interface is {1}.", remoteHost.Address.AddressFamily, localInterface.Address.AddressFamily)));

			if (remoteHost.Address.AddressFamily != localFilter.Address.AddressFamily) // Do not prepend/append 'SubmitBug' as an application could rely and the error message.
				throw (new ArgumentException(string.Format(CultureInfo.CurrentCulture, "Mismatching address families! Remote host is {0} while local filter is {1}.", remoteHost.Address.AddressFamily, localFilter.Address.AddressFamily)));

			this.instanceId     = instanceId;
			this.socketType     = socketType;

			this.remoteHost     = remoteHost;
			this.remotePort     = remotePort;
			this.localInterface = localInterface;
			this.localPort      = localPort;
			this.localFilter    = localFilter;

			this.serverSendMode = serverSendMode;
		}

		#region Disposal
		//------------------------------------------------------------------------------------------
		// Disposal
		//------------------------------------------------------------------------------------------

		/// <param name="disposing">
		/// <c>true</c> when called from <see cref="Dispose"/>,
		/// <c>false</c> when called from finalizer.
		/// </param>
		protected override void Dispose(bool disposing)
		{
			if (this.eventHelper != null) // Possible when called by finalizer (non-deterministic).
				this.eventHelper.DiscardAllEventsAndExceptions();

			// Dispose of managed resources:
			if (disposing)
			{
				DebugMessage("Disposing...");

				// In the 'normal' case, the items have already been disposed of, e.g. in Stop().
				DisposeSocketAndThreads();

				DebugMessage("...successfully disposed.");
			}

		////base.Dispose(disposing) of 'DisposableBase' doesn't need and cannot be called since abstract.
		}

		#endregion

		#endregion

		#region Properties
		//==========================================================================================
		// Properties
		//==========================================================================================

		/// <summary></summary>
		public virtual UdpSocketType SocketType
		{
			get
			{
			////AssertUndisposed() shall not be called from this simple get-property.

				return (this.socketType);
			}
		}

		/// <summary></summary>
		public virtual IPHostEx RemoteHost
		{
			get
			{
			////AssertUndisposed() shall not be called from this simple get-property.

				lock (this.socketSyncObj)
					return (this.remoteHost);
			}
		}

		/// <remarks>Convenience method, always returns a valid value, at least "(undefined)".</remarks>
		protected virtual string RemoteHostEndpointString
		{
			get
			{
			////AssertUndisposed() shall not be called from this simple get-property.

				var remoteHost = RemoteHost;
				return ((remoteHost != null) ? (remoteHost.ToEndpointAddressString()) : Undefined);
			}
		}

		/// <summary></summary>
		public virtual bool RemoteIPAddressIsDefined
		{
			get
			{
			////AssertUndisposed() shall not be called from this simple get-property.

				lock (this.socketSyncObj)
					return (IPAddressEx.NotEqualsNone(this.remoteHost.Address));
			}
		}

		/// <summary></summary>
		public virtual int RemotePort
		{
			get
			{
			////AssertUndisposed() shall not be called from this simple get-property.

				lock (this.socketSyncObj)
					return (this.remotePort);
			}
		}

		/// <summary></summary>
		public virtual System.Net.IPEndPoint RemoteEndPoint
		{
			get
			{
			////AssertUndisposed() shall not be called from this simple get-property.

				lock (this.socketSyncObj)
					return (new System.Net.IPEndPoint(this.remoteHost, this.remotePort));
			}
		}

		/// <summary></summary>
		public virtual IPNetworkInterfaceEx LocalInterface
		{
			get
			{
			////AssertUndisposed() shall not be called from this simple get-property.

				return (this.localInterface);
			}
		}

		/// <summary></summary>
		public virtual int LocalPort
		{
			get
			{
			////AssertUndisposed() shall not be called from this simple get-property.

				lock (this.socketSyncObj)
					return (this.localPort);
			}
		}

		/// <summary></summary>
		public virtual IPFilterEx LocalFilter
		{
			get
			{
			////AssertUndisposed() shall not be called from this simple get-property.

				lock (this.socketSyncObj)
					return (this.localFilter);
			}
		}

		/// <summary></summary>
		public virtual UdpServerSendMode ServerSendMode
		{
			get
			{
			////AssertUndisposed() shall not be called from this simple get-property.

				lock (this.socketSyncObj)
					return (this.serverSendMode);
			}
		}

		/// <summary></summary>
		public virtual bool IsStopped
		{
			get
			{
			////AssertUndisposed() shall not be called from this simple get-property.

				switch (GetStateSynchronized())
				{
					case SocketState.Closed:
					case SocketState.Error:
					{
						return (true);
					}
					default:
					{
						return (false);
					}
				}
			}
		}

		/// <summary></summary>
		public virtual bool IsStarted
		{
			get
			{
			////AssertUndisposed() shall not be called from this simple get-property.

				switch (GetStateSynchronized())
				{
					case SocketState.Opening:
					case SocketState.Opened:
					{
						return (true);
					}
					default:
					{
						return (false);
					}
				}
			}
		}

		/// <summary></summary>
		public virtual bool IsOpen
		{
			get
			{
			////AssertUndisposed() shall not be called from this simple get-property.

				switch (GetStateSynchronized())
				{
					case SocketState.Opened:
					{
						return (true);
					}
					default:
					{
						return (false);
					}
				}
			}
		}

		/// <summary></summary>
		public virtual bool IsConnected
		{
			get
			{
			////AssertUndisposed() is called by 'IsOpen' below.

				return (IsOpen);
			}
		}

		/// <summary></summary>
		public virtual bool IsTransmissive
		{
			get
			{
			////AssertUndisposed() is called by 'IsOpen' below.

				if (this.socketType == UdpSocketType.Server)
					return (IsOpen && RemoteIPAddressIsDefined); // Remote endpoint is the sender of the first or most recently received data.
				else
					return (IsOpen); // Remote endpoint has been defaulted on Create().
			}
		}

		/// <remarks>
		/// The value of this property only reflects the state of the send queue.
		/// <para>
		/// The state of the underlying <see cref="UdpSocket"/> is not taken into account, as there
		/// is no feasible to implement this in a solid way.
		/// </para><para>
		/// Neither is the state of the underlying operating system socket taken into account, as
		/// its state cannot be retrieved from within this .NET implementation by common means.
		/// </para></remarks>
		public virtual bool IsSending
		{
			get
			{
			////AssertUndisposed() shall not be called from this simple get-property.

				if (IsTransmissive)
				{
					lock (this.sendQueue) // Lock is required because "Queue<T>" is not synchronized.
						return (this.sendQueue.Count > 0);
				}
				else
				{
					return (false);
				}
			}
		}

		/// <summary></summary>
		public virtual object UnderlyingIOInstance
		{
			get
			{
				AssertUndisposed();

				return (this.socket);
			}
		}

		#endregion

		#region Public Methods
		//==========================================================================================
		// Public Methods
		//==========================================================================================

		/// <summary></summary>
		public virtual bool Start()
		{
		////AssertUndisposed() is called by 'IsStopped' below.

			if (IsStopped)
			{
				if ((this.socketType == UdpSocketType.Client) ||
				    (this.socketType == UdpSocketType.PairSocket))
				{
					DebugMessage("Resolving remote host address...");
					if (!this.remoteHost.TryResolve())
					{
						DebugMessage("...failed!");
						return (false);
					}
					DebugMessage("...succeeded ({0}).", this.remoteHost);
				}

				// Adjust the local filter in case it is set to a limited or directed broadcast address.
				// For [Client] and [PairSocket] this is the case if the remote host is set that way.
				// For [Server] this is the case if the user accidentally enters some *.255 address.
				//
				// Limited broadcast:  A packet is sent to a specific network or series of networks. A limited
				//                     broadcast address includes the network or subnet fields. In a limited
				//                     broadcast packet destined for a local network, the network identifier
				//                     portion and host identifier portion of the destination address is either
				//                     all ones (255.255.255.255) or all zeros (0.0.0.0).
				// Flooded broadcast:  A packet is sent to every network.
				// Directed broadcast: A packet is sent to a specific destination address where only the host
				//                     portion of the IP address is either all ones or all zeros (such as
				//                     192.20.255.255 or 190.20.0.0).
				// (https://www.juniper.net/documentation/en_US/junose15.1/topics/concept/ip-broadcast-addressing-overview.html)

				var localFilterCasted = (IPHostEx)this.localFilter.Address;
				if (localFilterCasted.IsBroadcast) // = limited broadcast (255.255.255.255)
				{                                                // Filtering for limited broadcast address (255.255.255.255) doesn't work.
					this.localFilter = (IPFilterEx)IPFilter.Any; // Nothing would be received => using any address (0.0.0.0) instead.
				}
				else
				{
					var directedBroadcastAddress = IPNetworkInterfaceEx.RetrieveDirectedBroadcastAddress(this.localFilter.Address); // e.g. (192.20.255.255)
					                             // IPAddress does not override the ==/!= operators, thanks Microsoft guys...
					if (this.localFilter.Address.Equals(directedBroadcastAddress)) // = directed broadcast e.g. (192.20.255.255)
					{                                                                                                       // Filtering for directed broadcast address (192.20.255.255) doesn't work.
						var directedAnyAddress = IPNetworkInterfaceEx.RetrieveDirectedAnyAddress(this.localFilter.Address); // Nothing would be received => using directed any address (192.20.0.0) instead.
						this.localFilter = directedAnyAddress;
					}
				}

				DebugMessage("Resolving local filter address...");
				if (!this.localFilter.TryResolve())
				{
					DebugMessage("...failed!");
					return (false);
				}
				DebugMessage("...succeeded ({0}).", this.localFilter);

				DebugMessage("Starting...");
				StartSocket();
				return (true);
			}
			else
			{
				DebugMessage("Start() requested but state already is {0}.", GetStateSynchronized());
				return (true); // Return 'true' since socket is already started.
			}
		}

		private void StartSocket()
		{
			SetStateSynchronizedAndNotify(SocketState.Opening);
			CreateAndStartSocketAndThreads();
			SetStateSynchronizedAndNotify(SocketState.Opened);

			BeginReceiveIfEnabled(); // Immediately begin receiving.
		}

		/// <summary></summary>
		[SuppressMessage("Microsoft.Naming", "CA1716:IdentifiersShouldNotMatchKeywords", MessageId = "Stop", Justification = "'Stop' is a common term to start/stop something.")]
		public virtual void Stop()
		{
		////AssertUndisposed() is called by 'IsStarted' below.

			if (IsStarted)
			{
				DebugMessage("Stopping...");
				StopSocket();
			}
			else
			{
				DebugMessage("Stop() requested but state is {0}.", GetStateSynchronized());
			}
		}

		private void StopSocket()
		{
			SetStateSynchronizedAndNotify(SocketState.Closing);
			DisposeSocketAndThreads();
			SetStateSynchronizedAndNotify(SocketState.Closed);
		}

		#endregion

		#region State Methods
		//==========================================================================================
		// State Methods
		//==========================================================================================

		private SocketState GetStateSynchronized()
		{
			lock (this.stateSyncObj)
				return (this.state);
		}

		private void SetStateSynchronizedAndNotify(SocketState state)
		{
			SocketState oldState;

			lock (this.stateSyncObj)
			{
				oldState = this.state;
				this.state = state;

			#if (DEBUG) // Inside lock to prevent potential mixup in debug output.
				if (state != oldState)
					DebugMessage("State has changed from {0} to {1}.", oldState, state);
				else
					DebugState("State already is {0}.", oldState); // State non-changes shall only be output when explicitly activated.
			#endif
			}

			if (state != oldState) // Outside lock is OK, only stating change, not state.
				OnIOChanged(new EventArgs<DateTime>(DateTime.Now));
		}

		#endregion

		#region Socket Methods
		//==========================================================================================
		// Socket Methods
		//==========================================================================================

		/// <remarks>
		/// Not using a separate StartThreads() like implementation of other serial entities as
		/// ReceiveThread() is created and started before socket and SendThread(). Implementation of
		/// other serial entities could also follow this implementation when there is need to do so.
		/// </remarks>
		private void CreateAndStartSocketAndThreads()
		{
			lock (this.receiveQueue) // Lock is required because "Queue<T>" is not synchronized.
			{
				this.receiveQueue.Clear();
			}

			// First, create and start receive thread to be ready when socket first receives data:

			lock (this.receiveThreadSyncObj)
			{
				if (this.receiveThread == null)
				{
					this.receiveThreadRunFlag = true;
					this.receiveThreadEvent = new AutoResetEvent(false);
					this.receiveThread = new Thread(new ThreadStart(ReceiveThread));
					this.receiveThread.Name = ToShortEndPointString() + " Receive Thread";
					this.receiveThread.Start();
				}
			}

			// Then, create socket:

			lock (this.socketSyncObj)
			{
				// Address family must be set in order to support IPv6. Otherwise, socket is fixed to IPv4.
				// But neither local nor remote endpoint must be set in constructor! Otherwise, options cannot be changed below!
				this.socket = new System.Net.Sockets.UdpClient(this.localInterface.Address.AddressFamily);

				// Configure the listener port:
				if (this.socketType == UdpSocketType.Server)
				{
					this.socket.ExclusiveAddressUse = false; // "Address" is misleading, it's about the port: "only one client to use a specific port".
					this.socket.Client.SetSocketOption(System.Net.Sockets.SocketOptionLevel.Socket, System.Net.Sockets.SocketOptionName.ReuseAddress, true);
				}

			////if (this.remoteHost.IsBroadcast) => Not used, see notes below.
			////{
			////	this.socket.EnableBroadcast = true;
			////	this.socket.Client.SetSocketOption(System.Net.Sockets.SocketOptionLevel.Socket, System.Net.Sockets.SocketOptionName.Broadcast, true);
			////}

				// Bind the socket:
				// Socket.Bind() "If you do not care which local port is used, you can create an IPEndPoint using 0 for the port number.
				//                In this case, the service provider will assign an available port number between 49152 and 65535."
				var localEP = new System.Net.IPEndPoint(this.localInterface.Address, this.localPort);
				this.socket.Client.Bind(localEP);
				DebugMessage("Socket bound to {0}.", localEP);

			////// Set the default remote endpoint of a client socket:
			////if ((this.socketType == UdpSocketType.Client) ||
			////    (this.socketType == UdpSocketType.PairSocket))
			////{
			////	this.socket.Connect(this.remoteHost.Address, this.remotePort);
			////	DebugMessage(string.Format(@"Socket ""connected"" to {0}.", new System.Net.IPEndPoint(this.remoteHost.Address, this.remotePort)));
			////
			////	// Note the following remark of the UdpClient.Connect() method:
			////	//
			////	// "You cannot set the default remote host to a broadcast address using this method unless (...)
			////	//  and set the socket option to SocketOptionName.Broadcast."
			////	// "You can however, broadcast data to the default broadcast address, 255.255.255.255, if
			////	//  you specify IPAddress.Broadcast in your call to the Send method."
			////	// (https://docs.microsoft.com/en-us/dotnet/api/system.net.sockets.udpclient.connect)
			////	//
			////	// However, this doesn't properly work. Sending to broadcast address works,
			////	// but receiving doesn't! Also, this wouldn't work with a directed broadcast!
			////	// Finally, there is not much benefit of calling UdpClient.Connect(), specifying
			////	// the remote host IP on each UdpClient.Send() is no issue.
			////	//  => UdpClient.Connect() above not used.
			////}
			////else // Server
			////{
			////	// The remote address will be set to the sender of the first or most recently received data.
			////}
			}

			lock (this.sendQueue) // Lock is required because "Queue<T>" is not synchronized.
			{
				this.sendQueue.Clear();
			}

			// Finally, create and start send thread:

			DebugThreads("SendThread() gets started...");

			lock (this.sendThreadSyncObj)
			{
				if (this.sendThread == null)
				{
					this.sendThreadRunFlag = true;
					this.sendThreadEvent = new AutoResetEvent(false);
					this.sendThread = new Thread(new ThreadStart(SendThread));
					this.sendThread.Name = ToShortEndPointString() + " Send Thread";
					this.sendThread.Start();
				}
			}
		}

		/// <remarks>
		/// Especially useful during potentially dangerous creation and disposal sequence.
		/// </remarks>
		private void SignalSendThreadSafely()
		{
			try
			{
				if (this.sendThreadEvent != null)
					this.sendThreadEvent.Set();
			}
			catch (ObjectDisposedException ex) { DebugEx.WriteException(GetType(), ex, "Unsafe thread signaling caught"); }
			catch (NullReferenceException ex)  { DebugEx.WriteException(GetType(), ex, "Unsafe thread signaling caught"); }

			// Catch 'NullReferenceException' for the unlikely case that the event has just been
			// disposed after the if-check. This way, the event doesn't need to be locked (which
			// is a relatively time-consuming operation). Still keep the if-check for the normal
			// cases.
		}

		/// <remarks>
		/// Especially useful during potentially dangerous creation and disposal sequence.
		/// </remarks>
		private void SignalReceiveThreadSafely()
		{
			try
			{
				if (this.receiveThreadEvent != null)
					this.receiveThreadEvent.Set();
			}
			catch (ObjectDisposedException ex) { DebugEx.WriteException(GetType(), ex, "Unsafe thread signaling caught"); }
			catch (NullReferenceException ex)  { DebugEx.WriteException(GetType(), ex, "Unsafe thread signaling caught"); }

			// Catch 'NullReferenceException' for the unlikely case that the event has just been
			// disposed after the if-check. This way, the event doesn't need to be locked (which
			// is a relatively time-consuming operation). Still keep the if-check for the normal
			// cases.
		}

		private void DisposeSocketAndThreads()
		{
			// First clear both flags to reduce the time to stop the receive thread, it may already
			// be signaled while receiving data while the send thread is still running.

			lock (this.sendThreadSyncObj)
				this.sendThreadRunFlag = false;

			lock (this.receiveThreadSyncObj)
				this.receiveThreadRunFlag = false;

			// Then, stop and dispose send thread to prevent more data being forwarded to socket:

			lock (this.sendThreadSyncObj)
			{
				if (this.sendThread != null)
				{
					DebugThreads("SendThread() gets stopped...");

					// Ensure that send thread has stopped after the stop request:
					try
					{
						Debug.Assert(this.sendThread.ManagedThreadId != Thread.CurrentThread.ManagedThreadId, "Attention: Tried to join itself!");

						bool isAborting = false;
						int accumulatedTimeout = 0;
						int interval = 0; // Use a relatively short random interval to trigger the thread:
						while (!this.sendThread.Join(interval = SocketBase.Random.Next(5, 20)))
						{
							SignalSendThreadSafely();

							accumulatedTimeout += interval;
							if (accumulatedTimeout >= ThreadWaitTimeout)
							{
								DebugThreads("...failed! Aborting...");
								DebugThreads("(Abort is likely required due to failed synchronization back the calling thread, which is typically the main thread.)");

								isAborting = true;       // Thread.Abort() must not be used whenever possible!
								this.sendThread.Abort(); // This is only the fall-back in case joining fails for too long.
								break;
							}

							DebugThreads("...trying to join at " + accumulatedTimeout + " ms...");
						}

						if (!isAborting)
							DebugThreads("...successfully stopped.");
					}
					catch (ThreadStateException)
					{
						// Ignore thread state exceptions such as "Thread has not been started" and
						// "Thread cannot be aborted" as it just needs to be ensured that the thread
						// has or will be terminated for sure.

						DebugThreads("...failed too but will be exectued as soon as the calling thread gets suspended again.");
					}

					this.sendThread = null;
				}

				if (this.sendThreadEvent != null)
				{
					try     { this.sendThreadEvent.Close(); }
					finally { this.sendThreadEvent = null; }
				}
			} // lock (sendThreadSyncObj)

			DropSendQueueAndNotify();

			// Then, close and dispose socket:

			lock (this.socketSyncObj)
			{
				if (this.socket != null)
				{
					this.socket.Close();
					this.socket = null;
				}
			}

			// Finally, stop and dispose receive thread:

			lock (this.receiveThreadSyncObj)
			{
				if (this.receiveThread != null)
				{
					DebugThreads("ReceiveThread() gets stopped...");

					// Ensure that receive thread has stopped after the stop request:
					try
					{
						Debug.Assert(this.receiveThread.ManagedThreadId != Thread.CurrentThread.ManagedThreadId, "Attention: Tried to join itself!");

						bool isAborting = false;
						int accumulatedTimeout = 0;
						int interval = 0; // Use a relatively short random interval to trigger the thread:
						while (!this.receiveThread.Join(interval = SocketBase.Random.Next(5, 20)))
						{
							SignalReceiveThreadSafely();

							accumulatedTimeout += interval;
							if (accumulatedTimeout >= ThreadWaitTimeout)
							{
								DebugThreads("...failed! Aborting...");
								DebugThreads("(Abort is likely required due to failed synchronization back the calling thread, which is typically the main thread.)");

								isAborting = true;          // Thread.Abort() must not be used whenever possible!
								this.receiveThread.Abort(); // This is only the fall-back in case joining fails for too long.
								break;
							}

							DebugThreads("...trying to join at " + accumulatedTimeout + " ms...");
						}

						if (!isAborting)
							DebugThreads("...successfully stopped.");
					}
					catch (ThreadStateException)
					{
						// Ignore thread state exceptions such as "Thread has not been started" and
						// "Thread cannot be aborted" as it just needs to be ensured that the thread
						// has or will be terminated for sure.

						DebugThreads("...failed too but will be exectued as soon as the calling thread gets suspended again.");
					}

					this.receiveThread = null;
				}

				if (this.receiveThreadEvent != null)
				{
					try     { this.receiveThreadEvent.Close(); }
					finally { this.receiveThreadEvent = null; }
				}
			} // lock (receiveThreadSyncObj)

			DropReceiveQueueAndNotify();
		}

		private int DropSendQueueAndNotify()
		{
			int droppedCount = DropSendQueue();
			if (droppedCount > 0)
			{
				string message;
				if (droppedCount <= 1)
					message = droppedCount + " byte not sent anymore.";  // Using "byte" rather than "octet" as that is more common, and .NET uses "byte" as well.
				else                                                     // Reason cannot be stated, could be "disconnected" or "stopped/closed"
					message = droppedCount + " bytes not sent anymore."; // Using "byte" rather than "octet" as that is more common, and .NET uses "byte" as well.

				OnIOWarning(new IOWarningEventArgs(Direction.Output, message));
			}

			return (droppedCount);
		}

		private int DropSendQueue()
		{
			int droppedCount;
			lock (this.sendQueue) // Lock is required because "Queue<T>" is not synchronized.
			{
				droppedCount = this.sendQueue.Count;
				this.sendQueue.Clear();
			}

			return (droppedCount);
		}

		private void DropReceiveQueueAndNotify()
		{
			int droppedCount = DropReceivedQueue();
			if (droppedCount > 0)
			{
				string message;
				if (droppedCount <= 1)
					message = droppedCount + " received byte dropped.";  // Using "byte" rather than "octet" as that is more common, and .NET uses "byte" as well.
				else                                                     // Reason cannot be stated, could be "disconnected" or "stopped/closed"
					message = droppedCount + " received bytes dropped."; // Using "byte" rather than "octet" as that is more common, and .NET uses "byte" as well.

				OnIOWarning(new IOWarningEventArgs(Direction.Output, message));
			}
		}

		private int DropReceivedQueue()
		{
			int droppedCount;
			lock (this.receiveQueue) // Lock is required because "Queue<T>" is not synchronized.
			{
				droppedCount = this.receiveQueue.Count;
				this.receiveQueue.Clear();
			}

			return (droppedCount);
		}

		private void SocketReset()
		{
			SetStateSynchronizedAndNotify(SocketState.Closing);
			DisposeSocketAndThreads();
			SetStateSynchronizedAndNotify(SocketState.Opening);
			CreateAndStartSocketAndThreads();
			SetStateSynchronizedAndNotify(SocketState.Opened);
		}

		private void SocketError()
		{
			DisposeSocketAndThreads();
			SetStateSynchronizedAndNotify(SocketState.Error);
		}

		#endregion

		#region Event Raising
		//==========================================================================================
		// Event Raising
		//==========================================================================================

		/// <summary></summary>
		protected virtual void OnIOChanged(EventArgs<DateTime> e)
		{
			if (IsUndisposed && IsOpen) // Make sure to propagate event only if active. // Ensure to not propagate event during closing anymore.
				this.eventHelper.RaiseSync(IOChanged, this, e);
		}

		/// <summary></summary>
		protected virtual void OnIOControlChanged(EventArgs<DateTime> e)
		{
			UnusedEvent.PreventCompilerWarning(IOControlChanged, "See exception message below.");
			throw (new InvalidOperationException(MessageHelper.InvalidExecutionPreamble + "The event 'IOControlChanged' is not in use for UDP/IP sockets!" + Environment.NewLine + Environment.NewLine + MessageHelper.SubmitBug));
		}

		/// <summary></summary>
		protected virtual void OnIOWarning(IOWarningEventArgs e)
		{
			if (IsUndisposed && IsOpen) // Make sure to propagate event only if active. // Ensure to not propagate event during closing anymore.
				this.eventHelper.RaiseSync<IOWarningEventArgs>(IOWarning, this, e);
		}

		/// <summary></summary>
		protected virtual void OnIOError(IOErrorEventArgs e)
		{
			if (IsUndisposed && IsOpen) // Make sure to propagate event only if active. // Ensure to not propagate event during closing anymore.
				this.eventHelper.RaiseSync<IOErrorEventArgs>(IOError, this, e);
		}

		/// <summary></summary>
		[CallingContract(IsNeverMainThread = true, IsAlwaysSequential = true)]
		protected virtual void OnDataReceived(DataReceivedEventArgs e)
		{
			if (IsUndisposed && IsOpen) // Make sure to propagate event only if active.
				this.eventHelper.RaiseSync<DataReceivedEventArgs>(DataReceived, this, e);
		}

		/// <summary></summary>
		[CallingContract(IsNeverMainThread = true, IsAlwaysSequential = true)]
		protected virtual void OnDataSent(DataSentEventArgs e)
		{
			if (IsUndisposed && IsOpen) // Make sure to propagate event only if active.
				this.eventHelper.RaiseSync<DataSentEventArgs>(DataSent, this, e);
		}

		#endregion

		#region Object Members
		//==========================================================================================
		// Object Members
		//==========================================================================================

		/// <summary>
		/// Converts the value of this instance to its equivalent string representation.
		/// </summary>
		public override string ToString()
		{
			// AssertUndisposed() shall not be called from such basic method! Its return value may be needed for debugging. All underlying fields are still valid after disposal.

			return (ToShortEndPointString());
		}

		/// <summary></summary>
		/// <remarks>
		/// Named according to .NET <see cref="System.Net.IPEndPoint"/>.
		/// </remarks>
		[SuppressMessage("Microsoft.Naming", "CA1702:CompoundWordsShouldBeCasedCorrectly", MessageId = "EndPoint", Justification = "Naming according to System.Net.EndPoint.")]
		public virtual string ToShortEndPointString()
		{
			// AssertUndisposed() shall not be called from such basic method! Its return value is needed for debugging! All underlying fields are still valid after disposal.

			switch (SocketType)
			{
				case UdpSocketType.Server:
					return ("Receive:" + LocalPort + " / " + RemoteHostEndpointString + ":" + RemotePort);

				case UdpSocketType.Client:
				case UdpSocketType.PairSocket:
					return (RemoteHostEndpointString + ":" + RemotePort + " / " + "Receive:" + LocalPort);

				case UdpSocketType.Unknown:
				default:
					return ("Unknown");
			}
		}

		#endregion

		#region Debug
		//==========================================================================================
		// Debug
		//==========================================================================================

		/// <remarks>
		/// Name "DebugWriteLine" would show relation to <see cref="Debug.WriteLine(string)"/>.
		/// However, named "Message" for compactness and more clarity that something will happen
		/// with the formatted message, and rather than e.g. "Common" for comprehensibility.
		/// </remarks>
		[Conditional("DEBUG")]
		protected void DebugMessage(string format, params object[] args)
		{
			DebugMessage(string.Format(CultureInfo.CurrentCulture, format, args));
		}

		/// <remarks>
		/// Name "DebugWriteLine" would show relation to <see cref="Debug.WriteLine(string)"/>.
		/// However, named "Message" for compactness and more clarity that something will happen
		/// with <paramref name="message"/>, and rather than e.g. "Common" for comprehensibility.
		/// </remarks>
		[Conditional("DEBUG")]
		protected virtual void DebugMessage(string message)
		{
			Debug.WriteLine
			(
				string.Format
				(
					CultureInfo.CurrentCulture,
					" @ {0} @ Thread #{1} : {2,36} {3,3} {4,-38} : {5}",
					DateTime.Now.ToString("HH:mm:ss.fff", DateTimeFormatInfo.CurrentInfo),
					Thread.CurrentThread.ManagedThreadId.ToString("D3", CultureInfo.CurrentCulture),
					GetType(),
					"#" + this.instanceId.ToString("D2", CultureInfo.CurrentCulture),
					"[" + ToShortEndPointString() + "]",
					message
				)
			);
		}

		/// <remarks>
		/// <c>private</c> because value of <see cref="ConditionalAttribute"/> is limited to file scope.
		/// </remarks>
		[Conditional("DEBUG_STATE")]
		private void DebugState(string format, params object[] args)
		{
			DebugMessage(format, args);
		}

		/// <remarks>
		/// <c>private</c> because value of <see cref="ConditionalAttribute"/> is limited to file scope.
		/// </remarks>
		[Conditional("DEBUG_THREADS")]
		private void DebugThreads(string message)
		{
			DebugMessage(message);
		}

		#endregion
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.IO.Serial.Socket/UdpSocket.cs $
//==================================================================================================
