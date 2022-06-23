//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/Usb/Descriptors.cs $
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

#region Using
//==================================================================================================
// Using
//==================================================================================================

using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;

#endregion

namespace MKY.Usb
{
	/// <summary>
	/// Encapsulates USB items.
	/// </summary>
	public static class Descriptors
	{
		#region Constants
		//==========================================================================================
		// Constants
		//==========================================================================================

		/// <summary>
		/// Maximum of 126 characters in UCS-2 format.
		/// </summary>
		public const int MaxStringDescriptorCharLength = 126;

		#endregion

		#region Static Methods
		//==========================================================================================
		// Static Methods
		//==========================================================================================

		/// <summary>
		/// Retrieves available culture information from language string.
		/// </summary>
		[SuppressMessage("Microsoft.Naming", "CA1720:IdentifiersShouldNotContainTypeNames", MessageId = "string", Justification = "The parameter shall clearly state what it represents.")]
		public static CultureInfo[] GetCultureInfoFromLanguageString(string languageString)
		{
			var l = new List<CultureInfo>(languageString.Length); // Preset the required capacity to improve memory management.
			foreach (char c in languageString)
			{
				int culture = (int)c;
				CultureInfo ci = null;
				try
				{
					ci = CultureInfo.GetCultureInfo(culture);
				}
				catch (ArgumentNullException)
				{
				}
				catch (ArgumentException)
				{
				}

				if (ci != null)
					l.Add(ci);
			}

			return (l.ToArray());
		}

		#endregion
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/Usb/Descriptors.cs $
//==================================================================================================
