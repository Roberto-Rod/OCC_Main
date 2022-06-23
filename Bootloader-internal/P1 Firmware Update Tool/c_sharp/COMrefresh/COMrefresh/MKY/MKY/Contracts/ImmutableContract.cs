//==================================================================================================
// YAT - Yet Another Terminal.
// Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
// Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
// ------------------------------------------------------------------------------------------------
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/Contracts/ImmutableContract.cs $
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
// Copyright © 2010-2021 Matthias Kläy.
// All rights reserved.
// ------------------------------------------------------------------------------------------------
// This source code is licensed under the GNU LGPL.
// See http://www.gnu.org/licenses/lgpl.html for license details.
//==================================================================================================

using System;

namespace MKY.Contracts
{
	/// <summary>
	/// Attribute to indicate the nature of a class or struct.
	/// </summary>
	/// <remarks>
	/// Sealed to improve performance during reflection on custom attributes according to FxCop:CA1813.
	/// </remarks>
	[AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct, AllowMultiple = false)]
	public sealed class ImmutableContractAttribute : Attribute
	{
		/// <summary>
		/// Indicates that the class or struct is immutable.
		/// </summary>
		public bool IsImmutable { get; }

		/// <summary></summary>
		public ImmutableContractAttribute(bool isImmutable)
		{
			IsImmutable = isImmutable;
		}
	}
}

//==================================================================================================
// End of
// $URL: file:///svn/p/y-a-terminal/code/trunk/MKY/MKY/Contracts/ImmutableContract.cs $
//==================================================================================================
