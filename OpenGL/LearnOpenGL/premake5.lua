workspace "LearnOpenGL"
	architecture "x64"
	startproject "Project1"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["Glad"] = "vendor/Glad/include"
IncludeDir["ImGui"] = "vendor/imgui"
IncludeDir["glm"] = "vendor/glm"

group "Dependencies"
	include "vendor/GLFW"
	include "vendor/Glad"
	include "vendor/imgui"

group ""

project "Project1"
	location "Project1"
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
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"vendor/spdlog/include",
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

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"