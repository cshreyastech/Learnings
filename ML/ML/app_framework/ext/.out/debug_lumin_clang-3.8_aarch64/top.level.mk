# Generated Makefile -- DO NOT EDIT!

HOST=win64
SPEC=debug_lumin_clang-3.8_aarch64
app_framework_BASE=C:/lcb/AutoECMControl/ML/app_framework
app_framework_OUTPUT=$(app_framework_BASE)/.out/$(SPEC)
glad_BASE=C:/lcb/AutoECMControl/ML/app_framework/ext
glad_OUTPUT=$(glad_BASE)/.out/$(SPEC)
ros_ml_server_OUTPUT=$(samples_common_comp_BASE)/BUILD/$(SPEC)
samples_common_comp_BASE=C:/lcb/AutoECMControl/ML/ml_apps


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

clean :: ros_ml_server-clean glad-clean app_framework-clean

$(MLSDK)/tools/mabu/data/configs/debug.config : 

$(MLSDK)/tools/mabu/data/options/debug/on.option : 

$(MLSDK)/tools/mabu/data/options/magicleap.option : 

$(MLSDK)/tools/mabu/data/options/optimize/off.option : 

$(MLSDK)/tools/mabu/data/options/package/debuggable/on.option : 

$(MLSDK)/tools/mabu/data/options/runtime/shared.option : 

$(MLSDK)/tools/mabu/data/options/warn/on.option : 

C:/lcb/AutoECMControl/ML/ml_apps/samples_common.comp : 

$(MLSDK)/tools/mabu/data/components/stdc++.comp : 

$(MLSDK)/tools/mabu/data/options/standard-c++/11.option : 

C:/lcb/AutoECMControl/ML/app_framework/common.comp : 

$(MLSDK)/.metadata/components/ml_sdk.comp : 

$(MLSDK)/.metadata/components/ml_sdk_common.comp : 

$(MLSDK)/tools/mabu/data/components/OpenGL.comp : 

C:/lcb/AutoECMControl/ML/app_framework/ext/assimp.comp : 

C:/lcb/AutoECMControl/ML/app_framework/ext/gflags.comp : 

C:/lcb/AutoECMControl/ML/app_framework/ext/glm.comp : 

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

-make-directories : C:/lcb/AutoECMControl/ML/app_framework/.out/debug_lumin_clang-3.8_aarch64 C:/lcb/AutoECMControl/ML/app_framework/.out/debug_lumin_clang-3.8_aarch64/bin C:/lcb/AutoECMControl/ML/app_framework/ext/.out/debug_lumin_clang-3.8_aarch64 C:/lcb/AutoECMControl/ML/app_framework/ext/.out/debug_lumin_clang-3.8_aarch64/bin C:/lcb/AutoECMControl/ML/app_framework/ext/.out/debug_lumin_clang-3.8_aarch64/obj.glad/glad/src C:/lcb/AutoECMControl/ML/ml_apps/BUILD/debug_lumin_clang-3.8_aarch64 C:/lcb/AutoECMControl/ML/ml_apps/BUILD/debug_lumin_clang-3.8_aarch64/bin C:/lcb/AutoECMControl/ML/ml_apps/BUILD/debug_lumin_clang-3.8_aarch64/data/res/shaders C:/lcb/AutoECMControl/ML/ml_apps/BUILD/debug_lumin_clang-3.8_aarch64/obj.ros_ml_server/decoco/src C:/lcb/AutoECMControl/ML/ml_apps/BUILD/debug_lumin_clang-3.8_aarch64/obj.ros_ml_server/decoco/src/zlib C:/lcb/AutoECMControl/ML/ml_apps/BUILD/debug_lumin_clang-3.8_aarch64/obj.ros_ml_server/src

C:/lcb/AutoECMControl/ML/app_framework/.out/debug_lumin_clang-3.8_aarch64 : 
	$(ECHO) @mkdir -p C:/lcb/AutoECMControl/ML/app_framework/.out/debug_lumin_clang-3.8_aarch64

C:/lcb/AutoECMControl/ML/app_framework/.out/debug_lumin_clang-3.8_aarch64/bin : 
	$(ECHO) @mkdir -p C:/lcb/AutoECMControl/ML/app_framework/.out/debug_lumin_clang-3.8_aarch64/bin

C:/lcb/AutoECMControl/ML/app_framework/ext/.out/debug_lumin_clang-3.8_aarch64 : 
	$(ECHO) @mkdir -p C:/lcb/AutoECMControl/ML/app_framework/ext/.out/debug_lumin_clang-3.8_aarch64

C:/lcb/AutoECMControl/ML/app_framework/ext/.out/debug_lumin_clang-3.8_aarch64/bin : 
	$(ECHO) @mkdir -p C:/lcb/AutoECMControl/ML/app_framework/ext/.out/debug_lumin_clang-3.8_aarch64/bin

C:/lcb/AutoECMControl/ML/app_framework/ext/.out/debug_lumin_clang-3.8_aarch64/obj.glad/glad/src : 
	$(ECHO) @mkdir -p C:/lcb/AutoECMControl/ML/app_framework/ext/.out/debug_lumin_clang-3.8_aarch64/obj.glad/glad/src

C:/lcb/AutoECMControl/ML/ml_apps/BUILD/debug_lumin_clang-3.8_aarch64 : 
	$(ECHO) @mkdir -p C:/lcb/AutoECMControl/ML/ml_apps/BUILD/debug_lumin_clang-3.8_aarch64

C:/lcb/AutoECMControl/ML/ml_apps/BUILD/debug_lumin_clang-3.8_aarch64/bin : 
	$(ECHO) @mkdir -p C:/lcb/AutoECMControl/ML/ml_apps/BUILD/debug_lumin_clang-3.8_aarch64/bin

C:/lcb/AutoECMControl/ML/ml_apps/BUILD/debug_lumin_clang-3.8_aarch64/data/res/shaders : 
	$(ECHO) @mkdir -p C:/lcb/AutoECMControl/ML/ml_apps/BUILD/debug_lumin_clang-3.8_aarch64/data/res/shaders

C:/lcb/AutoECMControl/ML/ml_apps/BUILD/debug_lumin_clang-3.8_aarch64/obj.ros_ml_server/decoco/src : 
	$(ECHO) @mkdir -p C:/lcb/AutoECMControl/ML/ml_apps/BUILD/debug_lumin_clang-3.8_aarch64/obj.ros_ml_server/decoco/src

C:/lcb/AutoECMControl/ML/ml_apps/BUILD/debug_lumin_clang-3.8_aarch64/obj.ros_ml_server/decoco/src/zlib : 
	$(ECHO) @mkdir -p C:/lcb/AutoECMControl/ML/ml_apps/BUILD/debug_lumin_clang-3.8_aarch64/obj.ros_ml_server/decoco/src/zlib

C:/lcb/AutoECMControl/ML/ml_apps/BUILD/debug_lumin_clang-3.8_aarch64/obj.ros_ml_server/src : 
	$(ECHO) @mkdir -p C:/lcb/AutoECMControl/ML/ml_apps/BUILD/debug_lumin_clang-3.8_aarch64/obj.ros_ml_server/src

include $(ros_ml_server_OUTPUT)/ros_ml_server.mk
include $(glad_OUTPUT)/glad.mk
include $(app_framework_OUTPUT)/app_framework.mk
build :  | ros_ml_server-all glad-all app_framework-all

