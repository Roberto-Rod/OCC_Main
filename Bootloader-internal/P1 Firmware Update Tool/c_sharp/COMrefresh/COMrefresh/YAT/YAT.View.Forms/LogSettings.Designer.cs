using System;
using System.Collections.Generic;
using System.Text;

namespace YAT.View.Forms
{
	partial class LogSettings
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(LogSettings));
			this.button_Cancel = new System.Windows.Forms.Button();
			this.button_OK = new System.Windows.Forms.Button();
			this.groupBox_Settings = new System.Windows.Forms.GroupBox();
			this.groupBox_Control = new System.Windows.Forms.GroupBox();
			this.comboBox_Control_Extension = new MKY.Windows.Forms.ComboBoxEx();
			this.pathLabel_Control = new MKY.Windows.Forms.PathLabel();
			this.checkBox_Control = new System.Windows.Forms.CheckBox();
			this.groupBox_Options_TextEncoding = new System.Windows.Forms.GroupBox();
			this.checkBox_Options_EmitEncodingPreamble = new System.Windows.Forms.CheckBox();
			this.radioButton_Options_TextEncodingTerminal = new System.Windows.Forms.RadioButton();
			this.radioButton_Options_TextEncodingUTF8 = new System.Windows.Forms.RadioButton();
			this.button_OpenRootDirectory = new System.Windows.Forms.Button();
			this.pathLabel_RootAndBase = new MKY.Windows.Forms.PathLabel();
			this.groupBox_Options_Folders = new System.Windows.Forms.GroupBox();
			this.checkBox_Options_FolderType = new System.Windows.Forms.CheckBox();
			this.checkBox_Options_FolderDirection = new System.Windows.Forms.CheckBox();
			this.groupBox_Options_Name = new System.Windows.Forms.GroupBox();
			this.checkBox_Options_NameType = new System.Windows.Forms.CheckBox();
			this.comboBox_Options_NameSeparator = new MKY.Windows.Forms.ComboBoxEx();
			this.checkBox_Options_NameDirection = new System.Windows.Forms.CheckBox();
			this.checkBox_Options_NameTime = new System.Windows.Forms.CheckBox();
			this.checkBox_Options_NameDate = new System.Windows.Forms.CheckBox();
			this.label_Options_NameSeparator = new System.Windows.Forms.Label();
			this.groupBox_Options_Mode = new System.Windows.Forms.GroupBox();
			this.radioButton_Options_ModeCreate = new System.Windows.Forms.RadioButton();
			this.radioButton_Options_ModeAppend = new System.Windows.Forms.RadioButton();
			this.label_RootAndBase = new System.Windows.Forms.Label();
			this.button_ChangeRootAndBase = new System.Windows.Forms.Button();
			this.groupBox_Raw = new System.Windows.Forms.GroupBox();
			this.pathLabel_Raw_Rx = new MKY.Windows.Forms.PathLabel();
			this.pathLabel_Raw_Bidir = new MKY.Windows.Forms.PathLabel();
			this.pathLabel_Raw_Tx = new MKY.Windows.Forms.PathLabel();
			this.checkBox_Raw_Bidir = new System.Windows.Forms.CheckBox();
			this.label_Raw_Extension = new System.Windows.Forms.Label();
			this.comboBox_Raw_Extension = new MKY.Windows.Forms.ComboBoxEx();
			this.checkBox_Raw_Rx = new System.Windows.Forms.CheckBox();
			this.checkBox_Raw_Tx = new System.Windows.Forms.CheckBox();
			this.groupBox_Neat = new System.Windows.Forms.GroupBox();
			this.pathLabel_Neat_Rx = new MKY.Windows.Forms.PathLabel();
			this.pathLabel_Neat_Bidir = new MKY.Windows.Forms.PathLabel();
			this.pathLabel_Neat_Tx = new MKY.Windows.Forms.PathLabel();
			this.label_Neat_Extension = new System.Windows.Forms.Label();
			this.comboBox_Neat_Extension = new MKY.Windows.Forms.ComboBoxEx();
			this.checkBox_Neat_Rx = new System.Windows.Forms.CheckBox();
			this.checkBox_Neat_Bidir = new System.Windows.Forms.CheckBox();
			this.checkBox_Neat_Tx = new System.Windows.Forms.CheckBox();
			this.button_Defaults = new System.Windows.Forms.Button();
			this.toolTip = new System.Windows.Forms.ToolTip(this.components);
			this.checkBox_RequestSwitchOn = new System.Windows.Forms.CheckBox();
			this.checkBox_IsOn = new System.Windows.Forms.CheckBox();
			this.groupBox_Settings.SuspendLayout();
			this.groupBox_Control.SuspendLayout();
			this.groupBox_Options_TextEncoding.SuspendLayout();
			this.groupBox_Options_Folders.SuspendLayout();
			this.groupBox_Options_Name.SuspendLayout();
			this.groupBox_Options_Mode.SuspendLayout();
			this.groupBox_Raw.SuspendLayout();
			this.groupBox_Neat.SuspendLayout();
			this.SuspendLayout();
			// 
			// button_Cancel
			// 
			this.button_Cancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.button_Cancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.button_Cancel.Location = new System.Drawing.Point(539, 73);
			this.button_Cancel.Name = "button_Cancel";
			this.button_Cancel.Size = new System.Drawing.Size(75, 23);
			this.button_Cancel.TabIndex = 2;
			this.button_Cancel.Text = "Cancel";
			this.button_Cancel.UseVisualStyleBackColor = true;
			this.button_Cancel.Click += new System.EventHandler(this.button_Cancel_Click);
			// 
			// button_OK
			// 
			this.button_OK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.button_OK.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.button_OK.Location = new System.Drawing.Point(539, 44);
			this.button_OK.Name = "button_OK";
			this.button_OK.Size = new System.Drawing.Size(75, 23);
			this.button_OK.TabIndex = 1;
			this.button_OK.Text = "OK";
			this.button_OK.UseVisualStyleBackColor = true;
			this.button_OK.Click += new System.EventHandler(this.button_OK_Click);
			// 
			// groupBox_Settings
			// 
			this.groupBox_Settings.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.groupBox_Settings.Controls.Add(this.groupBox_Control);
			this.groupBox_Settings.Controls.Add(this.groupBox_Options_TextEncoding);
			this.groupBox_Settings.Controls.Add(this.button_OpenRootDirectory);
			this.groupBox_Settings.Controls.Add(this.pathLabel_RootAndBase);
			this.groupBox_Settings.Controls.Add(this.groupBox_Options_Folders);
			this.groupBox_Settings.Controls.Add(this.groupBox_Options_Name);
			this.groupBox_Settings.Controls.Add(this.groupBox_Options_Mode);
			this.groupBox_Settings.Controls.Add(this.label_RootAndBase);
			this.groupBox_Settings.Controls.Add(this.button_ChangeRootAndBase);
			this.groupBox_Settings.Controls.Add(this.groupBox_Raw);
			this.groupBox_Settings.Controls.Add(this.groupBox_Neat);
			this.groupBox_Settings.Location = new System.Drawing.Point(12, 12);
			this.groupBox_Settings.Name = "groupBox_Settings";
			this.groupBox_Settings.Size = new System.Drawing.Size(507, 497);
			this.groupBox_Settings.TabIndex = 0;
			this.groupBox_Settings.TabStop = false;
			// 
			// groupBox_Control
			// 
			this.groupBox_Control.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.groupBox_Control.Controls.Add(this.comboBox_Control_Extension);
			this.groupBox_Control.Controls.Add(this.pathLabel_Control);
			this.groupBox_Control.Controls.Add(this.checkBox_Control);
			this.groupBox_Control.Location = new System.Drawing.Point(6, 63);
			this.groupBox_Control.Name = "groupBox_Control";
			this.groupBox_Control.Size = new System.Drawing.Size(495, 55);
			this.groupBox_Control.TabIndex = 4;
			this.groupBox_Control.TabStop = false;
			this.groupBox_Control.Text = "I/O &Control";
			// 
			// comboBox_Control_Extension
			// 
			this.comboBox_Control_Extension.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.comboBox_Control_Extension.Location = new System.Drawing.Point(411, 19);
			this.comboBox_Control_Extension.Name = "comboBox_Control_Extension";
			this.comboBox_Control_Extension.Size = new System.Drawing.Size(72, 21);
			this.comboBox_Control_Extension.TabIndex = 2;
			this.toolTip.SetToolTip(this.comboBox_Control_Extension, resources.GetString("comboBox_Control_Extension.ToolTip"));
			this.comboBox_Control_Extension.TextChanged += new System.EventHandler(this.comboBox_Control_Extension_TextChanged);
			this.comboBox_Control_Extension.Validating += new System.ComponentModel.CancelEventHandler(this.comboBox_Control_Extension_Validating);
			// 
			// pathLabel_Control
			// 
			this.pathLabel_Control.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.pathLabel_Control.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.pathLabel_Control.Location = new System.Drawing.Point(179, 19);
			this.pathLabel_Control.Name = "pathLabel_Control";
			this.pathLabel_Control.Size = new System.Drawing.Size(220, 21);
			this.pathLabel_Control.TabIndex = 1;
			this.pathLabel_Control.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.pathLabel_Control.Click += new System.EventHandler(this.pathLabel_Control_Click);
			// 
			// checkBox_Control
			// 
			this.checkBox_Control.AutoSize = true;
			this.checkBox_Control.Location = new System.Drawing.Point(12, 22);
			this.checkBox_Control.Name = "checkBox_Control";
			this.checkBox_Control.Size = new System.Drawing.Size(133, 17);
			this.checkBox_Control.TabIndex = 0;
			this.checkBox_Control.Text = "Log I/O control events";
			this.toolTip.SetToolTip(this.checkBox_Control, resources.GetString("checkBox_Control.ToolTip"));
			this.checkBox_Control.UseVisualStyleBackColor = true;
			this.checkBox_Control.CheckedChanged += new System.EventHandler(this.checkBox_Control_CheckedChanged);
			// 
			// groupBox_Options_TextEncoding
			// 
			this.groupBox_Options_TextEncoding.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.groupBox_Options_TextEncoding.Controls.Add(this.checkBox_Options_EmitEncodingPreamble);
			this.groupBox_Options_TextEncoding.Controls.Add(this.radioButton_Options_TextEncodingTerminal);
			this.groupBox_Options_TextEncoding.Controls.Add(this.radioButton_Options_TextEncodingUTF8);
			this.groupBox_Options_TextEncoding.Location = new System.Drawing.Point(340, 416);
			this.groupBox_Options_TextEncoding.Name = "groupBox_Options_TextEncoding";
			this.groupBox_Options_TextEncoding.Size = new System.Drawing.Size(161, 75);
			this.groupBox_Options_TextEncoding.TabIndex = 10;
			this.groupBox_Options_TextEncoding.TabStop = false;
			this.groupBox_Options_TextEncoding.Text = "File &Encoding";
			this.toolTip.SetToolTip(this.groupBox_Options_TextEncoding, "Applies to plain text files.\r\nApplies to XML files except Base64 encoded raw data" +
        ".\r\nDoes not apply to RTF files which are limited to ASCII.");
			// 
			// checkBox_Options_EmitEncodingPreamble
			// 
			this.checkBox_Options_EmitEncodingPreamble.AutoSize = true;
			this.checkBox_Options_EmitEncodingPreamble.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
			this.checkBox_Options_EmitEncodingPreamble.Location = new System.Drawing.Point(61, 22);
			this.checkBox_Options_EmitEncodingPreamble.Name = "checkBox_Options_EmitEncodingPreamble";
			this.checkBox_Options_EmitEncodingPreamble.Size = new System.Drawing.Size(72, 17);
			this.checkBox_Options_EmitEncodingPreamble.TabIndex = 1;
			this.checkBox_Options_EmitEncodingPreamble.Text = "with BOM";
			this.toolTip.SetToolTip(this.checkBox_Options_EmitEncodingPreamble, "Chose whether the Unicode BOM (encoding preamble) is emitted to the beginning of " +
        "log files.\r\nTypically, UTF-8 encoded files contains a BOM. The default setting i" +
        "s therefore \"with BOM\".");
			this.checkBox_Options_EmitEncodingPreamble.UseVisualStyleBackColor = true;
			this.checkBox_Options_EmitEncodingPreamble.CheckedChanged += new System.EventHandler(this.checkBox_Options_EmitEncodingPreamble_CheckedChanged);
			// 
			// radioButton_Options_TextEncodingTerminal
			// 
			this.radioButton_Options_TextEncodingTerminal.AutoSize = true;
			this.radioButton_Options_TextEncodingTerminal.Location = new System.Drawing.Point(12, 45);
			this.radioButton_Options_TextEncodingTerminal.Name = "radioButton_Options_TextEncodingTerminal";
			this.radioButton_Options_TextEncodingTerminal.Size = new System.Drawing.Size(112, 17);
			this.radioButton_Options_TextEncodingTerminal.TabIndex = 2;
			this.radioButton_Options_TextEncodingTerminal.Text = "Terminal encoding";
			this.toolTip.SetToolTip(this.radioButton_Options_TextEncodingTerminal, "The selected encoding of the terminal. In case of Unicode encodings, the Unicode " +
        "BOM (Byte Order Mark) will be preceeded at the beginning of the file.");
			this.radioButton_Options_TextEncodingTerminal.UseVisualStyleBackColor = true;
			this.radioButton_Options_TextEncodingTerminal.CheckedChanged += new System.EventHandler(this.radioButton_Options_TextEncodingTerminal_CheckedChanged);
			// 
			// radioButton_Options_TextEncodingUTF8
			// 
			this.radioButton_Options_TextEncodingUTF8.AutoSize = true;
			this.radioButton_Options_TextEncodingUTF8.Checked = true;
			this.radioButton_Options_TextEncodingUTF8.Location = new System.Drawing.Point(12, 21);
			this.radioButton_Options_TextEncodingUTF8.Name = "radioButton_Options_TextEncodingUTF8";
			this.radioButton_Options_TextEncodingUTF8.Size = new System.Drawing.Size(55, 17);
			this.radioButton_Options_TextEncodingUTF8.TabIndex = 0;
			this.radioButton_Options_TextEncodingUTF8.TabStop = true;
			this.radioButton_Options_TextEncodingUTF8.Text = "UTF-8";
			this.toolTip.SetToolTip(this.radioButton_Options_TextEncodingUTF8, "UFT-8 is the default encoding. The Unicode BOM (Byte Order Mark) will be preceede" +
        "d at the beginning of the file.");
			this.radioButton_Options_TextEncodingUTF8.UseVisualStyleBackColor = true;
			this.radioButton_Options_TextEncodingUTF8.CheckedChanged += new System.EventHandler(this.radioButton_Options_TextEncodingUTF8_CheckedChanged);
			// 
			// button_OpenRootDirectory
			// 
			this.button_OpenRootDirectory.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.button_OpenRootDirectory.Image = global::YAT.View.Forms.Properties.Resources.Image_Tool_folder_explorer_16x16;
			this.button_OpenRootDirectory.Location = new System.Drawing.Point(458, 32);
			this.button_OpenRootDirectory.Name = "button_OpenRootDirectory";
			this.button_OpenRootDirectory.Size = new System.Drawing.Size(31, 23);
			this.button_OpenRootDirectory.TabIndex = 3;
			this.toolTip.SetToolTip(this.button_OpenRootDirectory, "Open folder...");
			this.button_OpenRootDirectory.UseVisualStyleBackColor = true;
			this.button_OpenRootDirectory.Click += new System.EventHandler(this.button_OpenRootDirectory_Click);
			// 
			// pathLabel_RootAndBase
			// 
			this.pathLabel_RootAndBase.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.pathLabel_RootAndBase.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.pathLabel_RootAndBase.Location = new System.Drawing.Point(18, 33);
			this.pathLabel_RootAndBase.Name = "pathLabel_RootAndBase";
			this.pathLabel_RootAndBase.Size = new System.Drawing.Size(387, 21);
			this.pathLabel_RootAndBase.TabIndex = 1;
			this.pathLabel_RootAndBase.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.toolTip.SetToolTip(this.pathLabel_RootAndBase, "Specifies the root directory as well as the file name base for the log files.\r\nTh" +
        "e effectively resulting file names are indicated by the boxes below.");
			this.pathLabel_RootAndBase.Click += new System.EventHandler(this.pathLabel_RootAndBase_Click);
			// 
			// groupBox_Options_Folders
			// 
			this.groupBox_Options_Folders.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.groupBox_Options_Folders.Controls.Add(this.checkBox_Options_FolderType);
			this.groupBox_Options_Folders.Controls.Add(this.checkBox_Options_FolderDirection);
			this.groupBox_Options_Folders.Location = new System.Drawing.Point(6, 416);
			this.groupBox_Options_Folders.Name = "groupBox_Options_Folders";
			this.groupBox_Options_Folders.Size = new System.Drawing.Size(161, 75);
			this.groupBox_Options_Folders.TabIndex = 8;
			this.groupBox_Options_Folders.TabStop = false;
			this.groupBox_Options_Folders.Text = "Create F&olders";
			// 
			// checkBox_Options_FolderType
			// 
			this.checkBox_Options_FolderType.AutoSize = true;
			this.checkBox_Options_FolderType.Location = new System.Drawing.Point(12, 22);
			this.checkBox_Options_FolderType.Name = "checkBox_Options_FolderType";
			this.checkBox_Options_FolderType.Size = new System.Drawing.Size(133, 17);
			this.checkBox_Options_FolderType.TabIndex = 0;
			this.checkBox_Options_FolderType.Text = "Type (Port/Raw/Neat)";
			this.checkBox_Options_FolderType.UseVisualStyleBackColor = true;
			this.checkBox_Options_FolderType.CheckedChanged += new System.EventHandler(this.checkBox_Options_FolderType_CheckedChanged);
			// 
			// checkBox_Options_FolderDirection
			// 
			this.checkBox_Options_FolderDirection.AutoSize = true;
			this.checkBox_Options_FolderDirection.Location = new System.Drawing.Point(12, 46);
			this.checkBox_Options_FolderDirection.Name = "checkBox_Options_FolderDirection";
			this.checkBox_Options_FolderDirection.Size = new System.Drawing.Size(132, 17);
			this.checkBox_Options_FolderDirection.TabIndex = 1;
			this.checkBox_Options_FolderDirection.Text = "Direction (Tx/Bidir/Rx)";
			this.checkBox_Options_FolderDirection.UseVisualStyleBackColor = true;
			this.checkBox_Options_FolderDirection.CheckedChanged += new System.EventHandler(this.checkBox_Options_FolderDirection_CheckedChanged);
			// 
			// groupBox_Options_Name
			// 
			this.groupBox_Options_Name.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.groupBox_Options_Name.Controls.Add(this.checkBox_Options_NameType);
			this.groupBox_Options_Name.Controls.Add(this.comboBox_Options_NameSeparator);
			this.groupBox_Options_Name.Controls.Add(this.checkBox_Options_NameDirection);
			this.groupBox_Options_Name.Controls.Add(this.checkBox_Options_NameTime);
			this.groupBox_Options_Name.Controls.Add(this.checkBox_Options_NameDate);
			this.groupBox_Options_Name.Controls.Add(this.label_Options_NameSeparator);
			this.groupBox_Options_Name.Location = new System.Drawing.Point(6, 334);
			this.groupBox_Options_Name.Name = "groupBox_Options_Name";
			this.groupBox_Options_Name.Size = new System.Drawing.Size(495, 76);
			this.groupBox_Options_Name.TabIndex = 7;
			this.groupBox_Options_Name.TabStop = false;
			this.groupBox_Options_Name.Text = "File N&aming";
			// 
			// checkBox_Options_NameType
			// 
			this.checkBox_Options_NameType.AutoSize = true;
			this.checkBox_Options_NameType.Location = new System.Drawing.Point(12, 22);
			this.checkBox_Options_NameType.Name = "checkBox_Options_NameType";
			this.checkBox_Options_NameType.Size = new System.Drawing.Size(133, 17);
			this.checkBox_Options_NameType.TabIndex = 0;
			this.checkBox_Options_NameType.Text = "Type (Port/Raw/Neat)";
			this.checkBox_Options_NameType.UseVisualStyleBackColor = true;
			this.checkBox_Options_NameType.CheckedChanged += new System.EventHandler(this.checkBox_Options_NameType_CheckedChanged);
			// 
			// comboBox_Options_NameSeparator
			// 
			this.comboBox_Options_NameSeparator.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.comboBox_Options_NameSeparator.Location = new System.Drawing.Point(334, 39);
			this.comboBox_Options_NameSeparator.Name = "comboBox_Options_NameSeparator";
			this.comboBox_Options_NameSeparator.Size = new System.Drawing.Size(149, 21);
			this.comboBox_Options_NameSeparator.TabIndex = 5;
			this.toolTip.SetToolTip(this.comboBox_Options_NameSeparator, "Either select a preset from the list, or fill in any valid sequence of characters" +
        ".\r\n\\ / : * ? \" < > | are invalid characters.\r\n\r\nContact YAT via \"Help > Request " +
        "Feature\" to request additional presets.");
			this.comboBox_Options_NameSeparator.TextChanged += new System.EventHandler(this.comboBox_Options_NameSeparator_TextChanged);
			this.comboBox_Options_NameSeparator.Validating += new System.ComponentModel.CancelEventHandler(this.comboBox_Options_NameSeparator_Validating);
			// 
			// checkBox_Options_NameDirection
			// 
			this.checkBox_Options_NameDirection.AutoSize = true;
			this.checkBox_Options_NameDirection.Location = new System.Drawing.Point(12, 46);
			this.checkBox_Options_NameDirection.Name = "checkBox_Options_NameDirection";
			this.checkBox_Options_NameDirection.Size = new System.Drawing.Size(132, 17);
			this.checkBox_Options_NameDirection.TabIndex = 1;
			this.checkBox_Options_NameDirection.Text = "Direction (Tx/Bidir/Rx)";
			this.checkBox_Options_NameDirection.UseVisualStyleBackColor = true;
			this.checkBox_Options_NameDirection.CheckedChanged += new System.EventHandler(this.checkBox_Options_NameDirection_CheckedChanged);
			// 
			// checkBox_Options_NameTime
			// 
			this.checkBox_Options_NameTime.AutoSize = true;
			this.checkBox_Options_NameTime.Location = new System.Drawing.Point(179, 46);
			this.checkBox_Options_NameTime.Name = "checkBox_Options_NameTime";
			this.checkBox_Options_NameTime.Size = new System.Drawing.Size(96, 17);
			this.checkBox_Options_NameTime.TabIndex = 3;
			this.checkBox_Options_NameTime.Text = "Time (hhmmss)";
			this.checkBox_Options_NameTime.UseVisualStyleBackColor = true;
			this.checkBox_Options_NameTime.CheckedChanged += new System.EventHandler(this.checkBox_Options_NameTime_CheckedChanged);
			// 
			// checkBox_Options_NameDate
			// 
			this.checkBox_Options_NameDate.AutoSize = true;
			this.checkBox_Options_NameDate.Location = new System.Drawing.Point(179, 22);
			this.checkBox_Options_NameDate.Name = "checkBox_Options_NameDate";
			this.checkBox_Options_NameDate.Size = new System.Drawing.Size(106, 17);
			this.checkBox_Options_NameDate.TabIndex = 2;
			this.checkBox_Options_NameDate.Text = "Date (yyyymmdd)";
			this.checkBox_Options_NameDate.UseVisualStyleBackColor = true;
			this.checkBox_Options_NameDate.CheckedChanged += new System.EventHandler(this.checkBox_Options_NameDate_CheckedChanged);
			// 
			// label_Options_NameSeparator
			// 
			this.label_Options_NameSeparator.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.label_Options_NameSeparator.AutoSize = true;
			this.label_Options_NameSeparator.Location = new System.Drawing.Point(331, 23);
			this.label_Options_NameSeparator.Name = "label_Options_NameSeparator";
			this.label_Options_NameSeparator.Size = new System.Drawing.Size(56, 13);
			this.label_Options_NameSeparator.TabIndex = 4;
			this.label_Options_NameSeparator.Text = "Separator:";
			// 
			// groupBox_Options_Mode
			// 
			this.groupBox_Options_Mode.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.groupBox_Options_Mode.Controls.Add(this.radioButton_Options_ModeCreate);
			this.groupBox_Options_Mode.Controls.Add(this.radioButton_Options_ModeAppend);
			this.groupBox_Options_Mode.Location = new System.Drawing.Point(173, 416);
			this.groupBox_Options_Mode.Name = "groupBox_Options_Mode";
			this.groupBox_Options_Mode.Size = new System.Drawing.Size(161, 75);
			this.groupBox_Options_Mode.TabIndex = 9;
			this.groupBox_Options_Mode.TabStop = false;
			this.groupBox_Options_Mode.Text = "File Write &Mode";
			// 
			// radioButton_Options_ModeCreate
			// 
			this.radioButton_Options_ModeCreate.AutoSize = true;
			this.radioButton_Options_ModeCreate.Checked = true;
			this.radioButton_Options_ModeCreate.Location = new System.Drawing.Point(12, 21);
			this.radioButton_Options_ModeCreate.Name = "radioButton_Options_ModeCreate";
			this.radioButton_Options_ModeCreate.Size = new System.Drawing.Size(121, 17);
			this.radioButton_Options_ModeCreate.TabIndex = 0;
			this.radioButton_Options_ModeCreate.TabStop = true;
			this.radioButton_Options_ModeCreate.Text = "Create separate files";
			this.radioButton_Options_ModeCreate.UseVisualStyleBackColor = true;
			this.radioButton_Options_ModeCreate.CheckedChanged += new System.EventHandler(this.radioButton_Options_ModeCreate_CheckedChanged);
			// 
			// radioButton_Options_ModeAppend
			// 
			this.radioButton_Options_ModeAppend.AutoSize = true;
			this.radioButton_Options_ModeAppend.Location = new System.Drawing.Point(12, 45);
			this.radioButton_Options_ModeAppend.Name = "radioButton_Options_ModeAppend";
			this.radioButton_Options_ModeAppend.Size = new System.Drawing.Size(115, 17);
			this.radioButton_Options_ModeAppend.TabIndex = 1;
			this.radioButton_Options_ModeAppend.Text = "Append if file exists";
			this.radioButton_Options_ModeAppend.UseVisualStyleBackColor = true;
			this.radioButton_Options_ModeAppend.CheckedChanged += new System.EventHandler(this.radioButton_Options_ModeAppend_CheckedChanged);
			// 
			// label_RootAndBase
			// 
			this.label_RootAndBase.AutoSize = true;
			this.label_RootAndBase.Location = new System.Drawing.Point(12, 16);
			this.label_RootAndBase.Name = "label_RootAndBase";
			this.label_RootAndBase.Size = new System.Drawing.Size(168, 13);
			this.label_RootAndBase.TabIndex = 0;
			this.label_RootAndBase.Text = "&Root directory and file name base:";
			// 
			// button_ChangeRootAndBase
			// 
			this.button_ChangeRootAndBase.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.button_ChangeRootAndBase.Location = new System.Drawing.Point(417, 32);
			this.button_ChangeRootAndBase.Name = "button_ChangeRootAndBase";
			this.button_ChangeRootAndBase.Size = new System.Drawing.Size(31, 23);
			this.button_ChangeRootAndBase.TabIndex = 2;
			this.button_ChangeRootAndBase.Text = "...";
			this.toolTip.SetToolTip(this.button_ChangeRootAndBase, "Change...");
			this.button_ChangeRootAndBase.UseVisualStyleBackColor = true;
			this.button_ChangeRootAndBase.Click += new System.EventHandler(this.button_ChangeRootAndBase_Click);
			// 
			// groupBox_Raw
			// 
			this.groupBox_Raw.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.groupBox_Raw.Controls.Add(this.pathLabel_Raw_Rx);
			this.groupBox_Raw.Controls.Add(this.pathLabel_Raw_Bidir);
			this.groupBox_Raw.Controls.Add(this.pathLabel_Raw_Tx);
			this.groupBox_Raw.Controls.Add(this.checkBox_Raw_Bidir);
			this.groupBox_Raw.Controls.Add(this.label_Raw_Extension);
			this.groupBox_Raw.Controls.Add(this.comboBox_Raw_Extension);
			this.groupBox_Raw.Controls.Add(this.checkBox_Raw_Rx);
			this.groupBox_Raw.Controls.Add(this.checkBox_Raw_Tx);
			this.groupBox_Raw.Location = new System.Drawing.Point(6, 124);
			this.groupBox_Raw.Name = "groupBox_Raw";
			this.groupBox_Raw.Size = new System.Drawing.Size(495, 99);
			this.groupBox_Raw.TabIndex = 5;
			this.groupBox_Raw.TabStop = false;
			this.groupBox_Raw.Text = "Ra&w Data";
			this.toolTip.SetToolTip(this.groupBox_Raw, "Bytes as transmitted over serial interface");
			// 
			// pathLabel_Raw_Rx
			// 
			this.pathLabel_Raw_Rx.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.pathLabel_Raw_Rx.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.pathLabel_Raw_Rx.Location = new System.Drawing.Point(179, 65);
			this.pathLabel_Raw_Rx.Name = "pathLabel_Raw_Rx";
			this.pathLabel_Raw_Rx.Size = new System.Drawing.Size(220, 21);
			this.pathLabel_Raw_Rx.TabIndex = 5;
			this.pathLabel_Raw_Rx.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.pathLabel_Raw_Rx.Click += new System.EventHandler(this.pathLabel_Raw_Rx_Click);
			// 
			// pathLabel_Raw_Bidir
			// 
			this.pathLabel_Raw_Bidir.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.pathLabel_Raw_Bidir.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.pathLabel_Raw_Bidir.Location = new System.Drawing.Point(179, 42);
			this.pathLabel_Raw_Bidir.Name = "pathLabel_Raw_Bidir";
			this.pathLabel_Raw_Bidir.Size = new System.Drawing.Size(220, 21);
			this.pathLabel_Raw_Bidir.TabIndex = 3;
			this.pathLabel_Raw_Bidir.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.pathLabel_Raw_Bidir.Click += new System.EventHandler(this.pathLabel_Raw_Bidir_Click);
			// 
			// pathLabel_Raw_Tx
			// 
			this.pathLabel_Raw_Tx.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.pathLabel_Raw_Tx.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.pathLabel_Raw_Tx.Location = new System.Drawing.Point(179, 19);
			this.pathLabel_Raw_Tx.Name = "pathLabel_Raw_Tx";
			this.pathLabel_Raw_Tx.Size = new System.Drawing.Size(220, 21);
			this.pathLabel_Raw_Tx.TabIndex = 1;
			this.pathLabel_Raw_Tx.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.pathLabel_Raw_Tx.Click += new System.EventHandler(this.pathLabel_Raw_Tx_Click);
			// 
			// checkBox_Raw_Bidir
			// 
			this.checkBox_Raw_Bidir.AutoSize = true;
			this.checkBox_Raw_Bidir.Location = new System.Drawing.Point(12, 45);
			this.checkBox_Raw_Bidir.Name = "checkBox_Raw_Bidir";
			this.checkBox_Raw_Bidir.Size = new System.Drawing.Size(156, 17);
			this.checkBox_Raw_Bidir.TabIndex = 2;
			this.checkBox_Raw_Bidir.Text = "Log bidirectional data (Bidir)";
			this.checkBox_Raw_Bidir.UseVisualStyleBackColor = true;
			this.checkBox_Raw_Bidir.CheckedChanged += new System.EventHandler(this.checkBox_Raw_Bidir_CheckedChanged);
			// 
			// label_Raw_Extension
			// 
			this.label_Raw_Extension.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.label_Raw_Extension.AutoSize = true;
			this.label_Raw_Extension.Location = new System.Drawing.Point(408, 25);
			this.label_Raw_Extension.Name = "label_Raw_Extension";
			this.label_Raw_Extension.Size = new System.Drawing.Size(56, 13);
			this.label_Raw_Extension.TabIndex = 6;
			this.label_Raw_Extension.Text = "Extension:";
			// 
			// comboBox_Raw_Extension
			// 
			this.comboBox_Raw_Extension.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.comboBox_Raw_Extension.Location = new System.Drawing.Point(411, 41);
			this.comboBox_Raw_Extension.Name = "comboBox_Raw_Extension";
			this.comboBox_Raw_Extension.Size = new System.Drawing.Size(72, 21);
			this.comboBox_Raw_Extension.TabIndex = 7;
			this.toolTip.SetToolTip(this.comboBox_Raw_Extension, resources.GetString("comboBox_Raw_Extension.ToolTip"));
			this.comboBox_Raw_Extension.TextChanged += new System.EventHandler(this.comboBox_Raw_Extension_TextChanged);
			this.comboBox_Raw_Extension.Validating += new System.ComponentModel.CancelEventHandler(this.comboBox_Raw_Extension_Validating);
			// 
			// checkBox_Raw_Rx
			// 
			this.checkBox_Raw_Rx.AutoSize = true;
			this.checkBox_Raw_Rx.Location = new System.Drawing.Point(12, 68);
			this.checkBox_Raw_Rx.Name = "checkBox_Raw_Rx";
			this.checkBox_Raw_Rx.Size = new System.Drawing.Size(134, 17);
			this.checkBox_Raw_Rx.TabIndex = 4;
			this.checkBox_Raw_Rx.Text = "Log received data (Rx)";
			this.checkBox_Raw_Rx.UseVisualStyleBackColor = true;
			this.checkBox_Raw_Rx.CheckedChanged += new System.EventHandler(this.checkBox_Raw_Rx_CheckedChanged);
			// 
			// checkBox_Raw_Tx
			// 
			this.checkBox_Raw_Tx.AutoSize = true;
			this.checkBox_Raw_Tx.Location = new System.Drawing.Point(12, 22);
			this.checkBox_Raw_Tx.Name = "checkBox_Raw_Tx";
			this.checkBox_Raw_Tx.Size = new System.Drawing.Size(112, 17);
			this.checkBox_Raw_Tx.TabIndex = 0;
			this.checkBox_Raw_Tx.Text = "Log sent data (Tx)";
			this.checkBox_Raw_Tx.UseVisualStyleBackColor = true;
			this.checkBox_Raw_Tx.CheckedChanged += new System.EventHandler(this.checkBox_Raw_Tx_CheckedChanged);
			// 
			// groupBox_Neat
			// 
			this.groupBox_Neat.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.groupBox_Neat.Controls.Add(this.pathLabel_Neat_Rx);
			this.groupBox_Neat.Controls.Add(this.pathLabel_Neat_Bidir);
			this.groupBox_Neat.Controls.Add(this.pathLabel_Neat_Tx);
			this.groupBox_Neat.Controls.Add(this.label_Neat_Extension);
			this.groupBox_Neat.Controls.Add(this.comboBox_Neat_Extension);
			this.groupBox_Neat.Controls.Add(this.checkBox_Neat_Rx);
			this.groupBox_Neat.Controls.Add(this.checkBox_Neat_Bidir);
			this.groupBox_Neat.Controls.Add(this.checkBox_Neat_Tx);
			this.groupBox_Neat.Location = new System.Drawing.Point(6, 229);
			this.groupBox_Neat.Name = "groupBox_Neat";
			this.groupBox_Neat.Size = new System.Drawing.Size(495, 99);
			this.groupBox_Neat.TabIndex = 6;
			this.groupBox_Neat.TabStop = false;
			this.groupBox_Neat.Text = "Neat &Format";
			this.toolTip.SetToolTip(this.groupBox_Neat, "Time stamp, radix, length,... formatted as in monitor view");
			// 
			// pathLabel_Neat_Rx
			// 
			this.pathLabel_Neat_Rx.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.pathLabel_Neat_Rx.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.pathLabel_Neat_Rx.Location = new System.Drawing.Point(179, 65);
			this.pathLabel_Neat_Rx.Name = "pathLabel_Neat_Rx";
			this.pathLabel_Neat_Rx.Size = new System.Drawing.Size(220, 21);
			this.pathLabel_Neat_Rx.TabIndex = 5;
			this.pathLabel_Neat_Rx.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.pathLabel_Neat_Rx.Click += new System.EventHandler(this.pathLabel_Neat_Rx_Click);
			// 
			// pathLabel_Neat_Bidir
			// 
			this.pathLabel_Neat_Bidir.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.pathLabel_Neat_Bidir.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.pathLabel_Neat_Bidir.Location = new System.Drawing.Point(179, 42);
			this.pathLabel_Neat_Bidir.Name = "pathLabel_Neat_Bidir";
			this.pathLabel_Neat_Bidir.Size = new System.Drawing.Size(220, 21);
			this.pathLabel_Neat_Bidir.TabIndex = 3;
			this.pathLabel_Neat_Bidir.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.pathLabel_Neat_Bidir.Click += new System.EventHandler(this.pathLabel_Neat_Bidir_Click);
			// 
			// pathLabel_Neat_Tx
			// 
			this.pathLabel_Neat_Tx.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.pathLabel_Neat_Tx.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.pathLabel_Neat_Tx.Location = new System.Drawing.Point(179, 19);
			this.pathLabel_Neat_Tx.Name = "pathLabel_Neat_Tx";
			this.pathLabel_Neat_Tx.Size = new System.Drawing.Size(220, 21);
			this.pathLabel_Neat_Tx.TabIndex = 1;
			this.pathLabel_Neat_Tx.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.pathLabel_Neat_Tx.Click += new System.EventHandler(this.pathLabel_Neat_Tx_Click);
			// 
			// label_Neat_Extension
			// 
			this.label_Neat_Extension.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.label_Neat_Extension.AutoSize = true;
			this.label_Neat_Extension.Location = new System.Drawing.Point(408, 26);
			this.label_Neat_Extension.Name = "label_Neat_Extension";
			this.label_Neat_Extension.Size = new System.Drawing.Size(56, 13);
			this.label_Neat_Extension.TabIndex = 6;
			this.label_Neat_Extension.Text = "Extension:";
			// 
			// comboBox_Neat_Extension
			// 
			this.comboBox_Neat_Extension.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.comboBox_Neat_Extension.Location = new System.Drawing.Point(411, 42);
			this.comboBox_Neat_Extension.Name = "comboBox_Neat_Extension";
			this.comboBox_Neat_Extension.Size = new System.Drawing.Size(72, 21);
			this.comboBox_Neat_Extension.TabIndex = 7;
			this.toolTip.SetToolTip(this.comboBox_Neat_Extension, resources.GetString("comboBox_Neat_Extension.ToolTip"));
			this.comboBox_Neat_Extension.TextChanged += new System.EventHandler(this.comboBox_Neat_Extension_TextChanged);
			this.comboBox_Neat_Extension.Validating += new System.ComponentModel.CancelEventHandler(this.comboBox_Neat_Extension_Validating);
			// 
			// checkBox_Neat_Rx
			// 
			this.checkBox_Neat_Rx.AutoSize = true;
			this.checkBox_Neat_Rx.Location = new System.Drawing.Point(12, 68);
			this.checkBox_Neat_Rx.Name = "checkBox_Neat_Rx";
			this.checkBox_Neat_Rx.Size = new System.Drawing.Size(134, 17);
			this.checkBox_Neat_Rx.TabIndex = 4;
			this.checkBox_Neat_Rx.Text = "Log received data (Rx)";
			this.checkBox_Neat_Rx.UseVisualStyleBackColor = true;
			this.checkBox_Neat_Rx.CheckedChanged += new System.EventHandler(this.checkBox_Neat_Rx_CheckedChanged);
			// 
			// checkBox_Neat_Bidir
			// 
			this.checkBox_Neat_Bidir.AutoSize = true;
			this.checkBox_Neat_Bidir.Location = new System.Drawing.Point(12, 45);
			this.checkBox_Neat_Bidir.Name = "checkBox_Neat_Bidir";
			this.checkBox_Neat_Bidir.Size = new System.Drawing.Size(156, 17);
			this.checkBox_Neat_Bidir.TabIndex = 2;
			this.checkBox_Neat_Bidir.Text = "Log bidirectional data (Bidir)";
			this.checkBox_Neat_Bidir.UseVisualStyleBackColor = true;
			this.checkBox_Neat_Bidir.CheckedChanged += new System.EventHandler(this.checkBox_Neat_Bidir_CheckedChanged);
			// 
			// checkBox_Neat_Tx
			// 
			this.checkBox_Neat_Tx.AutoSize = true;
			this.checkBox_Neat_Tx.Location = new System.Drawing.Point(12, 22);
			this.checkBox_Neat_Tx.Name = "checkBox_Neat_Tx";
			this.checkBox_Neat_Tx.Size = new System.Drawing.Size(112, 17);
			this.checkBox_Neat_Tx.TabIndex = 0;
			this.checkBox_Neat_Tx.Text = "Log sent data (Tx)";
			this.checkBox_Neat_Tx.UseVisualStyleBackColor = true;
			this.checkBox_Neat_Tx.CheckedChanged += new System.EventHandler(this.checkBox_Neat_Tx_CheckedChanged);
			// 
			// button_Defaults
			// 
			this.button_Defaults.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.button_Defaults.Location = new System.Drawing.Point(539, 119);
			this.button_Defaults.Name = "button_Defaults";
			this.button_Defaults.Size = new System.Drawing.Size(75, 23);
			this.button_Defaults.TabIndex = 3;
			this.button_Defaults.Text = "&Defaults...";
			this.button_Defaults.UseVisualStyleBackColor = true;
			this.button_Defaults.Click += new System.EventHandler(this.button_Defaults_Click);
			// 
			// checkBox_RequestSwitchOn
			// 
			this.checkBox_RequestSwitchOn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.checkBox_RequestSwitchOn.CheckAlign = System.Drawing.ContentAlignment.BottomCenter;
			this.checkBox_RequestSwitchOn.Image = global::YAT.View.Forms.Properties.Resources.Image_Tool_accept_document_16x16;
			this.checkBox_RequestSwitchOn.Location = new System.Drawing.Point(525, 215);
			this.checkBox_RequestSwitchOn.Name = "checkBox_RequestSwitchOn";
			this.checkBox_RequestSwitchOn.Size = new System.Drawing.Size(103, 42);
			this.checkBox_RequestSwitchOn.TabIndex = 4;
			this.checkBox_RequestSwitchOn.Text = "Switch log o&n";
			this.checkBox_RequestSwitchOn.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			this.checkBox_RequestSwitchOn.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
			this.checkBox_RequestSwitchOn.UseVisualStyleBackColor = true;
			this.checkBox_RequestSwitchOn.CheckedChanged += new System.EventHandler(this.checkBox_RequestSwitchOn_CheckedChanged);
			// 
			// checkBox_IsOn
			// 
			this.checkBox_IsOn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.checkBox_IsOn.CheckAlign = System.Drawing.ContentAlignment.BottomCenter;
			this.checkBox_IsOn.Image = global::YAT.View.Forms.Properties.Resources.Image_Tool_accept_document_16x16;
			this.checkBox_IsOn.Location = new System.Drawing.Point(525, 215);
			this.checkBox_IsOn.Name = "checkBox_IsOn";
			this.checkBox_IsOn.Size = new System.Drawing.Size(103, 42);
			this.checkBox_IsOn.TabIndex = 5;
			this.checkBox_IsOn.Text = "Log is o&n";
			this.checkBox_IsOn.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			this.checkBox_IsOn.TextImageRelation = System.Windows.Forms.TextImageRelation.TextBeforeImage;
			this.checkBox_IsOn.UseVisualStyleBackColor = true;
			this.checkBox_IsOn.CheckedChanged += new System.EventHandler(this.checkBox_IsOn_CheckedChanged);
			// 
			// LogSettings
			// 
			this.AcceptButton = this.button_OK;
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.button_Cancel;
			this.ClientSize = new System.Drawing.Size(629, 521);
			this.Controls.Add(this.groupBox_Settings);
			this.Controls.Add(this.button_Defaults);
			this.Controls.Add(this.button_Cancel);
			this.Controls.Add(this.button_OK);
			this.Controls.Add(this.checkBox_RequestSwitchOn);
			this.Controls.Add(this.checkBox_IsOn);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "LogSettings";
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Log Settings";
			this.Deactivate += new System.EventHandler(this.LogSettings_Deactivate);
			this.Shown += new System.EventHandler(this.LogSettings_Shown);
			this.groupBox_Settings.ResumeLayout(false);
			this.groupBox_Settings.PerformLayout();
			this.groupBox_Control.ResumeLayout(false);
			this.groupBox_Control.PerformLayout();
			this.groupBox_Options_TextEncoding.ResumeLayout(false);
			this.groupBox_Options_TextEncoding.PerformLayout();
			this.groupBox_Options_Folders.ResumeLayout(false);
			this.groupBox_Options_Folders.PerformLayout();
			this.groupBox_Options_Name.ResumeLayout(false);
			this.groupBox_Options_Name.PerformLayout();
			this.groupBox_Options_Mode.ResumeLayout(false);
			this.groupBox_Options_Mode.PerformLayout();
			this.groupBox_Raw.ResumeLayout(false);
			this.groupBox_Raw.PerformLayout();
			this.groupBox_Neat.ResumeLayout(false);
			this.groupBox_Neat.PerformLayout();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.GroupBox groupBox_Raw;
		private MKY.Windows.Forms.ComboBoxEx comboBox_Options_NameSeparator;
		private System.Windows.Forms.CheckBox checkBox_Options_NameDirection;
		private System.Windows.Forms.CheckBox checkBox_Options_NameTime;
		private System.Windows.Forms.CheckBox checkBox_Options_NameDate;
		private System.Windows.Forms.Label label_Options_NameSeparator;
		private System.Windows.Forms.CheckBox checkBox_Options_FolderDirection;
		private System.Windows.Forms.GroupBox groupBox_Options_Mode;
		private System.Windows.Forms.RadioButton radioButton_Options_ModeCreate;
		private System.Windows.Forms.RadioButton radioButton_Options_ModeAppend;
		private System.Windows.Forms.GroupBox groupBox_Options_Name;
		private System.Windows.Forms.GroupBox groupBox_Options_Folders;
		private System.Windows.Forms.Label label_Raw_Extension;
		private MKY.Windows.Forms.ComboBoxEx comboBox_Raw_Extension;
		private System.Windows.Forms.CheckBox checkBox_Raw_Rx;
		private System.Windows.Forms.CheckBox checkBox_Raw_Tx;
		private System.Windows.Forms.GroupBox groupBox_Neat;
		private System.Windows.Forms.CheckBox checkBox_Raw_Bidir;
		private System.Windows.Forms.GroupBox groupBox_Settings;
		private MKY.Windows.Forms.ComboBoxEx comboBox_Neat_Extension;
		private System.Windows.Forms.Label label_Neat_Extension;
		private System.Windows.Forms.CheckBox checkBox_Neat_Tx;
		private System.Windows.Forms.CheckBox checkBox_Neat_Bidir;
		private System.Windows.Forms.CheckBox checkBox_Neat_Rx;
		private System.Windows.Forms.Button button_ChangeRootAndBase;
		private System.Windows.Forms.Label label_RootAndBase;
		private System.Windows.Forms.Button button_Cancel;
		private System.Windows.Forms.Button button_OK;
		private System.Windows.Forms.CheckBox checkBox_Options_FolderType;
		private System.Windows.Forms.CheckBox checkBox_Options_NameType;
		private MKY.Windows.Forms.PathLabel pathLabel_RootAndBase;
		private MKY.Windows.Forms.PathLabel pathLabel_Raw_Rx;
		private MKY.Windows.Forms.PathLabel pathLabel_Raw_Bidir;
		private MKY.Windows.Forms.PathLabel pathLabel_Raw_Tx;
		private MKY.Windows.Forms.PathLabel pathLabel_Neat_Rx;
		private MKY.Windows.Forms.PathLabel pathLabel_Neat_Bidir;
		private MKY.Windows.Forms.PathLabel pathLabel_Neat_Tx;
		private System.Windows.Forms.Button button_Defaults;
		private System.Windows.Forms.ToolTip toolTip;
		private System.Windows.Forms.Button button_OpenRootDirectory;
		private System.Windows.Forms.GroupBox groupBox_Options_TextEncoding;
		private System.Windows.Forms.RadioButton radioButton_Options_TextEncodingTerminal;
		private System.Windows.Forms.RadioButton radioButton_Options_TextEncodingUTF8;
		private System.Windows.Forms.CheckBox checkBox_Options_EmitEncodingPreamble;
		private System.Windows.Forms.GroupBox groupBox_Control;
		private MKY.Windows.Forms.PathLabel pathLabel_Control;
		private System.Windows.Forms.CheckBox checkBox_Control;
		private MKY.Windows.Forms.ComboBoxEx comboBox_Control_Extension;
		private System.Windows.Forms.CheckBox checkBox_RequestSwitchOn;
		private System.Windows.Forms.CheckBox checkBox_IsOn;
	}
}
