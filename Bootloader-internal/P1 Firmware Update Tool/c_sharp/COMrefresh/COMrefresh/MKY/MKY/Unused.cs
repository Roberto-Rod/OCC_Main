//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/Unused.cs $
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
// Copyright © 2010-2021 Matthias Kläy.
// All rights reserved.
// ------------------------------------------------------------------------------------------------
// This source code is licensed under the GNU LGPL.
// See http://www.gnu.org/licenses/lgpl.html for license details.
//==================================================================================================

using System;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;

namespace MKY
{
	/// <summary></summary>
	public static class UnusedEvent
	{
		/// <summary>
		/// Utility method that can be applied to unused events to prevent compiler warnings.
		/// </summary>
		/// <remarks>
		/// <paramref name="justification"/> is mandatory, same as SA1404:CSharp.Maintainability
		/// "A Code Analysis suppression must contain a non-empty justification describing the
		/// reason for the suppression."
		///
		/// Saying hello to StyleCop ;-.
		/// </remarks>
		public static void PreventCompilerWarning(EventHandler handler, string justification)
		{
			UnusedArg.PreventAnalysisWarning(justification, "Argument is solely used for stating justification right where issues occurs.");

			if (handler != null)
				return;

			// else return too...
		}

		/// <summary>
		/// Utility method that can be applied to unused events to prevent compiler warnings.
		/// </summary>
		/// <remarks>
		/// <paramref name="justification"/> is mandatory, same as SA1404:CSharp.Maintainability
		/// "A Code Analysis suppression must contain a non-empty justification describing the
		/// reason for the suppression."
		///
		/// Saying hello to StyleCop ;-.
		/// </remarks>
		/// <typeparam name="T">The type of the generic event handler.</typeparam>
		public static void PreventCompilerWarning<T>(EventHandler<T> handler, string justification) where T : EventArgs
		{
			UnusedArg.PreventAnalysisWarning(justification, "Argument is solely used for stating justification right where issues occurs.");

			if (handler != null)
				return;

			// else return too...
		}
	}

	/// <summary></summary>
	public static class UnusedArg
	{
		/// <summary>
		/// Utility method that can be applied to unused arguments to prevent compiler warnings.
		/// </summary>
		/// <remarks>
		/// <paramref name="justification"/> is mandatory, same as SA1404:CSharp.Maintainability
		/// "A Code Analysis suppression must contain a non-empty justification describing the
		/// reason for the suppression."
		///
		/// Saying hello to StyleCop ;-.
		/// </remarks>
		[SuppressMessage("Microsoft.Naming", "CA1720:IdentifiersShouldNotContainTypeNames", MessageId = "obj", Justification = "'obj' is commonly used throughout the .NET framework.")]
		public static void PreventCompilerWarning(object obj, string justification)
		{
			PreventAnalysisWarning(justification, "Argument is solely used for stating justification right where issues occurs.");

			if (obj != null)
				return;

			// else return too...
		}

		/// <summary>
		/// Utility method that can be applied to unused arguments to prevent code analysis warnings (e.g. FxCop).
		/// </summary>
		/// <remarks>
		/// Prevents FxCop "CA1801:ReviewUnusedParameters".
		/// </remarks>
		/// <remarks>
		/// <paramref name="justification"/> is mandatory, same as SA1404:CSharp.Maintainability
		/// "A Code Analysis suppression must contain a non-empty justification describing the
		/// reason for the suppression."
		/// </remarks>
		[SuppressMessage("Microsoft.Naming", "CA1720:IdentifiersShouldNotContainTypeNames", MessageId = "obj", Justification = "'obj' is commonly used throughout the .NET framework.")]
		[Conditional("DEBUG")]
		public static void PreventAnalysisWarning(object obj, string justification)
		{
		////PreventAnalysisWarning(justification, "...") is not needed, maybe because this method is [Conditional("DEBUG")].
		////PreventAnalysisWarning(justification, "...") would result in recursion, thus if (justification != null) would have to be used instead.

			if (obj != null)
				return;

			// else return too...
		}
	}

	/// <summary></summary>
	public static class UnusedLocal
	{
		/// <summary>
		/// Utility method that can be applied to unused local variables to prevent compiler warnings.
		/// </summary>
		/// <remarks>
		/// <paramref name="justification"/> is mandatory, same as SA1404:CSharp.Maintainability
		/// "A Code Analysis suppression must contain a non-empty justification describing the
		/// reason for the suppression."
		///
		/// Saying hello to StyleCop ;-.
		/// </remarks>
		[SuppressMessage("Microsoft.Naming", "CA1720:IdentifiersShouldNotContainTypeNames", MessageId = "obj", Justification = "'obj' is commonly used throughout the .NET framework.")]
		public static void PreventCompilerWarning(object obj, string justification)
		{
			PreventAnalysisWarning(justification, "Argument is solely used for stating justification right where issues occurs.");

			if (obj != null)
				return;

			// else return too...
		}

		/// <summary>
		/// Utility method that can be applied to unused local variables to prevent code analysis warnings (e.g. FxCop).
		/// </summary>
		/// <remarks>
		/// Prevents FxCop "CA1804:RemoveUnusedLocals".
		/// </remarks>
		/// <remarks>
		/// <paramref name="justification"/> is mandatory, same as SA1404:CSharp.Maintainability
		/// "A Code Analysis suppression must contain a non-empty justification describing the
		/// reason for the suppression."
		/// </remarks>
		[SuppressMessage("Microsoft.Naming", "CA1720:IdentifiersShouldNotContainTypeNames", MessageId = "obj", Justification = "'obj' is commonly used throughout the .NET framework.")]
		[Conditional("DEBUG")]
		public static void PreventAnalysisWarning(object obj, string justification)
		{
		////UnusedArg.PreventAnalysisWarning(justification, "...") is not needed, maybe because this method is [Conditional("DEBUG")].

			if (obj != null)
				return;

			// else return too...
		}
	}

	/// <summary></summary>
	public static class UnusedField
	{
		/// <summary>
		/// Utility method that can be applied to unused fields to prevent compiler warnings.
		/// </summary>
		/// <remarks>
		/// <paramref name="justification"/> is mandatory, same as SA1404:CSharp.Maintainability
		/// "A Code Analysis suppression must contain a non-empty justification describing the
		/// reason for the suppression."
		///
		/// Saying hello to StyleCop ;-.
		/// </remarks>
		/// <typeparam name="T">The type of the object.</typeparam>
		[SuppressMessage("Microsoft.Design", "CA1021:AvoidOutParameters", MessageId = "0#", Justification = "It is the goal of this method to modify a variable outside this method, and 'out' is better suited than 'ref' as it doesn't require the variable to be initialized.")]
		[SuppressMessage("Microsoft.Naming", "CA1720:IdentifiersShouldNotContainTypeNames", MessageId = "obj", Justification = "'obj' is commonly used throughout the .NET framework.")]
		public static void PreventCompilerWarning<T>(out T obj, string justification)
		{
			UnusedArg.PreventAnalysisWarning(justification, "Argument is solely used for stating justification right where issues occurs.");

			obj = default(T);
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/Unused.cs $
//==================================================================================================
