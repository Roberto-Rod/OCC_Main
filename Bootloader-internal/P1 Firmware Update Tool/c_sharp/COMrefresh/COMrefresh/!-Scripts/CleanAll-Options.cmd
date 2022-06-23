@ECHO OFF

::==================================================================================================
:: YAT - Yet Another Terminal.
:: Visit YAT at https://sourceforge.net/projects/y-a-terminal/.
:: Contact YAT by mailto:y-a-terminal@users.sourceforge.net.
:: ------------------------------------------------------------------------------------------------
:: $URL: file:///svn/p/y-a-terminal/code/trunk/!-Scripts/CleanAll-Options.cmd $
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
:: Copyright © 2003-2021 Matthias Kläy.
:: All rights reserved.
:: ------------------------------------------------------------------------------------------------
:: This source code is licensed under the GNU LGPL.
:: See http://www.gnu.org/licenses/lgpl.html for license details.
::==================================================================================================

PUSHD ..

ECHO Cleaning solution user options . . .
DEL /F /Q /A:H "*.suo"
ECHO . . . successfully cleaned

ECHO Cleaning additional solution settings . . .
DEL /F /Q /A:H "*.xml"
ECHO . . . successfully cleaned

ECHO Cleaning all project user options . . .
FOR /R %%I IN (.) DO CALL "!-Scripts\CleanFiles.cmd" "%%I" "*.csproj.user"
ECHO . . . successfully cleaned

POPD

::==================================================================================================
:: End of
:: $URL: file:///svn/p/y-a-terminal/code/trunk/!-Scripts/CleanAll-Options.cmd $
::==================================================================================================
