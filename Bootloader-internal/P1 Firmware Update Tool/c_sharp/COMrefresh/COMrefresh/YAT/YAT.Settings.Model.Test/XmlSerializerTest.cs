//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Settings.Model.Test/XmlSerializerTest.cs $
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

using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;

using MKY.Collections.Specialized;
using MKY.IO;
using MKY.Settings;

using NUnit.Framework;

using YAT.Application.Settings;
using YAT.Model.Settings;
using YAT.Model.Types;
using YAT.Settings.Application;

#endregion

namespace YAT.Settings.Model.Test
{
	/// <summary></summary>
	[TestFixture]
	public class XmlSerializerTest
	{
		#region Constants
		//==========================================================================================
		// Constants
		//==========================================================================================

		private const string FileExtension = ".xml";

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
		}

		/// <summary></summary>
		[SuppressMessage("Microsoft.Naming", "CA1702:CompoundWordsShouldBeCasedCorrectly", MessageId = "TearDown", Justification = "Naming according to NUnit.")]
		[TestFixtureTearDown]
		public virtual void TestFixtureTearDown()
		{
			Temp.CleanTempPath(GetType());

			// Close and dispose of temporary in-memory application settings:
			ApplicationSettings.CloseAndDispose();
		}

		#endregion

		#region Tests
		//==========================================================================================
		// Tests
		//==========================================================================================

		#region Tests > Serialization
		//------------------------------------------------------------------------------------------
		// Tests > Serialization
		//------------------------------------------------------------------------------------------

		#region Tests > Serialization > EmptyCommand
		//------------------------------------------------------------------------------------------
		// Tests > Serialization > EmptyCommand
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestEmptyCommandSerialization()
		{
			string filePath;

			filePath = Temp.MakeTempFilePath(GetType(), "EmptyArrayOfCommands", FileExtension);
			var a = new Command[] { };
			MKY.Test.Xml.Serialization.XmlSerializerTest.TestSerializationChain(typeof(Command[]), a, filePath);

			filePath = Temp.MakeTempFilePath(GetType(), "EmptyListOfCommands", FileExtension);
			var l = new List<Command>();
			MKY.Test.Xml.Serialization.XmlSerializerTest.TestSerializationChain(typeof(List<Command>), l, filePath);
		}

		#endregion

		#region Tests > Serialization > Recent
		//------------------------------------------------------------------------------------------
		// Tests > Serialization > Recent
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestRecentSerialization()
		{
			var filePath = Temp.MakeTempFilePath(GetType(), "RecentFileSettings", FileExtension);

			var ric = new RecentItemCollection<string>();
			ric.Add("RIA");
			ric.Add("RIB");

			var rfs = new RecentFileSettings();
			rfs.FilePaths = ric;
			MKY.Test.Xml.Serialization.XmlSerializerTest.TestSerializationChain(typeof(RecentFileSettings), rfs, filePath);
		}

		#endregion

		#region Tests > Serialization > Predefined
		//------------------------------------------------------------------------------------------
		// Tests > Serialization > Predefined
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestPredefinedSerialization()
		{
			string filePath;

			filePath = Temp.MakeTempFilePath(GetType(), "PredefinedCommandPage", FileExtension);
			var pcp = new PredefinedCommandPage();
			pcp.Commands.Add(new Command("Hello", new string[] { "World" }));
			pcp.Commands.Add(new Command("Hallo", new string[] { "Wält"  }));
			MKY.Test.Xml.Serialization.XmlSerializerTest.TestSerializationChain(typeof(PredefinedCommandPage), pcp, filePath);

			var c = new PredefinedCommandPageCollection();
			c.Add(pcp);
			c.Add(pcp);

			filePath = Temp.MakeTempFilePath(GetType(), "PredefinedCommandSettings", FileExtension);
			var pcs = new PredefinedCommandSettings();
			pcs.Pages = c;
			MKY.Test.Xml.Serialization.XmlSerializerTest.TestSerializationChain(typeof(PredefinedCommandSettings), pcs, filePath);
		}

		#endregion

		#region Tests > Serialization > Explicit
		//------------------------------------------------------------------------------------------
		// Tests > Serialization > Explicit
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestExplicitSerialization()
		{
			string filePath;

			filePath = Temp.MakeTempFilePath(GetType(), "ExplicitSettings", FileExtension);
			var s = new TerminalExplicitSettings();
			MKY.Test.Xml.Serialization.XmlSerializerTest.TestSerializationChain(typeof(TerminalExplicitSettings), s, filePath);
		}

		#endregion

		#region Tests > Serialization > Implicit
		//------------------------------------------------------------------------------------------
		// Tests > Serialization > Implicit
		//------------------------------------------------------------------------------------------

		/// <summary></summary>
		[Test]
		public virtual void TestImplicitSerialization()
		{
			string filePath;

			filePath = Temp.MakeTempFilePath(GetType(), "ImplicitSettings", FileExtension);
			var s = new TerminalImplicitSettings();
			MKY.Test.Xml.Serialization.XmlSerializerTest.TestSerializationChain(typeof(TerminalImplicitSettings), s, filePath);
		}

		#endregion

		#endregion

		#endregion
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/YAT/YAT.Settings.Model.Test/XmlSerializerTest.cs $
//==================================================================================================
