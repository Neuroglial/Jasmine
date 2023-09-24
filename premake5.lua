workspace "Jasmine"
	architecture "x64"
	startproject "Sandbox"


	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] 	= 	"Jasmine/vendor/GLFW/include"
IncludeDir["Glad"] 	= 	"Jasmine/vendor/Glad/include"
IncludeDir["ImGui"] 	= 	"Jasmine/vendor/imgui"
IncludeDir["glm"] 	=	"Jasmine/vendor/glm"


group "Dependencies"
	include "Jasmine/vendor/GLFW"
	include "Jasmine/vendor/Glad"
	include "Jasmine/vendor/imgui"
	
	

group ""

	
project "Jasmine"
	location "Jasmine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "JM_PCH.h"
	pchsource "Jasmine/src/JM_PCH.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"JM_PLATFORM_WINDOWS",
			"JM_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "JM_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "JM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "JM_DIST"
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
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Jasmine/vendor/spdlog/include",
		"Jasmine/src",
		"Jasmine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Jasmine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"JM_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "JM_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "JM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "JM_DIST"
		runtime "Release"
		optimize "on"