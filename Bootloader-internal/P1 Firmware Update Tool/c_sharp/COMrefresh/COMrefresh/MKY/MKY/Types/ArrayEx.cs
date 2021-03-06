//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/Types/ArrayEx.cs $
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

using System;
using System.Diagnostics.CodeAnalysis;
using System.Text;

using MKY.Collections;

// This code is intentionally placed into the MKY namespace even though the file is located in
// MKY.Types for consistency with the System namespace.
namespace MKY
{
	/// <summary>
	/// <see cref="Array"/> utility methods.
	/// </summary>
	[SuppressMessage("Microsoft.Naming", "CA1711:IdentifiersShouldNotHaveIncorrectSuffix", Justification = "'Ex' emphasizes that it's an extension to an existing class and not a replacement as '2' would emphasize.")]
	public static class ArrayEx
	{
		/// <summary>
		/// The invalid index.
		/// </summary>
		public const int InvalidIndex = -1;

		/// <summary>
		/// Indicates whether the specified array is <c>null</c> or empty.
		/// </summary>
		/// <remarks>
		/// Same syntax and semantic as <see cref="string.IsNullOrEmpty(string)"/>.
		/// </remarks>
		/// <param name="value">The array to test.</param>
		/// <returns>
		/// <c>true</c> if the value parameter is <c>null</c> or empty; otherwise, <c>false</c>.
		/// </returns>
		public static bool IsNullOrEmpty(Array value)
		{
			return ((value == null) || (value.Length == 0));
		}

		/// <summary>
		/// Creates an array using <see cref="Array.CreateInstance(Type, int)"/> and initializes
		/// the given number of array values with the given initial value.
		/// </summary>
		/// <typeparam name="T">The type of the array's values.</typeparam>
		public static T[] CreateAndInitializeInstance<T>(int length, T initialValue)
		{
			T[] a = (T[])Array.CreateInstance(typeof(T), length);

			for (int i = 0; i < a.Length; i++)
				a[i] = initialValue;

			return (a);
		}

		/// <summary>
		/// Determines whether the two arrays have value equality, i.e. contains the same number of
		/// values, all values are equally sequenced and have value equality.
		/// </summary>
		/// <remarks>
		/// This method has intentionally been called "ValuesEqual()"...
		/// ...for similar naming as <see cref="object.ReferenceEquals(object, object)"/> and...
		/// ...to emphasize difference to "Array.Equals()" which is just "object.Equals()".
		/// </remarks>
		/// <returns>
		/// True if arrays have value equality, otherwise false.
		/// </returns>
		public static bool ValuesEqual(Array objA, Array objB)
		{
			if (ReferenceEquals(objA, objB)) return (true);
			if (ReferenceEquals(objA, null)) return (false);
			if (ReferenceEquals(objB, null)) return (false);

			if (objA.Length != objB.Length)
				return (false);

			return (IEnumeratorEx.ItemsEqual(objA.GetEnumerator(), objB.GetEnumerator()));
		}

		/// <summary>
		/// Appends all values of an array to a comma separated string and returns it.
		/// Values that are <c>null</c> are returned as "(null)".
		/// An empty <paramref name="array"/> is returned as "(empty)".
		/// </summary>
		/// <returns>
		/// String containing values of all items.
		/// </returns>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public static string ValuesToString(Array array, string itemEnclosure = null)
		{
			// Attention:
			// Similar code exists in IEnumerableEx.ItemsToString().
			// Changes here may have to be applied there too.

			var sb = new StringBuilder();

			bool isFirst = true;
			foreach (object value in array)
			{
				if (isFirst)
					isFirst = false;
				else
					sb.Append(", ");

				if (!string.IsNullOrEmpty(itemEnclosure))
					sb.Append(itemEnclosure);

				if (value != null)
					sb.Append(value.ToString());
				else
					sb.Append("(null)");

				if (!string.IsNullOrEmpty(itemEnclosure))
					sb.Append(itemEnclosure);
			}

			if (isFirst) // i.e. no items.
				sb.Append("(empty)");

			return (sb.ToString());
		}

		/// <summary>
		/// Appends all values of an array to a comma separated string and returns it.
		/// Values that are <c>null</c> are returned as "(null)".
		/// </summary>
		/// <returns>
		/// String containing values of all items.
		/// </returns>
		public static string ValuesToString(Array array, char itemEnclosure)
		{
			// Attention:
			// Similar code exists in IEnumerableEx.ItemsToString().
			// Changes here may have to be applied there too.

			return (ValuesToString(array, itemEnclosure.ToString()));
		}

		/// <summary>
		/// Serves as a hash function that iterates over all values within the given array.
		/// </summary>
		public static int ValuesToHashCode(Array array)
		{
			// Attention:
			// Similar code exists in IEnumerableEx.ItemsToHashCode().
			// Changes here may have to be applied there too.

			int hashCode = 0;

			foreach (object value in array)
			{
				unchecked
				{
					hashCode = (hashCode * 397) ^ (value != null ? value.GetHashCode() : 0);
				}
			}

			return (hashCode);
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/Types/ArrayEx.cs $
//==================================================================================================
