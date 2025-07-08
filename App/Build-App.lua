project "App"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetname "Application"
	targetdir ("./Binaries/" .. OutputDir)
	objdir ("./Binaries/Intermediates/" .. OutputDir)
	debugdir "../" -- Set working directory to the root of the solution 
	
	dependson { "2DGameEngine", "Box2D", "Shared" }

	files { 
		"include/**.h", 
		"src/**.cpp", 
	}

	includedirs {
		-- Include Core
		"include",
		"../Core/Shared/include",
		"../Core/2DGameEngine/include",
		"../Core/Vendor/nlohmann-3.11.3", 
		"../Core/Vendor/Box2D/include",
		"../Core/Vendor/tinyxml2-10.0.0", 
		-- There are a lot of useful sdl structs/classes that the app could use
		"../Core/Vendor/SDL/SDL2-2.30.10/include",
		"../Core/Vendor/SDL/SDL2_image-2.8.2/include",
		"../Core/Vendor/SDL/SDL2_ttf-2.22.0/include",
		"../Core/Vendor/SDL/SDL2_mixer-2.8.0/include"
	}

	links { "2DGameEngine", "Box2D",  "Shared" }

	-- Copy Assets and Shared files in the target dir
	local copy_assets = {}
	if os.host() == "windows" then
		copy_assets = {
			'{MKDIR} "%{cfg.targetdir}/Core/Shared/Resources"',
			'{MKDIR} "%{cfg.targetdir}/App/Assets"',
			'xcopy /E /Y /I "..\\Core\\Shared\\Resources\\*" "%{cfg.targetdir}\\Core\\Shared\\Resources\\"',
			'xcopy /E /Y /I "Assets\\*" "%{cfg.targetdir}\\App\\Assets\\"'
		}
	else
		copy_assets = {
			"mkdir -p %{cfg.targetdir}/Core/Shared/Resources",
			"mkdir -p %{cfg.targetdir}/App/Assets",
			"cp -r ../Core/Shared/Resources/* %{cfg.targetdir}/Core/Shared/Resources/",
			"cp -r Assets/* %{cfg.targetdir}/App/Assets/"
		}
	end
	
	postbuildcommands(copy_assets)


	-- Linux
	filter "system:linux"
		links { "SDL2", "SDL2_image", "SDL2_ttf", "SDL2_mixer", "Box2D" }
		linkoptions { '-Wl,-rpath,\\$$ORIGIN' }
		
	-- Linux x86
	filter { "system:linux", "platforms:x86" }
		libdirs(table.join(
			get_sdl_libdirs("../Core/Vendor/SDL/", "Linux/", "x86/"),
			get_box2d_libdirs("../Core/Vendor/Box2D/Binaries/")))
		postbuildcommands {
			"mkdir -p %{cfg.targetdir}",
			"cp -v ../Core/Vendor/SDL/SDL2-2.30.10/lib/Linux/x86/*.so.0 %{cfg.targetdir}",
			"cp -v ../Core/Vendor/SDL/SDL2_image-2.8.2/lib/Linux/x86/*.so.0 %{cfg.targetdir}",
			"cp -v ../Core/Vendor/SDL/SDL2_ttf-2.22.0/lib/Linux/x86/*.so.0 %{cfg.targetdir}",
			"cp -v ../Core/Vendor/SDL/SDL2_mixer-2.8.0/lib/Linux/x86/*.so.0 %{cfg.targetdir}"
		}

	-- Linux x64
	filter { "system:linux", "platforms:x64" }
		libdirs(table.join(
			get_sdl_libdirs("../Core/Vendor/SDL/", "Linux/", "x64/"),
			get_box2d_libdirs("../Core/Vendor/Box2D/Binaries/")))
		postbuildcommands {
			"mkdir -p %{cfg.targetdir}",
			"cp -v ../Core/Vendor/SDL/SDL2-2.30.10/lib/Linux/x64/*.so.0 %{cfg.targetdir}",
			"cp -v ../Core/Vendor/SDL/SDL2_image-2.8.2/lib/Linux/x64/*.so.0 %{cfg.targetdir}",
			"cp -v ../Core/Vendor/SDL/SDL2_ttf-2.22.0/lib/Linux/x64/*.so.0 %{cfg.targetdir}",
			"cp -v ../Core/Vendor/SDL/SDL2_mixer-2.8.0/lib/Linux/x64/*.so.0 %{cfg.targetdir}"
		}

	-- Windows x86
	filter { "system:windows", "platforms:x86" }
		architecture "x86"
		libdirs(table.join(
			get_sdl_libdirs("../Core/Vendor/SDL/", "Windows/", "x86/"),
			get_box2d_libdirs("../Core/Vendor/Box2D/Binaries/")))
		postbuildcommands {
			'{MKDIR} "%{cfg.targetdir}"',
			'{COPY} ../Core/Vendor/SDL/SDL2-2.30.10/lib/Windows/x86/*.dll "%{cfg.targetdir}"',
			'{COPY} ../Core/Vendor/SDL/SDL2_image-2.8.2/lib/Windows/x86/*.dll "%{cfg.targetdir}"',
			'{COPY} ../Core/Vendor/SDL/SDL2_ttf-2.22.0/lib/Windows/x86/*.dll "%{cfg.targetdir}"',
			'{COPY} ../Core/Vendor/SDL/SDL2_mixer-2.8.0/lib/Windows/x86/*.dll "%{cfg.targetdir}"'
		}

	-- Windows x64
	filter { "system:windows", "platforms:x64" }
		architecture "x64"
		libdirs(table.join(
			get_sdl_libdirs("../Core/Vendor/SDL/", "Windows/", "x64/"),
			get_box2d_libdirs("../Core/Vendor/Box2D/Binaries/")))
		postbuildcommands {
			'{MKDIR} "%{cfg.targetdir}"',
			'{COPY} ../Core/Vendor/SDL/SDL2-2.30.10/lib/Windows/x64/*.dll "%{cfg.targetdir}"',
			'{COPY} ../Core/Vendor/SDL/SDL2_image-2.8.2/lib/Windows/x64/*.dll "%{cfg.targetdir}"',
			'{COPY} ../Core/Vendor/SDL/SDL2_ttf-2.22.0/lib/Windows/x64/*.dll "%{cfg.targetdir}"',
			'{COPY} ../Core/Vendor/SDL/SDL2_mixer-2.8.0/lib/Windows/x64/*.dll "%{cfg.targetdir}"'
		}

	-- Apparently Windows can resolve links through 2DGameEngine
	

	-- Filters
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

	filter "platforms:x86"
		architecture "x86"
		
	filter "platforms:x64"
		architecture "x64"