//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Application.Base/ApplicationEx.cs $
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

//// "System" is explicitly used for making origin more obvious.
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using System.IO;

using MKY.IO;

// This code is intentionally placed into the YAT namespace even though the file is located in
// YAT.Application since the class name already contains 'Application'.
namespace YAT
{
	/// <summary></summary>
	[SuppressMessage("StyleCop.CSharp.OrderingRules", "SA1203:ConstantsMustAppearBeforeFields", Justification = "Semantic of readonly fields is constant.")]
	[SuppressMessage("Microsoft.Naming", "CA1711:IdentifiersShouldNotHaveIncorrectSuffix", Justification = "'Ex' emphasizes that it's an extended enum and extends the underlying enum.")]
	public static class ApplicationEx
	{
	#if (!WITH_SCRIPTING)
		/// <summary>The common name, always "YAT", i.e. not "YAT" *or* "YATConsole".</summary>
		public const string CommonName = "YAT";
	#else
		/// <summary>The common name, always "Albatros", i.e. not "Albatros" *or* "AlbatrosConsole".</summary>
		public const string CommonName = "Albatros"; // Note that making name 'Albatros' publicly visible doesn't matter anymore, several SourceForge tickets created by UFi contain "Albatros" anyway.
	#endif

		/// <summary>The long variant of the common name.</summary>
	#if (!WITH_SCRIPTING)
		public const string CommonNameLong = CommonName + " - Yet Another Terminal";
	#else
		public const string CommonNameLong = CommonName + " - YAT with Scripting";
	#endif

		/// <summary>
		/// Constant string to expand the application's product name in places where neither
		/// <see cref="ProductName"/> nor <see cref="System.Windows.Forms.Application.ProductName"/>
		/// can be used, e.g. in case of attribute arguments.
		/// </summary>
	#if (!WITH_SCRIPTING)
		public const string ProductNameConstWorkaround = "YAT"; // Should be "YAT" or "YATConsole", but fixed for simplicity.
	#else                       // Note that making name 'Albatros' publicly visible is doesn't matter anymore, several SourceForge tickets created by UFi contain "Albatros" anyway.
		public const string ProductNameConstWorkaround = "Albatros"; // Should be "Albatros" or "AlbatrosConsole", but fixed for simplicity.
	#endif

		/// <summary>The product name.</summary>
		public static readonly string ProductName = System.Windows.Forms.Application.ProductName;

		/// <summary>The build designation.</summary>
	#if (!WITH_SCRIPTING)                              // Leading space for non-empty strings!
		public const string ProductBuildDesignation = ""; // This is to be used for final releases.
	////public const string ProductBuildDesignation = " 2.x.0 Beta Version";
	////public const string ProductBuildDesignation = " 2.x.0 Preliminary Version";
	////public const string ProductBuildDesignation = " 2.x.0 Development Version";
	#else
		public const string ProductBuildDesignation = "";
	#endif

		/// <summary>The product caption that combines product name and build designation.</summary>
		public static readonly string ProductCaption = ProductName + ProductBuildDesignation;

		/// <summary>The product version.</summary>
		public static readonly string ProductVersion = System.Windows.Forms.Application.ProductVersion;

		/// <summary>
		/// The product version including <see cref="System.Version.Revision"/>.
		/// </summary>
		/// <remarks>
		/// <see cref="ProductVersion"/> uses the <see cref="System.Reflection.AssemblyInformationalVersionAttribute"/>
		/// that hides the <see cref="System.Version.Revision"/> part.
		/// </remarks>
		public static System.Version ProductFullVersionValue
		{
			get { return (System.Reflection.Assembly.GetEntryAssembly().GetName().Version); }
		}

		/// <summary>
		/// The product version including <see cref="System.Version.Revision"/>.
		/// </summary>
		/// <remarks>
		/// <see cref="ProductVersion"/> uses the <see cref="System.Reflection.AssemblyInformationalVersionAttribute"/>
		/// that hides the <see cref="System.Version.Revision"/> part.
		/// </remarks>
		/// <remarks>
		/// Must be 'get' rather than 'readonly' as <see cref="ProductFullVersionValue"/> is 'get'.
		/// </remarks>
		public static string ProductFullVersion
		{
			get { return (ProductFullVersionValue.ToString()); }
		}

