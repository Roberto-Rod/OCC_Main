//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.IO.Serial.Socket/UdpSocket.Send.cs $
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

	// Enable debugging of sending:
////#define DEBUG_SEND

#endif // DEBUG

#endregion

#region Using
//==================================================================================================
// Using
//==================================================================================================

using System;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
//// "System.Net" as well as "ALAZ.SystemEx.NetEx" are explicitly used for more obvious distinction.
//// "System.Net.Sockets" as well.
using System.Text;
using System.Threading;

using MKY.Diagnostics;

#endregion

namespace MKY.IO.Serial.Socket
{
	/// <remarks>
	/// This partial class implements the send part of <see cref="UdpSocket"/>.
	/// </remarks>
	public partial class UdpSocket
	{
		#region Public Methods
		//==========================================================================================
		// Public Methods
		//==========================================================================================

		/// <remarks>
		/// If the underlying buffer has space, this method will immediately return; otherwise
		/// this method will be blocking until there is space, or the I/O instance is stopped
		/// or gets disconnected/closed.
		/// </remarks>
		public virtual bool Send(byte[] data)
		{
			// Attention:
			// Same code exists in [SerialPort|TcpClient|UdpSocket|SerialHidDevice].Send().
			// Changes here will have to be applied there too.
			//
			// Notes:
			// Implemented seperately rather than...
			// ...a 'SendBase' for more obviousness and compactness.
			// ...in YAT's 'RawTerminal' to make this class usable without YAT.

		////AssertUndisposed() is called by 'IsTransmissive' below.

			if (IsTransmissive)
			{
				var initialTimeStamp = DateTime.Now;

				for (int i = 0; i < data.Length; i++)
				{
					// Wait until there is space in the send queue:
					while (this.sendQueue.Count >= SendQueueFixedCapacity) // No lock required, just checking for full.
					{
						var isInDisposal = IsInDisposal;
						if (isInDisposal || !IsTransmissive) // Check disposal state first!
						{
							if (!isInDisposal)
							{
								string message;
								var droppedCount = (data.Length - i);
								if (droppedCount <= 1)
									message = droppedCount + " byte not enqueued for sending anymore.";  // Using "byte" rather than "octet" as that is more common, and .NET uses "byte" as well.
								else                                                                     // Reason cannot be stated, could be "disconnected" or "stopped/closed"
									message = droppedCount + " bytes not enqueued for sending anymore."; // Using "byte" rather than "octet" as that is more common, and .NET uses "byte" as well.

								OnIOWarning(new IOWarningEventArgs(Direction.Output, message));
							}

							return (false);
						}

						// Signal to ensure send thread keeps working:
						SignalSendThreadSafely();

						// Actively yield to other threads to allow dequeuing:
						var span = (DateTime.Now - initialTimeStamp);
						if (span.TotalMilliseconds < 4)
							Thread.Sleep(TimeSpan.Zero); // "TimeSpan.Zero" = 100% CPU is OK as send
						else                             // a) is expected to potentially be blocking and
							Thread.Sleep(1);             // b) is short (max. 4 ms) yet.
					}                                    // But sleep if longer!

					// There is space for at least one byte:
					var b = data[i];
					lock (this.sendQueue) // Lock is required because "Queue<T>" is not synchronized.
					{
						this.sendQueue.Enqueue(b);
					}
					DebugSendEnqueue(ConvertEx.ToHexString(b));

					// Do not signal after each byte, this is a) not efficient and b) not desired
					// as send requests shall ideally be sent as a single chunk.
				}

				// Signal thread to send the requested packet:
				SignalSendThreadSafely();

				return (true);
			}
			else
			{
				return (false);
			}
		}

		/// <summary>
		/// Clears the send buffer(s) immediately.
		/// </summary>
		public virtual int ClearSendBuffer()
		{
			AssertUndisposed();

			return (DropSendQueueAndNotify());
		}

		#endregion

		#region Non-Public Methods
		//==========================================================================================
		// Non-Public Methods
		//==========================================================================================

