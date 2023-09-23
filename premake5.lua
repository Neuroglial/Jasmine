workspace "Jasmine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Jasmine/vendor/GLFW/include"
IncludeDir["Glad"] = "Jasmine/vendor/Glad/include"
IncludeDir["ImGui"] = "Jasmine/vendor/imgui"

startproject "Sandbox"

group "Dependencies"
	include "Jasmine/vendor/GLFW"
	include "Jasmine/vendor/Glad"
	include "Jasmine/vendor/imgui"
	

group ""

	
project "Jasmine"
	location "Jasmine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "JM_PCH.h"
	pchsource "Jasmine/src/JM_PCH.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		defines
		{
			"JM_PLATFORM_WINDOWS",
			"JM_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox\"")
		}

	filter "configurations:Debug"
		defines "JM_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "JM_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "JM_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Jasmine/vendor/spdlog/include",
		"Jasmine/src"
	}

	links
	{
		"Jasmine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"JM_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "JM_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "JM_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "JM_DIST"
		runtime "Release"
		optimize "On"