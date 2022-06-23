//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Test/DummyMain.cs $
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
// Copyright © 2007-2021 Matthias Kläy.
// All rights reserved.
// ------------------------------------------------------------------------------------------------
// This source code is licensed under the GNU LGPL.
// See http://www.gnu.org/licenses/lgpl.html for license details.
//==================================================================================================

using System;
using System.Text;
using System.Windows.Forms;

using MKY.Windows.Forms;

namespace YAT.Test
{
	/// <summary>
	/// This is a dummy main for the YAT test projects.
	/// </summary>
	/// <remarks>
	/// See "!-ReadMe.txt" for more information.
	/// </remarks>
	public static class DummyMain
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		private static void Main()
		{
			var sb = new StringBuilder();
			sb.AppendLine(@"Note that this console application is only a dummy for testing purposes. Use """ + ApplicationEx.ProductName + @""" instead.");
			sb.AppendLine();
			sb.Append    (@"See ""!-ReadMe.txt"" for more information.");

			MessageBoxEx.Show(sb.ToString(), "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Test/DummyMain.cs $
//==================================================================================================
