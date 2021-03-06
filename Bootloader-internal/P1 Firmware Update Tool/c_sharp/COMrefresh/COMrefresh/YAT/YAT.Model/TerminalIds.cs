//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Model/TerminalIds.cs $
// $Revision: 3786 $
// $Date: 2021-04-20 16:33:31 +0000 (Tue, 20 Apr 2021) $
// $Author: maettu_this $
// ------------------------------------------------------------------------------------------------
// YAT Version 2.4.1
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

namespace YAT.Model
{
	/// <summary></summary>
	public static class TerminalIds
	{
		/// <remarks>
		/// "Normal" indices are 0 based.
		/// </remarks>
		public const int FirstIndex = 0;

		/// <remarks>
		/// "Normal" indices are 0 based.
		/// Index -1 means "invalid".
		/// </remarks>
		public const int InvalidIndex = -1;

		/// <remarks>
		/// IDs are 1 (not 0) based for consistency with "Terminal1"...
		/// </remarks>
		public const int FirstDynamicId = 1;

		/// <remarks>
		/// IDs are 1 (not 0) based for consistency with "Terminal1"...
		/// ID 0 refers to the active terminal, i.e. the 'default' terminal.
		/// </remarks>
		public const int ActiveDynamicId = 0;

		/// <remarks>
		/// IDs are 1 (not 0) based for consistency with "Terminal1"...
		/// ID -1 means 'invalid', i.e. no terminal.
		/// </remarks>
		public const int InvalidDynamicId = -1;

		/// <remarks>
		/// IDs are 1 (not 0) based for consistency with "Terminal1"...
		/// </remarks>
		public const int FirstSequentialId = 1;

		/// <remarks>
		/// IDs are 1 (not 0) based for consistency with "Terminal1"...
		/// ID 0 refers to the active terminal, i.e. the 'default' terminal.
		/// </remarks>
		public const int ActiveSequentialId = 0;

		/// <remarks>
		/// IDs are 1 (not 0) based for consistency with "Terminal1"...
		/// ID -1 means 'invalid', i.e. no terminal.
		/// </remarks>
		public const int InvalidSequentialId = -1;

		/// <remarks>
		/// IDs are 1 (not 0) based for consistency with "Terminal1"...
		/// </remarks>
		public const int FirstFixedId = Settings.TerminalSettingsItem.FirstFixedId;

		/// <remarks>
		/// IDs are 1 (not 0) based for consistency with "Terminal1"...
		/// ID 0 refers to the active terminal, i.e. the 'default' terminal.
		/// </remarks>
		public const int ActiveFixedId = Settings.TerminalSettingsItem.ActiveFixedId;

		/// <remarks>
		/// IDs are 1 (not 0) based for consistency with "Terminal1"...
		/// ID -1 means 'invalid', i.e. no terminal.
		/// </remarks>
		public const int InvalidFixedId = Settings.TerminalSettingsItem.InvalidFixedId;

		/// <summary>
		/// Returns the dynamic ID of the given index.
		/// </summary>
		public static int IndexToDynamicId(int index)
		{
			if (index >= FirstIndex)
				return (FirstDynamicId + (index - FirstIndex));
			else
				return (InvalidDynamicId);
		}

		/// <summary>
		/// Returns the index of the given dynamic ID.
		/// </summary>
		public static int DynamicIdToIndex(int dynamicId)
		{
			if (dynamicId >= FirstDynamicId)
				return (FirstIndex + (dynamicId - FirstDynamicId));
			else
				return (InvalidIndex);
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Model/TerminalIds.cs $
//==================================================================================================
