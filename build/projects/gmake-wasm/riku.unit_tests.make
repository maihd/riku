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

CC  = "$(EMSCRIPTEN)/emcc"
CXX = "$(EMSCRIPTEN)/em++"
AR  = "$(EMSCRIPTEN)/emar"

ifndef RESCOMP
  ifdef WINDRES
    RESCOMP = $(WINDRES)
  else
    RESCOMP = windres
  endif
endif

MAKEFILE = riku.unit_tests.make

ifeq ($(config),debug32)
  OBJDIR              = ../../wasm/obj/x32/debug/riku.unit_tests
  TARGETDIR           = ../../wasm/bin
  TARGET              = $(TARGETDIR)/riku.unit_testsdebug.exe
  DEFINES            += -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS -D_DEBUG
  INCLUDES           += -I"../../../include"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m32 -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m32 -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m32 -std=c++14 -fno-rtti -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m32 -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m32 -std=c++14 -fno-rtti -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -L"../../../3rdparty/lib/wasm" -L"../../wasm/bin" -m32
  LIBDEPS            += ../../wasm/bin/librikudebug.a
  LDDEPS             += ../../wasm/bin/librikudebug.a
  LIBS               += $(LDDEPS)
  EXTERNAL_LIBS      +=
  LINKOBJS            = $(OBJECTS)
  LINKCMD             = $(CXX) -o $(TARGET) $(LINKOBJS) $(RESOURCES) $(ARCH) $(ALL_LDFLAGS) $(LIBS)
  OBJECTS := \

  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
	@echo Running post-build commands
	$(SILENT) echo Running asmjs finalize.
	$(SILENT) "$(EMSCRIPTEN)/emcc" -O2 -s PRECISE_F32=1 -s TOTAL_MEMORY=268435456 -s WASM=1 --memory-init-file 1 "$(TARGET)" -o "$(TARGET)".html 
  endef
endif

ifeq ($(config),release32)
  OBJDIR              = ../../wasm/obj/x32/release/riku.unit_tests
  TARGETDIR           = ../../wasm/bin
  TARGET              = $(TARGETDIR)/riku.unit_testsrelease.exe
  DEFINES            += -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS -DNDEBUG
  INCLUDES           += -I"../../../include"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m32 -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m32 -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m32 -std=c++14 -fno-rtti -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m32 -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m32 -std=c++14 -fno-rtti -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -L"../../../3rdparty/lib/wasm" -L"../../wasm/bin" -m32
  LIBDEPS            += ../../wasm/bin/librikurelease.a
  LDDEPS             += ../../wasm/bin/librikurelease.a
  LIBS               += $(LDDEPS)
  EXTERNAL_LIBS      +=
  LINKOBJS            = $(OBJECTS)
  LINKCMD             = $(CXX) -o $(TARGET) $(LINKOBJS) $(RESOURCES) $(ARCH) $(ALL_LDFLAGS) $(LIBS)
  OBJECTS := \

  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
	@echo Running post-build commands
	$(SILENT) echo Running asmjs finalize.
	$(SILENT) "$(EMSCRIPTEN)/emcc" -O2 -s PRECISE_F32=1 -s TOTAL_MEMORY=268435456 -s WASM=1 --memory-init-file 1 "$(TARGET)" -o "$(TARGET)".html 
  endef
endif

ifeq ($(config),debug64)
  OBJDIR              = ../../wasm/obj/x64/debug/riku.unit_tests
  TARGETDIR           = ../../wasm/bin
  TARGET              = $(TARGETDIR)/riku.unit_testsdebug.exe
  DEFINES            += -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS -D_DEBUG
  INCLUDES           += -I"../../../include"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m64 -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m64 -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m64 -std=c++14 -fno-rtti -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m64 -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -m64 -std=c++14 -fno-rtti -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -L"../../../3rdparty/lib/wasm" -L"../../wasm/bin" -m64
  LIBDEPS            += ../../wasm/bin/librikudebug.a
  LDDEPS             += ../../wasm/bin/librikudebug.a
  LIBS               += $(LDDEPS)
  EXTERNAL_LIBS      +=
  LINKOBJS            = $(OBJECTS)
  LINKCMD             = $(CXX) -o $(TARGET) $(LINKOBJS) $(RESOURCES) $(ARCH) $(ALL_LDFLAGS) $(LIBS)
  OBJECTS := \

  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
	@echo Running post-build commands
	$(SILENT) echo Running asmjs finalize.
	$(SILENT) "$(EMSCRIPTEN)/emcc" -O2 -s PRECISE_F32=1 -s TOTAL_MEMORY=268435456 -s WASM=1 --memory-init-file 1 "$(TARGET)" -o "$(TARGET)".html 
  endef
endif

