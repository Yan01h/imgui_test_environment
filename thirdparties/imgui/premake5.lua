project "imgui"
		targetname "Imgui"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "Off"
		location "%{wks.location}/../build"

		targetdir "%{wks.location}/../bin/%{cfg.system}-%{cfg.buildcfg}%{cfg.platform}"
		objdir "%{wks.location}/../bin/%{cfg.system}-%{cfg.buildcfg}%{cfg.platform}/obj"

		includedirs {
			"include/imgui"
		}

		links {
			"d3d9.lib"
		}

		files {
			"include/**.h",
			"src/**.cpp"
		}

		filter "platforms:x86"
			architecture "x86"

		filter "platforms:x64"
			architecture "x86_64"