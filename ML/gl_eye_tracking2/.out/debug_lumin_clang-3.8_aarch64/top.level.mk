# Generated Makefile -- DO NOT EDIT!

HOST=win64
SPEC=debug_lumin_clang-3.8_aarch64
asio_BASE=C:/lcb/Learnings/ML/gl_eye_tracking2
asio_OUTPUT=$(asio_BASE)/.out/$(SPEC)
gl_eye_tracking2_OUTPUT=$(samples_common_comp_BASE)/BUILD/$(SPEC)
samples_common_comp_BASE=C:/lcb/Learnings/ML/gl_eye_tracking2


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

clean :: asio-clean gl_eye_tracking2-clean

$(MLSDK)/tools/mabu/data/configs/debug.config : 

$(MLSDK)/tools/mabu/data/options/debug/on.option : 

$(MLSDK)/tools/mabu/data/options/magicleap.option : 

$(MLSDK)/tools/mabu/data/options/optimize/off.option : 

$(MLSDK)/tools/mabu/data/options/package/debuggable/on.option : 

$(MLSDK)/tools/mabu/data/options/runtime/shared.option : 

$(MLSDK)/tools/mabu/data/options/standard-c++/17.option : 

$(MLSDK)/tools/mabu/data/options/warn/on.option : 

$(MLSDK)/.metadata/components/ml_sdk.comp : 

$(MLSDK)/.metadata/components/ml_sdk_common.comp : 

$(MLSDK)/tools/mabu/data/components/OpenGL.comp : 

$(MLSDK)/tools/mabu/data/components/stdc++.comp : 

$(MLSDK)/tools/mabu/data/options/exceptions/on.option : 

C:/lcb/Learnings/ML/gl_eye_tracking2/samples_common.comp : 

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

-make-directories : C:/lcb/Learnings/ML/gl_eye_tracking2/.out/debug_lumin_clang-3.8_aarch64 C:/lcb/Learnings/ML/gl_eye_tracking2/BUILD/debug_lumin_clang-3.8_aarch64 C:/lcb/Learnings/ML/gl_eye_tracking2/BUILD/debug_lumin_clang-3.8_aarch64/bin C:/lcb/Learnings/ML/gl_eye_tracking2/BUILD/debug_lumin_clang-3.8_aarch64/data/res/shaders C:/lcb/Learnings/ML/gl_eye_tracking2/BUILD/debug_lumin_clang-3.8_aarch64/data/res/texture C:/lcb/Learnings/ML/gl_eye_tracking2/BUILD/debug_lumin_clang-3.8_aarch64/obj.gl_eye_tracking2/src

C:/lcb/Learnings/ML/gl_eye_tracking2/.out/debug_lumin_clang-3.8_aarch64 : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/gl_eye_tracking2/.out/debug_lumin_clang-3.8_aarch64

C:/lcb/Learnings/ML/gl_eye_tracking2/BUILD/debug_lumin_clang-3.8_aarch64 : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/gl_eye_tracking2/BUILD/debug_lumin_clang-3.8_aarch64

C:/lcb/Learnings/ML/gl_eye_tracking2/BUILD/debug_lumin_clang-3.8_aarch64/bin : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/gl_eye_tracking2/BUILD/debug_lumin_clang-3.8_aarch64/bin

C:/lcb/Learnings/ML/gl_eye_tracking2/BUILD/debug_lumin_clang-3.8_aarch64/data/res/shaders : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/gl_eye_tracking2/BUILD/debug_lumin_clang-3.8_aarch64/data/res/shaders

C:/lcb/Learnings/ML/gl_eye_tracking2/BUILD/debug_lumin_clang-3.8_aarch64/data/res/texture : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/gl_eye_tracking2/BUILD/debug_lumin_clang-3.8_aarch64/data/res/texture

C:/lcb/Learnings/ML/gl_eye_tracking2/BUILD/debug_lumin_clang-3.8_aarch64/obj.gl_eye_tracking2/src : 
	$(ECHO) @mkdir -p C:/lcb/Learnings/ML/gl_eye_tracking2/BUILD/debug_lumin_clang-3.8_aarch64/obj.gl_eye_tracking2/src

include $(asio_OUTPUT)/asio.mk
include $(gl_eye_tracking2_OUTPUT)/gl_eye_tracking2.mk
build :  | asio-all gl_eye_tracking2-all

