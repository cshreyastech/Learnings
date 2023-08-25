# Generated Makefile -- DO NOT EDIT!

HOST=win64
SPEC=debug_lumin_clang-8.0_aarch64
app_framework_BASE=C:/lcb/Learnings/ML/ML/app_framework
app_framework_OUTPUT=$(app_framework_BASE)/.out/$(SPEC)
samples_common_comp_BASE=C:/lcb/Learnings/ML/ML/ml_apps
snappy_BASE=C:/lcb/Learnings/ML/ML/app_framework/ext
snappy_OUTPUT=$(snappy_BASE)/.out/$(SPEC)
snappy_poc_OUTPUT=$(samples_common_comp_BASE)/BUILD/$(SPEC)


# this turns off the suffix rules built into make
.SUFFIXES:

# this turns off the RCS / SCCS implicit rules of GNU Make
% : RCS/%,v
% : RCS/%
% : %,v
% : s.%
% : SCCS/s.%

# If a rule fails, delete $@.
.DELETE_ON_ERROR:

ifeq ($(VERBOSE),)
ECHO=@
else
ECHO=
endif

ifeq ($(QUIET),)
INFO=@echo
else
INFO=@:
endif

ifeq ($(VERBOSE),)
SPAM=@: \#
else
SPAM=@echo
endif

all : prebuild build postbuild

prebuild :: 

postbuild :: 

clean :: snappy-clean app_framework-clean snappy_poc-clean

$(MLSDK)/tools/mabu/data/components/stdc++.comp : 

$(MLSDK)/tools/mabu/data/configs/debug.config : 

$(MLSDK)/tools/mabu/data/options/debug/on.option : 

$(MLSDK)/tools/mabu/data/options/magicleap.option : 

$(MLSDK)/tools/mabu/data/options/optimize/off.option : 

$(MLSDK)/tools/mabu/data/options/package/debuggable/on.option : 

$(MLSDK)/tools/mabu/data/options/runtime/shared.option : 

$(MLSDK)/tools/mabu/data/options/warn/on.option : 

C:/lcb/Learnings/ML/ML/app_framework/common.comp : 

$(MLSDK)/.metadata/components/ml_sdk.comp : 

$(MLSDK)/.metadata/components/ml_sdk_common.comp : 

$(MLSDK)/tools/mabu/data/components/OpenGL.comp : 

C:/lcb/Learnings/ML/ML/app_framework/ext/glm.comp : 

C:/lcb/Learnings/ML/ML/ml_apps/samples_common.comp : 

PROGRAM_PREFIX=
PROGRAM_EXT=
SHARED_PREFIX=lib
SHARED_EXT=.so
IMPLIB_PREFIX=lib
IMPLIB_EXT=.so
STATIC_PREFIX=lib
STATIC_EXT=.a
COMPILER_PREFIX=
LINKER_PREFIX=

-make-directories : C:/lcb/Learnings/ML/ML/app_framework/.out/debug_lumin_clang-8.0_aarch64 C:/lcb/Learnings/ML/ML/app_framework/.out/debug_lumin_clang-8.0_aarch64/bin C:/lcb/Learnings/ML/ML/app_framework/ext/.out/debug_lumin_clang-8.0_aarch64 C:/lcb/Learnings/ML/ML/app_framework/ext/.out/debug_lumin_clang-8.0_aarch64/bin C:/lcb/Learnings/ML/ML/app_framework/ext/.out/debug_lumin_clang-8.0_aarch64/obj.snappy/snappy C:/lcb/Learnings/ML/ML/ml_apps/BUILD/debug_lumin_clang-8.0_aarch64 C:/lcb/Learnings/ML/ML/ml_apps/BUILD/debug_lumin_clang-8.0_aarch64/bin C:/lcb/Learnings/ML/ML/ml_apps/BUILD/debug_lumin_clang-8.0_aarch64/data/res/cloud C:/lcb/Learnings/ML/ML/ml_apps/BUILD/debug_lumin_clang-8.0_aarch64/obj.snappy_poc/src/snappy_poc

C:/lcb/Learnings/ML/ML/app_framework/.out/debug_lumin_clang-8.0_aarch64 : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/ML/app_framework/.out/debug_lumin_clang-8.0_aarch64

C:/lcb/Learnings/ML/ML/app_framework/.out/debug_lumin_clang-8.0_aarch64/bin : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/ML/app_framework/.out/debug_lumin_clang-8.0_aarch64/bin

C:/lcb/Learnings/ML/ML/app_framework/ext/.out/debug_lumin_clang-8.0_aarch64 : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/ML/app_framework/ext/.out/debug_lumin_clang-8.0_aarch64

C:/lcb/Learnings/ML/ML/app_framework/ext/.out/debug_lumin_clang-8.0_aarch64/bin : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/ML/app_framework/ext/.out/debug_lumin_clang-8.0_aarch64/bin

C:/lcb/Learnings/ML/ML/app_framework/ext/.out/debug_lumin_clang-8.0_aarch64/obj.snappy/snappy : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/ML/app_framework/ext/.out/debug_lumin_clang-8.0_aarch64/obj.snappy/snappy

C:/lcb/Learnings/ML/ML/ml_apps/BUILD/debug_lumin_clang-8.0_aarch64 : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/ML/ml_apps/BUILD/debug_lumin_clang-8.0_aarch64

C:/lcb/Learnings/ML/ML/ml_apps/BUILD/debug_lumin_clang-8.0_aarch64/bin : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/ML/ml_apps/BUILD/debug_lumin_clang-8.0_aarch64/bin

C:/lcb/Learnings/ML/ML/ml_apps/BUILD/debug_lumin_clang-8.0_aarch64/data/res/cloud : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/ML/ml_apps/BUILD/debug_lumin_clang-8.0_aarch64/data/res/cloud

C:/lcb/Learnings/ML/ML/ml_apps/BUILD/debug_lumin_clang-8.0_aarch64/obj.snappy_poc/src/snappy_poc : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/ML/ml_apps/BUILD/debug_lumin_clang-8.0_aarch64/obj.snappy_poc/src/snappy_poc

include $(snappy_OUTPUT)/snappy.mk
include $(app_framework_OUTPUT)/app_framework.mk
include $(snappy_poc_OUTPUT)/snappy_poc.mk
build :  | snappy-all app_framework-all snappy_poc-all

