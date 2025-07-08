@echo off

:: Data
set "PREMAKE_PATH=Core\Vendor\Premake\Windows\premake5.exe"
set "PREMAKE_PATH_BASH=Core/Vendor/Premake/Windows/premake5.exe"
set "HOOK_PATH=../.git/hooks/post-checkout"

pushd ..

:: Update submodules
git submodule update --init --recursive

:: Run Premake
echo Generating project files...
%PREMAKE_PATH% --file=Build.lua vs2022
popd
echo Project files generated!


:: Install Git hook (post-checkout)
echo Installing Git post-checkout hook...
(
	echo #!/bin/sh
	echo echo "Regenerating project files with Premake..."
	echo %PREMAKE_PATH_BASH% --file=Build.lua vs2022
) > %HOOK_PATH%
echo Hook installed at %HOOK_PATH%

pause