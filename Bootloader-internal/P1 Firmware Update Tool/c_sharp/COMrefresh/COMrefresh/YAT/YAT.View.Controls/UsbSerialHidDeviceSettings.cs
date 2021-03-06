//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.View.Controls/UsbSerialHidDeviceSettings.cs $
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

#region Using
//==================================================================================================
// Using
//==================================================================================================

using System;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using System.Windows.Forms;

using MKY;
using MKY.IO.Serial.Usb;
using MKY.IO.Usb;
using MKY.Windows.Forms;

#endregion

namespace YAT.View.Controls
{
	/// <remarks>The preview control is not scalable to simplify implementation.</remarks>
	[SuppressMessage("StyleCop.CSharp.OrderingRules", "SA1203:ConstantsMustAppearBeforeFields", Justification = "Semantic of readonly fields is constant.")]
	[DefaultEvent("ReportFormatChanged")]
	public partial class UsbSerialHidDeviceSettings : UserControl
	{
		#region Constants
		//==========================================================================================
		// Constants
		//==========================================================================================

		private const           SerialHidDeviceSettingsPreset PresetDefault = SerialHidDeviceSettings.PresetDefault;
		private static readonly SerialHidReportFormat   ReportFormatDefault = SerialHidDeviceSettings.ReportFormatDefault;
		private static readonly SerialHidRxFilterUsage RxFilterUsageDefault = SerialHidDeviceSettings.RxFilterUsageDefault;

		private const SerialHidFlowControl FlowControlDefault = SerialHidFlowControl.None;
		private const bool AutoOpenDefault = SerialHidDeviceSettings.AutoOpenDefault;

		private const string AnyIdIndication = "*";

		#endregion

		#region Fields
		//==========================================================================================
		// Fields
		//==========================================================================================

		private SettingControlsHelper isSettingControls;

		/// <remarks>Used for subsequently updating <see cref="Preset"/>.</remarks>
		private DeviceInfo deviceInfo; // = null;

		private SerialHidDeviceSettingsPreset preset        = PresetDefault;
		private SerialHidReportFormat         reportFormat  = ReportFormatDefault;
		private SerialHidRxFilterUsage        rxFilterUsage = RxFilterUsageDefault;

		private SerialHidFlowControl flowControl = FlowControlDefault;
		private bool                 autoOpen    = AutoOpenDefault;

		private int lineLabelTopDefault;
		private int lineLabelTopShifted;

		#endregion

		#region Events
		//==========================================================================================
		// Events
		//==========================================================================================

		/// <summary></summary>
		[Category("Property Changed")]
		[Description("Event raised when the Preset property is changed.")]
		public event EventHandler PresetChanged;

		/// <summary></summary>
		[Category("Property Changed")]
		[Description("Event raised when the ReportFormat property is changed.")]
		public event EventHandler ReportFormatChanged;

		/// <summary></summary>
		[Category("Property Changed")]
		[Description("Event raised when the RxFilterUsage property is changed.")]
		public event EventHandler RxFilterUsageChanged;

		/// <summary></summary>
		[Category("Property Changed")]
		[Description("Event raised when the FlowControl property is changed.")]
		public event EventHandler FlowControlChanged;

		/// <summary></summary>
		[Category("Property Changed")]
		[Description("Event raised when the AutoOpen property is changed.")]
		public event EventHandler AutoOpenChanged;

		#endregion

		#region Object Lifetime
		//==========================================================================================
		// Object Lifetime
		//==========================================================================================

		/// <summary></summary>
		public UsbSerialHidDeviceSettings()
		{
			InitializeComponent();

			InitializeControls();
		////SetControls() is initially called in the 'Paint' event handler.
		}

		#endregion

		#region Properties
		//==========================================================================================
		// Properties
		//==========================================================================================

		/// <remarks>
		/// Required for...
		/// ...setting the base for <see cref="ReportFormat"/> and <see cref="RxFilterUsage"/>.
		/// </remarks>
		public void SetDeviceInfoWithoutUpdateOfPresets(DeviceInfo deviceInfo)
		{
			if (this.deviceInfo != deviceInfo)
			{
				this.deviceInfo = deviceInfo;
				SetControls();
			////OnDeviceInfoChanged does not exist as this is not a true property.
			}
		}

