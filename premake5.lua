workspace "graph-drawing"
   configurations { "Debug", "Release" }
   platforms { "clang", "gcc"}

project "graph-drawing"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++14"
   flags "RelativeLinks"
   files { "src/**.hpp", "src/**.cpp" }

   sysincludedirs { "/usr/include/SDL2", "../lib/include" }
   libdirs { "../lib/lib" }
   links {
          "Magnum",
          "MagnumDebugTools",
          "MagnumShapes",
          "MagnumPrimitives",
          "MagnumMeshTools",
          "MagnumShaders",
          "MagnumSceneGraph",
          "MagnumSdl2Application",
          "SDL2",
          "CorradeUtility",
          "CorradePluginManager",
          "CorradeTestSuite",
          "GL"
         }

   location "build-premake/"
   targetdir "build-premake/%{cfg.platform}/bin/%{cfg.buildcfg}"

   filter { "platforms:clang" }
      toolset "clang"

  filter { "platforms:gcc" }
     toolset "gcc"

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
