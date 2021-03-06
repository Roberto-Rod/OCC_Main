//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/NUnit/NUnitEx/ContextDetector.cs $
// $Revision: 3786 $
// $Date: 2021-04-20 16:33:31 +0000 (Tue, 20 Apr 2021) $
// $Author: maettu_this $
// ------------------------------------------------------------------------------------------------
// NUnitEx Version 1.0.23
// ------------------------------------------------------------------------------------------------
// See release notes for product version details.
// See SVN change log for file revision details.
// Author(s): Matthias Klaey
// ------------------------------------------------------------------------------------------------
// Copyright © 2010-2021 Matthias Kläy.
// All rights reserved.
// ------------------------------------------------------------------------------------------------
// This source code is licensed under the GNU LGPL.
// See http://www.gnu.org/licenses/lgpl.html for license details.
//==================================================================================================

using System;
using System.Diagnostics.CodeAnalysis;
using System.Linq;

namespace NUnitEx
{
	/// <summary>
	/// Helper indicating whether the process is currently running in NUnit.
	/// </summary>
	/// <remarks>
	/// This helper should only be used if absolutely necessary, as it usually is a sign
	/// of bad design.
	/// </remarks>
	public static class ContextDetector
	{
		[SuppressMessage("Microsoft.Globalization", "CA1308:NormalizeStringsToUppercase", Justification = "Normalizing towards effective file/assembly name.")]
		static ContextDetector()
		{
			IsRunningInNUnit = AppDomain.CurrentDomain.GetAssemblies().Any
			(
				a => a.FullName.ToLowerInvariant().StartsWith("nunit.framework", StringComparison.OrdinalIgnoreCase)
			);
		}

		/// <summary>
		/// Gets a value indicating whether the process is currently running in NUnit.
		/// </summary>
		/// <remarks>
		/// This property should only be retrieved if absolutely necessary, as it usually is a sign
		/// of bad design.
		/// </remarks>
		public static bool IsRunningInNUnit { get; private set; }
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/NUnit/NUnitEx/ContextDetector.cs $
//==================================================================================================
