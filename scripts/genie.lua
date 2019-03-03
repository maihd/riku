local RIKU_DIR          = path.getabsolute("..")
local RIKU_BUILD_DIR    = path.join(RIKU_DIR, "build")
local RIKU_3RDPARTY_DIR = path.join(RIKU_DIR, "3rdparty")

function string.startwith(s, b)
   return string.sub(s, 1, string.len(b)) == b
end

newoption {
   trigger = "platform",
   value = "PLATFORM",
   description = "Choose target platform",

   allowed = {
      { "android-arm"  , "Android - ARM"   },
      { "windows-x86"  , "Windows - x86"   },
      { "windows-x64"  , "Windows - x64"   },
      { "windows-clang", "Windows - Clang" }
   }
}

newoption {
   trigger = "android",
   value = "#",
   description = "Choose target android platform version (default: android-19)",
}

local TARGET_PLATFORM = _OPTIONS["platform"]
if TARGET_PLATFORM == nil then
   if string.startwith(_ACTION, "vs") or string.startwith(_ACTION, "mingw") then
      TARGET_PLATFORM = "windows"
   else
      TARGET_PLATFORM = "linux"
   end
end

newaction {
   trigger = 'clean',
   description = 'Clean all generated projects',
   execute = function ()
      io.write('Removing build directory...')
      
      if os.rmdir(RIKU_BUILD_DIR) then
         io.write('DONE!\n')
      else
         io.write('FAILED!\n')
      end
   end,
}

solution 'riku'
do
   language 'c++'
   location (path.join(RIKU_BUILD_DIR, TARGET_PLATFORM))
   
   platforms {
      'x32', 'x64', 'native'
   }
   
   configurations {
      'debug', 'release'
   }

   startproject 'riku.unit_tests'

   configuration { 'debug' }
   do
      flags {
         'Symbols' 
      }

      defines {
         '_DEBUG=1'
      }
   end

   configuration { 'release' }
   do
      flags { 
         'OptimizeSpeed', 
         'No64BitChecks', 
      }

      defines {
         'NDEBUG=1'
      }
   end

   configuration { 'debug', 'x32' }
   do
      targetdir (path.join(RIKU_BUILD_DIR, TARGET_PLATFORM, 'x32/debug'))
   end

   configuration { 'debug', 'x64' }
   do
      targetdir (path.join(RIKU_BUILD_DIR, TARGET_PLATFORM, 'x64/debug'))
   end

   configuration { 'release', 'x32' }
   do
      targetdir (path.join(RIKU_BUILD_DIR, TARGET_PLATFORM, 'x32/release'))
   end

   configuration { 'release', 'x64' }
   do
      targetdir (path.join(RIKU_BUILD_DIR, TARGET_PLATFORM, 'x32/release'))
   end

   configuration { 'vs*' }
   do
      buildoptions {
         '/wd4201', -- warning C4201: nonstandard extension used : nameless struct/union
         '/wd4458', -- warning C4458: declaration of '*' hides class member
         '/wd4005', -- warning C4005: macro redefinition
      }
   end

   if TARGET_PLATFORM == "android-arm" then
      if not os.getenv("ANDROID_NDK_ARM")
      or not os.getenv("ANDROID_NDK_CLANG")
      or not os.getenv("ANDROID_NDK_ROOT") then
         print("You should set ANDROID_NDK_CLANG, ANDROID_NDK_ARM, and ANDROID_NDK_ROOT environment variables.")
      end

      premake.gcc.cc   = "$(ANDROID_NDK_CLANG)/bin/clang"
      premake.gcc.cxx  = "$(ANDROID_NDK_CLANG)/bin/clang++"
      premake.gcc.ar   = "$(ANDROID_NDK_ARM)/bin/arm-linux-androideabi-ar"
         
      premake.gcc.llvm = true
   end

   configuration { "android-*" }
   do
      flags {
			"NoImportLib",
      }

      includedirs {
			"$(ANDROID_NDK_ROOT)/sources/cxx-stl/llvm-libc++/include",
			"${ANDROID_NDK_ROOT}/sysroot/usr/include",
			"${ANDROID_NDK_ROOT}/sysroot/usr/include/arm-linux-androideabi",
      }
      
      linkoptions {
			"-nostdlib",
      }

      links {
			"c",
			"dl",
			"m",
			"android",
			"log",
			"c++_shared",
			"gcc",
      }

      buildoptions {
         "-fPIC",
         "-fdeclspec",
         "-fms-extensions",
			"-no-canonical-prefixes",
			"-Wa,--noexecstack",
			"-fstack-protector-strong",
			"-ffunction-sections",
			"-Wunused-value",
         "-Wundef",
         "-Wmacro-redefined",
      }

      defines {
         "__ANDROID__"
      }

      linkoptions {
      }
   end
   local androidPlatform = _OPTIONS[""] or "android-19"
   configuration { "android-arm" }
   do
		targetdir (path.join(_buildDir, "android-arm/bin"))
      objdir (path.join(_buildDir, "android-arm/obj"))
      
		libdirs {
			"$(ANDROID_NDK_ROOT)/sources/cxx-stl/llvm-libc++/libs/armeabi-v7a",
      }
      
		includedirs {
			"$(ANDROID_NDK_ROOT)/sysroot/usr/include/arm-linux-androideabi",
      }
      
		buildoptions {
			"-gcc-toolchain $(ANDROID_NDK_ARM)",
			"--sysroot=" .. path.join("$(ANDROID_NDK_ROOT)/platforms", androidPlatform, "arch-arm"),
			"-target armv7-none-linux-androideabi",
			"-mthumb",
			"-march=armv7-a",
			"-mfloat-abi=softfp",
			"-mfpu=neon",
			"-Wunused-value",
			"-Wundef",
      }
      
		linkoptions {
			"-gcc-toolchain $(ANDROID_NDK_ARM)",
			"--sysroot=" .. path.join("$(ANDROID_NDK_ROOT)/platforms", androidPlatform, "arch-arm"),
			path.join("$(ANDROID_NDK_ROOT)/platforms", androidPlatform, "arch-arm/usr/lib/crtbegin_so.o"),
			path.join("$(ANDROID_NDK_ROOT)/platforms", androidPlatform, "arch-arm/usr/lib/crtend_so.o"),
			"-target armv7-none-linux-androideabi",
			"-march=armv7-a",
			"-Wl,--fix-cortex-a8",
      }
   end
end

dofile('riku.genie.lua')(RIKU_BUILD_DIR, TARGET_PLATFORM)

project 'riku.unit_tests'
do
   kind 'consoleapp'

   links {
      'riku'
   }

   includedirs {
      path.join(RIKU_DIR, 'include')
   }

   files {
      path.join(RIKU_DIR, 'unit-tests/*.h'),
      path.join(RIKU_DIR, 'unit-tests/**/*.h'),
      path.join(RIKU_DIR, 'unit-tests/*.cc'),
      path.join(RIKU_DIR, 'unit-tests/**/*.cc'),
   }
end
