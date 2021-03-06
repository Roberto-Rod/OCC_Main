//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.View.Forms/AutoActionPlotHelp.cs $
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

using System;
using System.Windows.Forms;

using MKY.Windows.Forms;

namespace YAT.View.Forms
{
	/// <summary></summary>
	public partial class AutoActionPlotHelp : Form
	{
		/// <summary></summary>
		public AutoActionPlotHelp()
		{
			InitializeComponent();

			InitializeRemark();
		}

		private void InitializeRemark()
		{
			linkLabel_Remark.Text = "";
			var textBefore = ApplicationEx.CommonName + " uses "; // Fixed to "YAT".
			var textLink   =                                  "OxyPlot";
			var textAfter  =                                         " default interactions, except for [Pan → Left Mouse Button] and [Menu → Right Mouse Button].";
			linkLabel_Remark.Text += textBefore;
			var linkStart = linkLabel_Remark.Text.Length;
			linkLabel_Remark.Text += textLink;
			linkLabel_Remark.Links.Add(linkStart, textLink.Length, "https://oxyplot.github.io/");
			linkLabel_Remark.Text += textAfter;
		}

		private void AutoActionPlotHelp_Load(object sender, EventArgs e)
		{
			// By default, the first cell is selected when the data grid is shown. The trick by Ravi
			// at http://manfred-ramoser.blogspot.com/2008/01/hide-selection-in-datagridview.html
			// deselects properly. Attention, must be here, not in the constructor!

			dataGridView_ByFunction.ClearSelection();
			dataGridView_ByInput.ClearSelection();
		}

		private void linkLabel_Remark_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
		{
			LinkHelper.TryBrowseUriAndShowErrorIfItFails(Parent, e);
		}

		private void button_Close_Click(object sender, EventArgs e)
		{
			DialogResult = DialogResult.OK;
			Close();
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.View.Forms/AutoActionPlotHelp.cs $
//==================================================================================================
