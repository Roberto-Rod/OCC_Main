﻿//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Domain/Parser/States/OpeningState.cs $
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

// This code is intentionally placed into the parser base namespace even though the file is located
// in a "\States" sub-directory. The sub-directory shall only group the implementation but not open
// another namespace. The state classes already contain "State" in their name.
namespace YAT.Domain.Parser
{
	/// <summary>
	/// This state handles an opening '(' and then passes control to a nested parser.
	/// </summary>
	internal class OpeningState : ParserState
	{
		/// <summary></summary>
		public override bool TryParse(Parser parser, int parseChar, ref FormatException formatException)
		{
			if (parseChar == '(')
			{
				ChangeState(parser, new DefaultState());
				return (true);
			}
			else
			{
				formatException = new FormatException(@"Missing opening parenthesis ""("".");
				return (false);
			}
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Domain/Parser/States/OpeningState.cs $
//==================================================================================================
