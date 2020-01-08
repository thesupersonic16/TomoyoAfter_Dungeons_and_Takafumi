-- premake5.lua
workspace "TomoyoAfter_Dungeons_and_Takafumi"
   configurations { "Debug", "Release" }

project "TomoyoAfter_Dungeons_and_Takafumi"
   kind "SharedLib"
   language "C++"
   cppdialect("C++17")
   targetdir "bin/%{cfg.buildcfg}"
   targetname "dt00"
   pic "on"
   
   local includeDirs = { "include" }
   includedirs(includeDirs)
   files { "include/**.h", "src/**.h", "src/**.cpp" }

   -- MSC Optimization
   filter("toolset:msc")
      flags("MultiProcessorCompile")

   -- GCC C++ 17 Filesystem support
   filter("toolset:gcc")
      links("stdc++fs")

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"