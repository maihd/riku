local RIKU_DIR = path.getabsolute("..")

project "riku"
do
   kind "staticlib"

   flags {
      "NoPCH",
      "NoRTTI",
      "NoWinRT",
      "NoExceptions",
      "NoFramePointer",
      "NoEditAndContinue",
      "NoBufferSecurityCheck",

      "ExtraWarnings"
   }

   includedirs {
      path.join(RIKU_DIR, "include")
   }

   files {
      path.join(RIKU_DIR, "src/*.cc"),
      path.join(RIKU_DIR, "src/**/*.cc"),
      path.join(RIKU_DIR, "include/*.h"),
      path.join(RIKU_DIR, "include/**/*.h"),
   }

   defines {
   }

   configuration { "debug" }
   do
      defines {
         "_DEBUG"
      }
   end

   configuration { "release" }
   do
      defines {
         "NDEBUG"
      }

      flags {
         "NoBufferSecurityCheck",
      }
   end

   configuration { "linux-*" }
   do
      buildoptions {
         "-fPIC",
      }
   end
end