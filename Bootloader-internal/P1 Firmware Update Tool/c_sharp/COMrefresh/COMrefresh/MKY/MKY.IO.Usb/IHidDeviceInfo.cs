//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.IO.Usb/IHidDeviceInfo.cs $
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
	/// Information about a USB HID device.
	/// </summary>
	public interface IHidDeviceInfo
	{
		/// <summary></summary>
		int UsagePage { get; }

		/// <summary></summary>
		string UsagePageString { get; }

		/// <summary></summary>
		int UsageId { get; }

		/// <summary></summary>
		string UsageIdString { get; }

		/// <summary></summary>
		string ToString();

		/// <summary></summary>
		string ToString(bool insertVidPid);

		/// <summary></summary>
		string ToString(bool insertVidPid, bool appendUsage);

		/// <summary></summary>
		string ToShortString();

		/// <summary></summary>
		string ToLongString();
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.IO.Usb/IHidDeviceInfo.cs $
//==================================================================================================
