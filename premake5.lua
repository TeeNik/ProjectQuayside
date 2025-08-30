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
IncludeDir["glm"] = "Quayside/vendor/glm"

group "Dependencies"
	include "Quayside/vendor/GLFW"
	include "Quayside/vendor/Glad"
	include "Quayside/vendor/ImGui"
group ""

project "Quayside"
	location "Quayside"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "qspch.h"
	pchsource "Quayside/src/qspch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vedor/glm/glm/**.hpp",
		"%{prj.name}/vedor/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
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
		systemversion "latest"

		defines
		{
			"QS_PLATFORM_WINDOWS",
			"QS_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines 
		{
			"QS_DEBUG",
			"QS_ENABLE_ASSERTS"
		}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "QS_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "QS_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Quayside/src",
		"Quayside/vendor",
		"%{IncludeDir.glm}",
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
		systemversion "latest"

		defines
		{
			"QS_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "QS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "QS_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "QS_DIST"
		runtime "Release"
		optimize "on"