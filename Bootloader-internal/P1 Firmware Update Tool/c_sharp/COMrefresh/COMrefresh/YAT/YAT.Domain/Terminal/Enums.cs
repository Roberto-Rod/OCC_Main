//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Domain/Terminal/Enums.cs $
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

using System.Diagnostics.CodeAnalysis;

// The YAT.Domain namespace contains all raw/neutral/binary/text terminal infrastructure. This code
// is intentionally placed into the YAT.Domain namespace even though the file is located in
// YAT.Domain\Terminal for better separation of the implementation files.
namespace YAT.Domain
{
	// Disable warning 1591 "Missing XML comment for publicly visible type or member" to avoid
	// warnings for each undocumented member below. Documenting each member makes little sense
	// since they pretty much tell their purpose and documentation tags between the members
	// makes the code less readable.
	#pragma warning disable 1591

	/// <summary></summary>
	public enum RepositoryType
	{
		None,

		Tx,
		Bidir,
		Rx
	}

	/// <summary></summary>
	public enum SendMode
	{
		Text,
		File
	}

	/// <summary></summary>
	public enum LinePosition
	{
		/// <remarks>
		/// Also applies if the next line has not been started yet, i.e. 'LinePosition.None'.
		/// </remarks>
		Begin,
		Content,
		End
	}

	/// <summary></summary>
	public enum PostponeResult
	{
		Nothing,
		PartOfChunk,
		CompleteChunk
	}

	#pragma warning restore 1591
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Domain/Terminal/Enums.cs $
//==================================================================================================
