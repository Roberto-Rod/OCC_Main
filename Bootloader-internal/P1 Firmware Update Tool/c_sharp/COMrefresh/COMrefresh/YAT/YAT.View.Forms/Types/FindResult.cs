//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.View.Forms/Types/FindResult.cs $
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

// This code is intentionally placed into the YAT.View.Forms namespace even though the file is
// located in YAT.View.Forms.Types for same location as parent control.
namespace YAT.View.Forms
{
	/// <summary>
	/// The result of a find operation.
	/// </summary>
	public enum FindResult
	{
		/// <summary>Find has not been triggered yet, or find has been reset.</summary>
		Reset,

		/// <summary>Pattern is empty.</summary>
		Empty,

		/// <summary>Pattern has been found.</summary>
		Found,

		/// <summary>Pattern has not been found anymore.</summary>
		NotFoundAnymore,

		/// <summary>Pattern has not been found at all.</summary>
		NotFoundAtAll,

		/// <summary>Pattern is invalid.</summary>
		Invalid
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.View.Forms/Types/FindResult.cs $
//==================================================================================================
