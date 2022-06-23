//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Domain/Parser/Exceptions.cs $
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
using System.Runtime.Serialization;

namespace YAT.Domain.Parser
{
	/// <summary></summary>
	[Serializable]
	public class FormatException : System.FormatException
	{
		/// <summary></summary>
		public FormatException()
		{
		}

		/// <summary></summary>
		public FormatException(string message)
			: this(message, null)
		{
		}

		/// <summary></summary>
		public FormatException(string message, Exception innerException)
			: base
			(
			message + Environment.NewLine + Environment.NewLine +
			Parser.FormatHelp + Environment.NewLine + Environment.NewLine +
			Parser.KeywordHelp + Environment.NewLine + Environment.NewLine,
			innerException
			)
		{
		}

		/// <summary></summary>
		protected FormatException(SerializationInfo info, StreamingContext context)
			: base(info, context)
		{
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Domain/Parser/Exceptions.cs $
//==================================================================================================
