# GNU Make project makefile autogenerated by GENie
ifndef config
  config=debug32
endif

ifndef verbose
  SILENT = @
endif

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(MAKESHELL)))
  SHELLTYPE := posix
endif

ifeq (posix,$(SHELLTYPE))
  MKDIR = $(SILENT) mkdir -p "$(1)"
  COPY  = $(SILENT) cp -fR "$(1)" "$(2)"
  RM    = $(SILENT) rm -f "$(1)"
else
  MKDIR = $(SILENT) mkdir "$(subst /,\\,$(1))" 2> nul || exit 0
  COPY  = $(SILENT) copy /Y "$(subst /,\\,$(1))" "$(subst /,\\,$(2))"
  RM    = $(SILENT) del /F "$(subst /,\\,$(1))" 2> nul || exit 0
endif

CC  = gcc
CXX = g++
AR  = ar

ifndef RESCOMP
  ifdef WINDRES
    RESCOMP = $(WINDRES)
  else
    RESCOMP = windres
  endif
endif

MAKEFILE = riku.make

ifeq ($(config),debug32)
  OBJDIR              = ../../osx32_clang/obj/x32/debug/riku
  TARGETDIR           = ../../osx32_clang/bin
  TARGET              = $(TARGETDIR)/libriku.debug.a
  DEFINES            += -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS -D_DEBUG
  INCLUDES           += -I"../../../include/compat/osx" -I"../../../include" -I"../../../3rdparty/zlib-1.2.11"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m32 -Wshadow -m32 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m32 -Wshadow -m32 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m32 -std=c++14 -fno-rtti -fno-exceptions -Wshadow -m32 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m32 -Wshadow -m32 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m32 -std=c++14 -fno-rtti -fno-exceptions -Wshadow -m32 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -m32
  LIBDEPS            +=
  LDDEPS             +=
  LIBS               += $(LDDEPS)
  EXTERNAL_LIBS      +=
  LINKOBJS            = $(OBJECTS)
  LINKCMD             = $(AR)  -rcs $(TARGET)
  OBJECTS := \
	$(OBJDIR)/3rdparty/zlib-1.2.11/adler32.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/compress.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/crc32.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/deflate.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzclose.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzlib.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzread.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzwrite.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/infback.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/inffast.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/inflate.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/inftrees.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/trees.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/uncompr.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/zutil.o \
	$(OBJDIR)/src/cluster.o \
	$(OBJDIR)/src/core.o \
	$(OBJDIR)/src/crypto.o \
	$(OBJDIR)/src/dylib.o \
	$(OBJDIR)/src/fs.o \
	$(OBJDIR)/src/json.o \
	$(OBJDIR)/src/net.o \
	$(OBJDIR)/src/os.o \
	$(OBJDIR)/src/path.o \
	$(OBJDIR)/src/stream.o \
	$(OBJDIR)/src/thread.o \
	$(OBJDIR)/src/zlib.o \

  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release32)
  OBJDIR              = ../../osx32_clang/obj/x32/release/riku
  TARGETDIR           = ../../osx32_clang/bin
  TARGET              = $(TARGETDIR)/libriku.a
  DEFINES            += -DNDEBUG
  INCLUDES           += -I"../../../include/compat/osx" -I"../../../include" -I"../../../3rdparty/zlib-1.2.11"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m32 -Wshadow -m32 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m32 -Wshadow -m32 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m32 -Wshadow -m32 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m32 -Wshadow -m32 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m32 -Wshadow -m32 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -s -m32
  LIBDEPS            +=
  LDDEPS             +=
  LIBS               += $(LDDEPS)
  EXTERNAL_LIBS      +=
  LINKOBJS            = $(OBJECTS)
  LINKCMD             = $(AR)  -rcs $(TARGET)
  OBJECTS := \
	$(OBJDIR)/3rdparty/zlib-1.2.11/adler32.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/compress.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/crc32.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/deflate.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzclose.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzlib.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzread.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzwrite.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/infback.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/inffast.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/inflate.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/inftrees.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/trees.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/uncompr.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/zutil.o \
	$(OBJDIR)/src/cluster.o \
	$(OBJDIR)/src/core.o \
	$(OBJDIR)/src/crypto.o \
	$(OBJDIR)/src/dylib.o \
	$(OBJDIR)/src/fs.o \
	$(OBJDIR)/src/json.o \
	$(OBJDIR)/src/net.o \
	$(OBJDIR)/src/os.o \
	$(OBJDIR)/src/path.o \
	$(OBJDIR)/src/stream.o \
	$(OBJDIR)/src/thread.o \
	$(OBJDIR)/src/zlib.o \

  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),debug64)
  OBJDIR              = ../../osx64_clang/obj/x64/debug/riku
  TARGETDIR           = ../../osx64_clang/bin
  TARGET              = $(TARGETDIR)/libriku.debug.a
  DEFINES            += -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS -D_DEBUG
  INCLUDES           += -I"../../../include/compat/osx" -I"../../../include" -I"../../../3rdparty/zlib-1.2.11"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m64 -Wshadow -m64 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m64 -Wshadow -m64 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m64 -std=c++14 -fno-rtti -fno-exceptions -Wshadow -m64 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m64 -Wshadow -m64 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m64 -std=c++14 -fno-rtti -fno-exceptions -Wshadow -m64 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -m64
  LIBDEPS            +=
  LDDEPS             +=
  LIBS               += $(LDDEPS)
  EXTERNAL_LIBS      +=
  LINKOBJS            = $(OBJECTS)
  LINKCMD             = $(AR)  -rcs $(TARGET)
  OBJECTS := \
	$(OBJDIR)/3rdparty/zlib-1.2.11/adler32.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/compress.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/crc32.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/deflate.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzclose.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzlib.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzread.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzwrite.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/infback.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/inffast.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/inflate.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/inftrees.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/trees.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/uncompr.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/zutil.o \
	$(OBJDIR)/src/cluster.o \
	$(OBJDIR)/src/core.o \
	$(OBJDIR)/src/crypto.o \
	$(OBJDIR)/src/dylib.o \
	$(OBJDIR)/src/fs.o \
	$(OBJDIR)/src/json.o \
	$(OBJDIR)/src/net.o \
	$(OBJDIR)/src/os.o \
	$(OBJDIR)/src/path.o \
	$(OBJDIR)/src/stream.o \
	$(OBJDIR)/src/thread.o \
	$(OBJDIR)/src/zlib.o \

  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release64)
  OBJDIR              = ../../osx64_clang/obj/x64/release/riku
  TARGETDIR           = ../../osx64_clang/bin
  TARGET              = $(TARGETDIR)/libriku.a
  DEFINES            += -DNDEBUG
  INCLUDES           += -I"../../../include/compat/osx" -I"../../../include" -I"../../../3rdparty/zlib-1.2.11"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m64 -Wshadow -m64 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m64 -Wshadow -m64 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m64 -Wshadow -m64 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m64 -Wshadow -m64 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m64 -Wshadow -m64 -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -s -m64
  LIBDEPS            +=
  LDDEPS             +=
  LIBS               += $(LDDEPS)
  EXTERNAL_LIBS      +=
  LINKOBJS            = $(OBJECTS)
  LINKCMD             = $(AR)  -rcs $(TARGET)
  OBJECTS := \
	$(OBJDIR)/3rdparty/zlib-1.2.11/adler32.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/compress.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/crc32.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/deflate.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzclose.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzlib.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzread.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzwrite.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/infback.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/inffast.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/inflate.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/inftrees.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/trees.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/uncompr.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/zutil.o \
	$(OBJDIR)/src/cluster.o \
	$(OBJDIR)/src/core.o \
	$(OBJDIR)/src/crypto.o \
	$(OBJDIR)/src/dylib.o \
	$(OBJDIR)/src/fs.o \
	$(OBJDIR)/src/json.o \
	$(OBJDIR)/src/net.o \
	$(OBJDIR)/src/os.o \
	$(OBJDIR)/src/path.o \
	$(OBJDIR)/src/stream.o \
	$(OBJDIR)/src/thread.o \
	$(OBJDIR)/src/zlib.o \

  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),debug)
  OBJDIR              = obj/debug/riku
  TARGETDIR           = ../../../scripts
  TARGET              = $(TARGETDIR)/libriku.debug.a
  DEFINES            += -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS -D_DEBUG
  INCLUDES           += -I"../../../include/compat/osx" -I"../../../include" -I"../../../3rdparty/zlib-1.2.11"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -Wshadow -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -Wshadow -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -std=c++14 -fno-rtti -fno-exceptions -Wshadow -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -Wshadow -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -std=c++14 -fno-rtti -fno-exceptions -Wshadow -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS)
  LIBDEPS            +=
  LDDEPS             +=
  LIBS               += $(LDDEPS)
  EXTERNAL_LIBS      +=
  LINKOBJS            = $(OBJECTS)
  LINKCMD             = $(AR)  -rcs $(TARGET)
  OBJECTS := \
	$(OBJDIR)/3rdparty/zlib-1.2.11/adler32.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/compress.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/crc32.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/deflate.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzclose.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzlib.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzread.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzwrite.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/infback.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/inffast.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/inflate.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/inftrees.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/trees.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/uncompr.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/zutil.o \
	$(OBJDIR)/src/cluster.o \
	$(OBJDIR)/src/core.o \
	$(OBJDIR)/src/crypto.o \
	$(OBJDIR)/src/dylib.o \
	$(OBJDIR)/src/fs.o \
	$(OBJDIR)/src/json.o \
	$(OBJDIR)/src/net.o \
	$(OBJDIR)/src/os.o \
	$(OBJDIR)/src/path.o \
	$(OBJDIR)/src/stream.o \
	$(OBJDIR)/src/thread.o \
	$(OBJDIR)/src/zlib.o \

  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release)
  OBJDIR              = obj/release/riku
  TARGETDIR           = ../../../scripts
  TARGET              = $(TARGETDIR)/libriku.a
  DEFINES            += -DNDEBUG
  INCLUDES           += -I"../../../include/compat/osx" -I"../../../include" -I"../../../3rdparty/zlib-1.2.11"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -Wshadow -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -Wshadow -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -Wshadow -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -Wshadow -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -Wshadow -fdeclspec -fms-extensions -Wfatal-errors -msse2 -Wunused-value -Wundef
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -s
  LIBDEPS            +=
  LDDEPS             +=
  LIBS               += $(LDDEPS)
  EXTERNAL_LIBS      +=
  LINKOBJS            = $(OBJECTS)
  LINKCMD             = $(AR)  -rcs $(TARGET)
  OBJECTS := \
	$(OBJDIR)/3rdparty/zlib-1.2.11/adler32.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/compress.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/crc32.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/deflate.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzclose.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzlib.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzread.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/gzwrite.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/infback.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/inffast.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/inflate.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/inftrees.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/trees.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/uncompr.o \
	$(OBJDIR)/3rdparty/zlib-1.2.11/zutil.o \
	$(OBJDIR)/src/cluster.o \
	$(OBJDIR)/src/core.o \
	$(OBJDIR)/src/crypto.o \
	$(OBJDIR)/src/dylib.o \
	$(OBJDIR)/src/fs.o \
	$(OBJDIR)/src/json.o \
	$(OBJDIR)/src/net.o \
	$(OBJDIR)/src/os.o \
	$(OBJDIR)/src/path.o \
	$(OBJDIR)/src/stream.o \
	$(OBJDIR)/src/thread.o \
	$(OBJDIR)/src/zlib.o \

  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

