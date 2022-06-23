//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.IO.Usb/HidReports.cs $
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
// Copyright © 2010-2021 Matthias Kläy.
// All rights reserved.
// ------------------------------------------------------------------------------------------------
// This source code is licensed under the GNU LGPL.
// See http://www.gnu.org/licenses/lgpl.html for license details.
//==================================================================================================

namespace MKY.IO.Usb
{
	/// <summary>
	/// Abstract base for all HID report containers.
	/// </summary>
	public abstract class HidReportContainer
	{
		/// <summary>
		/// The device associated with this report.
		/// </summary>
		protected HidDevice Device { get; }

		/// <summary>
		/// The maximum byte length of a report. The length is given by the device capabilities.
		/// </summary>
		public int MaxByteLength { get; }

		/// <summary>
		/// Creates a report container and stores the reference to the device in use as well as
		/// the maximum length of a report.
		/// </summary>
		protected HidReportContainer(HidDevice device, int maxLength)
		{
			Device        = device;
			MaxByteLength = maxLength;
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.IO.Usb/HidReports.cs $
//==================================================================================================
