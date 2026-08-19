-- Root Build Script (build.lua)
workspace "Project"
	platforms  { "x86", "x64" }
	configurations { "Debug", "Release" }
	startproject "App"  -- Set the app project as the start project

	-- Workspace-wide build options for MSVC (Windows-specific)
	filter "system:windows"
		buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

	-- Output directory structure for builds
	OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"


	-- Helpers
	function make_dir(path)
		if os.host() == "windows" then
			path = path:gsub("/", "\\")
			return '{MKDIR} "' .. path .. '"'
		else
			return 'mkdir -p ' .. path
		end
	end


	function copy_dir(src, dst)
		if os.host() == "windows" then
			-- Convert forward slashes to backslashes
			src = src:gsub("/", "\\")
			dst = dst:gsub("/", "\\")
			return string.format('xcopy /E /Y /I "%s" "%s"', src, dst)
		else
			return string.format('cp -r %s %s', src, dst)
		end
	end

	function copy_file(src, dst)
		if os.host() == "windows" then
			src = src:gsub("/", "\\")
			dst = dst:gsub("/", "\\")
			return '{COPY} "' .. src .. '" "' .. dst .. '"'
		else
			return 'cp -v ' .. src .. ' ' .. dst
		end
	end

	function get_sdl_libdirs(basePath, platformPath, architecturePath)
		local sdl_version = "2.30.10"
		
		return basePath .. "SDL2-" .. sdl_version .. "/lib/" .. platformPath .. "/" .. architecturePath
	end

	function get_libdir(basePath)
		return {
			basePath .. OutputDir
		}
	end


	-- Include Core build script
	include "App/Build-App.lua"
	include "Core/Build.lua" 