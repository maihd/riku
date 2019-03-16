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
  OBJDIR              = ../../linux_x32/obj/x32/debug/riku
  TARGETDIR           = ../../linux_x32/bin
  TARGET              = $(TARGETDIR)/libriku.debug.a
  DEFINES            += -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS -D_DEBUG
  INCLUDES           += -I"../../../include" -I"../../../3rdparty/zlib-1.2.11"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m32 -msse2 -Wunused-value -Wundef -m32
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m32 -msse2 -Wunused-value -Wundef -m32
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m32 -std=c++14 -fno-rtti -fno-exceptions -msse2 -Wunused-value -Wundef -m32
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m32 -msse2 -Wunused-value -Wundef -m32
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m32 -std=c++14 -fno-rtti -fno-exceptions -msse2 -Wunused-value -Wundef -m32
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -L"../../../3rdparty/lib/linux_x32" -L"." -m32 -Wl,--gc-sections -Wl,--as-needed
  LIBDEPS            +=
  LDDEPS             +=
  LIBS               += $(LDDEPS) -lm -lrt -ldl
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
	$(OBJDIR)/src/riku_cluster.o \
	$(OBJDIR)/src/riku_core.o \
	$(OBJDIR)/src/riku_crypto.o \
	$(OBJDIR)/src/riku_dylib.o \
	$(OBJDIR)/src/riku_fs.o \
	$(OBJDIR)/src/riku_json.o \
	$(OBJDIR)/src/riku_math.o \
	$(OBJDIR)/src/riku_net.o \
	$(OBJDIR)/src/riku_os.o \
	$(OBJDIR)/src/riku_path.o \
	$(OBJDIR)/src/riku_stream.o \
	$(OBJDIR)/src/riku_thread.o \
	$(OBJDIR)/src/riku_zlib.o \

  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release32)
  OBJDIR              = ../../linux_x32/obj/x32/release/riku
  TARGETDIR           = ../../linux_x32/bin
  TARGET              = $(TARGETDIR)/libriku.a
  DEFINES            += -DNDEBUG
  INCLUDES           += -I"../../../include" -I"../../../3rdparty/zlib-1.2.11"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m32 -msse2 -Wunused-value -Wundef -m32
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m32 -msse2 -Wunused-value -Wundef -m32
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m32 -msse2 -Wunused-value -Wundef -m32
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m32 -msse2 -Wunused-value -Wundef -m32
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m32 -msse2 -Wunused-value -Wundef -m32
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -L"../../../3rdparty/lib/linux_x32" -L"." -s -m32 -Wl,--gc-sections -Wl,--as-needed
  LIBDEPS            +=
  LDDEPS             +=
  LIBS               += $(LDDEPS) -lm -lrt -ldl
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
	$(OBJDIR)/src/riku_cluster.o \
	$(OBJDIR)/src/riku_core.o \
	$(OBJDIR)/src/riku_crypto.o \
	$(OBJDIR)/src/riku_dylib.o \
	$(OBJDIR)/src/riku_fs.o \
	$(OBJDIR)/src/riku_json.o \
	$(OBJDIR)/src/riku_math.o \
	$(OBJDIR)/src/riku_net.o \
	$(OBJDIR)/src/riku_os.o \
	$(OBJDIR)/src/riku_path.o \
	$(OBJDIR)/src/riku_stream.o \
	$(OBJDIR)/src/riku_thread.o \
	$(OBJDIR)/src/riku_zlib.o \

  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),debug64)
  OBJDIR              = ../../linux_x64/obj/x64/debug/riku
  TARGETDIR           = ../../linux_x64/bin
  TARGET              = $(TARGETDIR)/libriku.debug.a
  DEFINES            += -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS -D_DEBUG
  INCLUDES           += -I"../../../include" -I"../../../3rdparty/zlib-1.2.11"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m64 -msse2 -Wunused-value -Wundef -m64
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m64 -msse2 -Wunused-value -Wundef -m64
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m64 -std=c++14 -fno-rtti -fno-exceptions -msse2 -Wunused-value -Wundef -m64
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m64 -msse2 -Wunused-value -Wundef -m64
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -m64 -std=c++14 -fno-rtti -fno-exceptions -msse2 -Wunused-value -Wundef -m64
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -L"../../../3rdparty/lib/linux_x64" -L"." -m64 -Wl,--gc-sections -Wl,--as-needed
  LIBDEPS            +=
  LDDEPS             +=
  LIBS               += $(LDDEPS) -lm -lrt -ldl
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
	$(OBJDIR)/src/riku_cluster.o \
	$(OBJDIR)/src/riku_core.o \
	$(OBJDIR)/src/riku_crypto.o \
	$(OBJDIR)/src/riku_dylib.o \
	$(OBJDIR)/src/riku_fs.o \
	$(OBJDIR)/src/riku_json.o \
	$(OBJDIR)/src/riku_math.o \
	$(OBJDIR)/src/riku_net.o \
	$(OBJDIR)/src/riku_os.o \
	$(OBJDIR)/src/riku_path.o \
	$(OBJDIR)/src/riku_stream.o \
	$(OBJDIR)/src/riku_thread.o \
	$(OBJDIR)/src/riku_zlib.o \

  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release64)
  OBJDIR              = ../../linux_x64/obj/x64/release/riku
  TARGETDIR           = ../../linux_x64/bin
  TARGET              = $(TARGETDIR)/libriku.a
  DEFINES            += -DNDEBUG
  INCLUDES           += -I"../../../include" -I"../../../3rdparty/zlib-1.2.11"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m64 -msse2 -Wunused-value -Wundef -m64
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m64 -msse2 -Wunused-value -Wundef -m64
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m64 -msse2 -Wunused-value -Wundef -m64
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m64 -msse2 -Wunused-value -Wundef -m64
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -m64 -msse2 -Wunused-value -Wundef -m64
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -L"../../../3rdparty/lib/linux_x64" -L"." -s -m64 -Wl,--gc-sections -Wl,--as-needed
  LIBDEPS            +=
  LDDEPS             +=
  LIBS               += $(LDDEPS) -lm -lrt -ldl
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
	$(OBJDIR)/src/riku_cluster.o \
	$(OBJDIR)/src/riku_core.o \
	$(OBJDIR)/src/riku_crypto.o \
	$(OBJDIR)/src/riku_dylib.o \
	$(OBJDIR)/src/riku_fs.o \
	$(OBJDIR)/src/riku_json.o \
	$(OBJDIR)/src/riku_math.o \
	$(OBJDIR)/src/riku_net.o \
	$(OBJDIR)/src/riku_os.o \
	$(OBJDIR)/src/riku_path.o \
	$(OBJDIR)/src/riku_stream.o \
	$(OBJDIR)/src/riku_thread.o \
	$(OBJDIR)/src/riku_zlib.o \

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
  INCLUDES           += -I"../../../include" -I"../../../3rdparty/zlib-1.2.11"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -msse2 -Wunused-value -Wundef
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -msse2 -Wunused-value -Wundef
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -std=c++14 -fno-rtti -fno-exceptions -msse2 -Wunused-value -Wundef
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -msse2 -Wunused-value -Wundef
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -g -Wall -Wextra -fomit-frame-pointer -std=c++14 -fno-rtti -fno-exceptions -msse2 -Wunused-value -Wundef
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -L"." -Wl,--gc-sections -Wl,--as-needed
  LIBDEPS            +=
  LDDEPS             +=
  LIBS               += $(LDDEPS) -lm -lrt -ldl
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
	$(OBJDIR)/src/riku_cluster.o \
	$(OBJDIR)/src/riku_core.o \
	$(OBJDIR)/src/riku_crypto.o \
	$(OBJDIR)/src/riku_dylib.o \
	$(OBJDIR)/src/riku_fs.o \
	$(OBJDIR)/src/riku_json.o \
	$(OBJDIR)/src/riku_math.o \
	$(OBJDIR)/src/riku_net.o \
	$(OBJDIR)/src/riku_os.o \
	$(OBJDIR)/src/riku_path.o \
	$(OBJDIR)/src/riku_stream.o \
	$(OBJDIR)/src/riku_thread.o \
	$(OBJDIR)/src/riku_zlib.o \

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
  INCLUDES           += -I"../../../include" -I"../../../3rdparty/zlib-1.2.11"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -msse2 -Wunused-value -Wundef
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -msse2 -Wunused-value -Wundef
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -msse2 -Wunused-value -Wundef
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -msse2 -Wunused-value -Wundef
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -O3 -msse2 -Wunused-value -Wundef
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -L"." -s -Wl,--gc-sections -Wl,--as-needed
  LIBDEPS            +=
  LDDEPS             +=
  LIBS               += $(LDDEPS) -lm -lrt -ldl
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
	$(OBJDIR)/src/riku_cluster.o \
	$(OBJDIR)/src/riku_core.o \
	$(OBJDIR)/src/riku_crypto.o \
	$(OBJDIR)/src/riku_dylib.o \
	$(OBJDIR)/src/riku_fs.o \
	$(OBJDIR)/src/riku_json.o \
	$(OBJDIR)/src/riku_math.o \
	$(OBJDIR)/src/riku_net.o \
	$(OBJDIR)/src/riku_os.o \
	$(OBJDIR)/src/riku_path.o \
	$(OBJDIR)/src/riku_stream.o \
	$(OBJDIR)/src/riku_thread.o \
	$(OBJDIR)/src/riku_zlib.o \

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

$(OBJDIR)/src/riku_cluster.o: ../../../src/riku_cluster.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/riku_core.o: ../../../src/riku_core.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/riku_crypto.o: ../../../src/riku_crypto.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/riku_dylib.o: ../../../src/riku_dylib.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/riku_fs.o: ../../../src/riku_fs.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/riku_json.o: ../../../src/riku_json.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/riku_math.o: ../../../src/riku_math.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/riku_net.o: ../../../src/riku_net.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/riku_os.o: ../../../src/riku_os.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/riku_path.o: ../../../src/riku_path.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/riku_stream.o: ../../../src/riku_stream.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/riku_thread.o: ../../../src/riku_thread.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

$(OBJDIR)/src/riku_zlib.o: ../../../src/riku_zlib.cc $(GCH) $(MAKEFILE) | $(OBJDIR)/src
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(OBJDIR)/$(notdir $(PCH)).d
  -include $(OBJDIR)/$(notdir $(PCH))_objc.d
endif
