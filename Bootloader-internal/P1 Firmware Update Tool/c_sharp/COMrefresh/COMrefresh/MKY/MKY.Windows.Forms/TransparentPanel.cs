//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.Windows.Forms/TransparentPanel.cs $
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
using System.Windows.Forms;

namespace MKY.Windows.Forms
{
	/// <summary>
	/// Provides a transparent panel. It can be used to handle user input on an invisible rectangle.
	/// </summary>
	public class TransparentPanel : Panel
	{
		/// <summary>
		/// Gets the required creation parameters when the control handle is created.
		/// </summary>
		[Browsable(false)]
		protected override CreateParams CreateParams
		{
			get
			{
				CreateParams cp = base.CreateParams;
				cp.ExStyle |= 0x20; // 0x20 = WS_EX_TRANSPARENT = one of the 'Extended Window Styles' of the Win32 API.
				return (cp);
			}
		}

		/// <summary>
		/// Paints the background of the control.
		/// </summary>
		/// <param name="e">A <see cref="PaintEventArgs"/> that contains the event data.</param>
		protected override void OnPaintBackground(PaintEventArgs e)
		{
			// Do nothing to leave the background invisible, i.e. leave the control transparent.
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.Windows.Forms/TransparentPanel.cs $
//==================================================================================================
