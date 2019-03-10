local ROOT_DIR = path.getabsolute("..")

function string.startwith(s, b)
    return string.sub(s, 1, string.len(b)) == b
 end

local function crt_none()
	defines {
		"CRT_NONE=1",
	}

	buildoptions {
		--"-nostdlib",
		--"-nodefaultlibs",
		"-nostartfiles",
		"-Wa,--noexecstack",
		"-ffreestanding",
	}

	linkoptions {
		--"-nostdlib",
		--"-nodefaultlibs",
		"-nostartfiles",
		"-Wa,--noexecstack",
		"-ffreestanding",
	}

	configuration { "linux-*" }

		buildoptions {
			"-mpreferred-stack-boundary=4",
			"-mstackrealign",
		}

		linkoptions {
			"-mpreferred-stack-boundary=4",
			"-mstackrealign",
		}

	configuration {}
end

function toolchain(BUILD_DIR, LIB_DIR)
	newoption {
		trigger = "platform",
		value = "PLATFORM",
		description = "Choose platform",
		allowed = {
			{ "android-arm",     "Android - ARM"              },
			{ "android-x86",     "Android - x86"              },
			{ "wasm",            "Emscripten/wasm"            },
			{ "asmjs",           "Emscripten/asm.js"          },
			--{ "freebsd",         "FreeBSD"                    },
			{ "linux",           "Linux (Clang compiler)"     },
			{ "linux-afl",       "Linux (Clang + AFL fuzzer)" },
			{ "windows-clang",   "Windows (Clang compiler)"   },
			{ "ios-arm",         "iOS - ARM"                  },
			{ "ios-arm64",       "iOS - ARM64"                },
			{ "ios-simulator",   "iOS - Simulator"            },
			{ "ios-simulator64", "iOS - Simulator 64"         },
			{ "tvos-arm64",      "tvOS - ARM64"               },
			{ "tvos-simulator",  "tvOS - Simulator"           },
			{ "mingw-clang",     "MinGW (clang compiler)"     },
			--{ "netbsd",          "NetBSD"                     },
			{ "osx",             "OSX"                        },
			--{ "orbis",           "Orbis"                      },
			--{ "riscv",           "RISC-V"                     },
			--{ "rpi",             "RaspberryPi"                },
		},
	}

	newoption {
		trigger = "vs",
		value = "toolset",
		description = "Choose VS toolset",
		allowed = {
			{ "vs2012-clang",  "Clang 3.6"                       },
			{ "vs2013-clang",  "Clang 3.6"                       },
			{ "vs2015-clang",  "Clang 3.9"                       },
			{ "vs2017-clang",  "Clang with MS CodeGen"           },
			{ "vs2012-xp",     "Visual Studio 2012 targeting XP" },
			{ "vs2013-xp",     "Visual Studio 2013 targeting XP" },
			{ "vs2015-xp",     "Visual Studio 2015 targeting XP" },
			{ "vs2017-xp",     "Visual Studio 2017 targeting XP" },
			{ "winstore100",   "Universal Windows App 10.0"      },
			{ "durango",       "Durango"                         },
			{ "orbis",         "Orbis"                           },
		},
	}

	newoption {
		trigger = "xcode",
		value = "xcode_target",
		description = "Choose XCode target",
		allowed = {
			{ "osx", "OSX" },
			{ "ios", "iOS" },
			{ "tvos", "tvOS" },
		}
	}

	newoption {
		trigger     = "android",
		value       = "#",
		description = "Set Android platform version (default: android-14).",
	}

	newoption {
		trigger     = "ios",
		value       = "#",
		description = "Set iOS target version (default: 8.0).",
	}

	newoption {
		trigger     = "macos",
		value       = "#",
		description = "Set macOS target version (default 10.11).",
	}

	newoption {
		trigger     = "tvos",
		value       = "#",
		description = "Set tvOS target version (default: 9.0).",
	}

	newoption {
		trigger = "windows",
		value = "#",
		description = "Set the Windows target platform version (default: $WindowsSDKVersion or 8.1).",
	}

	newoption {
		trigger     = "dynamic-runtime",
		description = "Dynamically link with the runtime rather than statically",
	}

	newoption {
		trigger     = "32bit-compiler",
		description = "Use 32-bit compiler instead 64-bit.",
	}

	newoption {
		trigger     = "with-avx",
		description = "Use AVX extension.",
	}

	-- Avoid error when invoking genie --help.
	if (_ACTION == nil) then return false end

	location (path.join(BUILD_DIR, "projects", _ACTION))

	if _ACTION == "clean" then
		os.rmdir(BUILD_DIR)
		os.mkdir(BUILD_DIR)
		os.exit(1)
	end

	local android_platform = "android-24"
	if _OPTIONS["android"] then
		android_platform = "android-" .. _OPTIONS["android"]
	end

	local ios_platform = ""
	if _OPTIONS["ios"] then
		ios_platform = _OPTIONS["ios"]
	end

	local osx_platform = ""
	if _OPTIONS["osx"] then
		osx_platform = _OPTIONS["osx"]
	end

	local tvosPlatform = ""
	if _OPTIONS["tvos"] then
		tvosPlatform = _OPTIONS["tvos"]
	end

	local windowsPlatform = string.gsub(os.getenv("WindowsSDKVersion") or "8.1", "\\", "")
	if _OPTIONS["windows"] then
		windowsPlatform = _OPTIONS["windows"]
	end

	local compiler_32bit = false
	if _OPTIONS["32bit-compiler"] then
		compiler_32bit = true
	end

	flags {
		"Cpp14",
		"ExtraWarnings",
	}

	if _ACTION == "gmake" or _ACTION == "ninja" then

		if nil == _OPTIONS["platform"] then
			print("Platform must be specified for gmake or ninja build!")
			os.exit(1)
		end

		if string.startwith(_OPTIONS["platform"], "android-") then
            if not os.getenv("ANDROID_NDK_ARM")
            or not os.getenv("ANDROID_NDK_ARM64")
			or not os.getenv("ANDROID_NDK_CLANG")
			or not os.getenv("ANDROID_NDK_ROOT") then
				print("Set ANDROID_NDK_CLANG, ANDROID_NDK_ARM, ANDROID_NDK_ARM64, and ANDROID_NDK_ROOT environment variables.")
			end

			premake.gcc.cc   = "$(ANDROID_NDK_CLANG)/bin/clang"
			premake.gcc.cxx  = "$(ANDROID_NDK_CLANG)/bin/clang++"
			premake.gcc.llvm = true
            location (path.join(BUILD_DIR, "projects", _ACTION .. "-" .. _OPTIONS["platform"]))

		elseif "asmjs" == _OPTIONS["platform"] then
			if not os.getenv("EMSCRIPTEN") then
				print("Set EMSCRIPTEN environment variable.")
			end

			premake.gcc.cc   = "\"$(EMSCRIPTEN)/emcc\""
			premake.gcc.cxx  = "\"$(EMSCRIPTEN)/em++\""
			premake.gcc.ar   = "\"$(EMSCRIPTEN)/emar\""
			premake.gcc.llvm = true
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-asmjs"))

		elseif "wasm" == _OPTIONS["platform"] then
			if not os.getenv("EMSCRIPTEN") then
				print("Set EMSCRIPTEN environment variable.")
			end

			premake.gcc.cc   = "\"$(EMSCRIPTEN)/emcc\""
			premake.gcc.cxx  = "\"$(EMSCRIPTEN)/em++\""
			premake.gcc.ar   = "\"$(EMSCRIPTEN)/emar\""
			premake.gcc.llvm = true
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-wasm"))

		elseif "freebsd" == _OPTIONS["platform"] then
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-freebsd"))

		elseif "ios-arm"   == _OPTIONS["platform"]
			or "ios-arm64" == _OPTIONS["platform"] then
			premake.gcc.cc  = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang"
			premake.gcc.cxx = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++"
			premake.gcc.ar  = "ar"
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-" .. _OPTIONS["platform"]))

		elseif "ios-simulator" == _OPTIONS["platform"] then
			premake.gcc.cc  = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang"
			premake.gcc.cxx = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++"
			premake.gcc.ar  = "ar"
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-ios-simulator"))

		elseif "ios-simulator64" == _OPTIONS["platform"] then
			premake.gcc.cc  = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang"
			premake.gcc.cxx = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++"
			premake.gcc.ar  = "ar"
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-ios-simulator64"))

		elseif "tvos-arm64" == _OPTIONS["platform"] then
			premake.gcc.cc  = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang"
			premake.gcc.cxx = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++"
			premake.gcc.ar  = "ar"
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-tvos-arm64"))

		elseif "tvos-simulator" == _OPTIONS["platform"] then
			premake.gcc.cc  = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang"
			premake.gcc.cxx = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++"
			premake.gcc.ar  = "ar"
            location (path.join(BUILD_DIR, "projects", _ACTION .. "-tvos-simulator"))
            
		elseif "linux" == _OPTIONS["platform"] then
			premake.gcc.cc  = "clang"
			premake.gcc.cxx = "clang++"
			premake.gcc.ar  = "ar"
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-linux"))

		elseif "linux-afl" == _OPTIONS["platform"] then
			premake.gcc.cc  = "afl-clang"
			premake.gcc.cxx = "afl-clang++"
			premake.gcc.ar  = "ar"
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-linux"))

        --[[
		elseif "linux-steamlink" == _OPTIONS["platform"] then
			if not os.getenv("MARVELL_SDK_PATH") then
				print("Set MARVELL_SDK_PATH environment variable.")
			end

			premake.gcc.cc  = "$(MARVELL_SDK_PATH)/toolchain/bin/armv7a-cros-linux-gnueabi-gcc"
			premake.gcc.cxx = "$(MARVELL_SDK_PATH)/toolchain/bin/armv7a-cros-linux-gnueabi-g++"
			premake.gcc.ar  = "$(MARVELL_SDK_PATH)/toolchain/bin/armv7a-cros-linux-gnueabi-ar"
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-linux-steamlink"))]]

		elseif "mingw-clang" == _OPTIONS["platform"] then
			premake.gcc.cc   = "$(CLANG)/bin/clang"
			premake.gcc.cxx  = "$(CLANG)/bin/clang++"
			premake.gcc.ar   = "$(MINGW)/bin/ar"
--			premake.gcc.ar   = "$(CLANG)/bin/llvm-ar"
--			premake.gcc.llvm = true
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-mingw"))

		elseif "windows-clang" == _OPTIONS["platform"] then
			premake.gcc.cc   = "clang"
			premake.gcc.cxx  = "clang++"
			premake.gcc.ar   = "ar"
--			premake.gcc.ar   = "$(CLANG)/bin/llvm-ar"
--			premake.gcc.llvm = true
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-windows-clang"))

        --[[
		elseif "netbsd" == _OPTIONS["platform"] then
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-netbsd"))]]

		elseif "osx" == _OPTIONS["platform"] then

			if os.is("linux") then
				if not os.getenv("OSXCROSS") then
					print("Set OSXCROSS environment variable.")
				end

				local osx_toolchain = "x86_64-apple-darwin15-"
				premake.gcc.cc  = "$(OSXCROSS)/target/bin/" .. osx_toolchain .. "clang"
				premake.gcc.cxx = "$(OSXCROSS)/target/bin/" .. osx_toolchain .. "clang++"
				premake.gcc.ar  = "$(OSXCROSS)/target/bin/" .. osx_toolchain .. "ar"
			end
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-osx"))

        --[[
		elseif "orbis" == _OPTIONS["platform"] then

			if not os.getenv("SCE_ORBIS_SDK_DIR") then
				print("Set SCE_ORBIS_SDK_DIR environment variable.")
			end

			orbisToolchain = "$(SCE_ORBIS_SDK_DIR)/host_tools/bin/orbis-"

			premake.gcc.cc  = orbisToolchain .. "clang"
			premake.gcc.cxx = orbisToolchain .. "clang++"
			premake.gcc.ar  = orbisToolchain .. "ar"
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-orbis"))

		elseif "rpi" == _OPTIONS["platform"] then
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-rpi"))

		elseif "riscv" == _OPTIONS["platform"] then
			premake.gcc.cc  = "$(FREEDOM_E_SDK)/work/build/riscv-gnu-toolchain/riscv64-unknown-elf/prefix/bin/riscv64-unknown-elf-gcc"
			premake.gcc.cxx = "$(FREEDOM_E_SDK)/work/build/riscv-gnu-toolchain/riscv64-unknown-elf/prefix/bin/riscv64-unknown-elf-g++"
			premake.gcc.ar  = "$(FREEDOM_E_SDK)/work/build/riscv-gnu-toolchain/riscv64-unknown-elf/prefix/bin/riscv64-unknown-elf-ar"
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-riscv"))]]

		end
	elseif _ACTION == "vs2012"
		or _ACTION == "vs2013"
		or _ACTION == "vs2015"
		or _ACTION == "vs2017"
		then

		local action = premake.action.current()
		action.vstudio.windowsTargetPlatformVersion    = windowsPlatform
		action.vstudio.windowsTargetPlatformMinVersion = windowsPlatform

		if (_ACTION .. "-clang") == _OPTIONS["vs"] then
			if "vs2017-clang" == _OPTIONS["vs"] then
				premake.vstudio.toolset = "v141_clang_c2"
			elseif "vs2015-clang" == _OPTIONS["vs"] then
				premake.vstudio.toolset = "LLVM-vs2014"
			else
				premake.vstudio.toolset = ("LLVM-" .. _ACTION)
			end
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-clang"))

		elseif "winstore100" == _OPTIONS["vs"] then
			premake.vstudio.toolset = "v141"
			premake.vstudio.storeapp = "10.0"

			platforms { "ARM" }
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-winstore100"))

		elseif "durango" == _OPTIONS["vs"] then
			if not os.getenv("DurangoXDK") then
				print("DurangoXDK not found.")
			end

			premake.vstudio.toolset = "v140"
			premake.vstudio.storeapp = "durango"
			platforms { "Durango" }
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-durango"))
		elseif "orbis" == _OPTIONS["vs"] then

			if not os.getenv("SCE_ORBIS_SDK_DIR") then
				print("Set SCE_ORBIS_SDK_DIR environment variable.")
			end

			platforms { "Orbis" }
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-orbis"))

		elseif ("vs2012-xp") == _OPTIONS["vs"] then
			premake.vstudio.toolset = ("v110_xp")
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-xp"))

		elseif "vs2013-xp" == _OPTIONS["vs"] then
			premake.vstudio.toolset = ("v120_xp")
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-xp"))

		elseif "vs2015-xp" == _OPTIONS["vs"] then
			premake.vstudio.toolset = ("v140_xp")
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-xp"))

		elseif "vs2015-xp" == _OPTIONS["vs"] then
			premake.vstudio.toolset = ("v141_xp")
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-xp"))

		end

	elseif _ACTION == "xcode4"
		or _ACTION == "xcode8"
		or _ACTION == "xcode9" then
		local action = premake.action.current()
		local str_or = function(str, def)
			return #str > 0 and str or def
		end

		if "osx" == _OPTIONS["xcode"] then
			action.xcode.macOSTargetPlatformVersion = str_or(osx_platform, "10.11")
			premake.xcode.toolset = "macosx"
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-osx"))

		elseif "ios" == _OPTIONS["xcode"] then
			action.xcode.iOSTargetPlatformVersion = str_or(ios_platform, "8.0")
			premake.xcode.toolset = "iphoneos"
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-ios"))

		elseif "tvos" == _OPTIONS["xcode"] then
			action.xcode.tvOSTargetPlatformVersion = str_or(tvosPlatform, "9.0")
			premake.xcode.toolset = "appletvos"
			location (path.join(BUILD_DIR, "projects", _ACTION .. "-tvos"))
		end
	end

	if not _OPTIONS["dynamic-runtime"] then
		flags { "StaticRuntime" }
	end

	if _OPTIONS["with-avx"] then
		flags { "EnableAVX" }
	end

	if _OPTIONS["with-crtnone"] then
		crt_none()
	end

	flags {
		"NoPCH",
		"NativeWChar",
		"NoRTTI",
		"NoExceptions",
		"NoEditAndContinue",
		"NoFramePointer",
		"Symbols",
	}

	defines {
		"__STDC_LIMIT_MACROS",
		"__STDC_FORMAT_MACROS",
		"__STDC_CONSTANT_MACROS",
	}

	configuration { "debug" }
		targetsuffix "debug"
		defines {
			"_DEBUG",
		}

	configuration { "release" }
		flags {
			"NoBufferSecurityCheck",
			"OptimizeSpeed",
		}
		defines {
			"NDEBUG",
		}
		targetsuffix "release"

	configuration { "qbs" }
		flags {
			"ExtraWarnings",
		}

	configuration { "vs*", "x32" }
		flags {
			"EnableSSE2",
		}

	configuration { "vs*", "not orbis", "not NX32", "not NX64" }
		--includedirs { path.join(ROOT_DIR, "include/compat/msvc") }
		defines {
			"WIN32",
			"_WIN32",
			"_HAS_EXCEPTIONS=0",
			"_HAS_ITERATOR_DEBUGGING=0",
			"_ITERATOR_DEBUG_LEVEL=0",
			"_SCL_SECURE=0",
			"_SECURE_SCL=0",
			"_SCL_SECURE_NO_WARNINGS",
			"_CRT_SECURE_NO_WARNINGS",
			"_CRT_SECURE_NO_DEPRECATE",
		}
		buildoptions {
			"/wd4201", -- warning C4201: nonstandard extension used: nameless struct/union
			"/wd4324", -- warning C4324: '': structure was padded due to alignment specifier
			"/Ob2",    -- The Inline Function Expansion
		}
		linkoptions {
			"/ignore:4221", -- LNK4221: This object file does not define any previously undefined public symbols, so it will not be used by any link operation that consumes this library
		}

	configuration { "vs2008" }
		--includedirs { path.join(ROOT_DIR, "include/compat/msvc/pre1600") }

	configuration { "x32", "vs*" }
		targetdir (path.join(BUILD_DIR, "windows_x32_" .. _ACTION, "bin"))
		objdir (path.join(BUILD_DIR, "windows_x32_" .. _ACTION, "obj"))
		libdirs {
			path.join(LIB_DIR, "lib/windows_x32_" .. _ACTION),
		}

	configuration { "x64", "vs*" }
		defines { "_WIN64" }
		targetdir (path.join(BUILD_DIR, "windows_x64_" .. _ACTION, "bin"))
		objdir (path.join(BUILD_DIR, "windows_x64_" .. _ACTION, "obj"))
		libdirs {
			path.join(LIB_DIR, "lib/windows_x64_" .. _ACTION),
		}

	configuration { "x32", "vs2017" }
		targetdir (path.join(BUILD_DIR, "windows_x32_" .. _ACTION, "bin"))
		objdir (path.join(BUILD_DIR, "windows_x32_" .. _ACTION, "obj"))
		libdirs {
			path.join(LIB_DIR, "lib/windows_x32_" .. _ACTION),
		}

	configuration { "x64", "vs2017" }
		defines { "_WIN64" }
		targetdir (path.join(BUILD_DIR, "windows_x64_" .. _ACTION, "bin"))
		objdir (path.join(BUILD_DIR, "windows_x64_" .. _ACTION, "obj"))
		libdirs {
			path.join(LIB_DIR, "lib/windows_x64_" .. _ACTION),
		}

	configuration { "ARM", "vs*" }
		targetdir (path.join(BUILD_DIR, "arm_" .. _ACTION, "bin"))
		objdir (path.join(BUILD_DIR, "arm_" .. _ACTION, "obj"))

	configuration { "vs*-clang" }
		buildoptions {
			"-Qunused-arguments",
		}

	configuration { "x32", "vs*-clang" }
		targetdir (path.join(BUILD_DIR, "windows_x32_" .. _ACTION .. "-clang/bin"))
		objdir (path.join(BUILD_DIR, "windows_x32_" .. _ACTION .. "-clang/obj"))

	configuration { "x64", "vs*-clang" }
		targetdir (path.join(BUILD_DIR, "windows_x64_" .. _ACTION .. "-clang/bin"))
		objdir (path.join(BUILD_DIR, "windows_x64_" .. _ACTION .. "-clang/obj"))

	configuration { "winstore*" }
		removeflags {
			"StaticRuntime",
			"NoBufferSecurityCheck",
		}
		buildoptions {
			"/wd4530", -- vccorlib.h(1345): warning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc
		}
		linkoptions {
			"/ignore:4264" -- LNK4264: archiving object file compiled with /ZW into a static library; note that when authoring Windows Runtime types it is not recommended to link with a static library that contains Windows Runtime metadata
		}

	configuration { "*-gcc* or osx" }
		buildoptions {
			"-Wshadow",
		}

	configuration { "mingw-*" }
		defines { "WIN32" }
		includedirs { path.join(ROOT_DIR, "include/compat/mingw") }
		defines {
			"MINGW_HAS_SECURE_API=1",
		}
		buildoptions {
			"-Wunused-value",
			"-fdata-sections",
			"-ffunction-sections",
			"-msse2",
			"-Wunused-value",
			"-Wundef",
		}
		linkoptions {
			"-Wl,--gc-sections",
			"-static",
			"-static-libgcc",
			"-static-libstdc++",
		}

    --[[
	configuration { "x32", "mingw-gcc" }
		targetdir (path.join(BUILD_DIR, "win32_mingw-gcc/bin"))
		objdir (path.join(BUILD_DIR, "win32_mingw-gcc/obj"))
		libdirs {
			path.join(LIB_DIR, "lib/win32_mingw-gcc"),
		}
		buildoptions {
			"-m32",
			"-mstackrealign",
		}

	configuration { "x64", "mingw-gcc" }
		targetdir (path.join(BUILD_DIR, "win64_mingw-gcc/bin"))
		objdir (path.join(BUILD_DIR, "win64_mingw-gcc/obj"))
		libdirs {
			path.join(LIB_DIR, "lib/win64_mingw-gcc"),
		}
		buildoptions { "-m64" }]]

	configuration { "mingw-clang" }
		buildoptions {
            "-fdeclspec",
            "-fms-extensions",
			"-isystem$(MINGW)/lib/gcc/x86_64-w64-mingw32/4.8.1/include/c++",
			"-isystem$(MINGW)/lib/gcc/x86_64-w64-mingw32/4.8.1/include/c++/x86_64-w64-mingw32",
			"-isystem$(MINGW)/x86_64-w64-mingw32/include",
		}
		linkoptions {
			"-Qunused-arguments",
			"-Wno-error=unused-command-line-argument-hard-error-in-future",
		}

	configuration { "x32", "mingw-clang" }
		targetdir (path.join(BUILD_DIR, "win32_mingw-clang/bin"))
		objdir (path.join(BUILD_DIR, "win32_mingw-clang/obj"))
		libdirs {
			path.join(LIB_DIR, "lib/win32_mingw-clang"),
		}
		buildoptions { "-m32" }

	configuration { "x64", "mingw-clang" }
		targetdir (path.join(BUILD_DIR, "win64_mingw-clang/bin"))
		objdir (path.join(BUILD_DIR, "win64_mingw-clang/obj"))
		libdirs {
			path.join(LIB_DIR, "lib/win64_mingw-clang"),
		}
		buildoptions { "-m64" }

    --[[
	configuration { "linux-gcc-6" }
		buildoptions {
--			"-fno-omit-frame-pointer",
--			"-fsanitize=address",
--			"-fsanitize=undefined",
--			"-fsanitize=float-divide-by-zero",
--			"-fsanitize=float-cast-overflow",
		}
		links {
--			"asan",
--			"ubsan",
		}

	configuration { "linux-gcc" }
		buildoptions {
			"-mfpmath=sse",
        }
    ]]

	configuration { "linux*" }
		buildoptions {
            "-fdeclspec",
            "-fms-extensions",
			"-msse2",
--			"-Wdouble-promotion",
--			"-Wduplicated-branches",
--			"-Wduplicated-cond",
--			"-Wjump-misses-init",
			"-Wshadow",
--			"-Wnull-dereference",
			"-Wunused-value",
			"-Wundef",
--			"-Wuseless-cast",
		}
		links {
			"rt",
			"dl",
		}
		linkoptions {
			"-Wl,--gc-sections",
			"-Wl,--as-needed",
		}

    --[[
	configuration { "linux-gcc*" }
		buildoptions {
			"-Wlogical-op",
		}

	configuration { "linux-gcc*", "x32" }
		targetdir (path.join(BUILD_DIR, "linux32_gcc/bin"))
		objdir (path.join(BUILD_DIR, "linux32_gcc/obj"))
		libdirs { path.join(LIB_DIR, "lib/linux32_gcc") }
		buildoptions {
			"-m32",
		}

	configuration { "linux-gcc*", "x64" }
		targetdir (path.join(BUILD_DIR, "linux64_gcc/bin"))
		objdir (path.join(BUILD_DIR, "linux64_gcc/obj"))
		libdirs { path.join(LIB_DIR, "lib/linux64_gcc") }
		buildoptions {
			"-m64",
        }
    ]]

	configuration { "linux*", "x32" }
		targetdir (path.join(BUILD_DIR, "linux_x32/bin"))
		objdir (path.join(BUILD_DIR, "linux_x32/obj"))
		libdirs { path.join(LIB_DIR, "lib/linux_x32") }
		buildoptions {
			"-m32",
		}

	configuration { "linux*", "x64" }
		targetdir (path.join(BUILD_DIR, "linux_x64/bin"))
		objdir (path.join(BUILD_DIR, "linux_x64/obj"))
		libdirs { path.join(LIB_DIR, "lib/linux_x64") }
		buildoptions {
			"-m64",
		}

    --[[
	configuration { "linux-mips-gcc" }
		targetdir (path.join(BUILD_DIR, "linux32_mips_gcc/bin"))
		objdir (path.join(BUILD_DIR, "linux32_mips_gcc/obj"))
		libdirs { path.join(LIB_DIR, "lib/linux32_mips_gcc") }
		buildoptions {
			"-Wunused-value",
			"-Wundef",
		}
		links {
			"rt",
			"dl",
		}
		linkoptions {
			"-Wl,--gc-sections",
		}

	configuration { "linux-arm-gcc" }
		targetdir (path.join(BUILD_DIR, "linux32_arm_gcc/bin"))
		objdir (path.join(BUILD_DIR, "linux32_arm_gcc/obj"))
		libdirs { path.join(LIB_DIR, "lib/linux32_arm_gcc") }
		buildoptions {
			"-Wunused-value",
			"-Wundef",
		}
		links {
			"rt",
			"dl",
		}
		linkoptions {
			"-Wl,--gc-sections",
        }
    ]]

	configuration { "android-*" }
		targetprefix ("lib")
		flags {
			"NoImportLib",
		}
		includedirs {
			"$(ANDROID_NDK_ROOT)/sources/cxx-stl/llvm-libc++/include",
			"${ANDROID_NDK_ROOT}/sysroot/usr/include",
			--"$(ANDROID_NDK_ROOT)/sources/android/native_app_glue",
		}
		linkoptions {
			--"-nostdlib",
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
            "-fdeclspec",
            "-fms-extensions",
			"-fPIC",
			"-no-canonical-prefixes",
			"-Wa,--noexecstack",
			"-fstack-protector-strong",
			"-ffunction-sections",
			"-Wunused-value",
			"-Wundef",
		}
		linkoptions {
			"-no-canonical-prefixes",
			"-Wl,--no-undefined",
			"-Wl,-z,noexecstack",
			"-Wl,-z,relro",
			"-Wl,-z,now",
		}

    --[[
	configuration { "linux-steamlink" }
		targetdir (path.join(BUILD_DIR, "steamlink/bin"))
		objdir (path.join(BUILD_DIR, "steamlink/obj"))
		libdirs { path.join(LIB_DIR, "lib/steamlink") }
		includedirs { path.join(ROOT_DIR, "include/compat/linux") }
		defines {
			"__STEAMLINK__=1", -- There is no special prefedined compiler symbol to detect SteamLink, faking it.
		}
		buildoptions {
			"-Wfatal-errors",
			"-Wunused-value",
			"-Wundef",
			"-pthread",
			"-marm",
			"-mfloat-abi=hard",
			"--sysroot=$(MARVELL_SDK_PATH)/rootfs",
		}
		linkoptions {
			"-static-libgcc",
			"-static-libstdc++",
			"--sysroot=$(MARVELL_SDK_PATH)/rootfs",
        }
    ]]

    configuration { "android-arm", "x32" }
    do
		targetdir (path.join(BUILD_DIR, "android-arm/bin"))
		objdir (path.join(BUILD_DIR, "android-arm/obj"))
		libdirs {
			"$(ANDROID_NDK_ROOT)/sources/cxx-stl/llvm-libc++/libs/armeabi-v7a",
		}
		includedirs {
			"$(ANDROID_NDK_ROOT)/sysroot/usr/include/arm-linux-androideabi",
		}
		buildoptions {
			"-gcc-toolchain $(ANDROID_NDK_ARM)",
			"--sysroot=" .. path.join("$(ANDROID_NDK_ROOT)/platforms", android_platform, "arch-arm"),
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
			"--sysroot=" .. path.join("$(ANDROID_NDK_ROOT)/platforms", android_platform, "arch-arm"),
			path.join("$(ANDROID_NDK_ROOT)/platforms", android_platform, "arch-arm/usr/lib/crtbegin_so.o"),
			path.join("$(ANDROID_NDK_ROOT)/platforms", android_platform, "arch-arm/usr/lib/crtend_so.o"),
			"-target armv7-none-linux-androideabi",
			"-march=armv7-a",
			"-Wl,--fix-cortex-a8",
        }

        premake.gcc.ar = "$(ANDROID_NDK_ARM)/bin/arm-linux-androideabi-ar"
        premake.gcc.ld = "$(ANDROID_NDK_ARM)/bin/arm-linux-androideabi-ld"
    end

    configuration { "android-arm", "x64" }
    do
        targetdir (path.join(BUILD_DIR, "android-arm64/bin"))
        objdir (path.join(BUILD_DIR, "android-arm64/obj"))
        libdirs {
            "$(ANDROID_NDK_ROOT)/sources/cxx-stl/llvm-libc++/libs/arm64-v8a",
        }
        includedirs {
            "$(ANDROID_NDK_ROOT)/sysroot/usr/include/aarch64-linux-android",
        }
        buildoptions {
            "-gcc-toolchain $(ANDROID_NDK_ARM)",
            "--sysroot=" .. path.join("$(ANDROID_NDK_ROOT)/platforms", android_platform, "arch-arm64"),
            "-target arm64-none-linux-android",
            "-march=armv8-a",
            "-Wunused-value",
            "-Wundef",
        }
        linkoptions {
            "-gcc-toolchain $(ANDROID_NDK_ARM)",
            "--sysroot=" .. path.join("$(ANDROID_NDK_ROOT)/platforms", android_platform, "arch-arm64"),
            path.join("$(ANDROID_NDK_ROOT)/platforms", android_platform, "arch-arm64/usr/lib/crtbegin_so.o"),
            path.join("$(ANDROID_NDK_ROOT)/platforms", android_platform, "arch-arm64/usr/lib/crtend_so.o"),
            "-target arm64-none-linux-android",
            "-march=armv8-a",
            "-Wl,--fix-cortex-a8",
        }
        
        premake.gcc.ar = "$(ANDROID_NDK_ARM64)/bin/aarch64-linux-android-ar"
        premake.gcc.ld = "$(ANDROID_NDK_ARM64)/bin/aarch64-linux-android-ld"
    end

	configuration { "android-x86" }
		targetdir (path.join(BUILD_DIR, "android-x86/bin"))
		objdir (path.join(BUILD_DIR, "android-x86/obj"))
		libdirs {
			"$(ANDROID_NDK_ROOT)/sources/cxx-stl/llvm-libc++/libs/x86",
		}
		includedirs {
			"$(ANDROID_NDK_ROOT)/sysroot/usr/include/x86_64-linux-android",
		}
		buildoptions {
			"-gcc-toolchain $(ANDROID_NDK_X86)",
			"--sysroot=" .. path.join("$(ANDROID_NDK_ROOT)/platforms", android_platform, "arch-x86"),
			"-target i686-none-linux-android",
			"-march=i686",
			"-mtune=atom",
			"-mstackrealign",
			"-msse3",
			"-mfpmath=sse",
			"-Wunused-value",
			"-Wundef",
		}
		linkoptions {
			"-gcc-toolchain $(ANDROID_NDK_X86)",
			"--sysroot=" .. path.join("$(ANDROID_NDK_ROOT)/platforms", android_platform, "arch-x86"),
			path.join("$(ANDROID_NDK_ROOT)/platforms", android_platform, "arch-x86/usr/lib/crtbegin_so.o"),
			path.join("$(ANDROID_NDK_ROOT)/platforms", android_platform, "arch-x86/usr/lib/crtend_so.o"),
			"-target i686-none-linux-android",
		}

	configuration { "asmjs" }
		targetdir (path.join(BUILD_DIR, "asmjs/bin"))
		objdir (path.join(BUILD_DIR, "asmjs/obj"))
		libdirs { path.join(LIB_DIR, "lib/asmjs") }
		buildoptions {
            "-s WASM=0", -- no Wasm
            "-fdeclspec",
            "-fms-extensions",
			--"-I\"$(EMSCRIPTEN)/system/include\"",
			--"-I\"$(EMSCRIPTEN)/system/include/libcxx\"",
			--"-I\"$(EMSCRIPTEN)/system/include/libc\"",
			"-Wunused-value",
			"-Wundef",
		}

    configuration { "wasm" }
        targetdir (path.join(BUILD_DIR, "wasm/bin"))
        objdir (path.join(BUILD_DIR, "wasm/obj"))
        libdirs { path.join(LIB_DIR, "lib/wasm") }
        buildoptions {
            "-s WASM=0", -- no Wasm
            "-fdeclspec",
            "-fms-extensions",
            --"-I\"$(EMSCRIPTEN)/system/include\"",
            --"-I\"$(EMSCRIPTEN)/system/include/libcxx\"",
            --"-I\"$(EMSCRIPTEN)/system/include/libc\"",
            "-Wunused-value",
            "-Wundef",
        }

    --[[
	configuration { "freebsd" }
		targetdir (path.join(BUILD_DIR, "freebsd/bin"))
		objdir (path.join(BUILD_DIR, "freebsd/obj"))
		libdirs { path.join(LIB_DIR, "lib/freebsd") }
		includedirs {
			path.join(ROOT_DIR, "include/compat/freebsd"),
        }
    ]]

	configuration { "xbox360" }
		targetdir (path.join(BUILD_DIR, "xbox360/bin"))
		objdir (path.join(BUILD_DIR, "xbox360/obj"))
		includedirs { path.join(ROOT_DIR, "include/compat/msvc") }
		libdirs { path.join(LIB_DIR, "lib/xbox360") }
		defines {
			"NOMINMAX",
		}

	configuration { "durango" }
		targetdir (path.join(BUILD_DIR, "durango/bin"))
		objdir (path.join(BUILD_DIR, "durango/obj"))
		includedirs { path.join(ROOT_DIR, "include/compat/msvc") }
		libdirs { path.join(LIB_DIR, "lib/durango") }
		removeflags { "StaticRuntime" }
		defines {
			"NOMINMAX",
		}

	configuration { "netbsd" }
		targetdir (path.join(BUILD_DIR, "netbsd/bin"))
		objdir (path.join(BUILD_DIR, "netbsd/obj"))
		libdirs { path.join(LIB_DIR, "lib/netbsd") }
		includedirs {
			path.join(ROOT_DIR, "include/compat/freebsd"),
		}

	configuration { "osx", "x32" }
		targetdir (path.join(BUILD_DIR, "osx32_clang/bin"))
		objdir (path.join(BUILD_DIR, "osx32_clang/obj"))
		--libdirs { path.join(LIB_DIR, "lib/osx32_clang") }
		buildoptions {
			"-m32",
		}

	configuration { "osx", "x64" }
		targetdir (path.join(BUILD_DIR, "osx64_clang/bin"))
		objdir (path.join(BUILD_DIR, "osx64_clang/obj"))
		--libdirs { path.join(LIB_DIR, "lib/osx64_clang") }
		buildoptions {
			"-m64",
		}

	configuration { "osx", "Universal" }
		targetdir (path.join(BUILD_DIR, "osx_universal/bin"))
		objdir (path.join(BUILD_DIR, "osx_universal/bin"))

	configuration { "osx" }
		buildoptions {
            "-fdeclspec",
            "-fms-extensions",
			"-Wfatal-errors",
			"-msse2",
			"-Wunused-value",
			"-Wundef",
		}
		includedirs { path.join(ROOT_DIR, "include/compat/osx") }

	configuration { "ios*" }
		linkoptions {
			"-lc++",
		}
		buildoptions {
            "-fdeclspec",
            "-fms-extensions",
			"-Wfatal-errors",
			"-Wunused-value",
			"-Wundef",
		}
		includedirs { path.join(ROOT_DIR, "include/compat/ios") }

	configuration { "xcode*", "ios*" }
		targetdir (path.join(BUILD_DIR, "ios-arm/bin"))
        objdir (path.join(BUILD_DIR, "ios-arm/obj"))

	configuration { "ios-arm" }
		targetdir (path.join(BUILD_DIR, "ios-arm/bin"))
		objdir (path.join(BUILD_DIR, "ios-arm/obj"))
		libdirs { path.join(LIB_DIR, "lib/ios-arm") }
		linkoptions {
			"-arch armv7",
		}
		buildoptions {
			"-arch armv7",
		}

	configuration { "ios-arm64" }
		targetdir (path.join(BUILD_DIR, "ios-arm64/bin"))
		objdir (path.join(BUILD_DIR, "ios-arm64/obj"))
		libdirs { path.join(LIB_DIR, "lib/ios-arm64") }
		linkoptions {
			"-arch arm64",
		}
		buildoptions {
			"-arch arm64",
		}

	configuration { "ios-arm*" }
		linkoptions {
			"-miphoneos-version-min=7.0",
			"--sysroot=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS" ..ios_platform .. ".sdk",
			"-L/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS" ..ios_platform .. ".sdk/usr/lib/system",
			"-F/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS" ..ios_platform .. ".sdk/System/Library/Frameworks",
			"-F/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS" ..ios_platform .. ".sdk/System/Library/PrivateFrameworks",
		}
		buildoptions {
			"-miphoneos-version-min=7.0",
			"--sysroot=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS" ..ios_platform .. ".sdk",
			"-fembed-bitcode",
		}

	configuration { "ios-simulator" }
		targetdir (path.join(BUILD_DIR, "ios-simulator/bin"))
		objdir (path.join(BUILD_DIR, "ios-simulator/obj"))
		libdirs { path.join(LIB_DIR, "lib/ios-simulator") }
		linkoptions {
			"-mios-simulator-version-min=7.0",
			"-arch i386",
			"--sysroot=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator" ..ios_platform .. ".sdk",
			"-L/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator" ..ios_platform .. ".sdk/usr/lib/system",
			"-F/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator" ..ios_platform .. ".sdk/System/Library/Frameworks",
			"-F/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator" ..ios_platform .. ".sdk/System/Library/PrivateFrameworks",
		}
		buildoptions {
			"-mios-simulator-version-min=7.0",
			"-arch i386",
			"--sysroot=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator" ..ios_platform .. ".sdk",
		}

	configuration { "ios-simulator64" }
		targetdir (path.join(BUILD_DIR, "ios-simulator64/bin"))
		objdir (path.join(BUILD_DIR, "ios-simulator64/obj"))
		libdirs { path.join(LIB_DIR, "lib/ios-simulator64") }
		linkoptions {
			"-mios-simulator-version-min=7.0",
			"-arch x86_64",
			"--sysroot=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator" ..ios_platform .. ".sdk",
			"-L/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator" ..ios_platform .. ".sdk/usr/lib/system",
			"-F/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator" ..ios_platform .. ".sdk/System/Library/Frameworks",
			"-F/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator" ..ios_platform .. ".sdk/System/Library/PrivateFrameworks",
		}
		buildoptions {
			"-mios-simulator-version-min=7.0",
			"-arch x86_64",
			"--sysroot=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator" ..ios_platform .. ".sdk",
		}

	configuration { "tvos*" }
		linkoptions {
			"-lc++",
		}
		buildoptions {
            "-fdeclspec",
            "-fms-extensions",
			"-Wfatal-errors",
			"-Wunused-value",
			"-Wundef",
		}
		includedirs { path.join(ROOT_DIR, "include/compat/ios") }

	configuration { "xcode*", "tvos*" }
		targetdir (path.join(BUILD_DIR, "tvos-arm64/bin"))
		objdir (path.join(BUILD_DIR, "tvos-arm64/obj"))

	configuration { "tvos-arm64" }
		targetdir (path.join(BUILD_DIR, "tvos-arm64/bin"))
		objdir (path.join(BUILD_DIR, "tvos-arm64/obj"))
		libdirs { path.join(LIB_DIR, "lib/tvos-arm64") }
		linkoptions {
			"-mtvos-version-min=9.0",
			"-arch arm64",
			"--sysroot=/Applications/Xcode.app/Contents/Developer/Platforms/AppleTVOS.platform/Developer/SDKs/AppleTVOS" ..tvosPlatform .. ".sdk",
			"-L/Applications/Xcode.app/Contents/Developer/Platforms/AppleTVOS.platform/Developer/SDKs/AppleTVOS" ..tvosPlatform .. ".sdk/usr/lib/system",
			"-F/Applications/Xcode.app/Contents/Developer/Platforms/AppleTVOS.platform/Developer/SDKs/AppleTVOS" ..tvosPlatform .. ".sdk/System/Library/Frameworks",
			"-F/Applications/Xcode.app/Contents/Developer/Platforms/AppleTVOS.platform/Developer/SDKs/AppleTVOS" ..tvosPlatform .. ".sdk/System/Library/PrivateFrameworks",
		}
		buildoptions {
			"-mtvos-version-min=9.0",
			"-arch arm64",
			"--sysroot=/Applications/Xcode.app/Contents/Developer/Platforms/AppleTVOS.platform/Developer/SDKs/AppleTVOS" ..tvosPlatform .. ".sdk",
		}

	configuration { "tvos-simulator" }
		targetdir (path.join(BUILD_DIR, "tvos-simulator/bin"))
		objdir (path.join(BUILD_DIR, "tvos-simulator/obj"))
		libdirs { path.join(LIB_DIR, "lib/tvos-simulator") }
		linkoptions {
			"-mtvos-simulator-version-min=9.0",
			"-arch i386",
			"--sysroot=/Applications/Xcode.app/Contents/Developer/Platforms/AppleTVSimulator.platform/Developer/SDKs/AppleTVSimulator" ..tvosPlatform .. ".sdk",
			"-L/Applications/Xcode.app/Contents/Developer/Platforms/AppleTVSimulator.platform/Developer/SDKs/AppleTVSimulator" ..tvosPlatform .. ".sdk/usr/lib/system",
			"-F/Applications/Xcode.app/Contents/Developer/Platforms/AppleTVSimulator.platform/Developer/SDKs/AppleTVSimulator" ..tvosPlatform .. ".sdk/System/Library/Frameworks",
			"-F/Applications/Xcode.app/Contents/Developer/Platforms/AppleTVSimulator.platform/Developer/SDKs/AppleTVSimulator" ..tvosPlatform .. ".sdk/System/Library/PrivateFrameworks",
		}
		buildoptions {
			"-mtvos-simulator-version-min=9.0",
			"-arch i386",
			"--sysroot=/Applications/Xcode.app/Contents/Developer/Platforms/AppleTVSimulator.platform/Developer/SDKs/AppleTVSimulator" ..tvosPlatform .. ".sdk",
		}

    --[[
	configuration { "orbis" }
		targetdir (path.join(BUILD_DIR, "orbis/bin"))
		objdir (path.join(BUILD_DIR, "orbis/obj"))
		libdirs { path.join(LIB_DIR, "lib/orbis") }
		includedirs {
			path.join(ROOT_DIR, "include/compat/freebsd"),
			"$(SCE_ORBIS_SDK_DIR)/target/include",
			"$(SCE_ORBIS_SDK_DIR)/target/include_common",
		}

	configuration { "rpi" }
		targetdir (path.join(BUILD_DIR, "rpi/bin"))
		objdir (path.join(BUILD_DIR, "rpi/obj"))
		libdirs {
			path.join(LIB_DIR, "lib/rpi"),
			"/opt/vc/lib",
		}
		defines {
			"__VCCOREVER__=0x04000000", -- There is no special prefedined compiler symbol to detect RaspberryPi, faking it.
			"__STDC_VERSION__=199901L",
		}
		buildoptions {
			"-Wunused-value",
			"-Wundef",
		}
		includedirs {
			"/opt/vc/include",
			"/opt/vc/include/interface/vcos/pthreads",
			"/opt/vc/include/interface/vmcs_host/linux",
		}
		links {
			"rt",
			"dl",
		}
		linkoptions {
			"-Wl,--gc-sections",
		}

	configuration { "riscv" }
		targetdir (path.join(BUILD_DIR, "riscv/bin"))
		objdir (path.join(BUILD_DIR, "riscv/obj"))
		defines {
			"__BSD_VISIBLE",
			"__MISC_VISIBLE",
		}
		includedirs {
			"$(FREEDOM_E_SDK)/work/build/riscv-gnu-toolchain/riscv64-unknown-elf/prefix/riscv64-unknown-elf/include",
			path.join(ROOT_DIR, "include/compat/riscv"),
		}
		buildoptions {
			"-Wunused-value",
			"-Wundef",
			"--sysroot=$(FREEDOM_E_SDK)/work/build/riscv-gnu-toolchain/riscv64-unknown-elf/prefix/riscv64-unknown-elf",
        }
    ]]

	configuration {} -- reset configuration

	return true
end

function strip()
	configuration { "android-arm", "release" }
		postbuildcommands {
			"$(SILENT) echo Stripping symbols.",
			"$(SILENT) $(ANDROID_NDK_ARM)/bin/arm-linux-androideabi-strip -s \"$(TARGET)\""
		}

	configuration { "android-x86", "release" }
		postbuildcommands {
			"$(SILENT) echo Stripping symbols.",
			"$(SILENT) $(ANDROID_NDK_X86)/bin/i686-linux-android-strip -s \"$(TARGET)\""
		}

	configuration { "linux-steamlink", "release" }
		postbuildcommands {
			"$(SILENT) echo Stripping symbols.",
			"$(SILENT) $(MARVELL_SDK_PATH)/toolchain/bin/armv7a-cros-linux-gnueabi-strip -s \"$(TARGET)\""
		}

	configuration { "linux-* or rpi", "not linux-steamlink", "release" }
		postbuildcommands {
			"$(SILENT) echo Stripping symbols.",
			"$(SILENT) strip -s \"$(TARGET)\""
		}

	configuration { "mingw*", "release" }
		postbuildcommands {
			"$(SILENT) echo Stripping symbols.",
			"$(SILENT) $(MINGW)/bin/strip -s \"$(TARGET)\""
		}

	configuration { "asmjs" }
		postbuildcommands {
			"$(SILENT) echo Running asmjs finalize.",
			"$(SILENT) \"$(EMSCRIPTEN)/emcc\" -O2 "

--				.. "-s ALLOW_MEMORY_GROWTH=1 "
--				.. "-s ASSERTIONS=2 "
--				.. "-s EMTERPRETIFY=1 "
--				.. "-s EMTERPRETIFY_ASYNC=1 "
				.. "-s PRECISE_F32=1 "
				.. "-s TOTAL_MEMORY=268435456 "
--				.. "-s USE_WEBGL2=1 "
                .. "-s WASM=0 " -- no wasm

				.. "--memory-init-file 1 "
				.. "\"$(TARGET)\" -o \"$(TARGET)\".html "
--				.. "--preload-file ../../../examples/runtime@/ "
		}

    configuration { "wasm" }
        postbuildcommands {
            "$(SILENT) echo Running asmjs finalize.",
            "$(SILENT) \"$(EMSCRIPTEN)/emcc\" -O2 "

--				.. "-s ALLOW_MEMORY_GROWTH=1 "
--				.. "-s ASSERTIONS=2 "
--				.. "-s EMTERPRETIFY=1 "
--				.. "-s EMTERPRETIFY_ASYNC=1 "
                .. "-s PRECISE_F32=1 "
                .. "-s TOTAL_MEMORY=268435456 "
--				.. "-s USE_WEBGL2=1 "
                .. "-s WASM=1 " -- has wasm

                .. "--memory-init-file 1 "
                .. "\"$(TARGET)\" -o \"$(TARGET)\".html "
--				.. "--preload-file ../../../examples/runtime@/ "
        }

    --[[
	configuration { "riscv" }
		postbuildcommands {
			"$(SILENT) echo Stripping symbols.",
			"$(SILENT) $(FREEDOM_E_SDK)/work/build/riscv-gnu-toolchain/riscv64-unknown-elf/prefix/bin/riscv64-unknown-elf-strip -s \"$(TARGET)\""
        }
    ]]

	configuration {} -- reset configuration
end
