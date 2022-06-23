//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Model.Base/Types/EventArgs.cs $
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

namespace YAT.Model.Types
{
	/// <summary></summary>
	public class PredefinedCommandEventArgs : EventArgs
	{
		/// <summary></summary>
		public int PageId { get; }

		/// <summary></summary>
		public int CommandId { get; }

		/// <summary></summary>
		public PredefinedCommandEventArgs(int commandId)
			: this(PredefinedCommandPageCollection.NoPageId, commandId)
		{
		}

		/// <summary></summary>
		public PredefinedCommandEventArgs(int pageId, int commandId)
		{
			PageId    = pageId;
			CommandId = commandId;
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Model.Base/Types/EventArgs.cs $
//==================================================================================================
