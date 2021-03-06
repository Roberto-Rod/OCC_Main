//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.View.Controls/Monitor.cs $
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

#region Configuration
//==================================================================================================
// Configuration
//==================================================================================================

// \remind (MKY 2013-05-25) (related to feature request #163)
// No feasible way to implement horizontal auto-scroll found. There are Win32 API functions to move
// the position of the scroll bar itself, and to scroll rectangles, but it is not feasible to do the
// whole translation from .NET Windows.Forms to Win32. Giving up.

// Enable to continue working/testing with an automatic horizontally scrolling list box:
//#define ENABLE_HORIZONTAL_AUTO_SCROLL

#if (DEBUG)

	// Enable debugging of monitor content:
////#define DEBUG_CONTENT              // 'DebugEnabled' is only preset for the 'Bidir' monitor.

	// Enable debugging of update management (incl. CPU performance measurement):
////#define DEBUG_UPDATE               // 'DebugEnabled' is only preset for the 'Bidir' monitor.

	// Enable debugging of vertical semi-auto-scrolling:
////#define DEBUG_VERTICAL_AUTO_SCROLL // 'DebugEnabled' is only preset for the 'Bidir' monitor.

	// Enable debugging of calls to "ListBox.[Set|Clear]Selected()":
////#define DEBUG_SELECTION            // 'DebugEnabled' is only preset for the 'Bidir' monitor.

#endif // DEBUG

#endregion

#region Using
//==================================================================================================
// Using
//==================================================================================================

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Drawing;
using System.Globalization;
using System.Runtime.CompilerServices;
using System.Text.RegularExpressions;
using System.Threading;
using System.Windows.Forms;

using MKY;
using MKY.Collections;
using MKY.Collections.Specialized;
using MKY.Contracts;
using MKY.Diagnostics;
using MKY.Windows.Forms;

using YAT.Application.Types;
using YAT.Format.Settings;

#endregion

namespace YAT.View.Controls
{
	/// <summary>
	/// This monitor implements a list box based terminal monitor in a speed optimized way.
	/// </summary>
	[SuppressMessage("StyleCop.CSharp.OrderingRules", "SA1203:ConstantsMustAppearBeforeFields", Justification = "Semantic of readonly fields is constant.")]
	public partial class Monitor : UserControl
	{
		#region Types
		//==========================================================================================
		// Types
		//==========================================================================================

		private enum OpacityState
		{
			Inactive,
			Incrementing,
			Decrementing
		}

		private enum ClearResult
		{
			NoElementOrLinePending,
			HasClearedAndCompleted,
			HasClearedButIsIncomplete,
			NoLineOngoing
		}

		#endregion

		#region Constants
		//==========================================================================================
		// Constants
		//==========================================================================================

		private const bool ShowStatusPanelDefault = true;
		private const Domain.RepositoryType RepositoryTypeDefault = Domain.RepositoryType.None;

		// State:
		private const MonitorActivityState  ActivityStateDefault  = MonitorActivityState.Inactive;
		private const double MinImageOpacity       =  0.20; //  20%
		private const double MaxImageOpacity       =  1.00; // 100%
		private const double ImageOpacityIncrement = +0.10; // +10% resulting in approx. 2 s intervals
		private const double ImageOpacityDecrement = -0.10; // -10%            (timer has 100 ms ticks)

		// Lines:
		private const int MaxLineCountDefault = Domain.Settings.DisplaySettings.MaxLineCountDefault;

		// Line numbers:
		private const int VerticalScrollBarWidth = 18;
		private const int AdditionalMargin = 4;
		private const bool ShowLineNumbersDefault = Domain.Settings.DisplaySettings.ShowLineNumbersDefault;
		private const Domain.Utilities.LineNumberSelection LineNumberSelectionDefault = Domain.Settings.DisplaySettings.LineNumberSelectionDefault;

		// Status:
		private const bool ShowTimeStatusDefault = false;
		private const bool ShowDataStatusDefault = false;

		// Copy of active line:
		private const bool ShowCopyOfActiveLineDefault = false;

		// Update:
		private const int DataStatusIntervalMs = 31; // Interval shall be quite short => fixed to 31 ms (a prime number) = approx. 32 updates per second.

		[SuppressMessage("StyleCop.CSharp.NamingRules", "SA1306:FieldNamesMustBeginWithLowerCaseLetter", Justification = "This is a 'readonly', thus meant to be constant.")]
		private readonly long DataStatusTickInterval = StopwatchEx.TimeToTicks(DataStatusIntervalMs);

		#endregion

		#region Fields
		//==========================================================================================
		// Fields
		//==========================================================================================

		private bool showStatusPanel = ShowStatusPanelDefault;
		private Domain.RepositoryType repositoryType = RepositoryTypeDefault;

		// State:
		private MonitorActivityState activityState = ActivityStateDefault;
		private MonitorActivityState activityStateOld = ActivityStateDefault;
		private Image imageInactive = null;
		private Image imageActive = null;
		private OpacityState imageOpacityState = OpacityState.Inactive;
		private double imageOpacity = MinImageOpacity;

		// Lines:
		private int maxLineCount = MaxLineCountDefault;
		private FormatSettings formatSettings = new FormatSettings();

		// Line numbers:
		private long lineNumberOffset;
		private int initialLineNumberWidth;
		private int currentLineNumberWidth;
		private bool showLineNumbers = ShowLineNumbersDefault;
		private Domain.Utilities.LineNumberSelection lineNumberSelection = LineNumberSelectionDefault;

		// Status:
		private bool showTimeStatus = ShowTimeStatusDefault;
		private MonitorTimeStatusHelper timeStatusHelper;
		private bool showDataStatus = ShowDataStatusDefault;
		private MonitorDataStatusHelper dataStatusHelper;

		// Copy of active line:
		private bool showCopyOfActiveLine = ShowCopyOfActiveLineDefault;

		// Find:
		private string findText; // = null;
		private bool findTextCaseSensitive; // = false;
		private bool findTextWholeWord; // = false;
		private Regex findRegex; // = null;
		private bool isFirstFindOnEdit = true;
		private int findOnEditStartIndex = ControlEx.InvalidIndex;
		private int lastFindIndex = ListBox.NoMatches;
		private bool findAllIsActive; // = false;
		private bool findAllSuccessAfterLastUpdate; // = false;
		private bool findAllSuccessOnCurrentUpdate; // = false;
		private SettingControlsHelper findAllOrSelectAllOrNoneIsChangingSelection;

		// Update:
		private List<object> pendingElementsAndLines = new List<object>(32); // Preset the initial capacity to improve memory management, 32 is an arbitrary value.		private bool performImmediateUpdate;
		private bool performImmediateMonitorAndStatusUpdate;
		private long monitorUpdateTickInterval;     // Ticks as defined by 'Stopwatch'.
		private long nextMonitorUpdateTickStamp;    // Ticks as defined by 'Stopwatch'.
		private long nextDataStatusUpdateTickStamp; // Ticks as defined by 'Stopwatch'.

		// Note that 'Stopwatch' is used instead of 'DateTime.Now.Ticks' or 'Environment.TickCount'
		// as suggested in several online resources.

////#if (DEBUG) must not be active, configuration must always be available for designer.
		private string debugCaption; // = null;
////#endif

		#endregion

		#region Events
		//==========================================================================================
		// Events
		//==========================================================================================

		/// <summary></summary>
		[Category("Property Changed")]
		[Description("Event raised when the TextFocusState property is changed.")]
		public event EventHandler TextFocusedChanged;

		/// <summary></summary>
		[Category("Action")]
		[Description("Event raised when the the number or selection of selected lines has changed.")]
		public event EventHandler<EventArgs<int>> SelectedLinesChanged;

		/// <summary></summary>
		[Category("Action")]
		[Description("Event raised when the state of find next/previous has changed.")]
		public event EventHandler FindItemStateChanged;

		/// <summary></summary>
		[Category("Action")]
		[Description("Event raised when the result of find all has changed.")]
		public event EventHandler<EventArgs<bool>> FindAllSuccessChanged;

		/// <summary></summary>
		[Category("Action")]
		[Description("Event raised when find all has been reset, e.g. when user selects a line.")]
		public event EventHandler FindAllDeactivatedWithinMonitor;

		#endregion

		#region Object Lifetime
		//==========================================================================================
		// Object Lifetime
		//==========================================================================================

		/// <summary></summary>
		[SuppressMessage("Microsoft.Mobility", "CA1601:DoNotUseTimersThatPreventPowerStateChanges", Justification = "Well, any better idea on how to implement the monitor update timeout?")]
		public Monitor()
		{
			InitializeComponent();

			timer_DataStatusUpdateTimeout.Interval = (DataStatusIntervalMs * 2); // Synchronous update shall have precedence over time-out.

			this.timeStatusHelper = new MonitorTimeStatusHelper();
			this.dataStatusHelper = new MonitorDataStatusHelper();

			this.timeStatusHelper.StatusTextChanged += timeStatusHelper_StatusTextChanged;
			this.dataStatusHelper.StatusTextChanged += dataStatusHelper_StatusTextChanged;

			ApplyFont(); // Required to initialize 'ListBox.ItemHeight', e.g. with scale != 100% (96 DPI).

			// Attention:
			// Since the line number list box will display the vertical scroll bar automatically,
			// the line number list box is placed underneath the monitor list box and sized larger
			// than it would have to be.
			var lblin = fastListBox_LineNumbers;
			this.initialLineNumberWidth = EffectiveWidthToRequestedWidth(lblin.Width);
			SetControls(this.initialLineNumberWidth);
		}

		#endregion

		#region Properties
		//==========================================================================================
		// Properties
		//==========================================================================================

		/// <summary></summary>
		[Category("Appearance")]
		[Description("Configures status panel visibility.")]
		[DefaultValue(ShowStatusPanelDefault)]
		public virtual bool ShowStatusPanel
		{
			get { return (this.showStatusPanel); }
			set
			{
				if (this.showStatusPanel != value)
				{
					this.showStatusPanel = value;
					SetControls();
				}
			}
		}

		/// <summary></summary>
		[Category("Behavior")]
		[Description("The repository type.")]
		[DefaultValue(RepositoryTypeDefault)]
		public virtual Domain.RepositoryType RepositoryType
		{
			get { return (this.repositoryType); }
			set
			{
				if (this.repositoryType != value)
				{
					this.repositoryType = value;
					this.dataStatusHelper.RepositoryType = value;
					SetControls();
				}
			}
		}

		/// <summary></summary>
		[Category("Behavior")]
		[Description("The activity state.")]
		[DefaultValue(ActivityStateDefault)]
		public virtual MonitorActivityState ActivityState
		{
			get { return (this.activityState); }
			set
			{
				if (this.activityState != value)
				{
					this.activityState = value;
					SetActivityStateControls();
				}
			}
		}

		/// <summary></summary>
		[Category("Behavior")]
		[Description("The maxmimal number of lines to display.")]
		[DefaultValue(MaxLineCountDefault)]
		public virtual int MaxLineCount
		{
			get { return (this.maxLineCount); }
			set
			{
				if (this.maxLineCount != value)
				{
					this.maxLineCount = value;
					Reload();
				}
			}
		}

