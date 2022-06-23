//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.Test/Equality/Types/ReferenceTypeNotIEquatableWithoutOperators_Derived.cs $
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

using System;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;

using MKY.Diagnostics;

namespace MKY.Test.Equality.Types
{
	/// <summary></summary>
	internal class ReferenceTypeNotIEquatableWithoutOperators_Derived : ReferenceTypeNotIEquatableWithoutOperators_Base
	{
		/// <summary></summary>
		public int D { get; } // = 'Derived'

		/// <summary></summary>
		public ReferenceTypeNotIEquatableWithoutOperators_Derived(int b, int d)
			: base(b)
		{
			D = d;
		}

		#region Object Members
		//======================================================================================
		// Object Members
		//======================================================================================

		/// <summary>
		/// Converts the value of this instance to its equivalent string representation.
		/// </summary>
		/// <remarks>
		/// Use properties instead of fields. This ensures that 'intelligent' properties,
		/// i.e. properties with some logic, are also properly handled.
		/// </remarks>
		public override string ToString()
		{
			return
			(
				Environment.NewLine + "      1:Base = " + base.ToString() +
				Environment.NewLine + "      1:D    = " + D.ToString(CultureInfo.CurrentCulture)
			);
		}

		/// <summary>
		/// Serves as a hash function for a particular type.
		/// </summary>
		/// <remarks>
		/// Use properties instead of fields to calculate hash code. This ensures that 'intelligent'
		/// properties, i.e. properties with some logic, are also properly handled.
		/// </remarks>
		public override int GetHashCode()
		{
			return (base.GetHashCode() ^ D.GetHashCode());
		}

		/// <summary>
		/// Determines whether this instance and the specified object have reference or value equality.
		/// </summary>
		/// <remarks>
		/// Use properties instead of fields to determine equality. This ensures that 'intelligent'
		/// properties, i.e. properties with some logic, are also properly handled.
		/// </remarks>
		[SuppressMessage("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily", Justification = "Performance is not an issue here, readability is...")]
		public override bool Equals(object obj)
		{
			if (Configuration.TraceCallingSequence) // Trace the calling sequence:
			{
				Trace.Indent();
				TraceEx.WriteLocation();

				if (!base.Equals(obj))
				{
					Trace.WriteLine("base.Equals() results in 'False'");
					Trace.Unindent();
					return (false);
				}

				var other = (obj as ReferenceTypeNotIEquatableWithoutOperators_Derived);
				bool result = (D.Equals(other.D));

				Trace.WriteLine("Results in " + result);
				Trace.Unindent();
				return (result);
			}
			else // Normal implementation:
			{
				if (!base.Equals(obj))
					return (false);

				var other = (obj as ReferenceTypeNotIEquatableWithoutOperators_Derived);
				return (D.Equals(other.D));
			}
		}

		#endregion
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.Test/Equality/Types/ReferenceTypeNotIEquatableWithoutOperators_Derived.cs $
//==================================================================================================