		/// <summary>
		/// The <see cref="System.Version.Revision"/> part of the product version.
		/// </summary>
		/// <remarks>
		/// Must be 'get' rather than 'readonly' as <see cref="ProductFullVersionValue"/> is 'get'.
		/// </remarks>
		public static string ProductRevision
		{
			get { return (ProductFullVersionValue.Revision.ToString(CultureInfo.InvariantCulture)); } // Version identification is invariant.
		}

		/// <summary>The version designation.</summary>          // Leading space for non-empty strings!
		public const string ProductVersionStabilityIndication = ""; // This is to be used for final releases.
	////public const string ProductVersionStabilityIndication = " Beta";
	////public const string ProductVersionStabilityIndication = " Preliminary";
	////public const string ProductVersionStabilityIndication = " Development";

		/// <summary>The product version that combines product version and version stability indication.</summary>
		public static readonly string ProductVersionWithStabilityIndication = ProductVersion + ProductVersionStabilityIndication;

		/// <summary>
		/// The product caption and version.
		/// </summary>
		/// <remarks>
		/// No longer using "Version" inbetween as many other applications which don't, e.g.
		///  > TortoiseSVN 1.9.7, Build 27907
		///  > Syncovery 7.68 build 446
		///  > FreeFileSync 9.9 [2018-03-09]
		///  > Firefox 59.0.2 (64-Bit) + Thunderbird 52.7.0 (32-Bit)
		/// Release sections in release notes no longer use "Version" either.
		/// </remarks>
		[SuppressMessage("StyleCop.CSharp.DocumentationRules", "SA1650:ElementDocumentationMustBeSpelledCorrectly", Justification = "'Syncovery' is a product name.")]
		public static readonly string ProductCaptionAndVersion = ProductCaption + " " + ProductVersionWithStabilityIndication;

		/// <summary>
		/// The product caption and version including build/revision.
		/// </summary>
		/// <remarks>
		/// Must be 'get' rather than 'readonly' as <see cref="ProductRevision"/> is 'get'.
		/// </remarks>
		public static string ProductCaptionAndVersionAndBuild
		{                  // Using more general term "Build" rather than .NET specific term "Revision". Resulting suboptimality: .NET "Revision" indicates
			get { return (ProductCaptionAndVersion + " Build " + ProductRevision); } // the number of seconds since midnight divided by two. Consequently
		}                                                                            // YAT's "Build" not necessarily increases for subsequent versions.

		/// <summary>The complete logo (text line sections) of the product.</summary>
		/// <remarks>Same content and structure as header of 'Release Notes'.</remarks>
		[SuppressMessage("Microsoft.Security", "CA2105:ArrayFieldsShouldNotBeReadOnly", Justification = "Nobody will modify this array, don't worry...")]
		public static readonly string[][] ProductLogoLineSections =
		{
			new string[]
			{
				CommonNameLong + ".", // Fixed to "YAT - Yet Another Terminal".
				"Engineering, testing and debugging of serial communications.",
				"Supports RS-232/422/423/485 as well as...", // Separated onto four lines to fit console widths as narrow as 80 characters,
				"...TCP/IP Client/Server/AutoSocket,...",    // opposed to the 'Release Notes' which are fixed to a width of 100 characters.
				"...UDP/IP Client/Server/PairSocket and...",
				"...USB Ser/HID.",
		#if (WITH_SCRIPTING)
				"Integrated C# scripting functionality.",
		#endif
			},
			new string[]
			{
				"Visit YAT at https://sourceforge.net/projects/y-a-terminal.",
		#if (!WITH_SCRIPTING)
				"Contact YAT by mailto:y-a-terminal@users.sourceforge.net.",
		#else
				"Contact Albatros by mailto:matthias.klaey@mt.com.",
		#endif
			},
			new string[]
			{
		#if (!WITH_SCRIPTING)
				"Copyright © 2003-2004 HSR Hochschule für Technik Rapperswil.",
				"Copyright © 2003-2021 Matthias Kläy.",
		#else
			////"YAT copyright © 2003-2004 HSR Hochschule für Technik Rapperswil and © 2003-2021 Matthias Kläy.",
				"YAT copyright © 2003-2004 HSR and © 2003-2021 Matthias Kläy.", // Shortended to fit standard console width of 80 characters.
				"Albatros copyright © 2008-2021 Mettler-Toledo.",
		#endif
				"All rights reserved.",
		#if (!WITH_SCRIPTING)
			},
			new string[]
			{
				"YAT is licensed under the GNU LGPL.", // Note that source files state "This source code is licensed under the GNU LGPL." to emphasize the context.
				"See http://www.gnu.org/licenses/lgpl.html for license details."
		#endif
			}
		};

