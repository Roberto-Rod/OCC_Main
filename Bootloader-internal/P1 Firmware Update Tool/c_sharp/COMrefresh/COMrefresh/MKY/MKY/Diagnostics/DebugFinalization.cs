//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/Diagnostics/DebugFinalization.cs $
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

using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;

namespace MKY.Diagnostics
{
	/// <summary>
	/// Provides static methods to help with finalization.
	/// </summary>
	public static class DebugFinalization
	{
		private static bool staticFinalizationShouldHaveCompleted; // = false;

		/// <summary></summary>
		public static bool FinalizationShouldHaveCompleted
		{
			get { return (staticFinalizationShouldHaveCompleted); }
			set { staticFinalizationShouldHaveCompleted = value;  }
		}

		/// <summary></summary>
		[SuppressMessage("Microsoft.Naming", "CA1720:IdentifiersShouldNotContainTypeNames", MessageId = "obj", Justification = "'obj' is commonly used throughout the .NET framework.")]
		[Conditional("DEBUG")]
		public static void DebugNotifyFinalizerAndCheckWhetherOverdue(object obj)
		{
			if (staticFinalizationShouldHaveCompleted)
				Debug.WriteLine("The finalizer of this '" + obj.GetType().FullName + "' has been called too late! If this is not a static object, ensure to de-reference it early enough!");
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/Diagnostics/DebugFinalization.cs $
//==================================================================================================
