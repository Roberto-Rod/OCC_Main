@ECHO OFF

::==================================================================================================
:: YAT - Yet Another Terminal.
:: Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
:: Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
:: ------------------------------------------------------------------------------------------------
:: $URL: file:///svn/p/y-a-terminal/code/trunk/!-Scripts/CleanAll.cmd $
:: $Revision: 3584 $
:: $Date: 2021-01-04 15:40:12 +0000 (Mon, 04 Jan 2021) $
:: $Author: maettu_this $
:: ------------------------------------------------------------------------------------------------
:: See release notes for product version details.
:: See SVN change log for file revision details.
::
::     !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
::     Attention: Windows/DOS requires that this file is encoded in ASCII/ANSI and not UTF-8!
::     !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
::
:: Author(s): Matthias Klaey
:: ------------------------------------------------------------------------------------------------
:: Copyright ? 2003-2021 Matthias Kl?y.
:: All rights reserved.
:: ------------------------------------------------------------------------------------------------
:: This source code is licensed under the GNU LGPL.
:: See http://www.gnu.org/licenses/lgpl.html for license details.
::==================================================================================================

:: First clean the large temporaries => speed up subsequent cleans:
CALL CleanAll-Temp.cmd

:: Then clean the remaining stuff in alphabetical order:
CALL CleanAll-Analyzer.cmd
CALL CleanAll-Options.cmd
CALL CleanAll-SCM.cmd
CALL CleanAll-Setup.cmd

::==================================================================================================
:: End of
:: $URL: file:///svn/p/y-a-terminal/code/trunk/!-Scripts/CleanAll.cmd $
::==================================================================================================
