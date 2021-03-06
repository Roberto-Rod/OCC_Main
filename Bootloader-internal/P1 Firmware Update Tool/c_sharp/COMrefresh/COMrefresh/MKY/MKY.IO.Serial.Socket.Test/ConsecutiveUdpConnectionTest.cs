//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.IO.Serial.Socket.Test/ConsecutiveUdpConnectionTest.cs $
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

using NUnit.Framework;
using NUnitEx;

namespace MKY.IO.Serial.Socket.Test
{
	/// <summary></summary>
	[TestFixture]
	public class ConsecutiveUdpConnectionTest
	{
		#region Tests
		//==========================================================================================
		// Tests
		//==========================================================================================

		#region Tests > ConsecutiveServerClientConnectAndShutdown()
		//------------------------------------------------------------------------------------------
		// Tests > ConsecutiveServerClientConnectAndShutdown()
		//------------------------------------------------------------------------------------------

		/// <remarks>
		/// A cycle takes around 2 seconds => 30 cycles for a minute.
		/// </remarks>
		[Test]
		[Repeat(30)]
		[EnduranceCategory, StandardDurationCategory.Minute1]
		public virtual void TestConsecutiveServerClientConnectAndShutdownEndurance01Minute()
		{
			var t = new SimpleUdpConnectionTest();
			t.TestServerClientConnectAndClientShutdown();
			t.TestServerClientConnectAndServerShutdown();
			t.TestServerClientConnectAndClientShutdown();
			t.TestServerClientConnectAndClientShutdown();
			t.TestServerClientConnectAndServerShutdown();
			t.TestServerClientConnectAndServerShutdown();
			t.TestServerClientConnectAndClientShutdown();
			t.TestServerClientConnectAndClientShutdown();
			t.TestServerClientConnectAndClientShutdown();
			t.TestServerClientConnectAndServerShutdown();
			t.TestServerClientConnectAndServerShutdown();
			t.TestServerClientConnectAndServerShutdown();
			t.TestServerClientConnectAndClientShutdown();
			t.TestServerClientConnectAndClientShutdown();
			t.TestServerClientConnectAndClientShutdown();
			t.TestServerClientConnectAndClientShutdown();
			t.TestServerClientConnectAndServerShutdown();
			t.TestServerClientConnectAndServerShutdown();
			t.TestServerClientConnectAndServerShutdown();
			t.TestServerClientConnectAndServerShutdown();
			t.TestServerClientConnectAndClientShutdown();
			t.TestServerClientConnectAndClientShutdown();
			t.TestServerClientConnectAndClientShutdown();
			t.TestServerClientConnectAndClientShutdown();
			t.TestServerClientConnectAndClientShutdown();
			t.TestServerClientConnectAndServerShutdown();
			t.TestServerClientConnectAndServerShutdown();
			t.TestServerClientConnectAndServerShutdown();
			t.TestServerClientConnectAndServerShutdown();
			t.TestServerClientConnectAndServerShutdown();
		}

		/// <summary></summary>
		[Test]
		[Repeat(15)]
		[EnduranceCategory, StandardDurationCategory.Minutes15]
		public virtual void TestConsecutiveServerClientConnectAndShutdownEndurance15Minutes()
		{
			TestConsecutiveServerClientConnectAndShutdownEndurance01Minute();
		}

		/// <summary></summary>
		[Test]
		[Repeat(int.MaxValue)]
		[EnduranceCategory, InfiniteDurationCategory]
		public virtual void TestConsecutiveServerClientConnectAndShutdownEnduranceInfinite()
		{
			TestConsecutiveServerClientConnectAndShutdownEndurance01Minute();
		}

		#endregion

		#region Tests > ConsecutivePairSocketPairSocketConnectAndShutdown()
		//------------------------------------------------------------------------------------------
		// Tests > ConsecutivePairSocketPairSocketConnectAndShutdown()
		//------------------------------------------------------------------------------------------

		/// <remarks>
		/// A cycle takes around 2 seconds => 30 cycles for a minute.
		/// </remarks>
		[Test]
		[Repeat(30)]
		[EnduranceCategory, StandardDurationCategory.Minute1]
		public virtual void TestConsecutivePairSocketPairSocketConnectAndShutdownEndurance01Minute()
		{
			var t = new SimpleUdpConnectionTest();
			t.TestPairSocketPairSocketConnectAndPairSocketAShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketBShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketAShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketAShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketBShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketBShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketAShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketAShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketAShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketBShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketBShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketBShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketAShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketAShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketAShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketAShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketBShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketBShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketBShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketBShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketAShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketAShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketAShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketAShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketAShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketBShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketBShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketBShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketBShutdown();
			t.TestPairSocketPairSocketConnectAndPairSocketBShutdown();
		}

		/// <summary></summary>
		[Test]
		[Repeat(15)]
		[EnduranceCategory, StandardDurationCategory.Minutes15]
		public virtual void TestConsecutivePairSocketPairSocketConnectAndShutdownEndurance15Minutes()
		{
			TestConsecutivePairSocketPairSocketConnectAndShutdownEndurance01Minute();
		}

		/// <summary></summary>
		[Test]
		[Repeat(int.MaxValue)]
		[EnduranceCategory, InfiniteDurationCategory]
		public virtual void TestConsecutivePairSocketPairSocketConnectAndShutdownEnduranceInfinite()
		{
			TestConsecutivePairSocketPairSocketConnectAndShutdownEndurance01Minute();
		}

		#endregion

		#endregion
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.IO.Serial.Socket.Test/ConsecutiveUdpConnectionTest.cs $
//==================================================================================================
