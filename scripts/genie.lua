local RIKU_DIR = path.getabsolute('..')
local RIKU_BUILD_DIR = path.join(RIKU_DIR, 'build')

function string.startwith(s, b)
   return string.sub(s, 1, string.len(b)) == b
end

local TARGET_PLATFORM = ''
if string.startwith(_ACTION, 'vs') or string.startwith(_ACTION, 'mingw') then
   TARGET_PLATFORM = 'windows'
else
   TARGET_PLATFORM = 'linux'
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
   location (RIKU_BUILD_DIR)
   
   platforms {
      'x32', 'x64', 'native'
   }
   
   configurations {
      'debug', 'release'
   }

   startproject 'riku.unit-tests'

   configuration { 'debug' }
   do
      targetdir (path.join(RIKU_BUILD_DIR, TARGET_PLATFORM, 'debug'))

      flags {
         'Symbols' 
      }

      defines {
         '_DEBUG'
      }
   end

   configuration { 'release' }
   do
      targetdir (path.join(RIKU_BUILD_DIR, TARGET_PLATFORM, 'release'))
      flags { 
         'OptimizeSpeed', 
         'No64BitChecks', 
      }

      defines {
         'NDEBUG=1'
      }
   end

   configuration { 'gmake' }
   do
      premake.gcc.cc = 'clang'
      premake.gcc.cxx = 'clang++'

      buildoptions {
         '-fdeclspec',
         '-fms-extensions',
         '-isystem'
      }

      linkoptions {
      }
   end

   configuration { 'vs*' }
   do
      buildoptions {
         "/wd4201", -- warning C4201: nonstandard extension used : nameless struct/union
      }
   end
end

project 'riku'
do
   kind 'staticlib'

   flags {
      'NoPCH',
      'NoRTTI',
      'NoWinRT',
      'NoExceptions',
      'NoEditAndContinue',
      'NoBufferSecurityCheck',

      'ExtraWarnings'
   }

   includedirs {
      path.join(RIKU_DIR, 'include')
   }

   files {
      path.join(RIKU_DIR, 'src/*.cc'),
      path.join(RIKU_DIR, 'src/**/*.cc'),
      path.join(RIKU_DIR, 'include/*.h'),
      path.join(RIKU_DIR, 'include/**/*.h'),
   }

   configuration { 'debug' }
   do
      defines {
         '_DEBUG'
      }
   end

   configuration { 'release' }
   do
      defines {
         'NDEBUG'
      }
   end

   configuration { 'gmake' }
   do
      buildoptions {
         '-std=c++11'
      }
   end
   
   configuration { 'vs*' }
   do
      defines {
         '_CRT_SECURE_NO_WARNINGS',
         --'_CRT_NO_VA_START_VALIDATION',
         '_USRLIB'
      }

      buildoptions {
      }

      linkoptions {
         '/NODEFAULTLIB'
      }
   end
end

project 'riku.unit-tests'
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
