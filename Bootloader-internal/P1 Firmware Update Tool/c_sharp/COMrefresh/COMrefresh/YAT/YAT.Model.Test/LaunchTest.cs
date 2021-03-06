//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Model.Test/LaunchTest.cs $
// $Revision: 3789 $
// $Date: 2021-04-28 08:29:13 +0000 (Wed, 28 Apr 2021) $
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

#region Using
//==================================================================================================
// Using
//==================================================================================================

using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.IO;

using MKY.IO;
using MKY.Settings;

using NUnit.Framework;

using YAT.Application.Settings;
using YAT.Settings.Application;
using YAT.Settings.Model.Test;

#endregion

namespace YAT.Model.Test
{
	/// <summary></summary>
	[TestFixture]
	public class LaunchTest
	{
		#region Constants
		//==========================================================================================
		// Constants
		//==========================================================================================

		// Empty:

		[SuppressMessage("StyleCop.CSharp.NamingRules", "SA1306:FieldNamesMustBeginWithLowerCaseLetter", Justification = "This is a 'readonly', thus meant to be constant.")]
		private readonly string EmptyTerminalFilePath = SettingsFilesProvider.FilePaths_Empty.TerminalFilePaths[TerminalSettingsTestCase.T_Empty];

		[SuppressMessage("StyleCop.CSharp.NamingRules", "SA1306:FieldNamesMustBeginWithLowerCaseLetter", Justification = "This is a 'readonly', thus meant to be constant.")]
		private readonly string EmptyWorkspaceFilePath = SettingsFilesProvider.FilePaths_Empty.WorkspaceFilePaths[WorkspaceSettingsTestCase.W_Empty];

		// Current:

		[SuppressMessage("StyleCop.CSharp.NamingRules", "SA1306:FieldNamesMustBeginWithLowerCaseLetter", Justification = "This is a 'readonly', thus meant to be constant.")]
		private readonly string TerminalFilePath = SettingsFilesProvider.FilePaths_Current.TerminalFilePaths[TerminalSettingsTestCase.T_00_COM1_Closed_Default];

		[SuppressMessage("StyleCop.CSharp.NamingRules", "SA1306:FieldNamesMustBeginWithLowerCaseLetter", Justification = "This is a 'readonly', thus meant to be constant.")]
		private readonly string Terminal1FilePath = SettingsFilesProvider.FilePaths_Current.TerminalFilePaths[TerminalSettingsTestCase.T_00_COM1_Closed_Default];

		[SuppressMessage("StyleCop.CSharp.NamingRules", "SA1306:FieldNamesMustBeginWithLowerCaseLetter", Justification = "This is a 'readonly', thus meant to be constant.")]
		private readonly string Terminal2FilePath = SettingsFilesProvider.FilePaths_Current.TerminalFilePaths[TerminalSettingsTestCase.T_00_COM2_Closed_Default];

		[SuppressMessage("StyleCop.CSharp.NamingRules", "SA1306:FieldNamesMustBeginWithLowerCaseLetter", Justification = "This is a 'readonly', thus meant to be constant.")]
		private readonly string WorkspaceFilePath = SettingsFilesProvider.FilePaths_Current.WorkspaceFilePaths[WorkspaceSettingsTestCase.W_04_Matthias];

		#endregion

		#region TestFixture
		//==========================================================================================
		// TestFixture
		//==========================================================================================

		/// <summary></summary>
		[SuppressMessage("Microsoft.Naming", "CA1702:CompoundWordsShouldBeCasedCorrectly", MessageId = "SetUp", Justification = "Naming according to NUnit.")]
		[TestFixtureSetUp]
		public virtual void TestFixtureSetUp()
		{
			// Create temporary in-memory application settings for this test run:
			ApplicationSettings.Create(ApplicationSettingsFileAccess.None);

			// Prevent auto-save of workspace settings:
			ApplicationSettings.LocalUserSettings.General.AutoSaveWorkspace = false;

			// Ensure that recent files are contained:
			ApplicationSettings.LocalUserSettings.RecentFiles = new RecentFileSettings();
			ApplicationSettings.LocalUserSettings.RecentFiles.FilePaths.Add(TerminalFilePath);
			ApplicationSettings.LocalUserSettings.RecentFiles.FilePaths.Add(WorkspaceFilePath);
			ApplicationSettings.LocalUserSettings.RecentFiles.SetChanged(); // Manual change required because underlying collection is modified.
		}

