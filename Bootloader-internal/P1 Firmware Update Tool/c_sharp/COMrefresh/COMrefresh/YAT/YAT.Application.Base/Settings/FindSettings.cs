//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Application.Base/Settings/FindSettings.cs $
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
using System.Xml.Serialization;

using MKY;
using MKY.Collections;
using MKY.Collections.Specialized;

using YAT.Application.Types;

namespace YAT.Application.Settings
{
	/// <summary></summary>
	public class FindSettings : MKY.Settings.SettingsItem, IEquatable<FindSettings>
	{
		private const int MaxRecentPatterns = 12;

		private string activePattern;
		private RecentItemCollection<string> recentPatterns;
		private FindOptions options;

		/// <summary></summary>
		public FindSettings()
			: this(MKY.Settings.SettingsType.Explicit)
		{
		}

		/// <summary></summary>
		public FindSettings(MKY.Settings.SettingsType settingsType)
			: base(settingsType)
		{
			SetMyDefaults();
			ClearChanged();
		}

		/// <remarks>
		/// Fields are assigned via properties even though changed flag will be cleared anyway.
		/// There potentially is additional code that needs to be run within the property method.
		/// </remarks>
		public FindSettings(FindSettings rhs)
			: base(rhs)
		{
			ActivePattern  = rhs.ActivePattern;
			RecentPatterns = new RecentItemCollection<string>(rhs.RecentPatterns);
			Options        = rhs.Options;

			ClearChanged();
		}

		/// <remarks>
		/// Fields are assigned via properties to ensure correct setting of changed flag.
		/// </remarks>
		protected override void SetMyDefaults()
		{
			base.SetMyDefaults();

			ActivePattern  = null;
			RecentPatterns = new RecentItemCollection<string>(MaxRecentPatterns);
			Options        = new FindOptions(true, false, false);
		}                                     // Same as .NET regex, which are "case-sensitive by default".
		                                      // Also same as byte sequence based triggers, which are case-sensitive by nature.

		#region Properties
		//==========================================================================================
		// Properties
		//==========================================================================================

		/// <remarks>
		/// Using "Pattern" instead of "TextOrPattern" for simplicity.
		/// </remarks>
		[XmlElement("ActivePattern")]
		public string ActivePattern
		{
			get { return (this.activePattern); }
			set
			{
				if (this.activePattern != value)
				{
					this.activePattern = value;
					SetMyChanged();
				}
			}
		}

		/// <remarks>
		/// Using "Pattern" instead of "TextOrPattern" for simplicity.
		/// </remarks>
		[SuppressMessage("Microsoft.Design", "CA1002:DoNotExposeGenericLists", Justification = "Public getter is required for default XML serialization/deserialization.")]
		[SuppressMessage("Microsoft.Usage", "CA2227:CollectionPropertiesShouldBeReadOnly", Justification = "Public setter is required for default XML serialization/deserialization.")]
		[XmlElement("RecentPatterns")]
		public RecentItemCollection<string> RecentPatterns
		{
			get { return (this.recentPatterns); }
			set
			{
				if (this.recentPatterns != value)
				{
					this.recentPatterns = value;
					SetMyChanged();
				}
			}
		}

		/// <summary></summary>
		[XmlElement("Options")]
		public FindOptions Options
		{
			get { return (this.options); }
			set
			{
				if (this.options != value)
				{
					this.options = value;
					SetMyChanged();
				}
			}
		}

		#endregion

		#region Object Members
		//==========================================================================================
		// Object Members
		//==========================================================================================

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
				int hashCode = base.GetHashCode(); // Get hash code of all settings nodes.

				hashCode = (hashCode * 397) ^ (ActivePattern  != null ? ActivePattern .GetHashCode() : 0);
				hashCode = (hashCode * 397) ^ (RecentPatterns != null ? RecentPatterns.GetHashCode() : 0);
				hashCode = (hashCode * 397) ^  Options                                .GetHashCode();

				return (hashCode);
			}
		}

		/// <summary>
		/// Determines whether this instance and the specified object have reference or value equality.
		/// </summary>
		public override bool Equals(object obj)
		{
			return (Equals(obj as FindSettings));
		}

		/// <summary>
		/// Determines whether this instance and the specified object have reference or value equality.
		/// </summary>
		/// <remarks>
		/// Use properties instead of fields to determine equality. This ensures that 'intelligent'
		/// properties, i.e. properties with some logic, are also properly handled.
		/// </remarks>
		public bool Equals(FindSettings other)
		{
			if (ReferenceEquals(other, null)) return (false);
			if (ReferenceEquals(this, other)) return (true);
			if (GetType() != other.GetType()) return (false);

			return
			(
				base.Equals(other) && // Compare all settings nodes.

				StringEx          .EqualsOrdinal(ActivePattern, other.ActivePattern)  &&
				IEnumerableEx.ItemsEqual(       RecentPatterns, other.RecentPatterns) &&
				Options           .Equals(                      other.Options)
			);
		}

		/// <summary>
		/// Determines whether the two specified objects have reference or value equality.
		/// </summary>
		public static bool operator ==(FindSettings lhs, FindSettings rhs)
		{
			if (ReferenceEquals(lhs, rhs))  return (true);
			if (ReferenceEquals(lhs, null)) return (false);
			if (ReferenceEquals(rhs, null)) return (false);

			object obj = (object)lhs; // Operators are not virtual! Calling object.Equals() ensures
			return (obj.Equals(rhs)); // that a potential virtual <Derived>.Equals() is called.
		}

		/// <summary>
		/// Determines whether the two specified objects have reference and value inequality.
		/// </summary>
		public static bool operator !=(FindSettings lhs, FindSettings rhs)
		{
			return (!(lhs == rhs));
		}

		#endregion
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Application.Base/Settings/FindSettings.cs $
//==================================================================================================