OBJDIRS := \
	$(OBJDIR) \
	$(OBJDIR)/3rdparty/zlib-1.2.11 \
	$(OBJDIR)/src \

RESOURCES := \

.PHONY: clean prebuild prelink

all: $(OBJDIRS) $(TARGETDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LIBDEPS) $(EXTERNAL_LIBS) $(RESOURCES) | $(TARGETDIR) $(OBJDIRS)
	@echo Archiving riku
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
endif
	$(SILENT) $(LINKCMD) $(LINKOBJS)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
	-$(call MKDIR,$(TARGETDIR))

$(OBJDIRS):
	@echo Creating $(@)
	-$(call MKDIR,$@)

clean:
	@echo Cleaning riku
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH) $(MAKEFILE) | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) -x c++-header $(DEFINES) $(INCLUDES) -o "$@" -c "$<"

$(GCH_OBJC): $(PCH) $(MAKEFILE) | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_OBJCPPFLAGS) -x objective-c++-header $(DEFINES) $(INCLUDES) -o "$@" -c "$<"
endif

$(OBJDIR)/3rdparty/zlib-1.2.11/adler32.o: ../../../3rdparty/zlib-1.2.11/adler32.c $(GCH) $(MAKEFILE) | $(OBJDIR)/3rdparty/zlib-1.2.11
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/3rdparty/zlib-1.2.11/compress.o: ../../../3rdparty/zlib-1.2.11/compress.c $(GCH) $(MAKEFILE) | $(OBJDIR)/3rdparty/zlib-1.2.11
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/3rdparty/zlib-1.2.11/crc32.o: ../../../3rdparty/zlib-1.2.11/crc32.c $(GCH) $(MAKEFILE) | $(OBJDIR)/3rdparty/zlib-1.2.11
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/3rdparty/zlib-1.2.11/deflate.o: ../../../3rdparty/zlib-1.2.11/deflate.c $(GCH) $(MAKEFILE) | $(OBJDIR)/3rdparty/zlib-1.2.11
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/3rdparty/zlib-1.2.11/gzclose.o: ../../../3rdparty/zlib-1.2.11/gzclose.c $(GCH) $(MAKEFILE) | $(OBJDIR)/3rdparty/zlib-1.2.11
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/3rdparty/zlib-1.2.11/gzlib.o: ../../../3rdparty/zlib-1.2.11/gzlib.c $(GCH) $(MAKEFILE) | $(OBJDIR)/3rdparty/zlib-1.2.11
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/3rdparty/zlib-1.2.11/gzread.o: ../../../3rdparty/zlib-1.2.11/gzread.c $(GCH) $(MAKEFILE) | $(OBJDIR)/3rdparty/zlib-1.2.11
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/3rdparty/zlib-1.2.11/gzwrite.o: ../../../3rdparty/zlib-1.2.11/gzwrite.c $(GCH) $(MAKEFILE) | $(OBJDIR)/3rdparty/zlib-1.2.11
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/3rdparty/zlib-1.2.11/infback.o: ../../../3rdparty/zlib-1.2.11/infback.c $(GCH) $(MAKEFILE) | $(OBJDIR)/3rdparty/zlib-1.2.11
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/3rdparty/zlib-1.2.11/inffast.o: ../../../3rdparty/zlib-1.2.11/inffast.c $(GCH) $(MAKEFILE) | $(OBJDIR)/3rdparty/zlib-1.2.11
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/3rdparty/zlib-1.2.11/inflate.o: ../../../3rdparty/zlib-1.2.11/inflate.c $(GCH) $(MAKEFILE) | $(OBJDIR)/3rdparty/zlib-1.2.11
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/3rdparty/zlib-1.2.11/inftrees.o: ../../../3rdparty/zlib-1.2.11/inftrees.c $(GCH) $(MAKEFILE) | $(OBJDIR)/3rdparty/zlib-1.2.11
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/3rdparty/zlib-1.2.11/trees.o: ../../../3rdparty/zlib-1.2.11/trees.c $(GCH) $(MAKEFILE) | $(OBJDIR)/3rdparty/zlib-1.2.11
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/3rdparty/zlib-1.2.11/uncompr.o: ../../../3rdparty/zlib-1.2.11/uncompr.c $(GCH) $(MAKEFILE) | $(OBJDIR)/3rdparty/zlib-1.2.11
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/3rdparty/zlib-1.2.11/zutil.o: ../../../3rdparty/zlib-1.2.11/zutil.c $(GCH) $(MAKEFILE) | $(OBJDIR)/3rdparty/zlib-1.2.11
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/cluster.o: ../../../src/cluster.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/core.o: ../../../src/core.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/crypto.o: ../../../src/crypto.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/dylib.o: ../../../src/dylib.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/fs.o: ../../../src/fs.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/json.o: ../../../src/json.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/net.o: ../../../src/net.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/os.o: ../../../src/os.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/path.o: ../../../src/path.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/stream.o: ../../../src/stream.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/thread.o: ../../../src/thread.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/zlib.o: ../../../src/zlib.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(OBJDIR)/$(notdir $(PCH)).d
  -include $(OBJDIR)/$(notdir $(PCH))_objc.d
endif