		/// <summary>
		/// Gets the path for the executable file that started the application,
		/// not including the name of the file, e.g. "C:\Program Files\YAT".
		/// </summary>
		/// <remarks>
		/// The value of this property equals <see cref="System.Windows.Forms.Application.StartupPath"/>.
		/// This dedicated property provides a more accurate name than the original property.
		/// </remarks>
		public static readonly string ExecutableDirectoryPath = System.Windows.Forms.Application.StartupPath;

		/// <summary>
		/// Gets the path for the executable file that started the application,
		/// including the name of the file, e.g. "C:\Program Files\YAT\YAT.exe".
		/// </summary>
		/// <remarks>
		/// The value of this property equals <see cref="System.Windows.Forms.Application.ExecutablePath"/>.
		/// This dedicated property provides a more accurate name than the original property.
		/// </remarks>
		public static readonly string ExecutableFilePath = System.Windows.Forms.Application.ExecutablePath;

		/// <summary>
		/// Gets the name of the executable file, without its extension, e.g. "YAT".
		/// </summary>
		public static readonly string ExecutableFileNameWithoutExtension = Path.GetFileNameWithoutExtension(ExecutableFilePath);

		/// <summary>
		/// Gets the absolute path of the given file, relative to and dependent on the path of the
		/// executable file, e.g. "C:\Program Files\YAT\YAT Release Notes.txt" or for development
		/// "D:\Workspaces\YAT\Trunk\YAT\YAT\bin\Debug\..\..\..\!-Doc.User\YAT Release Notes.txt".
		/// </summary>
		/// <remarks>
		/// This method assumes "Debug" and "Release" as the paths during development and is
		/// typically used with the generic 'Any CPU' target. Platform specific 'x64' and 'x86'
		/// require handling by the caller of this method.
		/// </remarks>
		public static string ResolveExecutableRelativePath(string runtimeRelativeFilePath, string developmentRelativeFilePath)
		{
			var di = new DirectoryInfo(ExecutableDirectoryPath);
			switch (di.Name) // Attention, Path.GetDirectoryName() would return the parent directory's name!
			{
				case "Debug":
				case "Release":
					return (PathEx.CombineDirectoryAndFilePaths(ExecutableDirectoryPath, developmentRelativeFilePath));

				default:
					return (PathEx.CombineDirectoryAndFilePaths(ExecutableDirectoryPath, runtimeRelativeFilePath));
			}
		}

		/// <summary>The .NET Framework prerequisite.</summary>
		public static readonly string PrerequisiteFramework = ".NET Framework 4.8";

		/// <summary>The Windows operating system prerequisite.</summary>
		public static readonly string PrerequisiteWindows = "Windows 7 SP1 or Windows Server 2008 R2 SP1 or later";

		/// <summary>The Linux operating system prerequisite.</summary>
		public static readonly string PrerequisiteLinux = "Linux with Mono 4.8.0 or later";
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Application.Base/ApplicationEx.cs $
//==================================================================================================
