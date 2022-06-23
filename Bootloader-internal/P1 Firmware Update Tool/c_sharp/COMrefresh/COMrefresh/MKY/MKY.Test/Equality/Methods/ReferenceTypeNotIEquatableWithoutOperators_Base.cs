﻿//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.Test/Equality/Methods/ReferenceTypeNotIEquatableWithoutOperators_Base.cs $
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
// Copyright © 2007-2021 Matthias Kläy.
// All rights reserved.
// ------------------------------------------------------------------------------------------------
// This source code is licensed under the GNU LGPL.
// See http://www.gnu.org/licenses/lgpl.html for license details.
//==================================================================================================

using System.Diagnostics;

using MKY.Diagnostics;

using NUnit.Framework;

namespace MKY.Test.Equality.Methods
{
	/// <summary></summary>
	internal static class ReferenceTypeNotIEquatableWithoutOperators_Base
	{
		/// <summary></summary>
		public static void TestOperatorsForReferenceEquality(Types.ReferenceTypeNotIEquatableWithoutOperators_Base obj)
		{
			if (Configuration.TraceCallingSequence) {
				Trace.Indent();
				TraceEx.WriteLocation();
				Trace.Indent();
			}

			try
			{
				// Reference equal:

				#pragma warning disable 1718 // Disable "Comparison made to same variable; did you mean to compare something else?"

				if (Configuration.TraceCallingSequence) {
					Trace.WriteLine("Reference equal using operator ==()");
					Trace.Indent();
				}

				if (!(obj == obj))
					Assert.Fail("Reference equal objects are not considered equal using operator ==()");

				if (Configuration.TraceCallingSequence) {
					Trace.Unindent();
					Trace.WriteLine("Reference equal using operator !=()");
					Trace.Indent();
				}

				if (obj != obj)
					Assert.Fail("Reference equal objects are not considered not equal using operator !=()");

				if (Configuration.TraceCallingSequence)
					Trace.Unindent();

				#pragma warning restore 1718
			}
			catch (AssertionException)
			{
				if (Configuration.TraceCallingSequence)
					Trace.Unindent();

				throw; // Rethrow!
			}
			finally
			{
				if (Configuration.TraceCallingSequence) {
					Trace.Unindent();
					Trace.Unindent();
				}
			}
		}

		// TestOperatorsForValueEquality() is useless since it never succeeds.
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.Test/Equality/Methods/ReferenceTypeNotIEquatableWithoutOperators_Base.cs $
//==================================================================================================
