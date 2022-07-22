workspace "Snake"
	architecture "x64"
	startproject "Snake"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Snake"
	location ""
	kind "ConsoleApp"
	language "C++"

	targetdir ("Binaries/" .. outputdir .. "/%{prj.name}/")
	objdir ("Intermediate/" .. outputdir .. "%{prj.name}")

	files
	{
		"Source/%{prj.name}/**.h",
		"Source/%{prj.name}/**.cpp",
		"Source/%{prj.name}/Public/**.h",
		"Source/%{prj.name}/Private/**.cpp",
	}

	includedirs
	{
		"Source/%{prj.name}/Public",
		"ThirdParty/SDL/include"
	}

	links
	{
		"ThirdParty/SDL/lib/x64/SDL2main.lib",
		"ThirdParty/SDL/lib/x64/SDL2.lib"
	}

	filter "configurations:Debug"
		staticruntime "Off"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		staticruntime "Off"
		runtime "Release"
		optimize "On"

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		
		postbuildcommands
		{
			("{COPYFILE} ThirdParty/SDL/lib/x64/SDL2.dll %{cfg.targetdir}")
		}
