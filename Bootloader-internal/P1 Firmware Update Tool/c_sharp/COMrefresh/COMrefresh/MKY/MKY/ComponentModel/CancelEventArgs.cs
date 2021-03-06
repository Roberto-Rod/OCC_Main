//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/ComponentModel/CancelEventArgs.cs $
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

using System.ComponentModel;

namespace MKY.ComponentModel
{
	/// <summary>
	/// Cancel event args with a string value.
	/// </summary>
	/// <remarks>
	/// \remind (2017-07-23 / MKY)
	/// This class could be implemented with a generic type argument instead of being fixed to
	/// <see cref="string"/>. However, the VS2015 designer cannot cope with generic event args!
	/// Findings:
	///  > Designer cannot display the 'SendCommandRequest' of 'SendText' as well as 'Send'.
	///  > It crashes again and again! But is this indeed the root cause?
	///
	/// \todo
	/// Check again with VS2017+.
	/// </remarks>
	public class StringCancelEventArgs : CancelEventArgs
	{
		/// <summary></summary>
		public string Value { get; }

		/// <summary></summary>
		public StringCancelEventArgs(string value)
		{
			Value = value;
		}

		/// <summary></summary>
		public StringCancelEventArgs(string value, bool cancel)
			: base(cancel)
		{
			Value = value;
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/ComponentModel/CancelEventArgs.cs $
//==================================================================================================
