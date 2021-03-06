//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/EventArgs.cs $
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

namespace MKY
{
	/// <summary>
	/// Generic event args with a (simple) type.
	/// </summary>
	/// <remarks>
	/// \remind (2017-07-23 / MKY)
	/// Attention, do not use this generic type with WinForms controls and forms up to at least
	/// VS2015 as its designer cannot cope with generic event args! Findings:
	///  > Designer cannot display the 'SendCommandRequest' of 'SendText' as well as 'Send'.
	///  > It crashes again and again! But is this indeed the root cause?
	///
	/// \todo
	/// Check again with VS2017+. If OK, revert 'YAT.View.Controls.SendTextOptionEventArgs'.
	/// </remarks>
	/// <typeparam name="T">(Simple) type of the event args.</typeparam>
	public class EventArgs<T> : EventArgs
	{
		/// <summary></summary>
		public T Value { get; }

		/// <summary></summary>
		public EventArgs(T value)
		{
			Value = value;
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/EventArgs.cs $
//==================================================================================================
