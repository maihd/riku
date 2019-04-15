local RIKU_DIR          = path.getabsolute("..")
local RIKU_BUILD_DIR    = path.join(RIKU_DIR, "build")
local RIKU_3RDPARTY_DIR = path.join(RIKU_DIR, "3rdparty")

solution "riku"
do
   language "c++"
   location (path.join(RIKU_BUILD_DIR, TARGET_PLATFORM))
   
   platforms {
      "x32", "x64", "native"
   }
   
   configurations {
      "debug", "release"
   }

   startproject "riku.unit_tests"

   configuration { "debug" }
   do
      flags {
         "Symbols"
      }
   end
end

-- Setting toolchain
dofile "toolchain.genie.lua"
toolchain(RIKU_BUILD_DIR, RIKU_3RDPARTY_DIR)

-- Setting riku project
dofile "riku.genie.lua"

project "riku.unit_tests"
do
   if _ACTION == "android-studio" then
      kind "sharedlib"
   else
      kind "consoleapp"
   end

   removeflags {
      "NoExceptions",
   }

   links {
      "riku"
   }

   includedirs {
      path.join(RIKU_DIR, "include")
   }

   files {
      path.join(RIKU_DIR, "unit_tests/*.h"),
      path.join(RIKU_DIR, "unit_tests/**/*.h"),
      path.join(RIKU_DIR, "unit_tests/*.cc"),
   }

   configuration { "linux" }
   do
      links {
         "pthread"
      }
   end

   strip()
end