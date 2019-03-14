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

   configuration {}
end