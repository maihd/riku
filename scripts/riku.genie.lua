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
      path.join(RIKU_DIR, "src/**/*.cc"),
      path.join(RIKU_DIR, "include/*.h"),
      path.join(RIKU_DIR, "include/**/*.h"),
      path.join(RIKU_DIR, "3rdparty/zlib-1.2.11/*.h"),
      path.join(RIKU_DIR, "3rdparty/zlib-1.2.11/*.c"),
   }

   defines {
   }

   configuration { "osx" }
   do
      files {
         path.join(RIKU_DIR, "src/osx/*.cc"),
         path.join(RIKU_DIR, "src/osx/**/*.cc"),
      }
   end

   configuration { "linux" }
   do
      files {
         path.join(RIKU_DIR, "src/linux/*.cc"),
         path.join(RIKU_DIR, "src/linux/**/*.cc"),
      }
   end

   configuration { "android" }
   do
      files {
         path.join(RIKU_DIR, "src/android/*.cc"),
         path.join(RIKU_DIR, "src/android/**/*.cc"),
      }
   end

   configuration { "windows" }
   do
      files {
         path.join(RIKU_DIR, "src/windows/*.cc"),
         path.join(RIKU_DIR, "src/windows/**/*.cc"),
      }
   end

   configuration {}
end