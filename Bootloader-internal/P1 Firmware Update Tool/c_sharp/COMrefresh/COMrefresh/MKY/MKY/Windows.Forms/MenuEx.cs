//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/Windows.Forms/MenuEx.cs $
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

using System.Diagnostics.CodeAnalysis;
using System.Text;

namespace MKY.Windows.Forms
{
	/// <summary>
	/// System.Windows.Forms utility methods.
	/// </summary>
	/// <remarks>
	/// This class is intentionally not placed into <c>MKY.Windows.Forms</c> since it's a
	/// pure utility containing no visual contents.
	/// </remarks>
	[SuppressMessage("Microsoft.Naming", "CA1711:IdentifiersShouldNotHaveIncorrectSuffix", Justification = "'Ex' emphasizes that it's an extension to an existing class and not a replacement as '2' would emphasize.")]
	public static class MenuEx
	{
		/// <summary>
		/// Convert a menu index into a prependable string, e.g. "1: ".
		/// Indices will be accessible via ALT + numeric key.
		/// </summary>
		/// <remarks>
		/// Ampersand is used as mark.
		/// </remarks>
		[SuppressMessage("StyleCop.CSharp.DocumentationRules", "SA1650:ElementDocumentationMustBeSpelledCorrectly", Justification = "'Prependable' is a correct English term.")]
		public static string PrependIndex(int index, string text)
		{
			var sb = new StringBuilder();

			if ((index >= 0) && (index <= 9))
			{
				sb.Append("&");
				sb.Append(index);
			}
			else if (index <= 99)
			{
				var tenths = (index / 10);
				var oneths = (index % 10);
				if (oneths == 0)
				{
					sb.Append(tenths);
					sb.Append("&0"); // Mark zero digit (may result in duplicate marks (0/10/...)).
				}
				else
				{
					sb.Append("&"); // Mark first digit (resulting in duplicate marks).
					sb.Append(index);
				}
			}
			else // Very unlikely case, who wants 100 or more menu items...
			{
				sb.Append("&"); // Simply mark first digit (resulting in even more duplicate marks).
				sb.Append(index);
			}
			sb.Append(": ");
			sb.Append(text);

			return (sb.ToString());
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/Windows.Forms/MenuEx.cs $
//==================================================================================================
