local RIKU_DIR = path.getabsolute('..')

function riku_project(BUILD_DIR, TARGET_PLATFORM)
   project 'riku'
   do
      kind 'staticlib'

      flags {
         'NoPCH',
         'NoRTTI',
         'NoWinRT',
         'NoExceptions',
         "NoFramePointer",
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

      defines {
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

         flags {
            "NoBufferSecurityCheck",
         }
      end

      configuration { 'debug', 'x32' }
      do
         targetdir (path.join(BUILD_DIR, TARGET_PLATFORM, 'x32/debug'))
      end

      configuration { 'debug', 'x64' }
      do
         targetdir (path.join(BUILD_DIR, TARGET_PLATFORM, 'x64/debug'))
      end

      configuration { 'release', 'x32' }
      do
         targetdir (path.join(BUILD_DIR, TARGET_PLATFORM, 'x32/release'))
      end

      configuration { 'release', 'x64' }
      do
         targetdir (path.join(BUILD_DIR, TARGET_PLATFORM, 'x32/release'))
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
         }

         buildoptions {
            '/wd4201', -- warning C4201: nonstandard extension used : nameless struct/union
            '/wd4458', -- warning C4458: declaration of '*' hides class member
            '/wd4005', -- warning C4005: macro redefinition
         }
      end
   end
end

return riku_project
