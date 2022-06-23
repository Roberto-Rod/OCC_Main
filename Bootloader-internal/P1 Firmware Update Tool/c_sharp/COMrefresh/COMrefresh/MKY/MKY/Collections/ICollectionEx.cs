//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/Collections/ICollectionEx.cs $
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

using System.Collections;
using System.Diagnostics.CodeAnalysis;

// This code is intentionally placed into the MKY namespace even though the file is located in
// MKY.Types for consistency with the System namespace.
namespace MKY.Collections
{
	/// <summary>
	/// <see cref="ICollection"/> utility methods.
	/// </summary>
	[SuppressMessage("Microsoft.Naming", "CA1711:IdentifiersShouldNotHaveIncorrectSuffix", Justification = "'Ex' emphasizes that it's an extension to an existing class and not a replacement as '2' would emphasize.")]
	public static class ICollectionEx
	{
		/// <summary>
		/// Indicates whether the specified collection is <c>null</c> or empty.
		/// </summary>
		/// <param name="obj">The collection to test.</param>
		/// <remarks>
		/// Same syntax and semantic as <see cref="string.IsNullOrEmpty(string)"/>.
		/// </remarks>
		/// <returns>
		/// <c>true</c> if the collection is <c>null</c> or empty; otherwise, <c>false</c>.
		/// </returns>
		public static bool IsNullOrEmpty(ICollection obj)
		{
			return ((obj == null) || (obj.Count == 0));
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/Collections/ICollectionEx.cs $
//==================================================================================================
