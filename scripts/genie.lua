local RIKU_DIR = path.getabsolute('..')
local RIKU_BUILD_DIR = path.join(RIKU_DIR, 'build')

newaction {
   trigger = 'clean',
   description = 'Clean all generated projects',
   execute = function ()
      io.write 'Removing build directory...'
      
      os.rmdir(RIKU_BUILD_DIR)
      
      io.write 'DONE.\n'
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
      targetdir (path.join(RIKU_BUILD_DIR, 'debug'))
   end

   configuration { 'release' }
   do
      targetdir (path.join(RIKU_BUILD_DIR, 'release'))
   end

   configuration { 'gmake' }
   do
      premake.gcc.cc = 'clang'
      premake.gcc.cxx = 'clang++'

      buildoptions {
         '-fdeclspec'
      }
   end
end

project 'riku'
do
   kind 'staticlib'

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
   
   configuration { 'vs*' }
   do
      defines {
         '_CRT_SECURE_NO_WARNINGS',
         '_USRLIB'
      }
   end
end

project 'riku.unit-tests'
do
   kind 'consoleapp'

   includedirs {
      path.join(RIKU_DIR, 'include')
   }

   files {
      path.join(RIKU_DIR, 'unit-tests/*.cc'),
      path.join(RIKU_DIR, 'unit-tests/**/*.cc'),
   }
end
