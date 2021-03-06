//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Model.Base/Types/AutoTriggerOptions.cs $
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
// Copyright © 2007-2021 Matthias Kläy.
// All rights reserved.
// ------------------------------------------------------------------------------------------------
// This source code is licensed under the GNU LGPL.
// See http://www.gnu.org/licenses/lgpl.html for license details.
//==================================================================================================

using System;
using System.Xml.Serialization;

namespace YAT.Model.Types
{
	/// <summary></summary>
	[Serializable]
	public struct AutoTriggerOptions : IEquatable<AutoTriggerOptions>
	{
		/// <summary></summary>
		[XmlElement("UseText")]
		public bool UseText { get; set; }

		/// <summary></summary>
		[XmlElement("CaseSensitive")]
		public bool CaseSensitive { get; set; }

		/// <summary></summary>
		[XmlElement("WholeWord")]
		public bool WholeWord { get; set; }

		/// <summary></summary>
		[XmlElement("EnableRegex")]
		public bool EnableRegex { get; set; }

		/// <summary></summary>
		public AutoTriggerOptions(bool useText, bool caseSensitive, bool wholeWord, bool enableRegex)
		{
			UseText       = useText;
			CaseSensitive = caseSensitive;
			WholeWord     = wholeWord;
			EnableRegex   = enableRegex;
		}

		#region Object Members
		//==========================================================================================
		// Object Members
		//==========================================================================================

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
				UseText       + ", " +
				CaseSensitive + ", " +
				WholeWord     + ", " +
				EnableRegex
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
			unchecked
			{
				int hashCode;

				hashCode =                    UseText      .GetHashCode();
				hashCode = (hashCode * 397) ^ CaseSensitive.GetHashCode();
				hashCode = (hashCode * 397) ^ WholeWord    .GetHashCode();
				hashCode = (hashCode * 397) ^ EnableRegex  .GetHashCode();

				return (hashCode);
			}
		}

		/// <summary>
		/// Determines whether this instance and the specified object have value equality.
		/// </summary>
		public override bool Equals(object obj)
		{
			if (obj is AutoTriggerOptions)
				return (Equals((AutoTriggerOptions)obj));
			else
				return (false);
		}

		/// <summary>
		/// Determines whether this instance and the specified object have value equality.
		/// </summary>
		/// <remarks>
		/// Use properties instead of fields to determine equality. This ensures that 'intelligent'
		/// properties, i.e. properties with some logic, are also properly handled.
		/// </remarks>
		public bool Equals(AutoTriggerOptions other)
		{
			return
			(
				UseText      .Equals(other.UseText)       &&
				CaseSensitive.Equals(other.CaseSensitive) &&
				WholeWord    .Equals(other.WholeWord)     &&
				EnableRegex  .Equals(other.EnableRegex)
			);
		}

		/// <summary>
		/// Determines whether the two specified objects have value equality.
		/// </summary>
		public static bool operator ==(AutoTriggerOptions lhs, AutoTriggerOptions rhs)
		{
			return (lhs.Equals(rhs));
		}

		/// <summary>
		/// Determines whether the two specified objects have value inequality.
		/// </summary>
		public static bool operator !=(AutoTriggerOptions lhs, AutoTriggerOptions rhs)
		{
			return (!(lhs == rhs));
		}

		#endregion
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Model.Base/Types/AutoTriggerOptions.cs $
//==================================================================================================
