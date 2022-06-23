//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/Settings/EventArgs.cs $
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
// Copyright © 2003-2004 HSR Hochschule für Technik Rapperswil.
// Copyright © 2003-2021 Matthias Kläy.
// All rights reserved.
// ------------------------------------------------------------------------------------------------
// This source code is licensed under the GNU LGPL.
// See http://www.gnu.org/licenses/lgpl.html for license details.
//==================================================================================================

using System;

namespace MKY.Settings
{
	/// <summary></summary>
	public class SettingsEventArgs : EventArgs
	{
		/// <summary></summary>
		public SettingsItem Source { get; }

		/// <summary></summary>
		public SettingsEventArgs Inner { get; }

		/// <summary></summary>
		public SettingsEventArgs(SettingsItem source)
		{
			Source = source;
		}

		/// <summary></summary>
		public SettingsEventArgs(SettingsItem source, SettingsEventArgs inner)
		{
			Source = source;
			Inner = inner;
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/Settings/EventArgs.cs $
//==================================================================================================
