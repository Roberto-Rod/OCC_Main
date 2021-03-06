//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Model/Utilities/CaptionHelper.cs $
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
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using System.Text;

using MKY.Settings;

using YAT.Settings.Model;

#endregion

namespace YAT.Model.Utilities
{
	/// <summary></summary>
	public static class CaptionHelper
	{
		/// <summary></summary>
		public static string ComposeMain(string indicatedName)
		{
			var sb = new StringBuilder(ApplicationEx.ProductName); // "YAT" or "YATConsole" shall be indicated in main title bar.

			// Attention:
			// Similar "YAT - [IndicatedName]" as in...
			// ...ComposeTerminal() below.
			// ...Workspace.ActiveTerminalInfoText{get}.
			// Changes here may have to be applied there too.

			if (!string.IsNullOrEmpty(indicatedName))
			{
				sb.Append(" - [");
				sb.Append(indicatedName);
				sb.Append("]");
			}

			return (sb.ToString());
		}

		/// <summary></summary>
		public static string ComposeTerminal(string indicatedName, string info)
		{
			return (ComposeTerminal(indicatedName, new string[] { info }));
		}

		/// <summary></summary>
		[SuppressMessage("Microsoft.Naming", "CA1704:IdentifiersShouldBeSpelledCorrectly", MessageId = "infos", Justification = "Plural of 'info'.")]
		public static string ComposeTerminal(string indicatedName, IEnumerable<string> infos)
		{
			var sb = new StringBuilder();

			// Attention:
			// Similar "[IndicatedName] - Info - Info - Info" as in...
			// ...ComposeMain() above.
			// ...ComposeTerminal() below.
			// ...Workspace.ActiveTerminalInfoText{get}.
			// Changes here may have to be applied there too.

			sb.Append("[");
			sb.Append(indicatedName);
			sb.Append("]");

			if (infos != null)
			{
				foreach (var info in infos)
				{
					sb.Append(" - ");
					sb.Append(info);
				}
			}

			return (sb.ToString());
		}

