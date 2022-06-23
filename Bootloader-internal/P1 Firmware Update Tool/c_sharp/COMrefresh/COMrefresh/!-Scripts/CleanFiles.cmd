@ECHO OFF

::==================================================================================================
:: YAT - Yet Another Terminal.
:: Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
:: Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
:: ------------------------------------------------------------------------------------------------
:: $URL: file:///svn/p/y-a-terminal/code/trunk/!-Scripts/CleanFiles.cmd $
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
:: Copyright � 2003-2021 Matthias Kl�y.
:: All rights reserved.
:: ------------------------------------------------------------------------------------------------
:: This source code is licensed under the GNU LGPL.
:: See http://www.gnu.org/licenses/lgpl.html for license details.
::==================================================================================================

IF %1=="" GOTO :NoPath
IF %2=="" GOTO :NoDirectory

::--------------------------------------------------------------------------------------------------
PUSHD %1

ECHO Cleaning %2 in %1 . . .
DEL /F /Q %2

POPD
GOTO :End
::--------------------------------------------------------------------------------------------------

:NoPath
ECHO Parameter 1 must be a valid file path (wildcards allowed)!
GOTO :End

:NoDirectory
ECHO Parameter 2 must be a valid directory name!
GOTO :End

:End

::==================================================================================================
:: End of
:: $URL: file:///svn/p/y-a-terminal/code/trunk/!-Scripts/CleanFiles.cmd $
::==================================================================================================
