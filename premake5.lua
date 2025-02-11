workspace "Quayside"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Quayside"
	location "Quayside"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
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
			"QS_BUILD_DLL"
		}
	
		postbuildcommands
		{
			("copy /B /Y ..\\bin\\" .. outputdir .. "\\%{prj.name}\\%{prj.name}.dll ..\\bin\\" .. outputdir .. "\\Sandbox\\ > nul")
		}

	filter "configurations:Debug"
		defines "QS_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "QS_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "QS_DIST"
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
		symbols "On"

	filter "configurations:Release"
		defines "QS_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "QS_DIST"
		optimize "On"