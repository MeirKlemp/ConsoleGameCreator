workspace "ConsoleGameCreator"
  configurations {
    "Debug", "Release"
  }

  architecture "x86_64"
  startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

includedir = {}
includedir["fmt"] = "ConsoleGameCreator/vendor/fmt/include"
includedir["unilib"] = "ConsoleGameCreator/vendor/unilib/unilib"

group "Dependencies"
  include "ConsoleGameCreator/vendor/unilib"
group ""

project "ConsoleGameCreator"
  location "ConsoleGameCreator"
  kind "StaticLib"
  language "C++"
  cppdialect "C++17"

  targetdir ("bin/" .. outputdir .. "/%{prj.name}")
  objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

  pchheader "cgcpch.h"
  pchsource "ConsoleGameCreator/src/cgcpch.cpp"

  files {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp",
    "%{prj.name}/vendor/fmt/include/fmt/**.h"
  }

  defines {
    "FMT_HEADER_ONLY"
  }

  includedirs {
    "%{prj.name}/src",
    includedir["fmt"],
    includedir["unilib"]
  }

  links {
    "unilib"
  }

  filter "system:windows"
    systemversion "latest"
    defines "CGC_WINDOWS"

  filter "configurations:Debug*"
    defines "CGC_DEBUG"
    runtime "Debug"
    symbols "on"
  
  filter "configurations:Release*"
    defines "CGC_RELEASE"
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
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp"
  }

  defines {
    "FMT_HEADER_ONLY"
  }

  includedirs {
    "ConsoleGameCreator/src",
    includedir["fmt"]
  }

  links {
    "ConsoleGameCreator"
  }

  filter "system:windows"
    systemversion "latest"
    defines "CGC_WINDOWS"

  filter "configurations:Debug*"
    defines "CGC_DEBUG"
    runtime "Debug"
    symbols "on"
  
  filter "configurations:Release*"
    defines "CGC_RELEASE"
    runtime "Release"
    optimize "on"