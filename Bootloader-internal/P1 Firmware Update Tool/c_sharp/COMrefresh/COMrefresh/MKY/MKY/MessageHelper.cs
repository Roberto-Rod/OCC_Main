//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/MessageHelper.cs $
// $Revision: 3786 $
// $Date: 2021-04-20 16:33:31 +0000 (Tue, 20 Apr 2021) $
// $Author: maettu_this $
// ------------------------------------------------------------------------------------------------
// MKY Version 1.0.30
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

namespace MKY
{
	/// <summary>
	/// User message utility methods.
	/// </summary>
	public static class MessageHelper
	{
		/// <summary>
		/// The default invalid execution preamble is <![CDATA["Program execution must never get here! "]]>.
		/// </summary>
		/// <remarks>
		/// Note the adjacent space.
		/// </remarks>
		public const string InvalidExecutionPreambleDefault = "Program execution must never get here! ";

		/// <summary>
		/// The default support request message is <![CDATA["Support may be requested at the origin of this software."]]>.
		/// </summary>
		public const string RequestSupportDefault = "Support may be requested at the origin of this software. Describe what you want to achieve or what doesn't work as detailed as possible.";

		/// <summary>
		/// The default feature request message is <![CDATA["New features may be requested at the origin of this software. Describe your request as detailed as possible (use case or user story, preconditions, postconditions,...)."]]>.
		/// </summary>
		public const string RequestFeatureDefault = "New features may be requested at the origin of this software. Describe your request as detailed as possible (use case or user story, preconditions, postconditions,...).";

		/// <summary>
		/// The default change request message is <![CDATA["Changes may be requested at the origin of this software. Describe your request as detailed as possible (use case or user story, preconditions, postconditions,...)."]]>.
		/// </summary>
		public const string RequestChangeDefault = "Changes may be requested at the origin of this software. Describe your request as detailed as possible (use case or user story, preconditions, postconditions,...).";

		/// <summary>
		/// The default bug submission message is <![CDATA["Please report this issue at the origin of this software."]]>.
		/// </summary>
		public const string SubmitBugDefault = "Please report this issue at the origin of this software. Describe the situation when the issue happened as detailed as possible (environment, preconditions, settings, actions,...).";

		private static string staticInvalidExecutionPreamble = InvalidExecutionPreambleDefault;
		private static string staticRequestSupport           = RequestSupportDefault;
		private static string staticRequestFeature           = RequestFeatureDefault;
		private static string staticRequestChange            = RequestChangeDefault;
		private static string staticSubmitBug                = SubmitBugDefault;

		/// <summary>
		/// The currently active invalid execution preamble.
		/// By default <see cref="InvalidExecutionPreambleDefault"/>.
		/// </summary>
		public static string InvalidExecutionPreamble
		{
			get { return (staticInvalidExecutionPreamble); }
			set { staticInvalidExecutionPreamble = value;  }
		}

		/// <summary>
		/// The currently active support request message.
		/// By default <see cref="RequestSupportDefault"/>.
		/// </summary>
		public static string RequestSupport
		{
			get { return (staticRequestSupport); }
			set { staticRequestSupport = value;  }
		}

		/// <summary>
		/// The currently active feature request message.
		/// By default <see cref="RequestFeatureDefault"/>.
		/// </summary>
		public static string RequestFeature
		{
			get { return (staticRequestFeature); }
			set { staticRequestFeature = value;  }
		}

		/// <summary>
		/// The currently active change request message.
		/// By default <see cref="RequestChangeDefault"/>.
		/// </summary>
		public static string RequestChange
		{
			get { return (staticRequestChange); }
			set { staticRequestChange = value;  }
		}

		/// <summary>
		/// The currently active bug submission message.
		/// By default <see cref="SubmitBugDefault"/>.
		/// </summary>
		public static string SubmitBug
		{
			get { return (staticSubmitBug); }
			set { staticSubmitBug = value;  }
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/MessageHelper.cs $
//==================================================================================================