		/// <remarks>
		/// Required for...
		/// ...initially updating <see cref="Preset"/> and <see cref="FlowControl"/>.
		/// ...subsequently updating <see cref="Preset"/> and <see cref="FlowControl"/>.
		/// </remarks>
		public void SetDeviceInfoIncludingUpdateOfPresets(DeviceInfo deviceInfo)
		{
			SetDeviceInfoWithoutUpdateOfPresets(deviceInfo);

			// Attention:
			// Similar code exists in YAT.Model.Settings.ScriptUSBSettingsHelper.UpdateFrom(IOSettings, ref USBSerHIDSettings).
			// Changes likely have to be applied there too.
			// Code is duplicated rather than encapsulated as resulting method and usage would not result in less code.

			if (this.deviceInfo != null)
			{
				// Try to automatically select one of the settings presets:
				{
					SerialHidDeviceSettingsPresetEx preset;
					if (SerialHidDeviceSettingsPresetEx.TryFrom(deviceInfo, out preset))
						Preset = preset;
				}

				// Also try to automatically set flow control based on that preset:
				{
					SerialHidFlowControlPresetEx preset;
					if (SerialHidFlowControlPresetEx.TryFrom(deviceInfo, out preset))
						FlowControl = preset.ToFlowControl();
					else
						FlowControl = SerialHidFlowControl.None; // Explicitly set [None], which is the most typical case.
				}
			}
		}

		/// <summary></summary>
		[Category("Data")]
		[Description("One of the available presets.")]
		[DefaultValue(PresetDefault)]
		public SerialHidDeviceSettingsPreset Preset
		{
			get { return (this.preset); }
			set
			{
				if (this.preset != value)
				{
					if (value != SerialHidDeviceSettingsPreset.None) // Only true presets shall change the dependent settings.
					{
						// Keep preset to be able to restore ambiguous presets:
						if (value == SerialHidDeviceSettingsPreset.YAT)         // But do not keep [YAT] preset as
							this.preset = SerialHidDeviceSettingsPreset.Common; // that shall be redirected to [Common].
						else
							this.preset = value;

						SetControls();
						OnPresetChanged(EventArgs.Empty);

						// Update dependent settings:
						var presetEx = new SerialHidDeviceSettingsPresetEx(Preset);
						ReportFormat  = presetEx.ToReportFormat();
						RxFilterUsage = presetEx.ToRxFilterUsage();

						// Sequence above may lead to up to three invocations of SetControls().
						// However, not assigning to the 'ReportFormat' and 'RxFilterUsage'
						// properties would require to replicate or extract their functionality.
						// Multiple invocations of SetControls() seems acceptable.

						// Also note that sequence in dependent properties as well as control
						// event handlers may lead to up to two invocations of SetControls().
						// However, not assigning to the "Preset" property would require to
						// replicate or extract its functionality. Multiple invocations of
						// SetControls() seems acceptable. Assigning to the "Preset" property
						// will not create a circular loop even if the "Preset" again calls
						// the other properties, since the resulting value will not differ.
					}
					else // == SerialHidDeviceSettingsPreset.None
					{
						this.preset = value;
						SetControls();
						OnPresetChanged(EventArgs.Empty);
					}
				}
			}
		}

