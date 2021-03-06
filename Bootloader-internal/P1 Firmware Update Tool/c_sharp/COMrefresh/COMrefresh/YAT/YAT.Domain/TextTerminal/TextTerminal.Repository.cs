//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Domain/TextTerminal/TextTerminal.Repository.cs $
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

using MKY;

// The YAT.Domain namespace contains all raw/neutral/binary/text terminal infrastructure.
// This code is intentionally placed into the YAT.Domain namespace even though the file is
// located in YAT.Domain\TextTerminal for better separation of the implementation files.
namespace YAT.Domain
{
	/// <remarks>
	/// This partial class implements the repository part of <see cref="TextTerminal"/>.
	/// </remarks>
	public partial class TextTerminal
	{
		/// <summary>
		/// Implements the text terminal specific <see cref="Settings.TextTerminalSettings.GlueCharsOfLine"/> functionality.
		/// </summary>
		protected override void DoFinishReload(RepositoryType repositoryType)
		{
			switch (repositoryType)
			{
				case RepositoryType.Tx:                                /* Nothing to do. */                                    break;
				case RepositoryType.Bidir: ProcessAndSignalGlueCharsOfLineTimeoutOfRemainingPostponedChunksOnReloadIfNeeded(); break;
				case RepositoryType.Rx:                                /* Nothing to do. */                                    break;

				case RepositoryType.None:  throw (new ArgumentOutOfRangeException("repositoryType", repositoryType, MessageHelper.InvalidExecutionPreamble + "'" + repositoryType + "' is a repository type that is not valid here!" + Environment.NewLine + Environment.NewLine + MessageHelper.SubmitBug));
				default:                   throw (new ArgumentOutOfRangeException("repositoryType", repositoryType, MessageHelper.InvalidExecutionPreamble + "'" + repositoryType + "' is an invalid repository type!"               + Environment.NewLine + Environment.NewLine + MessageHelper.SubmitBug));
			}

			base.DoFinishReload(repositoryType);
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Domain/TextTerminal/TextTerminal.Repository.cs $
//==================================================================================================
