//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.IO.Serial.Socket/EventArgs.cs $
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

using System.Net;

namespace MKY.IO.Serial.Socket
{
	/// <summary></summary>
	public class SocketDataSentEventArgs : DataSentEventArgs
	{
		private IPEndPoint remoteEndPoint;

		/// <summary></summary>
		public SocketDataSentEventArgs(byte data, IPEndPoint remoteEndPoint)
			: this(new byte[] { data }, remoteEndPoint)
		{
		}

		/// <summary></summary>
		public SocketDataSentEventArgs(byte[] data, IPEndPoint remoteEndPoint)
			: base(data)
		{
			this.remoteEndPoint = remoteEndPoint;
		}

		/// <summary></summary>
		public override string Device
		{
			get { return (this.remoteEndPoint.ToString()); }
		}
	}

	/// <summary></summary>
	public class SocketDataReceivedEventArgs : DataReceivedEventArgs
	{
		private IPEndPoint remoteEndPoint;

		/// <summary></summary>
		public SocketDataReceivedEventArgs(byte data, IPEndPoint remoteEndPoint)
			: this(new byte[] { data }, remoteEndPoint)
		{
		}

		/// <summary></summary>
		public SocketDataReceivedEventArgs(byte[] data, IPEndPoint remoteEndPoint)
			: base(data)
		{
			this.remoteEndPoint = remoteEndPoint;
		}

		/// <summary></summary>
		public override string Device
		{
			get { return (this.remoteEndPoint.ToString()); }
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.IO.Serial.Socket/EventArgs.cs $
//==================================================================================================
