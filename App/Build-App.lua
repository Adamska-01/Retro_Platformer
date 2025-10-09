project "App"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetname "Application"
	targetdir ("./Binaries/" .. OutputDir)
	objdir ("./Binaries/Intermediates/" .. OutputDir)
	debugdir "../" -- Set working directory to the root of the solution 
	
	defines { "DF2D_DYNAMIC", "SHARED_DYNAMIC" }

	dependson { "DeadFrame2D" }

	files { 
		"include/**.h", 
		"src/**.cpp", 
	}

	includedirs {
		-- Include Core
		"include",
		"../Core/Shared/include",
		"../Core/DeadFrame2D/include",
		"../Core/Vendor/nlohmann-3.11.3", 
		"../Core/Vendor/Box2D/Module/include",
		"../Core/Vendor/tinyxml2-10.0.0", 
		-- There are a lot of useful sdl structs/classes that the app could use
		"../Core/Vendor/SDL/SDL2-2.30.10/include",
		"../Core/Vendor/SDL/SDL2_image-2.8.2/include",
		"../Core/Vendor/SDL/SDL2_ttf-2.22.0/include",
		"../Core/Vendor/SDL/SDL2_mixer-2.8.0/include"
	}

	links { "DeadFrame2D", "Shared" }


	-- Copy Assets and Shared files in the target dir
	function configure_postbuild(osName, resolvedArch)
		local copy_assets = {}
		local commands = {}

		local libs = {
			SDL2       = "2.30.10",
			SDL2_image = "2.8.2",
			SDL2_ttf   = "2.22.0",
			SDL2_mixer = "2.8.0"
		}
		local engineDir = "../Core/DeadFrame2D/Binaries/" .. osName .. "-" .. "%{cfg.architecture}" .. "/%{cfg.buildcfg}/"
		local sharedDir = "../Core/Shared/Binaries/" .. osName .. "-" .. "%{cfg.architecture}" .. "/%{cfg.buildcfg}/"
		local sdlDir = "../Core/Vendor/SDL/"

		table.insert(copy_assets, make_dir("%{cfg.targetdir}/Core/Shared/Resources"))
		table.insert(copy_assets, make_dir("%{cfg.targetdir}/App/Assets"))
		table.insert(copy_assets, copy_dir("../Core/Shared/Resources/*", "%{cfg.targetdir}/Core/Shared/Resources/"))
		table.insert(copy_assets, copy_dir("Assets/*", "%{cfg.targetdir}/App/Assets/"))

		table.insert(commands, make_dir("%{cfg.targetdir}"))
		table.insert(commands, copy_file(engineDir .. (osName == "windows" and "DeadFrame2D.dll" or "libDeadFrame2D.so"), "%{cfg.targetdir}"))
		table.insert(commands, copy_file(sharedDir .. (osName == "windows" and "Shared.dll" or "libShared.so"), "%{cfg.targetdir}"))

		for lib, version in pairs(libs) do
			local ext = osName == "windows" and "dll" or "so.0"
			local platformDir = osName == "windows" and "Windows" or "Linux"
			
			table.insert(
				commands, 
				copy_file(
					sdlDir .. lib .. "-" .. version .. "/lib/" .. platformDir .. "/" .. resolvedArch .. "/*." .. ext,
					"%{cfg.targetdir}"))
		end

		local all_commands = {}
		table.move(copy_assets, 1, #copy_assets, #all_commands + 1, all_commands)
		table.move(commands, 1, #commands, #all_commands + 1, all_commands)

		postbuildcommands(all_commands)
	end

	
	filter "platforms:x86"
		architecture "x86"

	filter "platforms:x64"
		architecture "x64"


	-- Windows
	filter "system:windows"
		links { "SDL2main", "SDL2", "Box2D" } -- Horrible :( (Box2D will be removed)

	filter { "system:windows", "platforms:x86" }
		libdirs(table.join(
			get_sdl_libdirs("../Core/Vendor/SDL/", "Windows", "x86"),
			get_libdir("../Core/Vendor/Box2D/Binaries/")))
		configure_postbuild("windows", "x86")

	filter { "system:windows", "platforms:x64" }
		libdirs(table.join(
			get_sdl_libdirs("../Core/Vendor/SDL/", "Windows", "x64"),
			get_libdir("../Core/Vendor/Box2D/Binaries/")))
		configure_postbuild("windows", "x64")


	-- Linux
	filter "system:linux"
		linkoptions { '-Wl,-rpath,\\$$ORIGIN' }

	filter { "system:linux", "platforms:x86" }
		configure_postbuild("linux", "x86")

	filter { "system:linux", "platforms:x64" }
		configure_postbuild("linux", "x64")


	-- Build Filters
	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		kind "ConsoleApp"
		symbols "On"

	filter "configurations:Release"
		defines { "RELEASE" }
		runtime "Release"
		optimize "On"
		kind "WindowedApp"
		symbols "Off"