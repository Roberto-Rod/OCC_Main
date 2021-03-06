//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.IO.Serial.SerialPort/EventArgs.cs $
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

using MKY.IO.Ports;

namespace MKY.IO.Serial.SerialPort
{
	/// <summary></summary>
	public class SerialDataReceivedEventArgs : DataReceivedEventArgs
	{
		private SerialPortId portId;

		/// <summary></summary>
		public SerialDataReceivedEventArgs(byte data, SerialPortId portId)
			: this(new byte[] { data }, portId)
		{
		}

		/// <summary></summary>
		public SerialDataReceivedEventArgs(byte[] data, SerialPortId portId)
			: base(data)
		{
			this.portId = portId;
		}

		/// <summary></summary>
		public override string Device
		{
			get { return (this.portId.Name); }
		}
	}

	/// <summary></summary>
	public class SerialDataSentEventArgs : DataSentEventArgs
	{
		private SerialPortId portId;

		/// <summary></summary>
		public SerialDataSentEventArgs(byte data, SerialPortId portId)
			: this(new byte[] { data }, portId)
		{
		}

		/// <summary></summary>
		public SerialDataSentEventArgs(byte[] data, SerialPortId portId)
			: base(data)
		{
			this.portId = portId;
		}

		/// <summary></summary>
		public override string Device
		{
			get { return (this.portId.Name); }
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.IO.Serial.SerialPort/EventArgs.cs $
//==================================================================================================
