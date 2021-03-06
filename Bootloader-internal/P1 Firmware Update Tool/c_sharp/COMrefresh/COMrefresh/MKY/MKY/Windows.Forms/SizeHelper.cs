//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/Windows.Forms/SizeHelper.cs $
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

using System.Drawing;

namespace MKY.Windows.Forms
{
	/// <summary>
	/// Helper for handling changed DPI settings.
	/// </summary>
	/// <remarks>
	/// Based on https://www.codeproject.com/Tips/786170/Proper-Resizing-of-SplitterContainer-Controls-at-a.
	/// </remarks>
	public class SizeHelper
	{
		/// <summary>
		/// Gets or sets the current scale.
		/// </summary>
		public virtual SizeF Scale { get; set; } = new SizeF(1.0f, 1.0f);

		/// <summary>
		/// Adjusts the scale by the given factor.
		/// </summary>
		public virtual void AdjustScale(SizeF factor)
		{
			Scale = new SizeF(Scale.Width * factor.Width, Scale.Height * factor.Height);
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/Windows.Forms/SizeHelper.cs $
//==================================================================================================