		/// <summary></summary>
		[Browsable(false)]
		[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
		public SerialHidReportFormat ReportFormat
		{
			get { return (this.reportFormat); }
			set
			{
				if (this.reportFormat != value)
				{
					this.reportFormat = value;
					SetControls();
					OnReportFormatChanged(EventArgs.Empty); // Will update the dependent "Preset" if needed.
				}
			}
		}

		/// <summary></summary>
		[Browsable(false)]
		[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
		public SerialHidRxFilterUsage RxFilterUsage
		{
			get { return (this.rxFilterUsage); }
			set
			{
				if (this.rxFilterUsage != value)
				{
					this.rxFilterUsage = value;
					SetControls();
					OnRxFilterUsageChanged(EventArgs.Empty); // Will update the dependent "Preset" if needed.
				}
			}
		}

		/// <summary></summary>
		[Category("Data")]
		[Description("The flow control type.")]
		[DefaultValue(FlowControlDefault)]
		public virtual SerialHidFlowControl FlowControl
		{
			get { return (this.flowControl); }
			set
			{
				if (this.flowControl != value)
				{
					this.flowControl = value;
					SetControls();
					OnFlowControlChanged(EventArgs.Empty);

					// So far, flow control is just preset on change of device selection, thus
					// change of flow control here does not need to be fed back to a preset (yet).
				}
			}
		}

		/// <summary></summary>
		[Category("Data")]
		[Description("The auto open setting.")]
		[DefaultValue(AutoOpenDefault)]
		public bool AutoOpen
		{
			get { return (this.autoOpen); }
			set
			{
				if (this.autoOpen != value)
				{
					this.autoOpen = value;
					SetControls();
					OnAutoOpenChanged(EventArgs.Empty);
				}
			}
		}

		#endregion

		#region Control Event Handlers
		//==========================================================================================
		// Control Event Handlers
		//==========================================================================================

		/// <summary>
		/// Flag only used by the following event handler.
		/// </summary>
		private bool UsbSerialHidPortSettings_Paint_IsFirst { get; set; } = true;

		/// <summary>
		/// Initially set controls and validate its contents where needed.
		/// </summary>
		/// <remarks>
		/// Use paint event to ensure that message boxes in case of errors (e.g. validation errors)
		/// are shown on top of a properly painted control or form.
		/// </remarks>
		private void UsbSerialHidPortSettings_Paint(object sender, PaintEventArgs e)
		{
			if (UsbSerialHidPortSettings_Paint_IsFirst) {
				UsbSerialHidPortSettings_Paint_IsFirst = false;

				SetControls();
			}
		}

		/// <summary>
		/// Ensure that all controls are cleared when control gets disabled.
		/// </summary>
		private void UsbSerialHidDeviceSettings_EnabledChanged(object sender, EventArgs e)
		{
			if (this.isSettingControls)
				return;

			SetControls();
		}

		#endregion

		#region Controls Event Handlers
		//==========================================================================================
		// Controls Event Handlers
		//==========================================================================================

		private void checkBox_UseId_CheckedChanged(object sender, EventArgs e)
		{
			if (this.isSettingControls)
				return;

			this.reportFormat.UseId = checkBox_UseId.Checked;
			SetControls();
			OnReportFormatChanged(EventArgs.Empty); // Will update the dependent "Preset" if needed.
		}

		private void textBox_Id_Validating(object sender, CancelEventArgs e)
		{
			if (this.isSettingControls)
				return;

			byte id;
			if (byte.TryParse(textBox_Id.Text, out id)) // Attention, a similar validation exists in 'Domain.Parser.KeywordEx'. Changes here may have to be applied there too.
			{
				this.reportFormat.Id = id;
				SetControls();
				OnReportFormatChanged(EventArgs.Empty); // Will update the dependent "Preset" if needed.
			}
			else
			{
				MessageBoxEx.Show
				(
					this,
					"ID must be a numeric value within 0..255!",
					"Invalid Input",
					MessageBoxButtons.OK,
					MessageBoxIcon.Error
				);

				e.Cancel = true;
			}
		}

		private void checkBox_SeparateRxId_CheckedChanged(object sender, EventArgs e)
		{
			if (this.isSettingControls)
				return;

			this.rxFilterUsage.SeparateRxId = checkBox_SeparateRxId.Checked;
			SetControls();
			OnRxFilterUsageChanged(EventArgs.Empty); // Will update the dependent "Preset" if needed.
		}

		private void textBox_RxId_Validating(object sender, CancelEventArgs e)
		{
			if (this.isSettingControls)
				return;

			string idText = textBox_RxId.Text;
			if (idText == AnyIdIndication)
			{
				this.rxFilterUsage.AnyRxId = true;
				this.rxFilterUsage.RxId = this.reportFormat.Id;
				SetControls();
				OnRxFilterUsageChanged(EventArgs.Empty); // Will update the dependent "Preset" if needed.
			}
			else
			{
				byte id;
				if (byte.TryParse(idText, out id))
				{
					this.rxFilterUsage.AnyRxId = false;
					this.rxFilterUsage.RxId = id;
					SetControls();
					OnRxFilterUsageChanged(EventArgs.Empty); // Will update the dependent "Preset" if needed.
				}
				else
				{
					MessageBoxEx.Show
					(
						this,
						"ID must be a numeric value within 0..255 or enter '" + AnyIdIndication + "' to accept any ID.",
						"Invalid Input",
						MessageBoxButtons.OK,
						MessageBoxIcon.Error
					);

					e.Cancel = true;
				}
			}
		}

		private void checkBox_PrependPayloadByteLength_CheckedChanged(object sender, EventArgs e)
		{
			if (this.isSettingControls)
				return;

			this.reportFormat.PrependPayloadByteLength = checkBox_PrependPayloadByteLength.Checked;
			SetControls();
			OnReportFormatChanged(EventArgs.Empty); // Will update the dependent "Preset" if needed.
		}

		private void checkBox_AppendTerminatingZero_CheckedChanged(object sender, EventArgs e)
		{
			if (this.isSettingControls)
				return;

			this.reportFormat.AppendTerminatingZero = checkBox_AppendTerminatingZero.Checked;
			SetControls();
			OnReportFormatChanged(EventArgs.Empty); // Will update the dependent "Preset" if needed.
		}

		private void checkBox_FillLastReport_CheckedChanged(object sender, EventArgs e)
		{
			if (this.isSettingControls)
				return;

			string message =
				"USB HID is designed to use complete reports; " +
				"the Windows HID infrastructure even enforces this constraint. " +
				"As a consequence, this option must always be kept enabled.";

			// Windows HID.dll requires that input as well as output reports are always filled!
			// Still, enable the check box in order to make tool tip visible to the user.
			MessageBoxEx.Show
			(
				this,
				message,
				"USB HID Constraint",
				MessageBoxButtons.OK,
				MessageBoxIcon.Information
			);

		////this.reportFormat.FillLastReport = checkBox_FillLastReport.Checked;
			SetControls();
		////OnReportFormatChanged(EventArgs.Empty); // Will update the dependent "Preset" if needed.
		}

		private void comboBox_Preset_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (this.isSettingControls)
				return;

			var preset = (comboBox_Preset.SelectedItem as SerialHidDeviceSettingsPresetEx);
			if (preset != null)
			{
				Preset = preset;
			////SetControls() will be called by the Preset property method.
			}
			else
			{
				SetControls();
			}
		}

		private void linkLabel_Info_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
		{
			LinkHelper.TryBrowseUriAndShowErrorIfItFails(Parent, e);
		}

		private void comboBox_FlowControl_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (this.isSettingControls)
				return;

			FlowControl = (SerialHidFlowControlEx)comboBox_FlowControl.SelectedItem;
		}

