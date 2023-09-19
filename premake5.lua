workspace "Jasmine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Jasmine"
	location "Jasmine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"JM_PLATFORM_WINDOWS",
			"JM_BUILD_DLL"
		}

		postbuildcommands
		{
			{"{COPY} ../bin/" .. outputdir .. "/Jasmine/*.dll ../bin/" .. outputdir .. "/Sandbox"}
		}

	filter "configurations:Debug"
		defines "JM_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "JM_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "JM_DIST"
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
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"JM_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "JM_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "JM_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "JM_DIST"
		optimize "On"