		/// <summary>
		/// Asynchronously manage outgoing send requests to ensure that send events are not
		/// invoked on the same thread that triggered the send operation.
		/// Also, the mechanism implemented below reduces the amount of events that are propagated
		/// to the main application. Small chunks of sent data would generate many events in
		/// <see cref="Send(byte[])"/>. However, since <see cref="OnDataSent"/> synchronously
		/// invokes the event, it will take some time until the send queue is checked again.
		/// During this time, no more new events are invoked, instead, outgoing data is buffered.
		/// </summary>
		/// <remarks>
		/// Will be signaled by <see cref="Send(byte[])"/> method above.
		/// </remarks>
		[SuppressMessage("Microsoft.Portability", "CA1903:UseOnlyApiFromTargetedFramework", Justification = "Project does target .NET 4 but FxCop cannot handle that, project must be upgraded to Visual Studio Code Analysis (FR #231).")]
		private void SendThread()
		{
			DebugThreads("...SendThread() has started.");

			// Based on experiments:
			//
			// 65507 bytes is the maximum 'dgram' that can be handled by the Send() method further below in case of IPv4.
			//  > Anything larger than that results in WSAEMSGSIZE 10040 "Message too long."
			//  > https://docs.microsoft.com/en-us/windows/win32/winsock/windows-sockets-error-codes-2
			//
			// Based on https://stackoverflow.com/questions/1098897/what-is-the-largest-safe-udp-packet-size-on-the-internet:
			//
			// 508 bytes is the maximum safe payload for IPv4 as well as IPv6.
			// 1212 bytes is the maximum safe payload for IPv6-only routes.
			//  > Using these. If this ever becomes an issue, it will have to be configured.

			const int SafePayloadLengthOnIPv4 = 508;
			const int SafePayloadLengthOnIPv6 = 1212;

			int maxChunkLength;
			switch (this.localInterface.Address.AddressFamily)
			{
				case System.Net.Sockets.AddressFamily.InterNetwork:   maxChunkLength = SafePayloadLengthOnIPv4; break;
				case System.Net.Sockets.AddressFamily.InterNetworkV6: maxChunkLength = SafePayloadLengthOnIPv6; break;

				default: throw (new NotSupportedException(MessageHelper.InvalidExecutionPreamble + "'" + this.localInterface.Address.AddressFamily.ToString() + "' is not (yet) supported here!" + Environment.NewLine + Environment.NewLine + MessageHelper.SubmitBug));
			}

			try
			{
				// Outer loop, runs when signaled as well as periodically checking the state:
				while (IsUndisposed && this.sendThreadRunFlag) // Check disposal state first!
				{
					// A signal will only be received a while after initialization, thus waiting for
					// signal first. Also, placing this code first in the outer loop makes the logic
					// of the two loops more obvious.
					try
					{
						// WaitOne() would wait forever if the underlying I/O provider has crashed, or
						// if the overlying client isn't able or forgets to call Stop() or Dispose().
						// Therefore, only wait for a certain period and then poll the state again.
						// The period can be quite long, as an event signal will immediately resume.
						if (!this.sendThreadEvent.WaitOne(SocketBase.Random.Next(50, 200)))
							continue; // to periodically check state.
					}
					catch (AbandonedMutexException ex)
					{
						// The mutex should never be abandoned, but in case it nevertheless happens,
						// at least output a debug message and gracefully exit the thread.
						DebugEx.WriteException(GetType(), ex, "An 'AbandonedMutexException' occurred in SendThread()!");
						break;
					}

					// Inner loop, runs as long as there are items in the queue:
					while (IsUndisposed && this.sendThreadRunFlag && IsTransmissive && (this.sendQueue.Count > 0)) // Check disposal state first!
					{                                                               // No lock required, just checking for empty.
						// Initially, yield to other threads before starting to read the queue, since it is very
						// likely that more data is to be enqueued, thus resulting in larger chunks processed.
						// Subsequently, yield to other threads to allow processing the data.
						Thread.Sleep(TimeSpan.Zero); // "TimeSpan.Zero" = 100% CPU is OK as sending shall happen as fast as possible.

						// Synchronize the send/receive events to prevent mix-ups at the event
						// sinks, i.e. the send/receive operations shall be synchronized with
						// signaling of them.
						// But attention, do not simply lock() the sync obj. Instead, just try
						// to get the lock or try again later. The thread = direction that get's
						// the lock first, shall also be the one to signal first:

						if (Monitor.TryEnter(this.dataEventSyncObj, 10)) // Allow a short time to enter, as receiving
						{                                                // could be busy mostly locking the object.
							try
							{
								byte[] data;
								lock (this.sendQueue) // Lock is required because "Queue<T>" is not synchronized.
								{
									if (this.sendQueue.Count <= maxChunkLength) // Easy case, simply retrieve whole queue:
									{
										data = this.sendQueue.ToArray();
										this.sendQueue.Clear();
									}
									else // Chunking is needed:
									{
										data = new byte[maxChunkLength];
										for (int i = 0; i < maxChunkLength; i++)
											data[i] = this.sendQueue.Dequeue();
									}
								}

								// This approach should be good enough for the Send() method below,
								// further processing will be done synchronously, so there is no need
								// for using BeginSend() from this already asynchronous thread.

								DebugSendDequeue(data.Length);

								System.Net.IPEndPoint remoteEndPoint;
								lock (this.socketSyncObj)
									remoteEndPoint = new System.Net.IPEndPoint(this.remoteHost, this.remotePort);

								this.socket.Send(data, data.Length, remoteEndPoint);

								OnDataSent(new SocketDataSentEventArgs(data, remoteEndPoint));
							}
							catch (System.Net.Sockets.SocketException ex)
							{
								if (ex.SocketErrorCode == System.Net.Sockets.SocketError.ConnectionReset)
								{
									SocketReset(); // Required after this exception.
									OnIOError(new IOErrorEventArgs(ErrorSeverity.Acceptable, Direction.Output, ex.Message));
								}                                             // Acceptable as situation may recover.
								else
								{
								////SocketReset() shall not be done in case sending fails (yet). Additional cases to be added here.
									OnIOError(new IOErrorEventArgs(ErrorSeverity.Severe, Direction.Output, ex.Message));
								}
							}
							finally
							{
								Monitor.Exit(this.dataEventSyncObj);
							}
						}
					////else // Monitor.TryEnter()
					////{
					////	DebugMessage("SendThread() monitor has timed out, trying again...");
					////}

						// Note the Thread.Sleep(TimeSpan.Zero) further above.

						if (this.socketType == UdpSocketType.Client)
						{
							// Get the currently used local port:

							bool hasChanged = false;

							lock (this.socketSyncObj)
							{
								var localEndPoint = (System.Net.IPEndPoint)this.socket.Client.LocalEndPoint;
								if (this.localPort != localEndPoint.Port) {
									this.localPort = localEndPoint.Port;
									hasChanged = true;
								}
							}

							if (hasChanged) {
								OnIOChanged(new EventArgs<DateTime>(DateTime.Now));
							}
						} // Client
					} // Inner loop
				} // Outer loop
			}
			catch (ThreadAbortException ex)
			{
				DebugEx.WriteException(GetType(), ex, "SendThread() has been aborted! Confirming the abort, i.e. Thread.ResetAbort() will be called...");

				// Should only happen when failing to 'friendly' join the thread on stopping!
				// Don't try to set and notify a state change, or even restart the socket!

				// But reset the abort request, as 'ThreadAbortException' is a special exception
				// that would be rethrown at the end of the catch block otherwise!

				Thread.ResetAbort();
			}

			DebugThreads("SendThread() has terminated.");
		}