ifeq ($(config),release64)
  OBJDIR              = ../../wasm/obj/x64/release/riku.unit_tests
  TARGETDIR           = ../../wasm/bin
  TARGET              = $(TARGETDIR)/riku.unit_testsrelease.exe
  DEFINES            += -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS -DNDEBUG
  INCLUDES           += -I"../../../include"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m64 -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m64 -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m64 -std=c++14 -fno-rtti -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m64 -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -m64 -std=c++14 -fno-rtti -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -L"../../../3rdparty/lib/wasm" -L"../../wasm/bin" -m64
  LIBDEPS            += ../../wasm/bin/librikurelease.a
  LDDEPS             += ../../wasm/bin/librikurelease.a
  LIBS               += $(LDDEPS)
  EXTERNAL_LIBS      +=
  LINKOBJS            = $(OBJECTS)
  LINKCMD             = $(CXX) -o $(TARGET) $(LINKOBJS) $(RESOURCES) $(ARCH) $(ALL_LDFLAGS) $(LIBS)
  OBJECTS := \

  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
	@echo Running post-build commands
	$(SILENT) echo Running asmjs finalize.
	$(SILENT) "$(EMSCRIPTEN)/emcc" -O2 -s PRECISE_F32=1 -s TOTAL_MEMORY=268435456 -s WASM=1 --memory-init-file 1 "$(TARGET)" -o "$(TARGET)".html 
  endef
endif

ifeq ($(config),debug)
  OBJDIR              = ../../wasm/obj/debug/riku.unit_tests
  TARGETDIR           = ../../wasm/bin
  TARGET              = $(TARGETDIR)/riku.unit_testsdebug.exe
  DEFINES            += -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS -D_DEBUG
  INCLUDES           += -I"../../../include"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -std=c++14 -fno-rtti -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -std=c++14 -fno-rtti -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -L"../../../3rdparty/lib/wasm" -L"../../wasm/bin"
  LIBDEPS            += ../../wasm/bin/librikudebug.a
  LDDEPS             += ../../wasm/bin/librikudebug.a
  LIBS               += $(LDDEPS)
  EXTERNAL_LIBS      +=
  LINKOBJS            = $(OBJECTS)
  LINKCMD             = $(CXX) -o $(TARGET) $(LINKOBJS) $(RESOURCES) $(ARCH) $(ALL_LDFLAGS) $(LIBS)
  OBJECTS := \

  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
	@echo Running post-build commands
	$(SILENT) echo Running asmjs finalize.
	$(SILENT) "$(EMSCRIPTEN)/emcc" -O2 -s PRECISE_F32=1 -s TOTAL_MEMORY=268435456 -s WASM=1 --memory-init-file 1 "$(TARGET)" -o "$(TARGET)".html 
  endef
endif

ifeq ($(config),release)
  OBJDIR              = ../../wasm/obj/release/riku.unit_tests
  TARGETDIR           = ../../wasm/bin
  TARGET              = $(TARGETDIR)/riku.unit_testsrelease.exe
  DEFINES            += -D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_CONSTANT_MACROS -DNDEBUG
  INCLUDES           += -I"../../../include"
  ALL_CPPFLAGS       += $(CPPFLAGS) -MMD -MP -MP $(DEFINES) $(INCLUDES)
  ALL_ASMFLAGS       += $(ASMFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_CFLAGS         += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_CXXFLAGS       += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -std=c++14 -fno-rtti -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_OBJCFLAGS      += $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_OBJCPPFLAGS    += $(CXXFLAGS) $(CFLAGS) $(ALL_CPPFLAGS) $(ARCH) -Wall -Wextra -fomit-frame-pointer -g -O3 -std=c++14 -fno-rtti -s WASM=0 -fdeclspec -fms-extensions -Wunused-value -Wundef
  ALL_RESFLAGS       += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS        += $(LDFLAGS) -L"../../../3rdparty/lib/wasm" -L"../../wasm/bin"
  LIBDEPS            += ../../wasm/bin/librikurelease.a
  LDDEPS             += ../../wasm/bin/librikurelease.a
  LIBS               += $(LDDEPS)
  EXTERNAL_LIBS      +=
  LINKOBJS            = $(OBJECTS)
  LINKCMD             = $(CXX) -o $(TARGET) $(LINKOBJS) $(RESOURCES) $(ARCH) $(ALL_LDFLAGS) $(LIBS)
  OBJECTS := \

  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
	@echo Running post-build commands
	$(SILENT) echo Running asmjs finalize.
	$(SILENT) "$(EMSCRIPTEN)/emcc" -O2 -s PRECISE_F32=1 -s TOTAL_MEMORY=268435456 -s WASM=1 --memory-init-file 1 "$(TARGET)" -o "$(TARGET)".html 
  endef
endif

OBJDIRS := \
	$(OBJDIR) \

RESOURCES := \

.PHONY: clean prebuild prelink

all: $(OBJDIRS) $(TARGETDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LIBDEPS) $(EXTERNAL_LIBS) $(RESOURCES) | $(TARGETDIR) $(OBJDIRS)
	@echo Linking riku.unit_tests
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
	-$(call MKDIR,$(TARGETDIR))

$(OBJDIRS):
	@echo Creating $(@)
	-$(call MKDIR,$@)

clean:
	@echo Cleaning riku.unit_tests
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

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(OBJDIR)/$(notdir $(PCH)).d
  -include $(OBJDIR)/$(notdir $(PCH))_objc.d
endif
