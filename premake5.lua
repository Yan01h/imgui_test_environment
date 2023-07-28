workspace "imgui_test_environment"
	startproject "imgui_test_environment"
	configurations { "Debug", "Release" }
	location "build"

	flags { "MultiProcessorCompile" }

	filter "system:windows"
		systemversion "latest"
		defines { "_WINDOWS" }
		platforms { "x86", "x64" }

	filter "system:macosx"
		defines { "_MACOS" }

	filter "system:linux"
		defines { "_LINUX" }

	filter "configurations:Debug"
		symbols "On"
		optimize "Off"
		runtime "Debug"
		defines { "_DEBUG" }

	filter "configurations:Release"
		symbols "Off"
		optimize "On"
		runtime "Release"
		defines { "_RELEASE", "NDEBUG" }

	include "thirdparties/imgui"

	project "imgui_test_environment"
		targetname "ImguiTestEnvironment"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++20"
		staticruntime "Off"
		location "build"

		targetdir "bin/%{cfg.system}-%{cfg.buildcfg}%{cfg.platform}"
		objdir "bin/%{cfg.system}-%{cfg.buildcfg}%{cfg.platform}/obj"

		includedirs {
			"include",
			"thirdparties/imgui/include"
		}

		links {
			"imgui",
			"d3d9.lib",
		}

		files {
			"include/**.h",
			"src/**.cpp"
		}

		filter "platforms:x86"
			architecture "x86"

		filter "platforms:x64"
			architecture "x86_64"