		/// <summary></summary>
		[SuppressMessage("Microsoft.Design", "CA1044:PropertiesShouldNotBeWriteOnly", Justification = "Only setter required for initialization of control.")]
		[Browsable(false)]
		[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
		public virtual FormatSettings FormatSettings
		{
			set
			{
				if (this.formatSettings != value)
				{
					bool fontHasChanged = (this.formatSettings.Font      != value.Font);
					bool backHasChanged = (this.formatSettings.BackColor != value.BackColor);

					this.formatSettings = value;

					if (backHasChanged)
						fastListBox_Monitor.BackColor = this.formatSettings.BackColor;

					if (fontHasChanged)
						ApplyFont();
					else
						fastListBox_Monitor.Invalidate(); // Required e.g. when enabling/disabling formatting.
				}
			}
		}

		/// <summary></summary>
		[Category("Appearance")]
		[Description("Show line numbers.")]
		[DefaultValue(ShowLineNumbersDefault)]
		public virtual bool ShowLineNumbers
		{
			get { return (this.showLineNumbers); }
			set
			{
				if (this.showLineNumbers != value)
				{
					this.showLineNumbers = value;
					SetControls();
				}
			}
		}

		/// <summary></summary>
		[Category("Appearance")]
		[Description("Line number selection.")]
		[DefaultValue(LineNumberSelectionDefault)]
		public virtual Domain.Utilities.LineNumberSelection LineNumberSelection
		{
			get { return (this.lineNumberSelection); }
			set
			{
				if (this.lineNumberSelection != value)
				{
					this.lineNumberSelection = value;

					if (this.lineNumberSelection == Domain.Utilities.LineNumberSelection.Buffer) // This option keeps the offset at 0.
					{
						this.lineNumberOffset = 0;

						var lblin = fastListBox_LineNumbers;
						lblin.Invalidate();
					}

					SetControls();
				}
			}
		}

		/// <summary></summary>
		[Browsable(false)]
		public virtual long LineNumberOffset
		{
			get { return (this.lineNumberOffset); }
		}

		/// <summary></summary>
		[Category("Appearance")]
		[Description("Show the time status.")]
		[DefaultValue(ShowTimeStatusDefault)]
		public virtual bool ShowTimeStatus
		{
			get { return (this.showTimeStatus); }
			set
			{
				if (this.showTimeStatus != value)
				{
					this.showTimeStatus = value;
					SetTimeStatusVisible();
				}
			}
		}

		/// <summary></summary>
		/// <remarks>A default value of TimeSpan.Zero is not possible because it is not constant.</remarks>
		[Category("Action")]
		[Description("The active connection time.")]
		public virtual TimeSpan ActiveConnectTime
		{
			get { return (this.timeStatusHelper.ActiveConnectTime); }
			set { this.timeStatusHelper.ActiveConnectTime = value;  }
		}

		/// <summary></summary>
		/// <remarks>A default value of TimeSpan.Zero is not possible because it is not constant.</remarks>
		[Category("Action")]
		[Description("The total connection time.")]
		public virtual TimeSpan TotalConnectTime
		{
			get { return (this.timeStatusHelper.TotalConnectTime); }
			set { this.timeStatusHelper.TotalConnectTime = value;  }
		}

		/// <summary></summary>
		[Category("Appearance")]
		[Description("Show the data status.")]
		[DefaultValue(ShowDataStatusDefault)]
		public virtual bool ShowDataStatus
		{
			get { return (this.showDataStatus); }
			set
			{
				if (this.showDataStatus != value)
				{
					this.showDataStatus = value;
					SetDataStatusVisible();
				}
			}
		}

		/// <summary></summary>
		[Browsable(false)]
		[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
		public virtual Model.BytesLinesTuple Counts
		{
			get { return (this.dataStatusHelper.Counts); }
			set { this.dataStatusHelper.Counts = value;  }
		}

		/// <summary></summary>
		[Browsable(false)]
		[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
		public virtual Model.BytesLinesTuple Rates
		{
			get { return (this.dataStatusHelper.Rates); }
			set { this.dataStatusHelper.Rates = value;  }
		}

		/// <remarks>
		/// Name only "Active" instead of "LastActive" for simplicity.
		/// </remarks>
		[Category("Appearance")]
		[Description("Show a copy of the active line.")]
		[DefaultValue(ShowCopyOfActiveLineDefault)]
		public virtual bool ShowCopyOfActiveLine
		{
			get { return (this.showCopyOfActiveLine); }
			set
			{
				if (this.showCopyOfActiveLine != value)
				{
					this.showCopyOfActiveLine = value;
					SetControls();
				}
			}
		}

		/// <summary></summary>
		[Browsable(false)]
		public virtual bool TextFocused
		{
			get { return (textBox_CopyOfActiveLine.Focused); }
		}

		/// <summary></summary>
		[Browsable(false)]
		public virtual string SelectedTextInCopyOfActiveLine
		{
			get { return (textBox_CopyOfActiveLine.SelectedText); }
		}

////#if (DEBUG) must not be active, configuration must always be available for designer.

		/// <remarks>
		/// Flag in a addition to configuration item to allow selective debugging of just a single
		/// monitor, e.g. the bidir monitor, to reduce debug output.
		/// </remarks>
		[Category("Bevavior")]
		[Description("Enables or disables debugging.")]
		[DefaultValue(ListBoxEx.DebugEnabledDefault)]
		public virtual bool DebugEnabled
		{
			get { return (this.fastListBox_Monitor.DebugEnabled); }
			set { this.fastListBox_Monitor.DebugEnabled = value;  }
		}

		/// <summary></summary>
		[Category("Data")]
		[Description("Caption to ease debugging multiple items.")]
		[DefaultValue(null)]
		public virtual string DebugCaption
		{
			get { return (this.debugCaption); }
			set { this.debugCaption = value;  }
		}

////#endif

		#endregion

		#region Methods
		//==========================================================================================
		// Methods
		//==========================================================================================

		/// <summary></summary>
		public virtual void Activate()
		{
			SetHeaderBackColor(SystemColors.GradientActiveCaption);
		}

		/// <summary></summary>
		public virtual void Deactivate()
		{
			SetHeaderBackColor(SystemColors.Control);
		}

		/// <summary></summary>
		protected virtual void SetHeaderBackColor(Color color)
		{
			label_TimeStatus_Active .BackColor = color;
			label_TimeStatus_Total  .BackColor = color;
			label_TimeStatus_Back   .BackColor = color;

			label_DataStatus_BidirTx.BackColor = color;
			label_DataStatus_Unidir .BackColor = color;
			label_DataStatus_BidirRx.BackColor = color;
			label_DataStatus_Back   .BackColor = color;
		}

		/// <summary></summary>
		[CallingContract(IsAlwaysMainThread = true, Rationale = "Synchronized from the invoking thread onto the main thread.")]
		public virtual void AddElement(Domain.DisplayElement element)
		{
			DebugContent("Adding single element '" + element.ToString() + "'...");

			AddElementsOrLines(element);
		}

		/// <summary></summary>
		[CallingContract(IsAlwaysMainThread = true, Rationale = "Synchronized from the invoking thread onto the main thread.")]
		public virtual void AddElements(Domain.DisplayElementCollection elements)
		{
			DebugContent("Adding " + elements.Count.ToString(CultureInfo.InvariantCulture) + " element(s) '" + elements.ToString() + "'...");

			AddElementsOrLines(elements);
		}

		/// <summary></summary>
		[CallingContract(IsAlwaysMainThread = true, Rationale = "Synchronized from the invoking thread onto the main thread.")]
		public virtual void ReplaceCurrentLine(Domain.DisplayElementCollection elements)
		{
			DebugContent("Replacing current line with " + elements.Count.ToString(CultureInfo.InvariantCulture) + " element(s) '" + elements.ToString() + "'...");

			// Attention:
			// Similar code exists in ClearCurrentLine() below.
			// Changes here may have to be applied there too.

			var result = ClearCurrentLineInPendingElementsAndLines();

			bool clearCurrentLineInListBoxesIsNeeded;
			switch (result)
			{
				case ClearResult.NoElementOrLinePending:    // Nothing was pending, but a line may already have started earlier.
				case ClearResult.HasClearedButIsIncomplete: // Elements were pending, and the line has for sure already started earlier.
					clearCurrentLineInListBoxesIsNeeded = true;
					break;

				case ClearResult.HasClearedAndCompleted:
				case ClearResult.NoLineOngoing:
					clearCurrentLineInListBoxesIsNeeded = false;
					break;

				default:
					throw (new NotSupportedException(MessageHelper.InvalidExecutionPreamble + "'" + result + "' is a result that has not been implemented here!" + Environment.NewLine + Environment.NewLine + MessageHelper.SubmitBug));
			}

			if (clearCurrentLineInListBoxesIsNeeded)
				ClearCurrentLineInListBoxes(); // Remember that "current line" only applies to a started but not yet completed line.

			AddElementsOrLines(elements);
		}

		/// <summary></summary>
		[CallingContract(IsAlwaysMainThread = true, Rationale = "Synchronized from the invoking thread onto the main thread.")]
		public virtual void ClearCurrentLine()
		{
			DebugContent("Clearing current line...");

			// Attention:
			// Similar code exists in ReplaceCurrentLine() above.
			// Changes here may have to be applied there too.

			var result = ClearCurrentLineInPendingElementsAndLines();

			bool removeCurrentLineFromListBoxesIsNeeded;
			switch (result)
			{
				case ClearResult.NoElementOrLinePending:    // Nothing was pending, but a line may already have started earlier.
				case ClearResult.HasClearedButIsIncomplete: // Elements were pending, and the line has for sure already started earlier.
					removeCurrentLineFromListBoxesIsNeeded = true;
					break;

				case ClearResult.HasClearedAndCompleted:
				case ClearResult.NoLineOngoing:
					removeCurrentLineFromListBoxesIsNeeded = false;
					break;

				default:
					throw (new NotSupportedException(MessageHelper.InvalidExecutionPreamble + "'" + result + "' is a result that has not been implemented here!" + Environment.NewLine + Environment.NewLine + MessageHelper.SubmitBug));
			}

			if (removeCurrentLineFromListBoxesIsNeeded)
				RemoveCurrentLineFromListBoxes(); // Remember that "current line" only applies to a started but not yet completed line.
		}

		/// <summary></summary>
		[CallingContract(IsAlwaysMainThread = true, Rationale = "Synchronized from the invoking thread onto the main thread.")]
		public virtual void AddLine(Domain.DisplayLine line)
		{
			DebugContent("Adding single line '" + line.ToString() + "'...");

			AddElementsOrLines(line);
		}

		/// <summary></summary>
		[CallingContract(IsAlwaysMainThread = true, Rationale = "Synchronized from the invoking thread onto the main thread.")]
		public virtual void AddLines(Domain.DisplayLineCollection lines)
		{
			DebugContent("Adding " + lines.Count.ToString(CultureInfo.InvariantCulture) + " line(s) '" + lines.ToString() + "'...");

			AddElementsOrLines(lines);
		}

		/// <summary></summary>
		[CallingContract(IsAlwaysMainThread = true, Rationale = "Synchronized from the invoking thread onto the main thread.")]
		public virtual void Clear()
		{
			this.pendingElementsAndLines.Clear();

			ClearAndResetListBoxes();

			DebugContent("Cleared");
		}

		/// <summary></summary>
		[CallingContract(IsAlwaysMainThread = true, Rationale = "Synchronized from the invoking thread onto the main thread.")]
		public virtual void ResetLineNumbers()
		{
			if (this.lineNumberSelection != Domain.Utilities.LineNumberSelection.Buffer) // This option keeps the offset at 0.
			{
				this.lineNumberOffset = 0;

				var lblin = fastListBox_LineNumbers;
				lblin.Invalidate();
			}
		}

		/// <summary></summary>
		protected virtual void Reload()
		{
			var lb = fastListBox_Monitor;

			// Retrieve lines from list box:
			var lines = new Domain.DisplayLineCollection(lb.Items.Count); // Preset the required capacity to improve memory management.
			foreach (object item in lb.Items)
			{
				var line = (item as Domain.DisplayLine);
				if (line != null)
					lines.Add(line);
			}

			// Perform reload:
			Reload(lines);
		}

		/// <summary></summary>
		protected virtual void Reload(Domain.DisplayLineCollection lines)
		{
			Clear();
			AddLines(lines);
		}

		/// <summary></summary>
		public virtual void SelectAll()
		{
			this.findAllOrSelectAllOrNoneIsChangingSelection.Enter();
			try
			{
				var lb = fastListBox_Monitor;
				lb.SelectAll();
				DebugSetSelected(ControlEx.InvalidIndex);
			}
			finally
			{
				this.findAllOrSelectAllOrNoneIsChangingSelection.Leave();
			}
		}

		/// <summary></summary>
		public virtual void SelectNone()
		{
			this.findAllOrSelectAllOrNoneIsChangingSelection.Enter();
			try
			{
				var lb = fastListBox_Monitor;
				lb.ClearSelected();
				DebugClearSelected();
			}
			finally
			{
				this.findAllOrSelectAllOrNoneIsChangingSelection.Leave();
			}
		}

		/// <remarks>
		/// Using "pattern" instead of "textOrPattern" for simplicity.
		/// </remarks>
		[SuppressMessage("Microsoft.Design", "CA1021:AvoidOutParameters", MessageId = "2#", Justification = "Multiple return values are required, and 'out' is preferred to 'ref'.")]
		public virtual bool TryFindOnEdit(string pattern, FindOptions options, out FindDirection resultingDirection)
		{
			if (!this.findAllIsActive)
			{
				ResetFindAll();

				if (this.isFirstFindOnEdit)
				{
					this.isFirstFindOnEdit = false;

					int nextStartIndex;
					if (TryGetNextStartIndex(out nextStartIndex))
						this.findOnEditStartIndex = nextStartIndex; // Find will start after current item.
					else
						this.findOnEditStartIndex = ControlEx.InvalidIndex; // Find will start at first item.
				}

				if (!string.IsNullOrEmpty(pattern))
				{
					PrepareFind(pattern, options);

					if (TryFindNextAnyNotify(this.findOnEditStartIndex))
					{
						resultingDirection = FindDirection.Forward;
						return (true);
					}

					if (TryFindPreviousAndNotify(this.findOnEditStartIndex))
					{
						resultingDirection = FindDirection.Backward;
						return (true);
					}
				}
			}
			else // this.findAllIsActive
			{
				ResetFindOnEdit();

				if (!string.IsNullOrEmpty(pattern))
				{
					PrepareFind(pattern, options);

					if (TryFindAllAndNotify())
					{
						resultingDirection = FindDirection.All;
						return (true);
					}
				}
			}

			var lb = fastListBox_Monitor;
			lb.ClearSelected();   // "findAllOrSelectAllOrNoneIsChangingSelection" shall not be entered/left,
			DebugClearSelected(); // the find result shall be reflected in e.g. the copy of the active line.

			resultingDirection = FindDirection.Undetermined;
			return (false);
		}

		/// <remarks>
		/// Using "pattern" instead of "textOrPattern" for simplicity.
		/// </remarks>
		public virtual bool TryFindNext(string pattern, FindOptions options)
		{
			ResetFindOnEdit();
			ResetFindAll();

			PrepareFind(pattern, options);

			return (TryFindNextAndNotify());
		}

		/// <remarks>
		/// Using "pattern" instead of "textOrPattern" for simplicity.
		/// </remarks>
		public virtual bool TryFindPrevious(string pattern, FindOptions options)
		{
			ResetFindOnEdit();
			ResetFindAll();

			PrepareFind(pattern, options);

			return (TryFindPreviousAndNotify());
		}

		/// <summary></summary>
		public virtual void EmptyFindOnEdit()
		{
			ResetFindOnEdit();
		}

		/// <summary></summary>
		public virtual void LeaveFindOnEdit()
		{
			ResetFindOnEdit();

			// Selection shall be reset when leaving find, otherwise lines among the
			// monitors would stay highlighted. But of course not if [Find All] is active:
			if (!findAllIsActive)
				SelectNone();
		}

		/// <summary></summary>
		protected virtual void ResetFindOnEdit()
		{
			this.isFirstFindOnEdit = true;
			this.findOnEditStartIndex = ControlEx.InvalidIndex;
		}

		/// <summary></summary>
		protected virtual void ResetFindAll()
		{
			this.findAllSuccessAfterLastUpdate = false;
			this.findAllSuccessOnCurrentUpdate = false;
		}

		/// <remarks>
		/// Using "pattern" instead of "textOrPattern" for simplicity.
		/// </remarks>
		public virtual bool ActivateFindAll(string pattern, FindOptions options)
		{
			ResetFindOnEdit();

			PrepareFind(pattern, options);

			this.findAllIsActive = true;

			var success = TryFindAllWithoutNotify(); // Is done here for symmetricity with 'Deactivate()' below.
			OnFindItemStateChanged(EventArgs.Empty);
			OnFindAllSuccessChanged(new EventArgs<bool>(success));
			return (success);
		}

		/// <summary></summary>
		public virtual void DeactivateFindAll(bool clearSelected = true)
		{
			ResetFindAll();

			this.findAllIsActive = false;

			if (clearSelected)
			{
				this.findAllOrSelectAllOrNoneIsChangingSelection.Enter();
				try
				{
					var lb = fastListBox_Monitor;
					lb.ClearSelected();
					DebugClearSelected();
				}
				finally
				{
					this.findAllOrSelectAllOrNoneIsChangingSelection.Leave();
				}
			}

		////OnFindAllSuccessChanged(new EventArgs<bool>(false)) must not be called! Success has not changed!
		////OnFindAllDeactivatedWithinMonitor(EventArgs.Empty)  must not be called! Deactivation has been triggered outside!
			OnFindItemStateChanged(EventArgs.Empty);
		}

		/// <remarks>
		/// Using "pattern" instead of "textOrPattern" for simplicity.
		/// </remarks>
		protected virtual void PrepareFind(string pattern, FindOptions options)
		{
			if (options.EnableRegex)
			{
				var regexOptions = RegexOptions.Singleline;

				if (!options.CaseSensitive)
					regexOptions |= RegexOptions.IgnoreCase;

				if (options.WholeWord)            // Surround with Regex word delimiter:
					pattern = string.Format(CultureInfo.CurrentCulture, "{0}{1}{0}", @"\b", pattern);

				this.findRegex = new Regex(pattern, regexOptions);

				this.findText              = null;
				this.findTextCaseSensitive = false;
				this.findTextWholeWord     = false;
			}
			else
			{
				this.findText              = pattern;
				this.findTextCaseSensitive = options.CaseSensitive;
				this.findTextWholeWord     = options.WholeWord;

				this.findRegex = null;
			}
		}

		/// <summary></summary>
		protected virtual bool TryFindNextAndNotify()
		{
			int startIndex;
			if (!TryGetNextStartIndex(out startIndex))
				return (false);

			int findIndex;
			if (!TryFindNextAndNotify(startIndex, out findIndex))
				return (false);

			this.lastFindIndex = findIndex;
			return (true);
		}

		/// <summary></summary>
		protected virtual bool TryFindPreviousAndNotify()
		{
			int startIndex;
			if (!TryGetPreviousStartIndex(out startIndex))
				return (false);

			int findIndex;
			if (!TryFindPreviousAndNotify(startIndex, out findIndex))
				return (false);

			this.lastFindIndex = findIndex;
			return (true);
		}

		/// <summary></summary>
		protected virtual bool TryFindNextAnyNotify(int startIndex)
		{
			int findIndex;
			return (TryFindNextAndNotify(startIndex, out findIndex));
		}

		/// <summary></summary>
		protected virtual bool TryFindNextAndNotify(int startIndex, out int findIndex)
		{
			var lb = fastListBox_Monitor;

			var i = lb.FindNext(this.findText, this.findTextCaseSensitive, this.findTextWholeWord, this.findRegex, startIndex);
			if (i != ListBox.NoMatches)
			{
				DebugClearSelected();
				DebugSetSelected(i);

				lb.ClearSelected();      // "findAllOrSelectAllOrNoneIsChangingSelection" shall not be entered/left,
				lb.SetSelected(i, true); // the find result shall be reflected in e.g. the copy of the active line.
				lb.TopIndex = Math.Max(i - (lb.TotalVisibleItemCount / 2), 0);

				findIndex = i;
				OnFindItemStateChanged(EventArgs.Empty);
				return (true);
			}

			findIndex = ListBox.NoMatches;
			OnFindItemStateChanged(EventArgs.Empty);
			return (false);
		}

		/// <summary></summary>
		protected virtual bool TryFindPreviousAndNotify(int startIndex)
		{
			int findIndex;
			return (TryFindPreviousAndNotify(startIndex, out findIndex));
		}

		/// <summary></summary>
		protected virtual bool TryFindPreviousAndNotify(int startIndex, out int findIndex)
		{
			var lb = fastListBox_Monitor;

			var i = lb.FindPrevious(this.findText, this.findTextCaseSensitive, this.findTextWholeWord, this.findRegex, startIndex);
			if (i != ListBox.NoMatches)
			{
				DebugClearSelected();
				DebugSetSelected(i);

				lb.ClearSelected();      // "findAllOrSelectAllOrNoneIsChangingSelection" shall not be entered/left,
				lb.SetSelected(i, true); // the find result shall be reflected in e.g. the copy of the active line.
				lb.TopIndex = Math.Max(i - (lb.TotalVisibleItemCount / 2), 0);

				findIndex = i;
				OnFindItemStateChanged(EventArgs.Empty);
				return (true);
			}

			findIndex = ListBox.NoMatches;
			OnFindItemStateChanged(EventArgs.Empty);
			return (false);
		}

		/// <summary></summary>
		protected virtual bool TryFindAllAndNotify()
		{
			var success = TryFindAllWithoutNotify();
			OnFindItemStateChanged(EventArgs.Empty);
			OnFindAllSuccessChanged(new EventArgs<bool>(success));
			return (success);
		}

		/// <summary></summary>
		protected virtual bool TryFindAllWithoutNotify()
		{
			var lb = fastListBox_Monitor;

			for (var i = 0; i < lb.Items.Count; i++)
			{
				var result = lb.FindAt(this.findText, this.findTextCaseSensitive, this.findTextWholeWord, this.findRegex, i);
				if (result == i)
				{
					this.findAllOrSelectAllOrNoneIsChangingSelection.Enter();
					try
					{
						DebugSetSelected(i);
						lb.SetSelected(i, true);
					}
					finally
					{
						this.findAllOrSelectAllOrNoneIsChangingSelection.Leave();
					}

					this.findAllSuccessAfterLastUpdate = true;
				}
				else
				{
					this.findAllOrSelectAllOrNoneIsChangingSelection.Enter();
					try
					{
						DebugClearSelected(i);
						lb.SetSelected(i, false);
					}
					finally
					{
						this.findAllOrSelectAllOrNoneIsChangingSelection.Leave();
					}
				}
			}

			return (this.findAllSuccessAfterLastUpdate);
		}

		/// <summary></summary>
		protected virtual bool TryGetCurrentStartIndex(out int result)
		{
			var lb = fastListBox_Monitor;

			if (lb.Items.Count > 0)
			{
				if (lb.CurrentOrFormerFirstSelectedIndex != ControlEx.InvalidIndex)
				{
					result = lb.CurrentOrFormerFirstSelectedIndex;
					if (result <= lb.LastIndex)
						return (true);
					else
						return (false);
				}

				if (this.lastFindIndex != ListBox.NoMatches)
				{
					result = this.lastFindIndex;
					if (result <= lb.LastIndex)
						return (true);
					else
						return (false);
				}

				result = ControlEx.InvalidIndex;
				return (true);
			}

			result = ControlEx.InvalidIndex;
			return (false);
		}

		/// <summary></summary>
		protected virtual bool TryGetNextStartIndex(out int result)
		{
			var lb = fastListBox_Monitor;

			int currentStartIndex;
			if (TryGetCurrentStartIndex(out currentStartIndex))
			{
				result = (currentStartIndex + 1); // next = current + 1
				if (result <= lb.LastIndex)
					return (true);
				else
					return (false);
			}

			result = ControlEx.InvalidIndex;
			return (false);
		}

		/// <summary></summary>
		protected virtual bool TryGetPreviousStartIndex(out int result)
		{
			var lb = fastListBox_Monitor;

			int currentStartIndex;
			if (TryGetCurrentStartIndex(out currentStartIndex))
			{
				result = (currentStartIndex - 1); // previous = current - 1
				if (result >= lb.FirstIndex)
					return (true);
				else
					return (false);
			}

			result = ControlEx.InvalidIndex;
			return (false);
		}

		/// <summary></summary>
		public virtual int SelectedLineCount
		{
			get { return (fastListBox_Monitor.SelectedItems.Count); }
		}

		/// <remarks>
		/// If no lines are available, an empty collection is returned, never <c>null</c>.
		/// </remarks>
		public virtual Domain.DisplayLineCollection SelectedLines
		{
			get
			{
				var lb = fastListBox_Monitor;

				var selectedLines = new Domain.DisplayLineCollection(); // No preset needed, default behavior is good enough.

				if (lb.SelectedItems.Count > 0)
				{
					foreach (int i in lb.SelectedIndices)
						selectedLines.Add(lb.Items[i] as Domain.DisplayLine);
				}

				return (selectedLines);
			}
		}

		/// <remarks>
		/// If no lines are available, an empty collection is returned, never <c>null</c>.
		/// </remarks>
		public virtual Domain.DisplayLineCollection SelectedOrAllLines
		{
			get
			{
				var lb = fastListBox_Monitor;

				var selectedLines = new Domain.DisplayLineCollection(); // No preset needed, default behavior is good enough.

				if (lb.SelectedItems.Count > 0)
				{
					foreach (int i in lb.SelectedIndices)
						selectedLines.Add(lb.Items[i] as Domain.DisplayLine);
				}
				else
				{
					for (int i = 0; i < lb.Items.Count; i++)
						selectedLines.Add(lb.Items[i] as Domain.DisplayLine);
				}

				return (selectedLines);
			}
		}

		/// <summary></summary>
		public virtual void SetTimeStatus(TimeSpan activeConnectTime, TimeSpan totalConnectTime)
		{
			this.timeStatusHelper.Set(activeConnectTime, totalConnectTime);
		}

		/// <summary></summary>
		public virtual void ResetTimeStatus()
		{
			this.timeStatusHelper.Reset();
		}

		/// <summary></summary>
		public virtual void SetDataStatus(Model.CountsRatesTuple status)
		{
			if ((status.Counts.TxLines <= 0) && (status.Counts.RxLines <= 0))
			{
				this.lineNumberOffset = 0;

				var lblin = fastListBox_LineNumbers;
				lblin.Invalidate();
			}

			this.dataStatusHelper.SetCountsAndRates(status);
		}

		/// <summary></summary>
		public virtual void ResetDataStatus()
		{
			this.dataStatusHelper.Reset();
		}

		#endregion

		#region Control Event Handlers
		//==========================================================================================
		// Control Event Handlers
		//==========================================================================================

		/// <remarks>
		/// Labels are manually resized/relocated because <see cref="Label.AutoSize"/> doesn't work
		/// with <see cref="Label.AutoEllipsis"/>. But, not using <see cref="Label.AutoSize"/> means
		/// that label will not adjust to different font size, well...
		/// </remarks>
		/// <remarks>
		/// From YAT 2.4.0, two separate labels are used. This prevents undesireable line breaks a
		/// single label containing two lines will show when size becomes too small. Both labels
		/// have a <see cref="Control.Height"/> of 15, i.e. half the 'IconPanelHeightAvailable'.
		/// </remarks>
		/// <remarks>
		/// Note a limitation of <see cref="Label.AutoEllipsis"/>:
		/// As soon as ellipsis are required, <see cref="Label.TextAlign"/> will fallback to the
		/// default of <see cref="ContentAlignment.TopLeft"/>, resulting an odd looking 'BidirTx'
		/// label. This limitation is considered acceptable.
		/// </remarks>
		private void Monitor_Resize(object sender, EventArgs e)
		{
		////const int IconPanelHeight          = 34; // Informational only.
		////const int IconPanelBottomPadding   =  4; // Informational only.
		////const int IconPanelHeightAvailable = 30; // Informational only.

			const int HalfIconWidth = 14;
			int middle = (Width / 2);
			int labelWidth = (middle - HalfIconWidth);
			int labelLeft  = (middle + HalfIconWidth);

			label_TimeStatus_Active .Width = labelWidth;
			label_TimeStatus_Total  .Width = labelWidth;
			label_TimeStatus_Back   .Width = labelWidth;

			label_DataStatus_BidirTx.Width = labelWidth;
			label_DataStatus_Unidir .Width = labelWidth;
			label_DataStatus_BidirRx.Width = labelWidth;
			label_DataStatus_Back   .Width = labelWidth;

			label_DataStatus_BidirTx.Left = labelLeft;
			label_DataStatus_Unidir .Left = labelLeft;
			label_DataStatus_BidirRx.Left = labelLeft;
			label_DataStatus_Back   .Left = labelLeft;
		}

		#endregion

		#region Controls Event Handlers
		//==========================================================================================
		// Controls Event Handlers
		//==========================================================================================

		private void label_TimeStatus_Active_DoubleClick(object sender, EventArgs e)
		{
			ResetTimeStatus();
		}

		private void label_TimeStatus_Total_DoubleClick(object sender, EventArgs e)
		{
			ResetTimeStatus();
		}

		private void label_DataStatus_BidirTx_DoubleClick(object sender, EventArgs e)
		{
			ResetDataStatus();
		}

		private void label_DataStatus_Unidir_DoubleClick(object sender, EventArgs e)
		{
			ResetDataStatus();
		}

		private void label_DataStatus_BidirRx_DoubleClick(object sender, EventArgs e)
		{
			ResetDataStatus();
		}

		private void fastListBox_Monitor_SelectedIndexChanged(object sender, EventArgs e)
		{
			var lb = fastListBox_Monitor;

			if (!this.findAllOrSelectAllOrNoneIsChangingSelection)  // Changes not triggered by [Find All] shall:
			{
				DeactivateFindAll(clearSelected: false);            // a) Deactivate [Find All] for this...
				OnFindAllDeactivatedWithinMonitor(EventArgs.Empty); //    ...as well as other monitors.

				if (lb.SelectedItems.Count > 0)                     // b) Be reflected in the copy of the active line.
					SetCopyOfActiveLine(lb.SelectedItems[0]);
			}

			OnSelectedLinesChanged(new EventArgs<int>(lb.SelectedItems.Count));
		}

		/// <remarks>
		/// Note that the 'MeasureItem' event only measures the height and an item and is thus
		/// only needed for 'OwnerDrawnVariable' and not for 'OwnerDrawnFixed'.
		/// </remarks>
		[SuppressMessage("StyleCop.CSharp.ReadabilityRules", "SA1115:ParameterMustFollowComma",                       Justification = "There are too many parameters to pass.")]
		[SuppressMessage("StyleCop.CSharp.ReadabilityRules", "SA1116:SplitParametersMustStartOnLineAfterDeclaration", Justification = "There are too many parameters to pass.")]
		[SuppressMessage("StyleCop.CSharp.ReadabilityRules", "SA1117:ParametersMustBeOnSameLineOrSeparateLines",      Justification = "There are too many parameters to pass.")]
		private void fastListBox_LineNumbers_DrawItem(object sender, DrawItemEventArgs e)
		{
			unchecked
			{
				if (e.Index >= 0)
				{
					string lineNumberString = ((this.lineNumberOffset + e.Index + 1).ToString(CultureInfo.CurrentCulture));

					var lb = fastListBox_LineNumbers;
					int requestedWidth;

				////e.DrawBackground(); is not needed and actually draws a white background.
					MonitorRenderer.DrawAndMeasureLineNumber(lineNumberString, this.formatSettings,
					                                         e.Graphics, e.Bounds, out requestedWidth);
				////e.DrawFocusRectangle(); is not needed.

					// The item width is handled here.
					// The item height is set in the 'FormatSettings' property.
					if ((requestedWidth > 0) && (requestedWidth > EffectiveWidthToRequestedWidth(lb.Width)))
						ResizeAndRelocateControls(requestedWidth);
				}
			}
		}

		/// <remarks>
		/// Intentionally initializing to 0 and not ControlEx.InvalidIndex. Doing so would result in
		/// an unnecessary initial VerticalScrollToIndex() request.
		///
		/// This also matches to behavior of <see cref="ListBox.TopIndex"/>:
		///
		/// Initially, the item with the index position zero (0) is at the top of the visible region
		/// of the ListBox. If the contents of the ListBox have been scrolled, another item might be
		/// at the top of the control's display area.
		/// You can use this property to obtain the index within the ListBox.ObjectCollection for the
		/// ListBox of the item that is currently positioned at the top of the visible region of the
		/// control.
		/// You can also use this property to position an item in the list at the top of the visible
		/// region of the control.
		/// </remarks>
		[SuppressMessage("StyleCop.CSharp.NamingRules", "SA1310:FieldNamesMustNotContainUnderscore", Justification = "Clear separation of related item and field name.")]
		private int lbmon_DrawItem_lastTopIndex; // = 0;

		/// <remarks>
		/// Note that the 'MeasureItem' event is not needed for 'OwnerDrawnFixed' (item height only).
		///
		/// ListBox
		/// -------
		///
		/// Whether we like it or not, <see cref="System.Windows.Forms.ListBox.OnDrawItem"/> calls
		/// this method pretty often. Actually it's called twice each time a new line is added. In
		/// addition, another call is needed for the next still empty line. Thus:
		/// 1st line received => 3 calls to DrawItem() at index 0 | 0 | 1
		/// 2nd line received => 5                     at index 0 | 1 | 0 | 1 | 2
		/// 3rd line received => 7                     at index 0 | 1 | 2 | 0 | 1 | 2 | 3
		/// ...
		/// Nth line received => 2*N + 1               at index 0 | 1 | 2...N | 0 | 1 | 2...N | N+1
		///
		/// Each call takes a 0..2 ms. For 25 lines this results in something like:
		/// 51 x 2 ms = 100 ms per update!
		/// At least scrolling is handled properly, i.e. as soon as the listbox starts to scroll,
		/// the number of calls doesn't increase anymore.
		///
		/// Example measurements for SIR @ 18 samples per second:
		/// 1.99.20 => 30% CPU usage
		/// 1.99.22 with owner drawn and delayed scrolling => 25% CPU usage
		/// 1.99.22 with owner drawn without DrawItem() => 10% CPU usage
		/// 1.99.22 with normal drawn => 20% CPU usage
		///
		/// Double-buffered = <c>true</c> (form and control) doesn't make much difference either...
		///
		///
		/// FastListBox
		/// -----------
		///
		/// Fast and smooth :-)
		///
		/// CPU usage is about the same as above, however, FastListBox has no flickering at all
		/// whereas the standard ListBox has.
		///
		///
		/// Timed updated FastListBox
		/// -------------------------
		/// In case of really large data, the FastListBox still proved too slow. Thus, a timed
		/// update has been implemented to further improve the performance. Three approaches
		/// have been tried to implement such timed update:
		/// 1. More sophisticated handling within <see cref="fastListBox_Monitor_DrawItem"/>
		///    => Doesn't work because list box's back ground has already been drawn before
		///       this event is invoked, thus it just increases flickering...
		/// 2. More sophisticated handling within additional 'FastListBox.OnPaintBackground'
		///    => Doesn't work because list box has already been cleaned to a black background
		///       before this event is invoked, thus it increases flickering too...
		/// 3. Temporarily suspending the adding of elements. The elements are then added upon
		///    the next update. See <see cref="MonitorUpdateHasToBePerformed()"/> for details.
		///
		/// </remarks>
		[SuppressMessage("StyleCop.CSharp.ReadabilityRules", "SA1115:ParameterMustFollowComma",                       Justification = "There are too many parameters to pass.")]
		[SuppressMessage("StyleCop.CSharp.ReadabilityRules", "SA1116:SplitParametersMustStartOnLineAfterDeclaration", Justification = "There are too many parameters to pass.")]
		[SuppressMessage("StyleCop.CSharp.ReadabilityRules", "SA1117:ParametersMustBeOnSameLineOrSeparateLines",      Justification = "There are too many parameters to pass.")]
		[SuppressMessage("StyleCop.CSharp.DocumentationRules", "SA1650:ElementDocumentationMustBeSpelledCorrectly", Justification = "'ms' is the proper abbreviation for milliseconds but StyleCop isn't able to deal with such abbreviations...")]
		private void fastListBox_Monitor_DrawItem(object sender, DrawItemEventArgs e)
		{
			unchecked
			{
				if (e.Index >= 0)
				{
					var lblin = fastListBox_LineNumbers;
				#if (ENABLE_HORIZONTAL_AUTO_SCROLL)
					var lbmon = fastListBox_Monitor;
				#else
					var lbmon = fastListBox_Monitor;
				#endif
					int requestedWidth;

					if (this.formatSettings.FormattingEnabled)
					{
						// Handle non-standard background:
						if (this.formatSettings.BackColor != SystemColors.Window) // = 'FormatSettings.DefaultBackColor'.
						{
							if ((e.State & DrawItemState.Selected) == 0) // Change only needed if item is not selected.
								e = new DrawItemEventArgs(e.Graphics, e.Font, e.Bounds, e.Index, e.State, e.ForeColor, this.formatSettings.BackColor);
						}

						e.DrawBackground();

						var dl = (lbmon.Items[e.Index] as Domain.DisplayLine);
						MonitorRenderer.DrawAndMeasureLine(dl, this.formatSettings,
						                                   e.Graphics, e.Bounds, e.State, out requestedWidth);
						e.DrawFocusRectangle();
					}
					else
					{
						e.DrawBackground();

						var dl = (lbmon.Items[e.Index] as Domain.DisplayLine);
						MonitorRenderer.DrawAndMeasureLine(dl, e.Font,
						                                   e.Graphics, e.Bounds, e.State, e.ForeColor, e.BackColor, out requestedWidth);
						e.DrawFocusRectangle();

						// Note that it makes no sense to replace the 'FastListBox' by a standard 'ListBox' or 'ListBoxEx'
						// to further increase the speed of this view control. Doing so would only reintroduce flickering!
						// Refer to the 'MKY.Windows.Forms.Test' test application for comparison of the variants.
					}

					// The item width and horizontal extent is handled below.
					// The item height is set in the 'FormatSettings' property.
					if (lbmon.HorizontalExtent < requestedWidth)
						lbmon.HorizontalExtent = requestedWidth;

				#if (ENABLE_HORIZONTAL_AUTO_SCROLL)
					// Perform horizontal auto-scroll, but only on the last item:
					if (e.Index == lbmon.LastIndex)
						lbmon.HorizontalScrollToPosition(requestedWidth - e.Bounds.Width);
				#endif

					// Check whether the top index has changed, if so, also scroll the line numbers.
					// Especially applies when monitor gets cleared, the top index will become 0.
					if (lbmon_DrawItem_lastTopIndex != lbmon.TopIndex)
					{
						lbmon_DrawItem_lastTopIndex = lbmon.TopIndex;
						lblin.VerticalScrollToIndex(lbmon.TopIndex);
					}
				}
			}
		}

		private void fastListBox_Monitor_Leave(object sender, EventArgs e)
		{
			// Selection shall be reset when leaving the control, otherwise lines among the
			// monitors would stay highlighted. But of course not if [Find All] is active:
			if (!this.findAllIsActive)
				SelectNone();
		}

		/// <remarks>
		/// This 'Windows.Forms.Timer' event handler will be called on the application main thread.
		/// No additional synchronization or prevention of a race condition is needed.
		/// </remarks>
		[CallingContract(IsAlwaysMainThread = true, Rationale = "This 'Windows.Forms.Timer' event handler will be called on the application main thread.")]
		private void timer_MonitorUpdateTimeout_Tick(object sender, EventArgs e)
		{
			StopMonitorUpdateTimeout();
			UpdateFastListBoxWithPendingElementsAndLines();
		}

		/// <remarks>
		/// This 'Windows.Forms.Timer' event handler will be called on the application main thread.
		/// No additional synchronization or prevention of a race condition is needed.
		/// </remarks>
		[CallingContract(IsAlwaysMainThread = true, Rationale = "This 'Windows.Forms.Timer' event handler will be called on the application main thread.")]
		private void timer_DataStatusUpdateTimeout_Tick(object sender, EventArgs e)
		{
			StopDataStatusUpdateTimeout();
			UpdateDataStatusText();
		}

		[SuppressMessage("StyleCop.CSharp.NamingRules", "SA1310:FieldNamesMustNotContainUnderscore", Justification = "Clear separation of related item and field name.")]
		private MovingAverageInt32 timer_ProcessorLoad_Tick_MovingAverage = new MovingAverageInt32(11); // 11 is an arbitrary prime number.

		/// <remarks>
		/// This 'Windows.Forms.Timer' event handler will be called on the application main thread.
		/// No additional synchronization or prevention of a race condition is needed.
		/// </remarks>
		[CallingContract(IsAlwaysMainThread = true, Rationale = "This 'Windows.Forms.Timer' event handler will be called on the application main thread.")]
		private void timer_ProcessorLoad_Tick(object sender, EventArgs e)
		{
			// Calculate average of last two samples:

			int currentValue = ProcessorLoad.Update(); // Note that interval of 151 ms is a trade-off between responsiveness and wasting time (for Update() itself).
			int averageValue = timer_ProcessorLoad_Tick_MovingAverage.EnqueueAndCalculate(currentValue);

			DebugUpdate(DateTime.Now.ToString("HH:mm:ss.fff", DateTimeFormatInfo.CurrentInfo));
			DebugUpdate(" : CPU load (moving average) of " + averageValue.ToString(CultureInfo.CurrentCulture) + "% resulting in ");
			CalculateUpdateTickInterval(averageValue);
		}

		/// <remarks>
		/// This 'Windows.Forms.Timer' event handler will be called on the application main thread,
		/// i.e. is single-threaded. No additional synchronization or prevention of a race condition is needed.
		/// </remarks>
		private void timer_Opacity_Tick(object sender, EventArgs e)
		{
			if (this.imageOpacityState != OpacityState.Inactive)
			{
				if (this.imageOpacityState == OpacityState.Incrementing)
				{
					this.imageOpacity += ImageOpacityIncrement;
					if (this.imageOpacity >= MaxImageOpacity)
					{
						this.imageOpacity = MaxImageOpacity;
						this.imageOpacityState = OpacityState.Decrementing;
					}
				}
				else
				{
					this.imageOpacity += ImageOpacityDecrement;
					if (this.imageOpacity <= MinImageOpacity)
					{
						this.imageOpacity = MinImageOpacity;
						this.imageOpacityState = OpacityState.Incrementing;
					}
				}
			#if (FALSE)
				// \fixme:
				// Don't know how to alter image opacity (yet).
				pictureBox_Monitor.Image.Opacity = this.imageOpacity
			#endif
				const double ImageOpacitySpan = (MaxImageOpacity - MinImageOpacity);
				const double ImageOpacityThreshold = MinImageOpacity + (ImageOpacitySpan * 0.9); // 10/90 duty cycle.
				if (this.imageOpacity >= ImageOpacityThreshold)
					pictureBox_Monitor.Image = this.imageActive;
				else
					pictureBox_Monitor.Image = null;
			}
		}

		private void textBox_CopyOfActiveLine_Enter(object sender, EventArgs e)
		{
			OnTextFocusedChanged(e);
		}

		private void textBox_CopyOfActiveLine_Leave(object sender, EventArgs e)
		{
			OnTextFocusedChanged(e);
		}

		#endregion

		#region Utilities Event Handlers
		//==========================================================================================
		// Utilities Event Handlers
		//==========================================================================================

		private void timeStatusHelper_StatusTextChanged(object sender, EventArgs e)
		{
			SetTimeStatusText();
		}

		private void dataStatusHelper_StatusTextChanged(object sender, EventArgs e)
		{
			SetDataStatusText();
		}

		#endregion

		#region Non-Public Methods
		//==========================================================================================
		// Non-Public Methods
		//==========================================================================================

		private static int EffectiveWidthToRequestedWidth(int effectiveWidth)
		{
			return (effectiveWidth - (VerticalScrollBarWidth + AdditionalMargin));
		}

		private void SetControls()
		{
			SetControls(this.currentLineNumberWidth);
		}

		private void SetControls(int requestedLineNumberWidth)
		{
			panel_Picture.Visible = ShowStatusPanel; // // Adjust monitor for compact view, e.g. in 'FormatSettings' dialog:

			SetRepositoryDependentControls();
			SetActivityStateControls();

			SetTimeStatusVisible();
			SetTimeStatusText();

			SetDataStatusVisible();
			SetDataStatusText();

			ResizeAndRelocateControls(requestedLineNumberWidth);
		}

		private void SetRepositoryDependentControls()
		{
			if (RepositoryType != Domain.RepositoryType.None)
			{
				switch (RepositoryType)
				{
					case Domain.RepositoryType.Tx:    this.imageInactive = Properties.Resources.Image_Monitor_Tx_28x28_Grey;    this.imageActive = Properties.Resources.Image_Monitor_Tx_28x28_Blue;          break;
					case Domain.RepositoryType.Bidir: this.imageInactive = Properties.Resources.Image_Monitor_Bidir_28x28_Grey; this.imageActive = Properties.Resources.Image_Monitor_Bidir_28x28_BluePurple; break;
					case Domain.RepositoryType.Rx:    this.imageInactive = Properties.Resources.Image_Monitor_Rx_28x28_Grey;    this.imageActive = Properties.Resources.Image_Monitor_Rx_28x28_Purple;        break;

					case Domain.RepositoryType.None:  throw (new ArgumentOutOfRangeException("repositoryType", repositoryType, MessageHelper.InvalidExecutionPreamble + "'" + repositoryType + "' is a repository type that is not valid here!" + Environment.NewLine + Environment.NewLine + MessageHelper.SubmitBug));
					default:                          throw (new ArgumentOutOfRangeException("repositoryType", repositoryType, MessageHelper.InvalidExecutionPreamble + "'" + RepositoryType + "' is an invalid repository type!"               + Environment.NewLine + Environment.NewLine + MessageHelper.SubmitBug));
				}

				pictureBox_Monitor.BackgroundImage = this.imageInactive;
			}
		}

		private void SetActivityStateControls()
		{
			if (RepositoryType != Domain.RepositoryType.None)
			{
				switch (ActivityState)
				{
					case MonitorActivityState.Active:   this.imageOpacityState = OpacityState.Inactive; pictureBox_Monitor.Image = this.imageActive; break;
					case MonitorActivityState.Inactive: this.imageOpacityState = OpacityState.Inactive; pictureBox_Monitor.Image = null;             break;

					case MonitorActivityState.Pending:
					{
						if (this.imageOpacityState == OpacityState.Inactive)
						{
							if (this.activityStateOld == MonitorActivityState.Active)
							{
								pictureBox_Monitor.Image = this.imageActive;
								this.imageOpacity = MaxImageOpacity;
								this.imageOpacityState = OpacityState.Decrementing;
							}
							if (this.activityStateOld == MonitorActivityState.Inactive)
							{
								pictureBox_Monitor.Image = this.imageActive;
								this.imageOpacity = MinImageOpacity;
								this.imageOpacityState = OpacityState.Incrementing;
							}
						}
						break;
					}
				}

				this.activityStateOld = ActivityState;

				timer_Opacity.Enabled = (this.imageOpacityState != OpacityState.Inactive);
			}
		}

		/// <summary>
		/// Applies the font to the list boxes.
		/// </summary>
		/// <remarks>
		/// Directly apply the new settings to the list boxes. This ensures that update is only done
		/// done when required, as the update leads to move of list box to top, and re-drawing. Both
		/// takes time and impacts the monitor behavior. Thus, only update if really needed.
		/// </remarks>
		protected virtual void ApplyFont()
		{
			var f = this.formatSettings.Font;

			var lb = fastListBox_LineNumbers;
			lb.BeginUpdate();
			lb.Font = (Font)f.Clone();
			lb.ItemHeight = f.Height;
			lb.Invalidate();
			lb.EndUpdate();

			lb = fastListBox_Monitor;
			lb.BeginUpdate();
			lb.Font = (Font)f.Clone();
			lb.ItemHeight = f.Height;
			lb.Invalidate();
			lb.EndUpdate();

			var tb = textBox_CopyOfActiveLine;
			tb.Font = (Font)f.Clone();
			tb.Invalidate();

			ResizeAndRelocateControls();
		}

		/// <remarks>
		/// This method will always be called on the application main thread, either from a
		/// synchronized invocation or the synchronized 'Windows.Forms.Timer' event handler.
		/// No additional synchronization or prevention of a race condition is needed.
		/// </remarks>
		[CallingContract(IsAlwaysMainThread = true, Rationale = "Synchronized from the invoking thread onto the main thread.")]
		protected virtual void AddElementsOrLines(object elementsOrLines)
		{
			this.pendingElementsAndLines.Add(elementsOrLines);

			TriggerMonitorUpdate();
		}

		/// <remarks>
		/// This method will always be called on the application main thread, either from a
		/// synchronized invocation or the synchronized 'Windows.Forms.Timer' event handler.
		/// No additional synchronization or prevention of a race condition is needed.
		/// </remarks>
		[CallingContract(IsAlwaysMainThread = true, Rationale = "Synchronized from the invoking thread onto the main thread.")]
		private void TriggerMonitorUpdate()
		{
			// Either perform the update...
			// ...or arm the update time-out to ensure that update will be performed later:
			if (MonitorUpdateHasToBePerformed())
			{
				StopMonitorUpdateTimeout();
				UpdateFastListBoxWithPendingElementsAndLines();
			}
			else
			{
				StartMonitorUpdateTimeout(StopwatchEx.TicksToTime(this.monitorUpdateTickInterval) * 2); // Synchronous update shall have precedence over time-out.
			}
		}

		/// <remarks>
		/// This method will always be called on the application main thread, either from a
		/// synchronized invocation or the synchronized 'Windows.Forms.Timer' event handler.
		/// No additional synchronization or prevention of a race condition is needed.
		/// </remarks>
		[CallingContract(IsAlwaysMainThread = true, Rationale = "Synchronized from the invoking thread onto the main thread.")]
		private void UpdateFastListBoxWithPendingElementsAndLines()
		{
			this.findAllSuccessOnCurrentUpdate = false;

			var lblin = fastListBox_LineNumbers;
			var lbmon = fastListBox_Monitor;

			lblin.BeginUpdate();
			lbmon.BeginUpdate();

			foreach (object obj in this.pendingElementsAndLines)
			{
				{
					var element = (obj as Domain.DisplayElement);
					if (element != null)
					{
						AddElementToListBox(element);
						continue;
					}
				}
				{
					var elements = (obj as IEnumerable<Domain.DisplayElement>); // Covers [DisplayElementCollection] as well as [DisplayLine].
					if (elements != null)
					{
						foreach (var element in elements)
							AddElementToListBox(element);

						continue;
					}
				}
				{
					var lines = (obj as IEnumerable<Domain.DisplayLine>); // Covers [DisplayLineCollection].
					if (lines != null)
					{
						foreach (var line in lines)
							foreach (var element in line)
								AddElementToListBox(element);

						continue;
					}
				}

				// Kind of 'default':
				throw (new NotSupportedException(MessageHelper.InvalidExecutionPreamble + "'" + obj.GetType() + "' is a pending item that is not (yet) supported here!" + Environment.NewLine + Environment.NewLine + MessageHelper.SubmitBug));
			} // foreach (object in pending)

			this.pendingElementsAndLines.Clear();

			// Calculate tick stamp of next update:
			unchecked
			{
				this.nextMonitorUpdateTickStamp = (Stopwatch.GetTimestamp() + this.monitorUpdateTickInterval); // Loop-around is OK.
			}

			// Handle auto-scrolling in any case (a condition like "if (ItemCount >= FullyVisibleItemCount)"
			// makes little sense, as just few items will not result in an noticable drop of performance):
			if (!lbmon.UserIsScrolling) // Perform auto-scroll.
			{
				bool hasClearedSelected;

				var clearSelected = (!this.findAllIsActive);
				if (lbmon.VerticalScrollToBottomIfNoVisibleItemOrOnlyOneOfTheLastFewItemsIsSelected(clearSelected, out hasClearedSelected))
					lblin.VerticalScrollToBottom(); // Scroll line numbers accordingly.

				if (hasClearedSelected)
					DebugClearSelected();
			}
			else // UserIsScrolling => Suspend auto-scroll.
			{
				if (lbmon.VerticalScrollBarIsNearBottom) // Resume auto-scroll.
				{
					bool hasClearedSelected;

					var clearSelected = (!this.findAllIsActive);
					if (lbmon.VerticalScrollToBottomIfNoVisibleItemOrOnlyOneOfTheLastFewItemsIsSelected(clearSelected, out hasClearedSelected))
						lblin.VerticalScrollToBottom(); // Scroll line numbers accordingly.

					if (hasClearedSelected)
						DebugClearSelected();
				}
			}

			lblin.EndUpdate();
			lbmon.EndUpdate();

			DebugSelected();

			SetCopyOfActiveLine(lbmon.LastItem);

			if (this.findAllSuccessAfterLastUpdate != this.findAllSuccessOnCurrentUpdate) {
				this.findAllSuccessAfterLastUpdate = this.findAllSuccessOnCurrentUpdate;

				OnFindAllSuccessChanged(new EventArgs<bool>(this.findAllSuccessOnCurrentUpdate));
			}
		}

		/// <summary>
		/// Adds an element to the list box.
		/// </summary>
		/// <remarks>
		/// Neither calls <see cref="ListBox.BeginUpdate()"/> nor <see cref="ListBox.EndUpdate()"/>.
		/// If performance requires it, the calling function must do so.
		/// </remarks>
		protected virtual void AddElementToListBox(Domain.DisplayElement element)
		{
			var lblin = fastListBox_LineNumbers;
			var lbmon = fastListBox_Monitor;

			// If first line, add element to a new line:
			if (lbmon.Items.Count <= 0)
			{
				lblin.Items.Add(0);
				lbmon.Items.Add(new Domain.DisplayLine(element));

				UpdateCurrentIfFindAllIsActive(lbmon);
			}
			else
			{
				// Get current line:
				var current = (lbmon.LastItem as Domain.DisplayLine); // "LastItem" is defined for sure after having "Items.Count" above.

				// If first element, add element to line:
				if (current.Count <= 0)
				{
					current.Add(element);

					UpdateCurrentIfFindAllIsActive(lbmon);
				}
				else
				{
					// If a new line starts, add element to a new line.
					if (element is Domain.DisplayElement.LineStart)
					{
						// Remove lines if maximum exceeded:
						while (lbmon.Items.Count >= this.maxLineCount)
						{
							int adjustedTopIndex = Math.Max(0, (lbmon.TopIndex - 1)); // "bmon" is master; decrement accounts for item that will be removed.
							DebugVerticalAutoScroll("Removing least recent line...");
							lblin.Items.RemoveAt(0); // Remove/RemoveAt() resets 'TopIndex' to 0!
							lbmon.Items.RemoveAt(0); // \remind (2017-11-05 / MKY) check if still needed after upgrade to .NET 4.0 or higher (FR #229)
							DebugVerticalAutoScroll("......restoring 'TopIndex'...");
							lblin.TopIndex = adjustedTopIndex;
							lbmon.TopIndex = adjustedTopIndex;
							DebugVerticalAutoScroll(".........................done");

							if (this.lineNumberSelection != Domain.Utilities.LineNumberSelection.Buffer) // This option would require the offset to stay at 0.
							{
								// Increment the offset independent on 'showLineNumbers' to get
								// the indeed total value in case the user changes the setting.

								unchecked
								{
									this.lineNumberOffset++; // Overflow is OK.
								}
							}
						}

						// Add element to a new line:
						DebugVerticalAutoScroll("Adding new line..............");
						lblin.Items.Add(0); // 0 = dummy value. 'null' is not valid, it would result in an 'ArgumentNullException'.
						lbmon.Items.Add(new Domain.DisplayLine(element));
						DebugVerticalAutoScroll(".........................done");

						UpdateCurrentIfFindAllIsActive(lbmon);
					}
					else
					{
						current.Add(element);

						UpdateCurrentIfFindAllIsActive(lbmon);
					}
				}
			}
		}

		/// <summary></summary>
		protected virtual void UpdateCurrentIfFindAllIsActive(FastListBox lb)
		{
			if (this.findAllIsActive)
			{
				var index = lb.LastIndex;
				if (index >= 0)
				{
					if (!lb.GetSelected(index)) // It is very likely this method is called multiple times per line.
					{                           // But there is no need to waste time here if line is selected already.
						var result = lb.FindAt(this.findText, this.findTextCaseSensitive, this.findTextWholeWord, this.findRegex, index);
						if (result == index)
						{
							this.findAllOrSelectAllOrNoneIsChangingSelection.Enter();
							try
							{
								DebugSetSelected(index);
								lb.SetSelected(index, true);
							}
							finally
							{
								this.findAllOrSelectAllOrNoneIsChangingSelection.Leave();
							}

							this.findAllSuccessOnCurrentUpdate = true;
						}
					}
				}
			}
		}

		/// <summary></summary>
		protected static bool IsLineStart(Domain.DisplayElement element)
		{
			return ((element as Domain.DisplayElement.LineStart) != null);
		}

		/// <remarks>
		/// <c>private</c> because <see cref="ClearResult"/> is <c>private</c>.
		/// </remarks>
		private ClearResult ClearCurrentLineInPendingElementsAndLines()
		{
			bool hasCleared = false;

			while (this.pendingElementsAndLines.Count > 0)
			{
				var lastObj = this.pendingElementsAndLines[this.pendingElementsAndLines.Count - 1]; // Clearing has to be done from the end.
				{
					var element = (lastObj as Domain.DisplayElement);
					if (element != null)
					{
						this.pendingElementsAndLines.RemoveAt(this.pendingElementsAndLines.Count - 1);

						if (IsLineStart(element))
							return (ClearResult.HasClearedAndCompleted);

						hasCleared = true;
						continue;
					}
				}
				{
					var elements = (lastObj as Domain.DisplayElementCollection);
					if (elements != null)
					{
						int lineStartIndex = -1;

						for (int i = (elements.Count - 1); i >= 0; i--)
						{
							if (IsLineStart(elements[i]))
								lineStartIndex = i;
						}

						if (lineStartIndex == -1) // Collection does not contain a [LineStart], remove it and continue:
						{
							this.pendingElementsAndLines.RemoveAt(this.pendingElementsAndLines.Count - 1);
							hasCleared = true;
							continue;
						}
						else if (lineStartIndex == 0) // [LineStart] is located at the very beginning, remove it and return:
						{
							this.pendingElementsAndLines.RemoveAt(this.pendingElementsAndLines.Count - 1);
							return (ClearResult.HasClearedAndCompleted);
						}
						else // [LineStart] is located inside the collection, remove the correct elements and return:
						{
							var elementsBeforeCurrentLine = new Domain.DisplayElementCollection(); // No preset needed, default behavior is good enough.
							elements.CloneTo(0, elementsBeforeCurrentLine, (lineStartIndex - 1));
							this.pendingElementsAndLines[this.pendingElementsAndLines.Count - 1] = elementsBeforeCurrentLine;
							return (ClearResult.HasClearedAndCompleted);
						}
					}
				}
				{
					var line = (lastObj as Domain.DisplayLine);
					if (line != null)
					{
						if (hasCleared) // Currently last item is a completed line, i.e. not the *current* line, the line start of the current line is missing!
							throw (new InvalidOperationException(MessageHelper.InvalidExecutionPreamble + "The pending elements did not contain a [LineStart]!" + Environment.NewLine + Environment.NewLine + MessageHelper.SubmitBug));
						else
							return (ClearResult.NoLineOngoing); // Truly last item is a completed line, i.e. there is no current line.
					}
				}
				{
					var lines = (lastObj as Domain.DisplayLineCollection);
					if (lines != null)
					{
						if (hasCleared) // Currently last item is a completed line, i.e. not the *current* line, the line start of the current line is missing!
							throw (new InvalidOperationException(MessageHelper.InvalidExecutionPreamble + "The pending elements did not contain a [LineStart]!" + Environment.NewLine + Environment.NewLine + MessageHelper.SubmitBug));
						else
							return (ClearResult.NoLineOngoing); // Truly last item is a completed line, i.e. there is no current line.
					}
				}

				// Kind of 'default':
				throw (new NotSupportedException(MessageHelper.InvalidExecutionPreamble + "'" + lastObj.GetType() + "' is a pending item that is not (yet) supported here!" + Environment.NewLine + Environment.NewLine + MessageHelper.SubmitBug));
			} // while (has pending)

			if (hasCleared)
				return (ClearResult.HasClearedButIsIncomplete);
			else
				return (ClearResult.NoElementOrLinePending);
		}

		/// <summary></summary>
		protected virtual void ClearCurrentLineInListBoxes()
		{
		////var lblin = fastListBox_LineNumbers => Nothing to do (yet).
			var lbmon = fastListBox_Monitor;

			if (!ICollectionEx.IsNullOrEmpty(lbmon.Items)) // "bmon" is master.
			{
				var dl = (lbmon.Items[lbmon.Items.Count - 1] as Domain.DisplayLine);
				if (!ICollectionEx.IsNullOrEmpty(dl) && (!dl.IsComplete)) // "IsComplete" means that this is no longer the "current" line.
				{
					dl.Clear();
					lbmon.Invalidate();
				}
			}
		}

		/// <summary></summary>
		protected virtual void RemoveCurrentLineFromListBoxes()
		{
			var lblin = fastListBox_LineNumbers;
			var lbmon = fastListBox_Monitor;

			if (!ICollectionEx.IsNullOrEmpty(lbmon.Items)) // "bmon" is master.
			{
				var dl = (lbmon.Items[lbmon.Items.Count - 1] as Domain.DisplayLine);
				if (!ICollectionEx.IsNullOrEmpty(dl) && (!dl.IsComplete)) // "IsComplete" means that this is no longer the "current" line.
				{
					int adjustedTopIndex = Math.Max(0, (lbmon.TopIndex - 1)); // "bmon" is master; decrement accounts for item that will be removed.
					DebugVerticalAutoScroll("Clearing current line...");
					lblin.Items.RemoveAt(lblin.Items.Count - 1); // Remove/RemoveAt() resets 'TopIndex' to 0!
					lbmon.Items.RemoveAt(lbmon.Items.Count - 1);
					DebugVerticalAutoScroll("..restoring 'TopIndex'.."); // Aligned with output above and below.
					lblin.TopIndex = adjustedTopIndex;
					lbmon.TopIndex = adjustedTopIndex;
					DebugVerticalAutoScroll("....................done");
				}
			}
		}

		/// <summary></summary>
		protected virtual void ClearAndResetListBoxes()
		{
			var lblin = fastListBox_LineNumbers;
			lblin.BeginUpdate();
			lblin.Items.Clear();
			lblin.EndUpdate();

			var lbmon = fastListBox_Monitor;
			lbmon.BeginUpdate();
			lbmon.Items.Clear();
			lbmon.NotifyCleared();
			lbmon.HorizontalExtent = 0;
			lbmon.EndUpdate();

			ResizeAndRelocateControls(this.initialLineNumberWidth);
		}

		private void ResizeAndRelocateControls()
		{
			ResizeAndRelocateControls(this.currentLineNumberWidth);
		}

		private void ResizeAndRelocateControls(int requestedLineNumberWidth)
		{
			var lblin = fastListBox_LineNumbers;
			var lbmon = fastListBox_Monitor;

			// --- Width ---

			lblin.Visible = ShowLineNumbers;

			if (ShowLineNumbers)
			{
				int effectiveWidth = requestedLineNumberWidth + VerticalScrollBarWidth + AdditionalMargin;
				lblin.Width = effectiveWidth;

				int effectiveLeft = requestedLineNumberWidth + AdditionalMargin; // Hide the vertical scroll
				lbmon.Left = effectiveLeft;                                      // bar of the line numbers.
				lbmon.Width = (Width - effectiveLeft);

				textBox_CopyOfActiveLine.Left = effectiveLeft;
				textBox_CopyOfActiveLine.Width = (Width - effectiveLeft);
			}
			else
			{
				lbmon.Left = 0;
				lbmon.Width = Width;

				textBox_CopyOfActiveLine.Left = 0;
				textBox_CopyOfActiveLine.Width = Width;
			}

			this.currentLineNumberWidth = requestedLineNumberWidth;

			// --- Height ---

			var availableHeight = Height;
			var showAL = ShowCopyOfActiveLine;

			textBox_CopyOfActiveLine.Visible = showAL;

			if (showAL)
			{
				int activeLineHeight = (textBox_CopyOfActiveLine.Height + 1); // 1 aligns with 'SendPredefined'.
				textBox_CopyOfActiveLine.Top = (Height - activeLineHeight);

				availableHeight -= (activeLineHeight + 3); // 3 standard margin.
			}
			else
			{
				availableHeight -= 1; // 1 aligns with 'SendPredefined'.
			}

			if (ShowStatusPanel)
			{
				availableHeight -= panel_Picture.Height;

				lblin.Height = availableHeight;
				lblin.Top = panel_Picture.Height;

				lbmon.Height = availableHeight;
				lbmon.Top = panel_Picture.Height;
			}
			else
			{
				lblin.Top = 0;
				lblin.Height = availableHeight;

				lbmon.Top = 0;
				lbmon.Height = availableHeight;
			}
		}

		/// <remarks>
		/// Name only "Active" instead of "LastActive" for simplicity.
		/// </remarks>
		protected virtual void SetCopyOfActiveLine(object selectedItem)
		{
			string lineText = "";

			var dl = (selectedItem as Domain.DisplayLine);
			if (dl != null)
				lineText = dl.Text;

			textBox_CopyOfActiveLine.Text = lineText;
		}

		/// <remarks>Separated from <see cref="SetTimeStatusText"/> to improve performance.</remarks>
		protected virtual void SetTimeStatusVisible()
		{
			label_TimeStatus_Active.Visible = ShowTimeStatus;
			label_TimeStatus_Total .Visible = ShowTimeStatus;
		}

		/// <summary></summary>
		protected virtual void SetTimeStatusText()
		{
			label_TimeStatus_Active.Text = this.timeStatusHelper.ActiveStatusText;
			label_TimeStatus_Total .Text = this.timeStatusHelper.TotalStatusText;
		}

		/// <remarks>Separated from <see cref="SetDataStatusText"/> to improve performance.</remarks>
		protected virtual void SetDataStatusVisible()
		{
			label_DataStatus_BidirTx.Visible = (ShowDataStatus && (RepositoryType == Domain.RepositoryType.Bidir));
			label_DataStatus_Unidir .Visible = (ShowDataStatus && (RepositoryType != Domain.RepositoryType.Bidir));
			label_DataStatus_BidirRx.Visible = (ShowDataStatus && (RepositoryType == Domain.RepositoryType.Bidir));
		}

		/// <summary></summary>
		protected virtual void SetDataStatusText()
		{
			// Either perform the update...
			// ...or arm the update time-out to ensure that update will be performed later:
			if (DataStatusUpdateHasToBePerformed())
				UpdateDataStatusText();
			else
				StartDataStatusUpdateTimeout();
		}

		private void UpdateDataStatusText()
		{
			switch (RepositoryType)
			{
				case Domain.RepositoryType.Tx:    label_DataStatus_Unidir .Text = this.dataStatusHelper.TxStatusText; break;
				case Domain.RepositoryType.Bidir: label_DataStatus_BidirTx.Text = this.dataStatusHelper.TxStatusText;
				                                  label_DataStatus_BidirRx.Text = this.dataStatusHelper.RxStatusText; break;
				case Domain.RepositoryType.Rx:    label_DataStatus_Unidir .Text = this.dataStatusHelper.RxStatusText; break;

				case Domain.RepositoryType.None:
				default: /* Do nothing, and also don't throw, as this case/default will occur during control init. */ break;
			}

			// Calculate tick stamp of next update:
			unchecked
			{
				this.nextDataStatusUpdateTickStamp = (Stopwatch.GetTimestamp() + DataStatusTickInterval); // Loop-around is OK.
			}
		}

		/// <summary>
		/// The update interval is calculated dependent on the total CPU load:
		///
		///      update interval in ms
		///                 ^
		///      max = 1125 |-------------xx|
		///                 |            x  |
		///                 |           x   |
		///                 |          x    |
		///                 |       xx      |
		///        min = 41 |xxxxx          |
		///                 o-----------------> total CPU load in %
		///                 0  25  50  75  100
		///
		/// Up to 25%, the update is done more or less immediately.
		/// Above 95%, the update is done every 1125 ms.
		/// Quadratic inbetween, at y = x^2.
		///
		/// Rationale:
		///  - For better user expericence, interval shall gradually increase.
		///  - Even at high CPU load, there shall still be some updating.
		/// </summary>
		/// <param name="processorLoadPercentage">
		/// Load in %, i.e. values from 0 to 100.
		/// </param>
		[SuppressMessage("StyleCop.CSharp.DocumentationRules", "SA1650:ElementDocumentationMustBeSpelledCorrectly", Justification = "'Inbetween' is a correct English term.")]
		private void CalculateUpdateTickInterval(int processorLoadPercentage)
		{
			const int LowerLoad = 25; // %
			const int UpperLoad = 95; // %

			const int LowerInterval =   41; // Interval shall be quite short => fixed to 41 ms (a prime number) = approx. 24 updates per second.
			const int UpperInterval = 1125; // = (75*75) / 5 => eases calculation.

			if (processorLoadPercentage < LowerLoad)
			{
				this.monitorUpdateTickInterval = StopwatchEx.TimeToTicks(LowerInterval);
				this.performImmediateMonitorAndStatusUpdate = true;

				DebugUpdate("minimum update interval of ");
			}
			else if (processorLoadPercentage > UpperLoad)
			{
				this.monitorUpdateTickInterval = StopwatchEx.TimeToTicks(UpperInterval);
				this.performImmediateMonitorAndStatusUpdate = false;

				DebugUpdate("maximum update interval of ");
			}
			else
			{
				int x = (processorLoadPercentage - LowerLoad); // Resulting x must be max. 75%.
				int y = (LowerInterval + ((x * x) / 5));

				y = Int32Ex.Limit(y, LowerInterval, UpperInterval); // "min" and "max" are fixed.

				this.monitorUpdateTickInterval = StopwatchEx.TimeToTicks(y);
				this.performImmediateMonitorAndStatusUpdate = false;

				DebugUpdate("calculated update interval of ");
			}

			DebugUpdate(this.monitorUpdateTickInterval.ToString(CultureInfo.CurrentCulture) + " ticks = ");
			DebugUpdate(StopwatchEx.TicksToTime(this.monitorUpdateTickInterval).ToString(CultureInfo.CurrentCulture) + " ms.");
			DebugUpdate(Environment.NewLine);
		}

		/// <summary>
		/// Either perform the update if immediate update is active (e.g. low data traffic)
		/// or if the tick interval has expired.
		/// </summary>
		private bool MonitorUpdateHasToBePerformed()
		{
			// Immediate update:
			if (this.performImmediateMonitorAndStatusUpdate)
				return (true);

			// Calculate whether the update interval has expired:
			if (Stopwatch.GetTimestamp() >= this.nextMonitorUpdateTickStamp)
				return (true);

			return (false);
		}

		private void StopMonitorUpdateTimeout()
		{
			if (timer_MonitorUpdateTimeout.Enabled)
				timer_MonitorUpdateTimeout.Stop();
		}

		/// <param name="timeout">
		/// The value cannot be less than one.
		/// </param>
		/// <exception cref="ArgumentOutOfRangeException">
		/// The <paramref name="timeout"/> value is less than one.
		/// </exception>
		private void StartMonitorUpdateTimeout(int timeout)
		{
			if (!timer_MonitorUpdateTimeout.Enabled && (timeout > 0))
			{
				timer_MonitorUpdateTimeout.Interval = timeout;
				timer_MonitorUpdateTimeout.Start();
			}
		}

		/// <summary>
		/// Either perform the update if immediate update is active (e.g. low data traffic)
		/// or if the tick interval has expired.
		/// </summary>
		private bool DataStatusUpdateHasToBePerformed()
		{
			// Immediate update:
			if (this.performImmediateMonitorAndStatusUpdate)
				return (true);

			// Calculate whether the update interval has expired:
			if (Stopwatch.GetTimestamp() >= this.nextDataStatusUpdateTickStamp)
				return (true);

			return (false);
		}

		private void StopDataStatusUpdateTimeout()
		{
			if (timer_DataStatusUpdateTimeout.Enabled)
				timer_DataStatusUpdateTimeout.Stop();
		}

		private void StartDataStatusUpdateTimeout()
		{
			if (!timer_DataStatusUpdateTimeout.Enabled)
				timer_DataStatusUpdateTimeout.Start();
		}

		#endregion

		#region Event Raising
		//==========================================================================================
		// Event Raising
		//==========================================================================================

		/// <summary></summary>
		protected virtual void OnTextFocusedChanged(EventArgs e)
		{
			EventHelper.RaiseSync(TextFocusedChanged, this, e);
		}

		/// <summary></summary>
		protected virtual void OnSelectedLinesChanged(EventArgs<int> e)
		{
			EventHelper.RaiseSync<EventArgs<int>>(SelectedLinesChanged, this, e);
		}

		/// <summary></summary>
		protected virtual void OnFindItemStateChanged(EventArgs e)
		{
			EventHelper.RaiseSync(FindItemStateChanged, this, e);
		}

		/// <summary></summary>
		protected virtual void OnFindAllSuccessChanged(EventArgs<bool> e)
		{
			EventHelper.RaiseSync<EventArgs<bool>>(FindAllSuccessChanged, this, e);
		}

		/// <summary></summary>
		protected virtual void OnFindAllDeactivatedWithinMonitor(EventArgs e)
		{
			EventHelper.RaiseSync(FindAllDeactivatedWithinMonitor, this, e);
		}

		#endregion

		#region Debug
		//==========================================================================================
		// Debug
		//==========================================================================================

		/// <remarks>
		/// Name "DebugWriteLine" would show relation to <see cref="Debug.WriteLine(string)"/>.
		/// However, named "Message" for compactness and more clarity that something will happen
		/// with the formatted message, and rather than e.g. "Common" for comprehensibility.
		/// </remarks>
		[Conditional("DEBUG")]
		protected virtual void DebugMessage(string format, params object[] args)
		{
			DebugMessage(string.Format(CultureInfo.CurrentCulture, format, args));
		}

		/// <remarks>
		/// Name "DebugWriteLine" would show relation to <see cref="Debug.WriteLine(string)"/>.
		/// However, named "Message" for compactness and more clarity that something will happen
		/// with <paramref name="message"/>, and rather than e.g. "Common" for comprehensibility.
		/// </remarks>
		[Conditional("DEBUG")]
		protected virtual void DebugMessage(string message)
		{
			Debug.WriteLine
			(
				string.Format
				(
					CultureInfo.CurrentCulture,
					" @ {0} @ Thread #{1} : {2,36} {3,3} {4,-38} : {5}",
					DateTime.Now.ToString("HH:mm:ss.fff", DateTimeFormatInfo.CurrentInfo),
					Thread.CurrentThread.ManagedThreadId.ToString("D3", CultureInfo.CurrentCulture),
					GetType(),
					DebugCaption,
					"",
					message
				)
			);
		}

		/// <remarks>
		/// <c>private</c> because value of <see cref="ConditionalAttribute"/> is limited to file scope.
		/// </remarks>
		[Conditional("DEBUG_CONTENT")]
		private void DebugContent(string message)
		{
			if (DebugEnabled)
			{
				DebugMessage(message);
			}
		}

		/// <remarks>
		/// Using <see cref="Debug.Write(string)"/> for manually composing line.
		/// </remarks>
		/// <remarks>
		/// <c>private</c> because value of <see cref="ConditionalAttribute"/> is limited to file scope.
		/// </remarks>
		[Conditional("DEBUG_UPDATE")]
		private void DebugUpdate(string message)
		{
			if (DebugEnabled)
			{
				DebugMessage(message);
			}
		}

		/// <remarks>
		/// <c>private</c> because value of <see cref="ConditionalAttribute"/> is limited to file scope.
		/// </remarks>
		[Conditional("DEBUG_VERTICAL_AUTO_SCROLL")]
		private void DebugVerticalAutoScroll(string leadMessage)
		{
			if (DebugEnabled)
			{
				var lbmon = fastListBox_Monitor;

				DebugMessage
				(
					string.Format
					(
						CultureInfo.CurrentCulture,
						"{0} : ItemCount = {1} | FullyVisibleItemCount = {2} | TotalVisibleItemCount = {3} | TopIndex = {4} | BottomIndex = {5}",
						leadMessage,
						lbmon.Items.Count,
						lbmon.FullyVisibleItemCount,
						lbmon.TotalVisibleItemCount,
						lbmon.TopIndex,
						lbmon.BottomIndex
					)
				);
			}
		}

		/// <remarks>
		/// <c>private</c> because value of <see cref="ConditionalAttribute"/> is limited to file scope.
		/// </remarks>
		[Conditional("DEBUG_SELECTION")]
		private void DebugSetSelected(int index, [CallerMemberName] string callerMemberName = "")
		{
			if (DebugEnabled)
			{
				if (index != ControlEx.InvalidIndex)
					DebugMessage("ListBox.SetSelected({0}) @ {1}()", index, callerMemberName);
				else
					DebugMessage("ListBox.SetSelected(*) @ {0}()", callerMemberName);
			}
		}

		/// <remarks>
		/// <c>private</c> because value of <see cref="ConditionalAttribute"/> is limited to file scope.
		/// </remarks>
		[Conditional("DEBUG_SELECTION")]
		private void DebugClearSelected(int index, [CallerMemberName] string callerMemberName = "")
		{
			if (DebugEnabled)
			{
				if (index != ControlEx.InvalidIndex)
					DebugMessage("ListBox.ClearSelected({0}) @ {1}()", index, callerMemberName);
				else
					DebugMessage("ListBox.ClearSelected(*) @ {0}()", callerMemberName);
			}
		}

		/// <remarks>
		/// <c>private</c> because value of <see cref="ConditionalAttribute"/> is limited to file scope.
		/// </remarks>
		[Conditional("DEBUG_SELECTION")]
		private void DebugClearSelected([CallerMemberName] string callerMemberName = "")
		{
			if (DebugEnabled)
			{
				DebugMessage("ListBox.ClearSelected() @ {0}()", callerMemberName);
			}
		}

		/// <remarks>
		/// <c>private</c> because value of <see cref="ConditionalAttribute"/> is limited to file scope.
		/// </remarks>
		[Conditional("DEBUG_SELECTION")]
		private void DebugSelected()
		{
			if (DebugEnabled)
			{
				DebugMessage("ListBox.SelectedIndices is [{0}]", IEnumerableEx.ItemsToString(fastListBox_Monitor.SelectedIndices));
			}
		}

		#endregion
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.View.Controls/Monitor.cs $
//==================================================================================================
