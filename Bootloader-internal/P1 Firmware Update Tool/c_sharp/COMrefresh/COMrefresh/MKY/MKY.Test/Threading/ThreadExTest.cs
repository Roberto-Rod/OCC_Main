//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.Test/Threading/ThreadExTest.cs $
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

#region Using
//==================================================================================================
// Using
//==================================================================================================

using System;

using MKY.Threading;

using NUnit.Framework;

#endregion

namespace MKY.Test.Threading
{
	/// <summary></summary>
	[TestFixture]
	public class ThreadExTest
	{
		#region Tests
		//==========================================================================================
		// Tests
		//==========================================================================================

		/// <summary></summary>
		[Test]
		public virtual void TestSleepUntilAt()
		{
			var begin = DateTime.Now;
			var at = begin + TimeSpan.FromMilliseconds(1000);
			ThreadEx.SleepUntilAt(at);
			var end = DateTime.Now;
			Assert.That(end, Is.GreaterThanOrEqualTo(at));
		}

		/// <summary></summary>
		[Test]
		public virtual void TestSleepUntilOffset()
		{
			var begin = DateTime.Now;
			ThreadEx.SleepUntilOffset(begin, 1000);
			var end = DateTime.Now;
			Assert.That(end, Is.GreaterThanOrEqualTo(begin + TimeSpan.FromMilliseconds(1000)));
		}

		#endregion
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.Test/Threading/ThreadExTest.cs $
//==================================================================================================
