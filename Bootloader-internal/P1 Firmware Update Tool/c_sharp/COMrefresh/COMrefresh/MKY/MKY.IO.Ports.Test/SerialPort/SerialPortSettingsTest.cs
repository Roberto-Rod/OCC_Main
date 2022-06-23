//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.IO.Ports.Test/SerialPort/SerialPortSettingsTest.cs $
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

using NUnit.Framework;

namespace MKY.IO.Ports.Test.SerialPort
{
	/// <summary></summary>
	[TestFixture]
	public class SerialPortSettingsTest
	{
		#region Tests
		//==========================================================================================
		// Tests
		//==========================================================================================

		#region Tests > Serialization()
		//------------------------------------------------------------------------------------------
		// Tests > Serialization()
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestSerialization()
		{
			// \fixme:
			// Improve SerialPortSettings and XBaudRate such that they can handle user defined baud rates.
			// Then, add a test case that verifies that user defined baud rates are properly handled.
		}

		#endregion

		#endregion
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.IO.Ports.Test/SerialPort/SerialPortSettingsTest.cs $
//==================================================================================================