		/// <summary></summary>
		[SuppressMessage("StyleCop.CSharp.ReadabilityRules", "SA1115:ParameterMustFollowComma",                       Justification = "There are too many parameters to pass.")]
		[SuppressMessage("StyleCop.CSharp.ReadabilityRules", "SA1116:SplitParametersMustStartOnLineAfterDeclaration", Justification = "There are too many parameters to pass.")]
		[SuppressMessage("StyleCop.CSharp.ReadabilityRules", "SA1117:ParametersMustBeOnSameLineOrSeparateLines",      Justification = "There are too many parameters to pass.")]
		public static string ComposeTerminal(DocumentSettingsHandler<TerminalSettingsRoot> settingsHandler, TerminalSettingsRoot settingsRoot, Domain.Terminal terminal,
		                                     string indicatedName, bool isStarted, bool isOpen, bool isConnected)
		{
			var sb = new StringBuilder();

			// Attention:
			// Same "[IndicatedName] - Info - Info - Info" as in...
			// ...ComposeMain() above.
			// ...ComposeTerminal() above.
			// ...Workspace.ActiveTerminalInfoText{get}.
			// Changes here may have to be applied there too.

			if ((settingsHandler == null) || (settingsRoot == null))
			{
				sb.Append("[");
				sb.Append(indicatedName);
				sb.Append("]");
			}
			else
			{
				sb.Append("[");
				{
					if (settingsHandler.SettingsFileIsReadOnly)
						sb.Append("#");

					sb.Append(indicatedName);

					if (settingsHandler.SettingsFileIsReadOnly)
						sb.Append("#");

					if (settingsRoot.ExplicitHaveChanged) // Notes on indication:
						sb.Append(" *");                  //  > Visual Studio without space,             e.g. [Main.cs*]
				}                                         //  > Programmer's Notepad and IAR with space, e.g. [Main.cs *] => YAT's choice
				sb.Append("]");                           //  > Notepad++ with leading space,            e.g. [*Main.cs]

				switch (settingsRoot.IOType)
				{
					case Domain.IOType.SerialPort:
					{
						string portNameAndCaption;
						bool autoReopenEnabled;

						var port = (terminal.UnderlyingIOProvider as MKY.IO.Serial.SerialPort.SerialPort);
						if (port != null) // Effective settings from port object:
						{
							var settings = port.Settings;
							portNameAndCaption = settings.PortId.ToNameAndCaptionString();
							autoReopenEnabled  = settings.AutoReopen.Enabled;
						}
						else // Fallback to settings object tree:
						{
							var settings = settingsRoot.IO.SerialPort;
							portNameAndCaption = settings.PortId.ToNameAndCaptionString();
							autoReopenEnabled  = settings.AutoReopen.Enabled;
						}

						sb.Append(" - ");
						sb.Append(portNameAndCaption);
						sb.Append(" - ");

						if (isStarted)
						{
							if (isOpen)
							{
								sb.Append("Open");
								sb.Append(" - ");
								sb.Append(isConnected ? "Connected" : "Disconnected"); // Break?
							}
							else if (autoReopenEnabled)
							{
								sb.Append("Closed - Waiting for reconnect");
							}
							else
							{
								sb.Append("Closed");
							}
						}
						else
						{
							sb.Append("Closed");
						}

						break;
					}

					case Domain.IOType.TcpClient:
					{
						var settings = settingsRoot.IO.Socket;

						sb.Append(" - ");
						sb.Append(settings.RemoteEndPointString);
						sb.Append(" - ");

						if (isConnected)
							sb.Append("Connected");
						else if (isStarted && settings.TcpClientAutoReconnect.Enabled)
							sb.Append("Disconnected - Waiting for reconnect");
						else
							sb.Append("Disconnected");

						break;
					}

					case Domain.IOType.TcpServer:
					{
						var settings = settingsRoot.IO.Socket;

						sb.Append(" - ");
						sb.Append("Server:");
						sb.Append(settings.LocalPort.ToString(CultureInfo.InvariantCulture)); // "InvariantCulture" for TCP and UDP ports!
						sb.Append(" - ");

						if (isStarted)
							sb.Append(isConnected ? "Connected" : "Listening");
						else
							sb.Append("Closed");

						break;
					}

					case Domain.IOType.TcpAutoSocket:
					{
						var settings = settingsRoot.IO.Socket;
						if (isStarted)
						{
							bool isClient = false;
							bool isServer = false;

							var socket = (terminal.UnderlyingIOProvider as MKY.IO.Serial.Socket.TcpAutoSocket);
							if (socket != null)
							{
								isClient = socket.IsClient;
								isServer = socket.IsServer;
							}

							if (isClient)
							{
								sb.Append(" - ");
								sb.Append(settings.RemoteEndPointString);
								sb.Append(" - ");
								sb.Append(isConnected ? "Connected" : "Disconnected");
							}
							else if (isServer)
							{
								sb.Append(" - ");
								sb.Append("Server:");
								sb.Append(settings.LocalPort.ToString(CultureInfo.InvariantCulture)); // "InvariantCulture" for TCP and UDP ports!
								sb.Append(" - ");
								sb.Append(isConnected ? "Connected" : "Listening");
							}
							else
							{
								sb.Append(" - ");
								sb.Append("Starting"); // "to connect to..." or "to listen on..." makes little sense as role is yet undetermined.
							}
						}
						else
						{
							sb.Append(" - ");
							sb.Append("AutoSocket:");
							sb.Append(settings.RemotePort.ToString(CultureInfo.InvariantCulture)); // "InvariantCulture" for TCP and UDP ports!
							sb.Append(" - ");
							sb.Append("Disconnected");
						}

						break;
					}

					case Domain.IOType.UdpClient:
					{
						var settings = settingsRoot.IO.Socket;
						sb.Append(" - ");
						sb.Append(settings.RemoteEndPointString);
						sb.Append(" - ");
						sb.Append(isOpen ? "Open" : "Closed");
						break;
					}

					case Domain.IOType.UdpServer:
					{
						var settings = settingsRoot.IO.Socket;
						sb.Append(" - ");
						sb.Append("Receive:");
						sb.Append(settings.LocalPort.ToString(CultureInfo.InvariantCulture)); // "InvariantCulture" for TCP and UDP ports!
						sb.Append(" - ");
						sb.Append(isOpen ? "Open" : "Closed");
						break;
					}

					case Domain.IOType.UdpPairSocket:
					{
						var settings = settingsRoot.IO.Socket;
						sb.Append(" - ");
						sb.Append(settings.RemoteEndPointString);
						sb.Append(" - ");
						sb.Append("Receive:");
						sb.Append(settings.LocalPort.ToString(CultureInfo.InvariantCulture)); // "InvariantCulture" for TCP and UDP ports!
						sb.Append(" - ");
						sb.Append(isOpen ? "Open" : "Closed");
						break;
					}

					case Domain.IOType.UsbSerialHid:
					{
						var settings = settingsRoot.IO.UsbSerialHidDevice;
						sb.Append(" - ");
						var device = (terminal.UnderlyingIOProvider as MKY.IO.Serial.Usb.SerialHidDevice);
						if (device != null)
							sb.Append(device.InfoString);
						else
							settings.DeviceInfo.ToString(true, false);

						sb.Append(" - ");

						if (isStarted)
						{
							if (isConnected)
							{
								if (isOpen)
									sb.Append("Connected - Open");
								else if (device.Settings.AutoOpen)
									sb.Append("Connected - Waiting for reopen");
								else
									sb.Append("Connected - Closed");
							}
							else if (device.Settings.AutoOpen)
							{
								sb.Append("Disconnected - Waiting for reconnect");
							}
							else
							{
								sb.Append("Disconnected - Closed");
							}
						}
						else
						{
							sb.Append("Closed");
						}

						break;
					}

					default:
					{
						throw (new NotSupportedException(MKY.MessageHelper.InvalidExecutionPreamble + "'" + settingsRoot.IOType + "' is an I/O type that is not (yet) supported here!" + Environment.NewLine + Environment.NewLine + MKY.MessageHelper.SubmitBug));
					}
				} // switch (I/O type)
			} // if (settings available)

			return (sb.ToString());
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Model/Utilities/CaptionHelper.cs $
//==================================================================================================
