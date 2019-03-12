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

CC  = clang
CXX = clang++
AR  = $(ANDROID_NDK_ARM64)/bin/aarch64-linux-android-ar

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
  TARGET              = $(TARGETDIR)/librikudebug.a
  DEFINES            += -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS -D_DEBUG
  INCLUDES           += -I"../../../include"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m32 -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m32
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m32 -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m32
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m32 -std=c++14 -fno-rtti -fno-exceptions -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m32
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m32 -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m32
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m32 -std=c++14 -fno-rtti -fno-exceptions -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m32
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -L"../../../3rdparty/lib/linux_x32" -L"." -m32 -Wl,--gc-sections -Wl,--as-needed
  LIBDEPS            +=
  LDDEPS             +=
  LIBS               += $(LDDEPS) -lrt -ldl
  EXTERNAL_LIBS      +=
  LINKOBJS            = $(OBJECTS)
  LINKCMD             = $(AR)  -rcs $(TARGET)
  OBJECTS := \
	$(OBJDIR)/src/cluster.o \
	$(OBJDIR)/src/core.o \
	$(OBJDIR)/src/crypto.o \
	$(OBJDIR)/src/dylib.o \
	$(OBJDIR)/src/fs.o \
	$(OBJDIR)/src/json.o \
	$(OBJDIR)/src/net.o \
	$(OBJDIR)/src/os.o \
	$(OBJDIR)/src/path.o \
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
  OBJDIR              = ../../linux_x32/obj/x32/release/riku
  TARGETDIR           = ../../linux_x32/bin
  TARGET              = $(TARGETDIR)/librikurelease.a
  DEFINES            += -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS -DNDEBUG
  INCLUDES           += -I"../../../include"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m32 -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m32
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m32 -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m32
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m32 -std=c++14 -fno-rtti -fno-exceptions -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m32
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m32 -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m32
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m32 -std=c++14 -fno-rtti -fno-exceptions -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m32
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -L"../../../3rdparty/lib/linux_x32" -L"." -m32 -Wl,--gc-sections -Wl,--as-needed
  LIBDEPS            +=
  LDDEPS             +=
  LIBS               += $(LDDEPS) -lrt -ldl
  EXTERNAL_LIBS      +=
  LINKOBJS            = $(OBJECTS)
  LINKCMD             = $(AR)  -rcs $(TARGET)
  OBJECTS := \
	$(OBJDIR)/src/cluster.o \
	$(OBJDIR)/src/core.o \
	$(OBJDIR)/src/crypto.o \
	$(OBJDIR)/src/dylib.o \
	$(OBJDIR)/src/fs.o \
	$(OBJDIR)/src/json.o \
	$(OBJDIR)/src/net.o \
	$(OBJDIR)/src/os.o \
	$(OBJDIR)/src/path.o \
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
  OBJDIR              = ../../linux_x64/obj/x64/debug/riku
  TARGETDIR           = ../../linux_x64/bin
  TARGET              = $(TARGETDIR)/librikudebug.a
  DEFINES            += -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS -D_DEBUG
  INCLUDES           += -I"../../../include"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m64 -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m64
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m64 -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m64
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m64 -std=c++14 -fno-rtti -fno-exceptions -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m64
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m64 -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m64
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m64 -std=c++14 -fno-rtti -fno-exceptions -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m64
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -L"../../../3rdparty/lib/linux_x64" -L"." -m64 -Wl,--gc-sections -Wl,--as-needed
  LIBDEPS            +=
  LDDEPS             +=
  LIBS               += $(LDDEPS) -lrt -ldl
  EXTERNAL_LIBS      +=
  LINKOBJS            = $(OBJECTS)
  LINKCMD             = $(AR)  -rcs $(TARGET)
  OBJECTS := \
	$(OBJDIR)/src/cluster.o \
	$(OBJDIR)/src/core.o \
	$(OBJDIR)/src/crypto.o \
	$(OBJDIR)/src/dylib.o \
	$(OBJDIR)/src/fs.o \
	$(OBJDIR)/src/json.o \
	$(OBJDIR)/src/net.o \
	$(OBJDIR)/src/os.o \
	$(OBJDIR)/src/path.o \
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
  OBJDIR              = ../../linux_x64/obj/x64/release/riku
  TARGETDIR           = ../../linux_x64/bin
  TARGET              = $(TARGETDIR)/librikurelease.a
  DEFINES            += -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS -DNDEBUG
  INCLUDES           += -I"../../../include"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m64 -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m64
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m64 -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m64
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m64 -std=c++14 -fno-rtti -fno-exceptions -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m64
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m64 -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m64
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m64 -std=c++14 -fno-rtti -fno-exceptions -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef -m64
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -L"../../../3rdparty/lib/linux_x64" -L"." -m64 -Wl,--gc-sections -Wl,--as-needed
  LIBDEPS            +=
  LDDEPS             +=
  LIBS               += $(LDDEPS) -lrt -ldl
  EXTERNAL_LIBS      +=
  LINKOBJS            = $(OBJECTS)
  LINKCMD             = $(AR)  -rcs $(TARGET)
  OBJECTS := \
	$(OBJDIR)/src/cluster.o \
	$(OBJDIR)/src/core.o \
	$(OBJDIR)/src/crypto.o \
	$(OBJDIR)/src/dylib.o \
	$(OBJDIR)/src/fs.o \
	$(OBJDIR)/src/json.o \
	$(OBJDIR)/src/net.o \
	$(OBJDIR)/src/os.o \
	$(OBJDIR)/src/path.o \
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
  TARGET              = $(TARGETDIR)/librikudebug.a
  DEFINES            += -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS -D_DEBUG
  INCLUDES           += -I"../../../include"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -std=c++14 -fno-rtti -fno-exceptions -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -std=c++14 -fno-rtti -fno-exceptions -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -L"." -Wl,--gc-sections -Wl,--as-needed
  LIBDEPS            +=
  LDDEPS             +=
  LIBS               += $(LDDEPS) -lrt -ldl
  EXTERNAL_LIBS      +=
  LINKOBJS            = $(OBJECTS)
  LINKCMD             = $(AR)  -rcs $(TARGET)
  OBJECTS := \
	$(OBJDIR)/src/cluster.o \
	$(OBJDIR)/src/core.o \
	$(OBJDIR)/src/crypto.o \
	$(OBJDIR)/src/dylib.o \
	$(OBJDIR)/src/fs.o \
	$(OBJDIR)/src/json.o \
	$(OBJDIR)/src/net.o \
	$(OBJDIR)/src/os.o \
	$(OBJDIR)/src/path.o \
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
  TARGET              = $(TARGETDIR)/librikurelease.a
  DEFINES            += -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS -DNDEBUG
  INCLUDES           += -I"../../../include"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -std=c++14 -fno-rtti -fno-exceptions -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -std=c++14 -fno-rtti -fno-exceptions -fdeclspec -fms-extensions -msse2 -Wshadow -Wunused-value -Wundef
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -L"." -Wl,--gc-sections -Wl,--as-needed
  LIBDEPS            +=
  LDDEPS             +=
  LIBS               += $(LDDEPS) -lrt -ldl
  EXTERNAL_LIBS      +=
  LINKOBJS            = $(OBJECTS)
  LINKCMD             = $(AR)  -rcs $(TARGET)
  OBJECTS := \
	$(OBJDIR)/src/cluster.o \
	$(OBJDIR)/src/core.o \
	$(OBJDIR)/src/crypto.o \
	$(OBJDIR)/src/dylib.o \
	$(OBJDIR)/src/fs.o \
	$(OBJDIR)/src/json.o \
	$(OBJDIR)/src/net.o \
	$(OBJDIR)/src/os.o \
	$(OBJDIR)/src/path.o \
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