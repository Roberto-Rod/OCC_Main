//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Application.Base/CommandLineMessageHelper.cs $
// $Revision: 3790 $
// $Date: 2021-04-28 08:56:57 +0000 (Wed, 28 Apr 2021) $
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
using System.Text;
using System.IO;

using MKY;

#endregion

namespace YAT.Application
{
	/// <summary></summary>
	public static class CommandLineMessageHelper
	{
		#region Constants
		//==========================================================================================
		// Constants
		//==========================================================================================

		private const int DefaultTextWidth = 80;

		private static readonly string[] ResultTextLines =
		{
			"Return values:",
			"",
		#if (WITH_SCRIPTING)
			">= 4      Any other user defined script result",
			"   3      Script result (e.g. 'Auxiliaries.StandardResult.User')",
			"   2      Script result (e.g. 'Auxiliaries.StandardResult.Failure')",
			"   1      Script result (e.g. 'Auxiliaries.StandardResult.Cancel')",
			"   0      Success       (e.g. 'Auxiliaries.StandardResult.Success')",
		#else
			"   0      Success",
		#endif
			"  -1      Command line error",
			"  -2      System environment error",
			"  -3      Application settings error",
			"  -4      Application launch cancel",
			"  -5      Application launch error",
			"  -6      Application run error",
			"  -7      Application exit error",
			"  -8      Unhandled exception",
		#if (WITH_SCRIPTING)
			"-100      Script invalid content",
			"-101      Script stop on error",
			"-102      Script exit",
			"-103      Script user break",
			"-104      Script unhandled exception",
			"-105      Script invalid return value (legacy)",
			"-106      Script thread abort",
			"-107      Script remoting exception",
			"-108      Script invalid operation"
		#endif
		};

		#endregion

		#region Methods
		//==========================================================================================
		// Methods
		//==========================================================================================

		/// <remarks>
		/// Does not include a trailing empty line.
		/// </remarks>
		public static string GetVersion()
		{
			return (ApplicationEx.ProductCaptionAndVersionAndBuild);
		}

		/// <remarks>
		/// Does not include a trailing empty line.
		/// </remarks>
		public static string GetVersionAndLogo()
		{
			var sb = new StringBuilder();

			using (var writer = new StringWriter(sb))
			{
				WriteVersionAndLogo(writer, DefaultTextWidth, appendEmptyLine: false);
			}

			return (sb.ToString());
		}

		/// <remarks>
		/// Does not include a trailing empty line.
		/// </remarks>
		public static string GetVersionAndLogoAndHelpAndReturn(Func<int, string> getHelpText)
		{
			var sb = new StringBuilder();

			using (var writer = new StringWriter(sb))
			{
				WriteVersionAndLogoAndHelpAndReturn(writer, DefaultTextWidth, getHelpText, appendEmptyLine: false);
			}

			return (sb.ToString());
		}

		/// <remarks>
		/// Just the version number, neither caption nor build nor trailing empty line.
		/// </remarks>
		public static void WriteVersionOnly(TextWriter writer)
		{
			writer.WriteLine(ApplicationEx.ProductVersion);
		}

		/// <remarks>
		/// Appends a trailing empty line.
		/// </remarks>
		public static void WriteVersionAndLogo(TextWriter writer, int maxWidth)
		{
			WriteVersionAndLogo(writer, maxWidth, appendEmptyLine: true);
		}

		private static void WriteVersionAndLogo(TextWriter writer, int maxWidth, bool appendEmptyLine)
		{
			DoWriteVersionAndLogo(writer, maxWidth, appendEmptyLine, isComplete: true);
		}

		/// <remarks>
		/// Appends a trailing empty line.
		/// </remarks>
		public static void WriteVersionAndLogoAndHelpAndReturn(TextWriter writer, int maxWidth, Func<int, string> getHelpText)
		{
			WriteVersionAndLogoAndHelpAndReturn(writer, maxWidth, getHelpText, appendEmptyLine: true);
		}

		private static void WriteVersionAndLogoAndHelpAndReturn(TextWriter writer, int maxWidth, Func<int, string> getHelpText, bool appendEmptyLine)
		{
			DoWriteVersionAndLogo(writer, maxWidth, appendEmptyLine: true, isComplete: false);
			DoWriteHelp(          writer, maxWidth, getHelpText);
			DoWriteReturn(        writer, maxWidth, appendEmptyLine);
		}

		private static void DoWriteVersionAndLogo(TextWriter writer, int maxWidth, bool appendEmptyLine, bool isComplete)
		{
			if (maxWidth < DefaultTextWidth)
				throw (new ArgumentOutOfRangeException("maxWidth", maxWidth, MessageHelper.InvalidExecutionPreamble + "'ProductLogoLineSections' requires a width of at least " + DefaultTextWidth + " characters!" + Environment.NewLine + Environment.NewLine + MessageHelper.SubmitBug));

			var additionalIndent = "  "; // Additional spaces, similar to header of 'Release Notes' which uses a single space.

			writer.WriteLine();
			writer.WriteLine(new string('=', maxWidth)); // ==========...
			writer.WriteLine();

			writer.WriteLine(ApplicationEx.ProductCaptionAndVersionAndBuild + ":"); // Same as e.g. "Usage:" of help text.

			foreach (var section in ApplicationEx.ProductLogoLineSections)
			{
				writer.WriteLine();

				foreach (string line in section)
					writer.WriteLine(additionalIndent + line);
			}

			writer.WriteLine();
			writer.WriteLine(new string((isComplete ? '=' : '-'), maxWidth)); // ==========... or ----------...

			if (appendEmptyLine)
				writer.WriteLine();
		}

		private static void DoWriteHelp(TextWriter writer, int maxWidth, Func<int, string> getHelpText)
		{
			writer.Write(getHelpText(maxWidth));
		}

		private static void DoWriteReturn(TextWriter writer, int maxWidth, bool appendEmptyLine)
		{
			writer.WriteLine();

			foreach (var line in ResultTextLines)
				writer.WriteLine(line);

			writer.WriteLine();
			writer.WriteLine(new string('=', maxWidth)); // ==========...

			if (appendEmptyLine)
				writer.WriteLine();
		}

		#endregion
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Application.Base/CommandLineMessageHelper.cs $
//==================================================================================================
