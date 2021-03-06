//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Model/EventArgs.cs $
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
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Windows.Forms;

namespace YAT.Model
{
	/// <summary></summary>
	public class SavedEventArgs : EventArgs
	{
		/// <summary></summary>
		public string FilePath { get; }

		/// <summary>
		/// Auto save means that the settings have been saved at an automatically chosen location,
		/// without telling the user anything about it.
		/// </summary>
		public bool IsAutoSave { get; }

		/// <summary></summary>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public SavedEventArgs(string filePath, bool isAutoSave = false)
		{
			FilePath = filePath;
			IsAutoSave = isAutoSave;
		}
	}

	/// <summary></summary>
	public class TerminalEventArgs : EventArgs
	{
		/// <summary></summary>
		public Terminal Terminal { get; }

		/// <summary></summary>
		public int SequentialId { get; }

		/// <summary></summary>
		public int DynamicId { get; }

		/// <summary></summary>
		public int FixedId { get; }

		/// <summary></summary>
		public TerminalEventArgs(Terminal terminal, int sequentialId, int dynamicId, int fixedId)
		{
			Terminal     = terminal;

			SequentialId = sequentialId;
			DynamicId    = dynamicId;
			FixedId      = fixedId;
		}
	}

	/// <summary></summary>
	public class ClosedEventArgs : EventArgs
	{
		/// <summary></summary>
		public bool IsParentClose { get; }

		/// <summary></summary>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public ClosedEventArgs(bool isParentClose = false)
		{
			IsParentClose = isParentClose;
		}
	}

	/// <summary></summary>
	public class MessageInputEventArgs : EventArgs
	{
		/// <summary></summary>
		public string Text { get; }

		/// <summary></summary>
		public string Caption { get; }

		/// <summary></summary>
		public MessageBoxButtons Buttons { get; }

		/// <summary></summary>
		public MessageBoxIcon Icon { get; }

		/// <summary></summary>
		public MessageBoxDefaultButton DefaultButton { get; }

		/// <summary></summary>
		public DialogResult Result { get; set; }

		/// <summary></summary>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public MessageInputEventArgs(string text, string caption, MessageBoxButtons buttons = MessageBoxButtons.OK, MessageBoxIcon icon = MessageBoxIcon.None, MessageBoxDefaultButton defaultButton = MessageBoxDefaultButton.Button1)
		{
			Text          = text;
			Caption       = caption;
			Buttons       = buttons;
			Icon          = icon;
			DefaultButton = defaultButton;
		}
	}

	/// <summary></summary>
	public class ExtendedMessageInputEventArgs : MessageInputEventArgs
	{
		/// <summary></summary>
		public ICollection<LinkLabel.Link> Links { get; }

		/// <summary></summary>
		public string CheckText { get; }

		/// <summary></summary>
		public bool CheckValue { get; set; }

		/// <summary></summary>
		[SuppressMessage("Microsoft.Design", "CA1026:DefaultParametersShouldNotBeUsed", Justification = "Default parameters may result in cleaner code and clearly indicate the default behavior.")]
		public ExtendedMessageInputEventArgs(string text, ICollection<LinkLabel.Link> links, string caption, string checkText, bool checkValue, MessageBoxButtons buttons = MessageBoxButtons.OK, MessageBoxIcon icon = MessageBoxIcon.None, MessageBoxDefaultButton defaultButton = MessageBoxDefaultButton.Button1)
			: base(text, caption, buttons, icon, defaultButton)
		{
			Links      = links;
			CheckText  = checkText;
			CheckValue = checkValue;
		}
	}

	/// <summary></summary>
	public class DialogEventArgs : EventArgs
	{
		/// <summary></summary>
		public DialogResult Result { get; set; }

		/// <summary></summary>
		public DialogEventArgs()
		{
		}
	}

	/// <summary></summary>
	public class FilePathDialogEventArgs : EventArgs
	{
		/// <summary></summary>
		public string FilePathOld { get; }

		/// <summary></summary>
		public string FilePathNew { get; set; }

		/// <summary></summary>
		public DialogResult Result { get; set; }

		/// <summary></summary>
		public FilePathDialogEventArgs(string filePathOld)
		{
			FilePathOld = filePathOld;
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Model/EventArgs.cs $
//==================================================================================================