		/// <summary></summary>
		[SuppressMessage("Microsoft.Naming", "CA1702:CompoundWordsShouldBeCasedCorrectly", MessageId = "TearDown", Justification = "Naming according to NUnit.")]
		[TestFixtureTearDown]
		public virtual void TestFixtureTearDown()
		{
			// Close and dispose of temporary in-memory application settings:
			ApplicationSettings.CloseAndDispose();

			Temp.CleanTempPath(GetType());
		}

		#endregion

		#region Tests
		//==========================================================================================
		// Tests
		//==========================================================================================

		#region Tests > EmptyPrepare
		//------------------------------------------------------------------------------------------
		// Tests > EmptyPrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestEmptyPrepare()
		{
			using (var m = new Main())
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler, Is.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,  Is.Null);
				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,    Is.True);

				Assert.That(m.LaunchArgs.PerformOperationOnRequestedTerminal, Is.False);
				Assert.That(m.LaunchArgs.RequestedDynamicTerminalId,          Is.EqualTo(TerminalIds.ActiveDynamicId));
				Assert.That(m.LaunchArgs.RequestedFixedTerminalId,            Is.EqualTo(TerminalIds.ActiveFixedId));
				Assert.That(m.LaunchArgs.RequestedTransmitText,               Is.Null.Or.Empty);
				Assert.That(m.LaunchArgs.RequestedTransmitFilePath,           Is.Null.Or.Empty);
				Assert.That(m.LaunchArgs.IsAutoRun,                           Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,                          Is.False);