		private void checkBox_AutoOpen_CheckedChanged(object sender, EventArgs e)
		{
			if (this.isSettingControls)
				return;

			AutoOpen = checkBox_AutoOpen.Checked;
		}

		#endregion

		#region Non-Public Methods
		//==========================================================================================
		// Non-Public Methods
		//==========================================================================================

		private void InitializeControls()
		{
			this.isSettingControls.Enter();
			try
			{
				comboBox_Preset     .Items.AddRange(SerialHidDeviceSettingsPresetEx.GetItems());
				comboBox_FlowControl.Items.AddRange(SerialHidFlowControlEx.GetItems());

				this.lineLabelTopDefault = label_Line.Top;
				this.lineLabelTopShifted = (comboBox_Preset.Bottom + ((comboBox_FlowControl.Top - comboBox_Preset.Bottom) / 2));
			}
			finally
			{
				this.isSettingControls.Leave();
			}
		}

		private void SetControls()
		{
			this.isSettingControls.Enter();
			try
			{
				label_ReportFormat.Enabled = Enabled;

				if (this.reportFormat.UseId)
				{
					checkBox_UseId.Text        = "Tx &ID:";
					checkBox_SeparateRxId.Text = "Rx I&D:";

					checkBox_UseId.Checked        =  Enabled; // if (this.reportFormat.UseId) is checked above.
					checkBox_SeparateRxId.Enabled =  Enabled;
					checkBox_SeparateRxId.Checked = (Enabled ? this.rxFilterUsage.SeparateRxId : false);
					textBox_Id.Enabled            =  Enabled;
					textBox_RxId.Enabled          = (Enabled ? this.rxFilterUsage.SeparateRxId : false);

					textBox_Id.Text = this.reportFormat.Id.ToString(CultureInfo.InvariantCulture); // "InvariantCulture" for report ID!
					if (!this.rxFilterUsage.SeparateRxId) // Typical case = same ID for Tx and Rx.
					{
						textBox_RxId.Text = this.reportFormat.Id.ToString(CultureInfo.InvariantCulture); // "InvariantCulture" for report ID!
					}
					else // Special case = separate ID for Rx.
					{
						if (this.rxFilterUsage.AnyRxId)
							textBox_RxId.Text = AnyIdIndication;
						else
							textBox_RxId.Text = this.rxFilterUsage.RxId.ToString(CultureInfo.InvariantCulture); // "InvariantCulture" for report ID!
					}
				}
				else
				{
					checkBox_UseId.Text        = "Use &ID:";
					checkBox_SeparateRxId.Text = "";

					checkBox_UseId.Checked        = false;
					checkBox_SeparateRxId.Enabled = false;
					checkBox_SeparateRxId.Checked = false;
					textBox_Id.Enabled            = false;
					textBox_RxId.Enabled          = false;

					textBox_Id.Text   = "";
					textBox_RxId.Text = "";
				}

				checkBox_PrependPayloadByteLength.Checked = (Enabled ? this.reportFormat.PrependPayloadByteLength : false);
				checkBox_AppendTerminatingZero.Checked    = (Enabled ? this.reportFormat.AppendTerminatingZero : false);
			////checkBox_FillLastReport.Checked           = (Enabled ? this.reportFormat.FillLastReport : false);
				checkBox_FillLastReport.Checked           = true; // Windows HID.dll requires that output reports are always filled!

				reportFormatPreview.Format = this.reportFormat;

				if (Enabled)
				{
					comboBox_Preset.SelectedItem = (SerialHidDeviceSettingsPresetEx)this.preset;

					// Note that 'DropDownList' requires that an item like "[No preset selected]" is
					// listed. It is not possible to set the 'SelectedIndex' to 'ControlEx.InvalidIndex'
					// and then set an arbitrary 'Text';
				}
				else // Note that 'SelectionHelper' is not used for this 'DropDownList'-style ComboBox.
				{
					comboBox_Preset.SelectedIndex = ControlEx.InvalidIndex;
				}

				string linkText;
				string linkUri;
				if (((SerialHidDeviceSettingsPresetEx)preset).HasInfoLink(out linkText, out linkUri))
				{
					linkLabel_Info.Links.Clear();
					linkLabel_Info.Text = linkText;
					linkLabel_Info.Links.Add(0, linkText.Length, linkUri);
					linkLabel_Info.Visible = true;

					label_Line.Top = this.lineLabelTopDefault;
				}
				else
				{
					linkLabel_Info.Visible = false;

					label_Line.Top = this.lineLabelTopShifted; // Shift to middle of gap.
				}

				if (Enabled)
				{
					comboBox_FlowControl.SelectedItem = (SerialHidFlowControlEx)this.flowControl;
				}
				else
				{
					comboBox_FlowControl.SelectedIndex = ControlEx.InvalidIndex;
				}

				checkBox_AutoOpen.Checked = (Enabled ? this.autoOpen : false);
			}
			finally
			{
				this.isSettingControls.Leave();
			}
		}