		#endregion

		#region Debug
		//==========================================================================================
		// Debug
		//==========================================================================================

	#if (DEBUG_SEND)
		private int DebugSend_enqueueCounter; // = 0;
		private int DebugSend_dequeueCounter; // = 0;
	#endif

		/// <remarks>
		/// <c>private</c> because value of <see cref="ConditionalAttribute"/> is limited to file scope.
		/// </remarks>
		[Conditional("DEBUG_SEND")]
		private void DebugSendEnqueue(string byteAsHex)
		{
			var sb = new StringBuilder(byteAsHex + " enqueued for sending, ");
		#if (DEBUG_SEND)
			unchecked { DebugSend_enqueueCounter++; }
			sb.AppendFormat(CultureInfo.CurrentCulture, "{0} byte(s) in total.", DebugSend_enqueueCounter);
		#endif
			DebugMessage(sb.ToString());
		}

		/// <remarks>
		/// <c>private</c> because value of <see cref="ConditionalAttribute"/> is limited to file scope.
		/// </remarks>
		[Conditional("DEBUG_SEND")]
		private void DebugSendDequeue(int count)
		{
			var sb = new StringBuilder();
			sb.AppendFormat(CultureInfo.CurrentCulture, "{0} byte(s) dequeued for sending, ", count);
		#if (DEBUG_SEND)
			unchecked { DebugSend_dequeueCounter += count; }
			sb.AppendFormat(CultureInfo.CurrentCulture, "{0} byte(s) in total.", DebugSend_dequeueCounter);
		#endif
			DebugMessage(sb.ToString());
		}

		#endregion
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.IO.Serial.Socket/UdpSocket.Send.cs $
//==================================================================================================
