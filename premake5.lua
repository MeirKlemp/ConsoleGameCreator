workspace "ConsoleGameCreator"
  configurations {
    "Debug32", "Release32",
    "Debug64", "Release64"
  }

  startproject "Sandbox"

  filter "configurations:*32"
    architecture "x86"
  filter "configurations:*64"
    architecture "x86_64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "ConsoleGameCreator"
  location "ConsoleGameCreator"
  kind "StaticLib"
  language "C++"
  cppdialect "C++17"

  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
  objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  pchheader "cgcpch.h"

  files {
    "%{prj.name}/src/*.h",
    "%{prj.name}/src/*.cpp"
  }

  defines {}

  includedirs {}

  links {}

  filter "system:windows"
    systemversion "latest"
    defines "CGC_Windows"

  filter "configurations:Debug*"
    defines "CGC_Debug"
    runtime "Debug"
    symbols "on"
  
  filter "configurations:Release*"
    defines "CGC_Release"
    runtime "Release"
    optimize "on"
  
project "Sandbox"
  location "Sandbox"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"

  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
  objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  files {
    "%{prj.name}/src/*.h",
    "%{prj.name}/src/*.cpp"
  }

  defines {}

  includedirs {
    "ConsoleGameCreator/src"
  }

  links {
    "ConsoleGameCreator"
  }

  filter "system:windows"
    systemversion "latest"
    defines "CGC_Windows"

  filter "configurations:Debug*"
    defines "CGC_Debug"
    runtime "Debug"
    symbols "on"
  
  filter "configurations:Release*"
    defines "CGC_Release"
    runtime "Release"
    optimize "on"