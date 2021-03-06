//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.Windows.Forms.Test/TextInputTest.cs $
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

using System;
using System.Windows.Forms;

namespace MKY.Windows.Forms.Test
{
	/// <summary>
	/// Test form for <see cref="TextBoxEx"/> and <see cref="ComboBoxEx"/>.
	/// </summary>
	public partial class TextInputTest : Form
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="TextInputTest"/> class which
		/// tests variants of the standard text input controls.
		/// </summary>
		public TextInputTest()
		{
			InitializeComponent();
		}

		private void TextInputTest_Deactivate(object sender, EventArgs e)
		{
		////comboBox is a standard ComboBox.
			comboBoxEx.OnFormDeactivateWorkaround();
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.Windows.Forms.Test/TextInputTest.cs $
//==================================================================================================
