local RIKU_DIR          = path.getabsolute("..")
local RIKU_BUILD_DIR    = path.join(RIKU_DIR, "build")
local RIKU_3RDPARTY_DIR = path.join(RIKU_DIR, "3rdparty")

newaction {
   trigger = "clean",
   description = "Clean all generated projects",
   execute = function ()
      io.write("Removing build directory...")
      
      if os.rmdir(RIKU_BUILD_DIR) then
         io.write("DONE!\n")
      else
         io.write("FAILED!\n")
      end
   end,
}

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
   kind "consoleapp"

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
      path.join(RIKU_DIR, "unit_tests/**/*.cc"),
   }

   configuration { "linux" }
   do
      links {
         "pthread"
      }
   end

   strip()
end