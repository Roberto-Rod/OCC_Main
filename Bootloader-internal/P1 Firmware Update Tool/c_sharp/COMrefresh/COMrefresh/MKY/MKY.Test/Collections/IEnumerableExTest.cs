//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.Test/Collections/IEnumerableExTest.cs $
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

using System.Collections;

using MKY.Collections;
using MKY.Test.Collections.ObjectModel;
using MKY.Test.Types;

using NUnit.Framework;

namespace MKY.Test.Collections
{
	/// <summary></summary>
	[TestFixture]
	public class IEnumerableExTest
	{
		/// <remarks>Re-uses the test cases of the <see cref="ArrayExTest"/>.</remarks>
		[Test, TestCaseSource(typeof(ArrayExTestData), "TestCases")]
		public virtual void TestArrayItemsEqual(IEnumerable objA, IEnumerable objB, bool equals)
		{
			Assert.That(IEnumerableEx.ItemsEqual(objA, objB), Is.EqualTo(equals));
		}

		/// <remarks>Re-uses the test cases of the <see cref="ReadOnlyCollectionExTest"/>.</remarks>
		[Test]
		[TestCaseSource(typeof(ReadOnlyCollectionExTestData), "TestCasesInt")]
		[TestCaseSource(typeof(ReadOnlyCollectionExTestData), "TestCasesEnum")]
		[TestCaseSource(typeof(ReadOnlyCollectionExTestData), "TestCasesReferenceType")]
		[TestCaseSource(typeof(ReadOnlyCollectionExTestData), "TestCasesString")]
		public virtual void TestReadOnlyCollectionItemsEqualInt(IEnumerable objA, IEnumerable objB, bool equals)
		{
			Assert.That(IEnumerableEx.ItemsEqual(objA, objB), Is.EqualTo(equals));
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.Test/Collections/IEnumerableExTest.cs $
//==================================================================================================
