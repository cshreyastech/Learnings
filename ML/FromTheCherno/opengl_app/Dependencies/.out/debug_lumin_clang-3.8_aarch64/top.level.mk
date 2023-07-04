# Generated Makefile -- DO NOT EDIT!

HOST=win64
SPEC=debug_lumin_clang-3.8_aarch64
opengl_app_BASE=C:/lcb/Learnings/ML/FromTheCherno/opengl_app
opengl_app_OUTPUT=$(opengl_app_BASE)/.out/$(SPEC)
stb_image_BASE=C:/lcb/Learnings/ML/FromTheCherno/opengl_app/Dependencies
stb_image_OUTPUT=$(stb_image_BASE)/.out/$(SPEC)


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

clean :: stb_image-clean opengl_app-clean

$(MLSDK)/tools/mabu/data/components/stdc++.comp : 

$(MLSDK)/tools/mabu/data/configs/debug.config : 

$(MLSDK)/tools/mabu/data/options/debug/on.option : 

$(MLSDK)/tools/mabu/data/options/magicleap.option : 

$(MLSDK)/tools/mabu/data/options/optimize/off.option : 

$(MLSDK)/tools/mabu/data/options/package/debuggable/on.option : 

$(MLSDK)/tools/mabu/data/options/runtime/shared.option : 

$(MLSDK)/tools/mabu/data/options/warn/on.option : 

$(MLSDK)/.metadata/components/ml_sdk.comp : 

$(MLSDK)/.metadata/components/ml_sdk_common.comp : 

$(MLSDK)/tools/mabu/data/components/OpenGL.comp : 

$(MLSDK)/tools/mabu/data/options/exceptions/on.option : 

$(MLSDK)/tools/mabu/data/options/standard-c++/17.option : 

C:/lcb/Learnings/ML/FromTheCherno/opengl_app/Dependencies/glm.comp : 

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

-make-directories : C:/lcb/Learnings/ML/FromTheCherno/opengl_app/.out/debug_lumin_clang-3.8_aarch64 C:/lcb/Learnings/ML/FromTheCherno/opengl_app/.out/debug_lumin_clang-3.8_aarch64/bin C:/lcb/Learnings/ML/FromTheCherno/opengl_app/.out/debug_lumin_clang-3.8_aarch64/obj.opengl_app/src C:/lcb/Learnings/ML/FromTheCherno/opengl_app/Dependencies/.out/debug_lumin_clang-3.8_aarch64 C:/lcb/Learnings/ML/FromTheCherno/opengl_app/Dependencies/.out/debug_lumin_clang-3.8_aarch64/bin C:/lcb/Learnings/ML/FromTheCherno/opengl_app/Dependencies/.out/debug_lumin_clang-3.8_aarch64/obj.stb_image/stb_image/stb_image

C:/lcb/Learnings/ML/FromTheCherno/opengl_app/.out/debug_lumin_clang-3.8_aarch64 : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/FromTheCherno/opengl_app/.out/debug_lumin_clang-3.8_aarch64

C:/lcb/Learnings/ML/FromTheCherno/opengl_app/.out/debug_lumin_clang-3.8_aarch64/bin : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/FromTheCherno/opengl_app/.out/debug_lumin_clang-3.8_aarch64/bin

C:/lcb/Learnings/ML/FromTheCherno/opengl_app/.out/debug_lumin_clang-3.8_aarch64/obj.opengl_app/src : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/FromTheCherno/opengl_app/.out/debug_lumin_clang-3.8_aarch64/obj.opengl_app/src

C:/lcb/Learnings/ML/FromTheCherno/opengl_app/Dependencies/.out/debug_lumin_clang-3.8_aarch64 : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/FromTheCherno/opengl_app/Dependencies/.out/debug_lumin_clang-3.8_aarch64

C:/lcb/Learnings/ML/FromTheCherno/opengl_app/Dependencies/.out/debug_lumin_clang-3.8_aarch64/bin : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/FromTheCherno/opengl_app/Dependencies/.out/debug_lumin_clang-3.8_aarch64/bin

C:/lcb/Learnings/ML/FromTheCherno/opengl_app/Dependencies/.out/debug_lumin_clang-3.8_aarch64/obj.stb_image/stb_image/stb_image : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/FromTheCherno/opengl_app/Dependencies/.out/debug_lumin_clang-3.8_aarch64/obj.stb_image/stb_image/stb_image

include $(stb_image_OUTPUT)/stb_image.mk
include $(opengl_app_OUTPUT)/opengl_app.mk
build :  | stb_image-all opengl_app-all