				Assert.That(m.LaunchArgs.KeepOpen,             Is.True);
				Assert.That(m.LaunchArgs.KeepOpenOnNonSuccess, Is.True);
				Assert.That(m.LaunchArgs.TileHorizontal,       Is.False);
				Assert.That(m.LaunchArgs.TileVertical,         Is.False);
			}
		}

		#endregion

		#region Tests > TerminalFilePathPrepare
		//------------------------------------------------------------------------------------------
		// Tests > TerminalFilePathPrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestTerminalFilePathPrepare()
		{
			using (var m = new Main(TerminalFilePath))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler,                 Is.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,                  Is.Not.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.SettingsFilePath, Is.EqualTo(TerminalFilePath));
				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,                    Is.False);
				Assert.That(m.LaunchArgs.IsAutoRun,                                Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,                               Is.False);
			}

			using (var m = new Main(new CommandLineArgs(new string[] { TerminalFilePath })))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler,                 Is.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,                  Is.Not.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.SettingsFilePath, Is.EqualTo(TerminalFilePath));
				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,                    Is.False);
				Assert.That(m.LaunchArgs.IsAutoRun,                                Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,                               Is.False);
			}
		}

		#endregion

		#region Tests > WorkspaceFilePathPrepare
		//------------------------------------------------------------------------------------------
		// Tests > WorkspaceFilePathPrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestWorkspaceFilePathPrepare()
		{
			using (var m = new Main(WorkspaceFilePath))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler,                  Is.Not.Null);
				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler.SettingsFilePath, Is.EqualTo(WorkspaceFilePath));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,                   Is.Null);
				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,                     Is.False);
				Assert.That(m.LaunchArgs.IsAutoRun,                                 Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,                                Is.False);
			}

			using (var m = new Main(new CommandLineArgs(new string[] { WorkspaceFilePath })))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler,                  Is.Not.Null);
				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler.SettingsFilePath, Is.EqualTo(WorkspaceFilePath));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,                   Is.Null);
				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,                     Is.False);
				Assert.That(m.LaunchArgs.IsAutoRun,                                 Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,                                Is.False);
			}
		}

		#endregion

		#region Tests > EmptyTerminalFilePathPrepare
		//------------------------------------------------------------------------------------------
		// Tests > EmptyTerminalFilePathPrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestEmptyTerminalFilePathPrepare()
		{                   // Format following NUnit's "***** YAT.Model.Test.StartTest.<Test>"
			Trace.Write(" > ** INFO: This test will throw several XML related exception because empty files are being used.");

			using (var m = new Main(EmptyTerminalFilePath))
			{
				PrepareLaunchAndVerifyResult(m, MainResult.CommandLineError);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler, Is.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,  Is.Null);
				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,    Is.False);
				Assert.That(m.LaunchArgs.IsAutoRun,                Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,               Is.False);
			}

			using (var m = new Main(new CommandLineArgs(new string[] { EmptyTerminalFilePath })))
			{
				PrepareLaunchAndVerifyResult(m, MainResult.CommandLineError);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler, Is.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,  Is.Null);
				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,    Is.False);
				Assert.That(m.LaunchArgs.IsAutoRun,                Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,               Is.False);
			}

			Trace.Write(" > ** INFO: End of test.");
		}

		#endregion

		#region Tests > EmptyWorkspaceFilePathPrepare
		//------------------------------------------------------------------------------------------
		// Tests > EmptyWorkspaceFilePathPrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestEmptyWorkspaceFilePathPrepare()
		{                   // Format following NUnit's "***** YAT.Model.Test.StartTest.<Test>"
			Trace.Write(" > ** INFO: This test will throw several XML related exception because empty files are being used.");

			using (var m = new Main(EmptyWorkspaceFilePath))
			{
				PrepareLaunchAndVerifyResult(m, MainResult.CommandLineError);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler, Is.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,  Is.Null);
				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,    Is.False);
				Assert.That(m.LaunchArgs.IsAutoRun,                Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,               Is.False);
			}

			using (var m = new Main(new CommandLineArgs(new string[] { EmptyWorkspaceFilePath })))
			{
				PrepareLaunchAndVerifyResult(m, MainResult.CommandLineError);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler, Is.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,  Is.Null);
				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,    Is.False);
				Assert.That(m.LaunchArgs.IsAutoRun,                Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,               Is.False);
			}

			Trace.Write(" > ** INFO: End of test.");
		}

		#endregion

		#region Tests > OpenOptionPrepare
		//------------------------------------------------------------------------------------------
		// Tests > OpenOptionPrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestOpenOptionPrepare()
		{
			// Workspace only:
			using (var m = new Main(new CommandLineArgs(new string[] { "--Open=" + WorkspaceFilePath })))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler,                  Is.Not.Null);
				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler.SettingsFilePath, Is.EqualTo(WorkspaceFilePath));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,                   Is.Null);
				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,                     Is.False);
				Assert.That(m.LaunchArgs.IsAutoRun,                                 Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,                                Is.False);
			}

			// Terminal only:
			using (var m = new Main(new CommandLineArgs(new string[] { "--Open=" + Terminal1FilePath })))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler,                 Is.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,                  Is.Not.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.SettingsFilePath, Is.EqualTo(Terminal1FilePath));
				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,                    Is.False);
				Assert.That(m.LaunchArgs.IsAutoRun,                                Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,                               Is.False);
			}

			// Workspace + Terminal = Terminal (the last argument is used):
			using (var m = new Main(new CommandLineArgs(new string[] { "--Open=" + WorkspaceFilePath, "--Open=" + Terminal1FilePath })))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler,                 Is.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,                  Is.Not.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.SettingsFilePath, Is.EqualTo(Terminal1FilePath));
				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,                    Is.False);
				Assert.That(m.LaunchArgs.IsAutoRun,                                Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,                               Is.False);
			}

			// Terminal + Workspace = Workspace (the last argument is used):
			using (var m = new Main(new CommandLineArgs(new string[] { "--Open=" + Terminal1FilePath, "--Open=" + WorkspaceFilePath })))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler,                  Is.Not.Null);
				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler.SettingsFilePath, Is.EqualTo(WorkspaceFilePath));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,                   Is.Null);
				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,                     Is.False);
				Assert.That(m.LaunchArgs.IsAutoRun,                                 Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,                                Is.False);
			}

			// Terminal1 + Terminal2 = Terminal2 (the last argument is used):
			using (var m = new Main(new CommandLineArgs(new string[] { "--Open=" + Terminal1FilePath, "--Open=" + Terminal2FilePath })))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler,                 Is.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,                  Is.Not.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.SettingsFilePath, Is.EqualTo(Terminal2FilePath));
				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,                    Is.False);
				Assert.That(m.LaunchArgs.IsAutoRun,                                Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,                               Is.False);
			}

			// Invalid file:
			string invalidFilePath = "MyFile.txt";
			using (var m = new Main(new CommandLineArgs(new string[] { "--Open=" + invalidFilePath })))
			{
				PrepareLaunchAndVerifyResult(m, MainResult.CommandLineError);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler, Is.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,  Is.Null);
			}
		}

		#endregion

		#region Tests > RecentOptionPrepare
		//------------------------------------------------------------------------------------------
		// Tests > RecentOptionPrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestRecentOptionPrepare()
		{
			using (var m = new Main(new CommandLineArgs(new string[] { "--Recent" })))
			{
				PrepareMainAndVerifyResult(m);

				bool hasRecent = ((m.LaunchArgs.TerminalSettingsHandler != null) || ((m.LaunchArgs.WorkspaceSettingsHandler != null)));
				Assert.That(hasRecent, Is.True);
				Assert.That(m.LaunchArgs.ShowNewTerminalDialog, Is.False);
				Assert.That(m.LaunchArgs.IsAutoRun,             Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,            Is.False);
			}
		}

		#endregion

		#region Tests > NewOptionPrepare
		//------------------------------------------------------------------------------------------
		// Tests > NewOptionPrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestNewOptionPrepare()
		{
			using (var m = new Main(new CommandLineArgs(new string[] { "--New" })))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.ShowNewTerminalDialog, Is.False);
				Assert.That(m.LaunchArgs.IsAutoRun,             Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,            Is.False);
			}
		}

		#endregion

		#region Tests > NewSerialPortOptionsPrepare
		//------------------------------------------------------------------------------------------
		// Tests > NewSerialPortOptionsPrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestNewSerialPortOptionsPrepare()
		{
			using (var m = new Main(new CommandLineArgs(new string[] { "--New", "--TerminalType=Binary", "--SerialPort=5", "--DataBits=7", "--Parity=E", "--FlowControl=Software", "--LogOn" })))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.TerminalSettingsHandler, Is.Not.Null);

				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.TerminalType, Is.EqualTo(Domain.TerminalType.Binary));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IOType,       Is.EqualTo(Domain.IOType.SerialPort));

				Assert.That((int)m.LaunchArgs.TerminalSettingsHandler.Settings.IO.SerialPort.PortId, Is.EqualTo(5)); // COM5

				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IO.SerialPort.Communication.BaudRate,    Is.EqualTo(MKY.IO.Serial.SerialPort.SerialCommunicationSettings.BaudRateDefault));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IO.SerialPort.Communication.DataBits,    Is.EqualTo(MKY.IO.Ports.DataBits.Seven));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IO.SerialPort.Communication.Parity,      Is.EqualTo(System.IO.Ports.Parity.Even));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IO.SerialPort.Communication.StopBits,    Is.EqualTo(MKY.IO.Serial.SerialPort.SerialCommunicationSettings.StopBitsDefault));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IO.SerialPort.Communication.FlowControl, Is.EqualTo(MKY.IO.Serial.SerialPort.SerialFlowControl.Software));

				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IO.SerialPort.SignalXOnWhenOpened,   Is.EqualTo(MKY.IO.Serial.SerialPort.SerialPortSettings.SignalXOnWhenOpenedDefault));

				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IO.SerialPort.AliveMonitor.Enabled,  Is.EqualTo(MKY.IO.Serial.SerialPort.SerialPortSettings.AliveMonitorDefault.Enabled));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IO.SerialPort.AliveMonitor.Interval, Is.EqualTo(MKY.IO.Serial.SerialPort.SerialPortSettings.AliveMonitorDefault.Interval));

				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IO.SerialPort.AutoReopen.Enabled,  Is.EqualTo(MKY.IO.Serial.SerialPort.SerialPortSettings.AutoReopenDefault.Enabled));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IO.SerialPort.AutoReopen.Interval, Is.EqualTo(MKY.IO.Serial.SerialPort.SerialPortSettings.AutoReopenDefault.Interval));

				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.TerminalIsStarted, Is.True);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.LogIsOn,           Is.True);

				Assert.That(m.LaunchArgs.PerformOperationOnRequestedTerminal, Is.False);
				Assert.That(m.LaunchArgs.RequestedDynamicTerminalId,          Is.EqualTo(TerminalIds.ActiveDynamicId));
				Assert.That(m.LaunchArgs.RequestedFixedTerminalId,            Is.EqualTo(TerminalIds.ActiveFixedId));
				Assert.That(m.LaunchArgs.RequestedTransmitText,               Is.Null.Or.Empty);
				Assert.That(m.LaunchArgs.RequestedTransmitFilePath,           Is.Null.Or.Empty);
				Assert.That(m.LaunchArgs.IsAutoRun,                           Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,                          Is.False);

				Assert.That(m.LaunchArgs.ShowNewTerminalDialog, Is.False);

				Assert.That(m.LaunchArgs.KeepOpen,             Is.True);
				Assert.That(m.LaunchArgs.KeepOpenOnNonSuccess, Is.True);
				Assert.That(m.LaunchArgs.TileHorizontal,       Is.False);
				Assert.That(m.LaunchArgs.TileVertical,         Is.False);
			}
		}

		#endregion

		#region Tests > NewTcpAutoSocketOptionsPrepare
		//------------------------------------------------------------------------------------------
		// Tests > NewTcpAutoSocketOptionsPrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestNewTcpAutoSocketOptionsPrepare()
		{
			using (var m = new Main(new CommandLineArgs(new string[] { "--New", "--IOType=TCPAutoSocket", "--RemotePort=12345", "--LocalPort=56789", "--LogOn" })))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.TerminalSettingsHandler, Is.Not.Null);

				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.TerminalType, Is.EqualTo(Domain.TerminalType.Text));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IOType,       Is.EqualTo(Domain.IOType.TcpAutoSocket));

				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IO.Socket.RemoteHost, Is.EqualTo((MKY.Net.IPHostEx)MKY.Net.IPHost.Localhost));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IO.Socket.RemotePort, Is.EqualTo(12345));

				Assert.That((MKY.Net.IPNetworkInterfaceEx)m.LaunchArgs.TerminalSettingsHandler.Settings.IO.Socket.LocalInterface, Is.EqualTo((MKY.Net.IPNetworkInterfaceEx)MKY.Net.IPNetworkInterface.Any));
				Assert.That(                              m.LaunchArgs.TerminalSettingsHandler.Settings.IO.Socket.LocalPort,      Is.EqualTo(56789));

				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.TerminalIsStarted, Is.True);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.LogIsOn,           Is.True);

				Assert.That(m.LaunchArgs.PerformOperationOnRequestedTerminal, Is.False);
				Assert.That(m.LaunchArgs.RequestedDynamicTerminalId,          Is.EqualTo(TerminalIds.ActiveDynamicId));
				Assert.That(m.LaunchArgs.RequestedFixedTerminalId,            Is.EqualTo(TerminalIds.ActiveFixedId));
				Assert.That(m.LaunchArgs.RequestedTransmitText,               Is.Null.Or.Empty);
				Assert.That(m.LaunchArgs.RequestedTransmitFilePath,           Is.Null.Or.Empty);
				Assert.That(m.LaunchArgs.IsAutoRun,                           Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,                          Is.False);

				Assert.That(m.LaunchArgs.ShowNewTerminalDialog, Is.False);

				Assert.That(m.LaunchArgs.KeepOpen,             Is.True);
				Assert.That(m.LaunchArgs.KeepOpenOnNonSuccess, Is.True);
				Assert.That(m.LaunchArgs.TileHorizontal,       Is.False);
				Assert.That(m.LaunchArgs.TileVertical,         Is.False);
			}
		}

		#endregion

		#region Tests > NewUsbSerialHidOptionsPrepare
		//------------------------------------------------------------------------------------------
		// Tests > NewUsbSerialHidOptionsPrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestNewUsbSerialHidOptionsPrepare()
		{
			using (var m = new Main(new CommandLineArgs(new string[] { "--New", "--IOType=USBSerHID", "--VendorID=1234", "--ProductID=ABCD", "--NoUsbAutoOpen", "--LogOn" })))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.TerminalSettingsHandler, Is.Not.Null);

				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.TerminalType, Is.EqualTo(Domain.TerminalType.Text));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IOType,       Is.EqualTo(Domain.IOType.UsbSerialHid));

				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IO.UsbSerialHidDevice.DeviceInfo.VendorIdString,  Is.EqualTo("1234"));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IO.UsbSerialHidDevice.DeviceInfo.ProductIdString, Is.EqualTo("ABCD"));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IO.UsbSerialHidDevice.FlowControl,                Is.EqualTo(MKY.IO.Serial.Usb.SerialHidFlowControl.None));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IO.UsbSerialHidDevice.SignalXOnWhenOpened,        Is.True);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IO.UsbSerialHidDevice.AutoOpen,                   Is.False);

				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.TerminalIsStarted, Is.True);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.LogIsOn,           Is.True);

				Assert.That(m.LaunchArgs.PerformOperationOnRequestedTerminal, Is.False);
				Assert.That(m.LaunchArgs.RequestedDynamicTerminalId,          Is.EqualTo(TerminalIds.ActiveDynamicId));
				Assert.That(m.LaunchArgs.RequestedFixedTerminalId,            Is.EqualTo(TerminalIds.ActiveFixedId));
				Assert.That(m.LaunchArgs.RequestedTransmitText,               Is.Null.Or.Empty);
				Assert.That(m.LaunchArgs.RequestedTransmitFilePath,           Is.Null.Or.Empty);
				Assert.That(m.LaunchArgs.IsAutoRun,                           Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,                          Is.False);

				Assert.That(m.LaunchArgs.ShowNewTerminalDialog, Is.False);

				Assert.That(m.LaunchArgs.KeepOpen,             Is.True);
				Assert.That(m.LaunchArgs.KeepOpenOnNonSuccess, Is.True);
				Assert.That(m.LaunchArgs.TileHorizontal,       Is.False);
				Assert.That(m.LaunchArgs.TileVertical,         Is.False);
			}
		}

		#endregion

		#region Tests > ReplaceTerminalSettingsPrepare
		//------------------------------------------------------------------------------------------
		// Tests > ReplaceTerminalSettingsPrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestReplaceTerminalSettingsPrepare()
		{
			using (var m = new Main(new CommandLineArgs(new string[] { TerminalFilePath, "--BaudRate=19200" })))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler,                 Is.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,                  Is.Not.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.SettingsFilePath, Is.EqualTo(TerminalFilePath));

				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IO.SerialPort.Communication.BaudRate, Is.EqualTo(19200));

				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,               Is.False);
				Assert.That(m.LaunchArgs.PerformOperationOnRequestedTerminal, Is.False);
				Assert.That(m.LaunchArgs.IsAutoRun,                           Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,                          Is.False);

				Assert.That(m.LaunchArgs.KeepOpen,             Is.True);
				Assert.That(m.LaunchArgs.KeepOpenOnNonSuccess, Is.True);
				Assert.That(m.LaunchArgs.TileHorizontal,       Is.False);
				Assert.That(m.LaunchArgs.TileVertical,         Is.False);
			}
		}

		#endregion

		#region Tests > ReplaceTerminalSettingsInWorkspacePrepare
		//------------------------------------------------------------------------------------------
		// Tests > ReplaceTerminalSettingsInWorkspacePrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestReplaceTerminalSettingsInWorkspacePrepare()
		{
			using (var m = new Main(new CommandLineArgs(new string[] { WorkspaceFilePath, "--DynamicTerminalId=1", "--DataBits=7" })))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler,                  Is.Not.Null);
				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler.SettingsFilePath, Is.EqualTo(WorkspaceFilePath));
				Assert.That(m.LaunchArgs.RequestedDynamicTerminalId,                Is.EqualTo(1));
				Assert.That(m.LaunchArgs.RequestedFixedTerminalId,                  Is.EqualTo(TerminalIds.InvalidFixedId));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,                   Is.Not.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.Settings.IO.SerialPort.Communication.DataBits, Is.EqualTo(MKY.IO.Ports.DataBits.Seven));

				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,               Is.False);
				Assert.That(m.LaunchArgs.PerformOperationOnRequestedTerminal, Is.False);
				Assert.That(m.LaunchArgs.IsAutoRun,                           Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,                          Is.False);

				Assert.That(m.LaunchArgs.KeepOpen,             Is.True);
				Assert.That(m.LaunchArgs.KeepOpenOnNonSuccess, Is.True);
				Assert.That(m.LaunchArgs.TileHorizontal,       Is.False);
				Assert.That(m.LaunchArgs.TileVertical,         Is.False);
			}
		}

		#endregion

		#region Tests > TransmitTextOptionPrepare
		//------------------------------------------------------------------------------------------
		// Tests > TransmitTextOptionPrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestTransmitTextOptionPrepare()
		{
			string text = @"Send something\!(Delay)Send delayed";

			using (var m = new Main(new CommandLineArgs(new string[] { TerminalFilePath, "--TransmitText=" + text, "--KeepOpenOnNonSuccess"})))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler,                 Is.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,                  Is.Not.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.SettingsFilePath, Is.EqualTo(TerminalFilePath));
				Assert.That(m.LaunchArgs.RequestedTransmitText,                    Is.EqualTo(text));

				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,               Is.False);
				Assert.That(m.LaunchArgs.PerformOperationOnRequestedTerminal, Is.True);
				Assert.That(m.LaunchArgs.IsAutoRun,                           Is.True);
				Assert.That(m.LaunchArgs.IsAutoExit,                          Is.True);

				Assert.That(m.LaunchArgs.KeepOpen,             Is.False);
				Assert.That(m.LaunchArgs.KeepOpenOnNonSuccess, Is.True);
				Assert.That(m.LaunchArgs.TileHorizontal,       Is.False);
				Assert.That(m.LaunchArgs.TileVertical,         Is.False);
			}
		}

		#endregion

		#region Tests > TransmitTextOptionInWorkspacePrepare
		//------------------------------------------------------------------------------------------
		// Tests > TransmitTextOptionInWorkspacePrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestTransmitTextOptionInWorkspacePrepare()
		{
			string text = @"Send something\!(Delay)Send delayed";

			using (var m = new Main(new CommandLineArgs(new string[] { WorkspaceFilePath, "--TransmitText=" + text, "--FixedTerminalId=1", "--KeepOpenOnNonSuccess"})))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler,                  Is.Not.Null);
				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler.SettingsFilePath, Is.EqualTo(WorkspaceFilePath));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,                   Is.Not.Null);
				Assert.That(m.LaunchArgs.RequestedTransmitText,                     Is.EqualTo(text));
				Assert.That(m.LaunchArgs.RequestedFixedTerminalId,                  Is.EqualTo(1));
				Assert.That(m.LaunchArgs.RequestedDynamicTerminalId,                Is.EqualTo(TerminalIds.InvalidDynamicId));

				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,               Is.False);
				Assert.That(m.LaunchArgs.PerformOperationOnRequestedTerminal, Is.True);
				Assert.That(m.LaunchArgs.IsAutoRun,                           Is.True);
				Assert.That(m.LaunchArgs.IsAutoExit,                          Is.True);

				Assert.That(m.LaunchArgs.KeepOpen,             Is.False);
				Assert.That(m.LaunchArgs.KeepOpenOnNonSuccess, Is.True);
				Assert.That(m.LaunchArgs.TileHorizontal,       Is.False);
				Assert.That(m.LaunchArgs.TileVertical,         Is.False);
			}
		}

		#endregion

		#region Tests > TransmitFilePathOptionPrepare
		//------------------------------------------------------------------------------------------
		// Tests > TransmitFilePathOptionPrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestTransmitFilePathOptionPrepare()
		{
			string filePath = Temp.MakeTempFilePath(GetType(), ".xyz");
			File.Create(filePath); // File must exist!

			using (var m = new Main(new CommandLineArgs(new string[] { TerminalFilePath, "--TransmitFile=" + filePath, "--KeepOpenOnNonSuccess"})))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler,                 Is.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,                  Is.Not.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler.SettingsFilePath, Is.EqualTo(TerminalFilePath));
				Assert.That(m.LaunchArgs.RequestedTransmitFilePath,                Is.EqualTo(filePath));

				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,               Is.False);
				Assert.That(m.LaunchArgs.PerformOperationOnRequestedTerminal, Is.True);
				Assert.That(m.LaunchArgs.IsAutoRun,                           Is.True);
				Assert.That(m.LaunchArgs.IsAutoExit,                          Is.True);

				Assert.That(m.LaunchArgs.KeepOpen,             Is.False);
				Assert.That(m.LaunchArgs.KeepOpenOnNonSuccess, Is.True);
				Assert.That(m.LaunchArgs.TileHorizontal,       Is.False);
				Assert.That(m.LaunchArgs.TileVertical,         Is.False);
			}
		}

		#endregion

		#region Tests > TransmitFilePathOptionInWorkspacePrepare
		//------------------------------------------------------------------------------------------
		// Tests > TransmitFilePathOptionInWorkspacePrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestTransmitFilePathOptionInWorkspacePrepare()
		{
			string filePath = Temp.MakeTempFilePath(GetType(), ".xyz");
			File.Create(filePath); // File must exist!

			using (var m = new Main(new CommandLineArgs(new string[] { WorkspaceFilePath, "--TransmitFile=" + filePath, "--FixedTerminalId=2", "--KeepOpenOnNonSuccess"})))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler,                  Is.Not.Null);
				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler.SettingsFilePath, Is.EqualTo(WorkspaceFilePath));
				Assert.That(m.LaunchArgs.TerminalSettingsHandler,                   Is.Not.Null);
				Assert.That(m.LaunchArgs.RequestedTransmitFilePath,                 Is.EqualTo(filePath));
				Assert.That(m.LaunchArgs.RequestedFixedTerminalId,                  Is.EqualTo(2));
				Assert.That(m.LaunchArgs.RequestedDynamicTerminalId,                Is.EqualTo(TerminalIds.InvalidDynamicId));

				Assert.That(m.LaunchArgs.ShowNewTerminalDialog,               Is.False);
				Assert.That(m.LaunchArgs.PerformOperationOnRequestedTerminal, Is.True);
				Assert.That(m.LaunchArgs.IsAutoRun,                           Is.True);
				Assert.That(m.LaunchArgs.IsAutoExit,                          Is.True);

				Assert.That(m.LaunchArgs.KeepOpen,             Is.False);
				Assert.That(m.LaunchArgs.KeepOpenOnNonSuccess, Is.True);
				Assert.That(m.LaunchArgs.TileHorizontal,       Is.False);
				Assert.That(m.LaunchArgs.TileVertical,         Is.False);
			}
		}

		#endregion

		#region Tests > EmptyOptionPrepare
		//------------------------------------------------------------------------------------------
		// Tests > EmptyOptionPrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestEmptyOptionPrepare()
		{
			using (var m = new Main(new CommandLineArgs(new string[] { "--Empty" })))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.WorkspaceSettingsHandler, Is.Null);
				Assert.That(m.LaunchArgs.TerminalSettingsHandler, Is.Null);

				Assert.That(m.LaunchArgs.ShowNewTerminalDialog, Is.False);
				Assert.That(m.LaunchArgs.IsAutoRun,             Is.False);
				Assert.That(m.LaunchArgs.IsAutoExit,            Is.False);

				Assert.That(m.LaunchArgs.KeepOpen,             Is.False);
				Assert.That(m.LaunchArgs.KeepOpenOnNonSuccess, Is.False);
				Assert.That(m.LaunchArgs.TileHorizontal,       Is.False);
				Assert.That(m.LaunchArgs.TileVertical,         Is.False);
			}
		}

		#endregion

		#region Tests > TileOptionsPrepare
		//------------------------------------------------------------------------------------------
		// Tests > TileOptionsPrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestTileOptionsPrepare()
		{
			using (var m = new Main(new CommandLineArgs(new string[] { "--TileHorizontal" })))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.TileHorizontal, Is.True);
				Assert.That(m.LaunchArgs.TileVertical,   Is.False);
			}

			using (var m = new Main(new CommandLineArgs(new string[] { "--TileVertical" })))
			{
				PrepareMainAndVerifyResult(m);

				Assert.That(m.LaunchArgs.TileHorizontal, Is.False);
				Assert.That(m.LaunchArgs.TileVertical,   Is.True);
			}

			using (var m = new Main(new CommandLineArgs(new string[] { "--TileHorizontal", "--TileVertical" })))
			{
				PrepareLaunchAndVerifyResult(m, MainResult.CommandLineError);

				Assert.That(m.LaunchArgs.TileHorizontal, Is.False);
				Assert.That(m.LaunchArgs.TileVertical,   Is.False);
			}
		}

		#endregion

		#region Tests > InvalidPrepare
		//------------------------------------------------------------------------------------------
		// Tests > InvalidPrepare
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestInvalidPrepare()
		{
			using (var m = new Main(new CommandLineArgs(new string[] { "--Blablabla" })))
			{
				PrepareLaunchAndVerifyResult(m, MainResult.CommandLineError);
			}

			using (var m = new Main(new CommandLineArgs(new string[] { "+r" })))
			{
				PrepareLaunchAndVerifyResult(m, MainResult.CommandLineError);
			}

			using (var m = new Main(new CommandLineArgs(new string[] { "-+Recent" })))
			{
				PrepareLaunchAndVerifyResult(m, MainResult.CommandLineError);
			}

			using (var m = new Main(new CommandLineArgs(new string[] { "+-Recent" })))
			{
				PrepareLaunchAndVerifyResult(m, MainResult.CommandLineError);
			}
		}

		#endregion

		#endregion

		#region Non-Public Methods
		//==========================================================================================
		// Non-Public Methods
		//==========================================================================================

		private static void PrepareMainAndVerifyResult(Main main)
		{
			PrepareLaunchAndVerifyResult(main, MainResult.Success);
		}

		private static void PrepareLaunchAndVerifyResult(Main main, MainResult expectedMainResult)
		{
			var mainResult = main.PrepareLaunch_ForTestOnly();
			Assert.That(mainResult, Is.EqualTo(expectedMainResult));
		}

		#endregion
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Model.Test/LaunchTest.cs $
//==================================================================================================
