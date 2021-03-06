//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Application.Base/Settings/MainWindowSettings.cs $
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
using System.Drawing;
using System.Windows.Forms;
using System.Xml.Serialization;

namespace YAT.Application.Settings
{
	/// <summary></summary>
	public class MainWindowSettings : WindowSettings, IEquatable<MainWindowSettings>
	{
		private FormStartPosition startPosition;

		private bool alwaysOnTop;

		private bool showTerminalInfo;
		private bool showTime;
		private bool showChrono;

		/// <summary></summary>
		public MainWindowSettings()
			: this(MKY.Settings.SettingsType.Explicit)
		{
		}

		/// <summary></summary>
		public MainWindowSettings(MKY.Settings.SettingsType settingsType)
			: base(settingsType)
		{
			SetMyDefaults();
			ClearChanged();
		}

		/// <remarks>
		/// Fields are assigned via properties even though changed flag will be cleared anyway.
		/// There potentially is additional code that needs to be run within the property method.
		/// </remarks>
		public MainWindowSettings(MainWindowSettings rhs)
			: base(rhs)
		{
			StartPosition    = rhs.StartPosition;

			AlwaysOnTop      = rhs.AlwaysOnTop;

			ShowTerminalInfo = rhs.ShowTerminalInfo;
			ShowTime         = rhs.ShowTime;
			ShowChrono       = rhs.ShowChrono;

			ClearChanged();
		}

		/// <remarks>
		/// Fields are assigned via properties to ensure correct setting of changed flag.
		/// </remarks>
		protected override void SetMyDefaults()
		{
			base.SetMyDefaults();

			StartPosition    = FormStartPosition.WindowsDefaultLocation; // Standard when opening an application.

			State            = FormWindowState.Normal; // Override to intended state of the 'Main' form.
			Size             = new Size(912, 684);     // Override to designed 'Size' of the 'Main' form.
			     //// ClientSize = Size(896, 645)
			AlwaysOnTop      = false;

			ShowTerminalInfo = false;
			ShowTime         = false;
			ShowChrono       = true;
		}

		#region Properties
		//==========================================================================================
		// Properties
		//==========================================================================================

		/// <summary></summary>
		[XmlElement("StartPosition")]
		public FormStartPosition StartPosition
		{
			get { return (this.startPosition); }
			set
			{
				if (this.startPosition != value)
				{
					this.startPosition = value;
					SetMyChanged();
				}
			}
		}

		/// <summary></summary>
		[XmlElement("AlwaysOnTop")]
		public bool AlwaysOnTop
		{
			get { return (this.alwaysOnTop); }
			set
			{
				if (this.alwaysOnTop != value)
				{
					this.alwaysOnTop = value;
					SetMyChanged();
				}
			}
		}

		/// <remarks>
		/// Using term "Info" since the info contains name and IDs.
		/// </remarks>
		[XmlElement("ShowTerminalInfo")]
		public bool ShowTerminalInfo
		{
			get { return (this.showTerminalInfo); }
			set
			{
				if (this.showTerminalInfo != value)
				{
					this.showTerminalInfo = value;
					SetMyChanged();
				}
			}
		}

		/// <summary></summary>
		[XmlElement("ShowTime")]
		public bool ShowTime
		{
			get { return (this.showTime); }
			set
			{
				if (this.showTime != value)
				{
					this.showTime = value;
					SetMyChanged();
				}
			}
		}

		/// <summary></summary>
		[XmlElement("ShowChrono")]
		public bool ShowChrono
		{
			get { return (this.showChrono); }
			set
			{
				if (this.showChrono != value)
				{
					this.showChrono = value;
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
				int hashCode = base.GetHashCode(); // Get hash code of base including all settings nodes.

				hashCode = (hashCode * 397) ^ StartPosition   .GetHashCode();

				hashCode = (hashCode * 397) ^ AlwaysOnTop     .GetHashCode();

				hashCode = (hashCode * 397) ^ ShowTerminalInfo.GetHashCode();
				hashCode = (hashCode * 397) ^ ShowTime        .GetHashCode();
				hashCode = (hashCode * 397) ^ ShowChrono      .GetHashCode();

				return (hashCode);
			}
		}

		/// <summary>
		/// Determines whether this instance and the specified object have reference or value equality.
		/// </summary>
		public override bool Equals(object obj)
		{
			return (Equals(obj as MainWindowSettings));
		}

		/// <summary>
		/// Determines whether this instance and the specified object have reference or value equality.
		/// </summary>
		/// <remarks>
		/// Use properties instead of fields to determine equality. This ensures that 'intelligent'
		/// properties, i.e. properties with some logic, are also properly handled.
		/// </remarks>
		public bool Equals(MainWindowSettings other)
		{
			if (ReferenceEquals(other, null)) return (false);
			if (ReferenceEquals(this, other)) return (true);
			if (GetType() != other.GetType()) return (false);

			return
			(
				base.Equals(other) && // Compare base including all settings nodes.

				StartPosition   .Equals(other.StartPosition)    &&

				AlwaysOnTop     .Equals(other.AlwaysOnTop)      &&

				ShowTerminalInfo.Equals(other.ShowTerminalInfo) &&
				ShowTime        .Equals(other.ShowTime)         &&
				ShowChrono      .Equals(other.ShowChrono)
			);
		}

		/// <summary>
		/// Determines whether the two specified objects have reference or value equality.
		/// </summary>
		public static bool operator ==(MainWindowSettings lhs, MainWindowSettings rhs)
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
		public static bool operator !=(MainWindowSettings lhs, MainWindowSettings rhs)
		{
			return (!(lhs == rhs));
		}

		#endregion
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Application.Base/Settings/MainWindowSettings.cs $
//==================================================================================================
