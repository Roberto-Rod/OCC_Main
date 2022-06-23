//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.IO.Serial.Socket/SocketBase.cs $
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
using System.Threading;

namespace MKY.IO.Serial.Socket
{
	/// <summary></summary>
	internal static class SocketBase
	{
		#region Static Fields
		//==========================================================================================
		// Static Fields
		//==========================================================================================

		private static int staticInstanceCounter;
		private static Random staticRandom = new Random(RandomEx.NextRandomSeed());

		#endregion

		#region Static Properties
		//==========================================================================================
		// Static Properties
		//==========================================================================================

		/// <summary>
		/// Gets the next instance identifier.
		/// </summary>
		public static int NextInstanceId
		{
			get { return (Interlocked.Increment(ref staticInstanceCounter)); }
		}

		/// <summary>
		/// Gets the random.
		/// </summary>
		public static Random Random
		{
			get { return (staticRandom); }
		}

		#endregion
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY.IO.Serial.Socket/SocketBase.cs $
//==================================================================================================