		#endregion

		#region Event Raising
		//==========================================================================================
		// Event Raising
		//==========================================================================================

		/// <summary></summary>
		protected virtual void OnPresetChanged(EventArgs e)
		{
			// Note that update of dependent "ReportFormat" and "RxFilterUsage" is done inside the
			// "Preset" property, as those settings shall only be updated if not "Preset.None".

			EventHelper.RaiseSync(PresetChanged, this, e);
		}

		/// <summary></summary>
		protected virtual void OnReportFormatChanged(EventArgs e)
		{
			// Update the dependent "Preset" if needed (done here instead of multiple locations for convenience):
			if (((SerialHidDeviceSettingsPresetEx)Preset).ToReportFormat() != ReportFormat)
			{
				SerialHidDeviceSettingsPresetEx presetFromDeviceInfo = null;
				bool parseHasSucceeded = false;

				if (this.deviceInfo != null)
					parseHasSucceeded = SerialHidDeviceSettingsPresetEx.TryParse(this.deviceInfo, out presetFromDeviceInfo);

				if ((parseHasSucceeded) &&
				    (presetFromDeviceInfo != null) &&
				    (presetFromDeviceInfo.ToReportFormat() == ReportFormat) &&
				    (presetFromDeviceInfo.ToRxFilterUsage() == RxFilterUsage))
				{
					Preset = presetFromDeviceInfo; // Preset matching the device shall have precedence, e.g. 'MT_SerHid' rather than just 'ZeroTerminated'.
				}
				else
				{
					SerialHidDeviceSettingsPreset presetFromReportFormatAndRxFilterUsage;
					if (SerialHidDeviceSettingsPresetEx.TryFromReportFormatAndRxFilterUsage(ReportFormat, RxFilterUsage, out presetFromReportFormatAndRxFilterUsage))
						Preset = presetFromReportFormatAndRxFilterUsage;
					else
						Preset = SerialHidDeviceSettingsPreset.None;
				}
			}

			EventHelper.RaiseSync(ReportFormatChanged, this, e);
		}

