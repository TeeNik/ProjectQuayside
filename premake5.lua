workspace "Quayside"
	architecture "x64"
	startproject "Sandbox"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Quayside/vendor/GLFW/include"
IncludeDir["Glad"] = "Quayside/vendor/Glad/include"
IncludeDir["ImGui"] = "Quayside/vendor/ImGui"

group "Dependencies"
	include "Quayside/vendor/GLFW"
	include "Quayside/vendor/Glad"
	include "Quayside/vendor/ImGui"
group ""

project "Quayside"
	location "Quayside"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "qspch.h"
	pchsource "Quayside/src/qspch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"dwmapi.lib"
	}

	buildoptions
	{
		"/utf-8"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"QS_PLATFORM_WINDOWS",
			"QS_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
	
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines 
		{
			"QS_DEBUG",
			"QS_ENABLE_ASSERTS"
		}
		staticruntime "off"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "QS_RELEASE"
		staticruntime "off"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "QS_DIST"
		staticruntime "off"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Quayside/vendor/spdlog/include",
		"Quayside/src"
	}

	links
	{
		"Quayside"
	}

	buildoptions
	{
		"/utf-8"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"QS_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "QS_DEBUG"
		staticruntime "off"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "QS_RELEASE"
		staticruntime "off"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "QS_DIST"
		staticruntime "off"
		runtime "Release"
		optimize "On"