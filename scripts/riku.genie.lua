local RIKU_DIR = path.getabsolute("..")

project "riku"
do
   kind "staticlib"

   includedirs {
      path.join(RIKU_DIR, "include"),
      path.join(RIKU_DIR, "3rdparty/zlib-1.2.11")
   }

   files {
      path.join(RIKU_DIR, "src/*.cc"),
      path.join(RIKU_DIR, "include/*.h"),
      path.join(RIKU_DIR, "include/**/*.h"),
      path.join(RIKU_DIR, "3rdparty/zlib-1.2.11/*.h"),
      path.join(RIKU_DIR, "3rdparty/zlib-1.2.11/*.c"),
   }

   defines {
   }

   local PLATFORM = _OPTIONS["platform"];
   if PLATFORM == "osx" then
      files {
         path.join(RIKU_DIR, "src/osx/*.cc"),
         path.join(RIKU_DIR, "src/osx/**/*.cc"),
      }
   end

   if PLATFORM == "ios" then
      files {
         path.join(RIKU_DIR, "src/ios/*.cc"),
         path.join(RIKU_DIR, "src/ios/**/*.cc"),
      }
   end

   if string.sub(PLATFORM, 0, 5) == "linux" then
      files {
         path.join(RIKU_DIR, "src/linux/*.cc"),
         path.join(RIKU_DIR, "src/linux/**/*.cc"),
      }
   end

   if string.sub(PLATFORM, 0, 7) == "android" then
      files {
         path.join(RIKU_DIR, "src/android/*.cc"),
         path.join(RIKU_DIR, "src/android/**/*.cc"),
      }
   end

   if string.sub(PLATFORM, 0, 7) == "windows" then
      files {
         path.join(RIKU_DIR, "src/windows/*.cc"),
         path.join(RIKU_DIR, "src/windows/**/*.cc"),
      }
   end

   configuration {}
end