		/// <summary></summary>
		protected virtual void OnRxFilterUsageChanged(EventArgs e)
		{
			// Update the dependent "Preset" if needed (done here instead of multiple locations for convenience):
			if (((SerialHidDeviceSettingsPresetEx)Preset).ToRxFilterUsage() != RxFilterUsage)
			{
				SerialHidDeviceSettingsPresetEx presetFromDeviceInfo = null;
				bool parseHasSucceeded = false;

				if (this.deviceInfo != null)
					parseHasSucceeded = SerialHidDeviceSettingsPresetEx.TryParse(this.deviceInfo, out presetFromDeviceInfo);

				if ((parseHasSucceeded) &&
				    (presetFromDeviceInfo != null) &&
				    (presetFromDeviceInfo.ToReportFormat() == ReportFormat) &&
				    (presetFromDeviceInfo.ToRxFilterUsage() == RxFilterUsage))
				{
					Preset = presetFromDeviceInfo; // Preset matching the device shall have precedence, e.g. 'MT_SerHid' rather than just 'ZeroTerminated'.
				}
				else
				{
					SerialHidDeviceSettingsPreset presetFromReportFormatAndRxFilterUsage;
					if (SerialHidDeviceSettingsPresetEx.TryFromReportFormatAndRxFilterUsage(ReportFormat, RxFilterUsage, out presetFromReportFormatAndRxFilterUsage))
						Preset = presetFromReportFormatAndRxFilterUsage;
					else
						Preset = SerialHidDeviceSettingsPreset.None;
				}
			}

			EventHelper.RaiseSync(RxFilterUsageChanged, this, e);
		}

		/// <summary></summary>
		protected virtual void OnFlowControlChanged(EventArgs e)
		{
			EventHelper.RaiseSync(FlowControlChanged, this, e);
		}

		/// <summary></summary>
		protected virtual void OnAutoOpenChanged(EventArgs e)
		{
			EventHelper.RaiseSync(AutoOpenChanged, this, e);
		}

		#endregion
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.View.Controls/UsbSerialHidDeviceSettings.cs $
//==================================================================================================
