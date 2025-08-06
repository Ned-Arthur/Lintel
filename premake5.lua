-- premake generates project files (eg VS, make, xcode)

workspace "Lintel"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Lintel"
	location "Lintel"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	-- Libraries used by the engine, should remain empty
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/src/Lintel",
	}

----- PLATFORMS -----
	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"LN_PLATFORM_WINDOWS",
			"LN_BUILD_DLL"
		}

----- CONFIGURATIONS -----
	filter "configurations:Debug"
		defines "LN_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "LN_RELEASE"
		optimize "on"


---------- Game Project ----------

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	-- Libraries used by the game, i.e. the engine
	includedirs
	{
		"Lintel/src"
	}

	links
	{
		"Lintel"
	}

----- PLATFORMS -----
	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"LN_PLATFORM_WINDOWS"
		}

----- CONFIGURATIONS -----
	filter "configurations:Debug"
		defines "LN_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "LN_RELEASE"
		optimize "on"
