//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Domain/Utilities/ForSomeTimeEventHelper.cs $
// $Revision: 3786 $
// $Date: 2021-04-20 16:33:31 +0000 (Tue, 20 Apr 2021) $
// $Author: maettu_this $
// ------------------------------------------------------------------------------------------------
// YAT Version 2.4.1
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

namespace YAT.Domain.Utilities
{
	/// <summary>
	/// While sending, the 'IsSendingForSomeTimeChanged' event must be raised before or when
	/// intensive processing is done. This is required because a client may want to indicate that
	/// time intensive sending is currently ongoing and no further data shall be sent.
	/// The event shall be raised if the time lag will significantly be noticeable by the user
	/// (i.e. >= 250 ms). But the event shall be raised BEFORE the actual time lag. This helper
	/// struct manages the state and the various criteria.
	/// </summary>
	[SuppressMessage("StyleCop.CSharp.DocumentationRules", "SA1650:ElementDocumentationMustBeSpelledCorrectly", Justification = "'ms' is the proper abbreviation for milliseconds but StyleCop isn't able to deal with such abbreviations...")]
	public class ForSomeTimeEventHelper
	{
		/// <remarks>In milliseconds.</remarks>
		public const int Threshold = 250;

		private bool eventMustBeRaised;
		private DateTime initialTimeStamp;

		/// <summary></summary>
		public ForSomeTimeEventHelper(DateTime initialTimeStamp)
		{
			this.eventMustBeRaised = false;
			this.initialTimeStamp = initialTimeStamp;
		}

		/// <summary></summary>
		public bool EventMustBeRaised
		{
			get { return (this.eventMustBeRaised); }
		}

		/// <remarks>Using term "byte" rather than "octet" as that is more common, and .NET uses "byte" as well.</remarks>
		public static bool ChunkSizeIsAboveThreshold(int chunkSize, double typicalNumberOfBytesPerMillisecond)
		{
			return (chunkSize >= (Threshold * typicalNumberOfBytesPerMillisecond));
		}

		/// <remarks>Using term "byte" rather than "octet" as that is more common, and .NET uses "byte" as well.</remarks>
		[SuppressMessage("Microsoft.Design", "CA1030:UseEventsWhereAppropriate", Justification = "Funny, this *is* an event helper.")]
		public bool RaiseEventIfChunkSizeIsAboveThreshold(int chunkSize, double typicalNumberOfBytesPerMillisecond)
		{
			// Only let the event get raised if it hasn't been yet:
			if (!this.eventMustBeRaised && ChunkSizeIsAboveThreshold(chunkSize, typicalNumberOfBytesPerMillisecond))
			{
				this.eventMustBeRaised = true;
				return (true);
			}

			return (false);
		}

		/// <summary></summary>
		public static bool DelayIsAboveThreshold(int delay)
		{
			return (delay >= Threshold);
		}

		/// <summary></summary>
		[SuppressMessage("Microsoft.Design", "CA1030:UseEventsWhereAppropriate", Justification = "Funny, this *is* an event helper.")]
		public bool RaiseEventIfDelayIsAboveThreshold(int delay)
		{
			// Only let the event get raised if it hasn't been yet:
			if (!this.eventMustBeRaised && DelayIsAboveThreshold(delay))
			{
				this.eventMustBeRaised = true;
				return (true);
			}

			return (false);
		}

		/// <summary></summary>
		public bool TotalTimeLagIsAboveThreshold()
		{
			TimeSpan totalTimeLag = (DateTime.Now - this.initialTimeStamp);
			return (totalTimeLag.Milliseconds >= Threshold);
		}

		/// <summary></summary>
		[SuppressMessage("Microsoft.Design", "CA1030:UseEventsWhereAppropriate", Justification = "Funny, this *is* an event helper.")]
		public bool RaiseEventIfTotalTimeLagIsAboveThreshold()
		{
			// Only let the event get raised if it hasn't been yet:
			if (!this.eventMustBeRaised && TotalTimeLagIsAboveThreshold())
			{
				this.eventMustBeRaised = true;
				return (true);
			}

			return (false);
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Domain/Utilities/ForSomeTimeEventHelper.cs $
//==================================================================================================
