# Generated Makefile -- DO NOT EDIT!

AR=C:/Users/cshre/MagicLeap/mlsdk/v0.26.0/tools/toolchains/bin/aarch64-linux-android-gcc-ar.exe
HOST=win64
RM=rm
SPEC=debug_lumin_clang-3.8_aarch64
TOUCH=touch
glew_ARFLAGS=
glew_BASE=C:/lcb/Learnings/ML/gl_eye_tracking2
glew_OUTPUT=$(glew_BASE)/.out/$(SPEC)

$(glew_OUTPUT)/libglew.a :  $(glew_BASE)/glew.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/gl_eye_tracking2/common.comp
	$(INFO) \[glew\]\ Linking\ static\ library\ 'libglew.a'...
	$(ECHO) $(RM) -f $(glew_OUTPUT)/libglew.a
	$(ECHO) cd $(glew_OUTPUT) && $(AR) crs libglew.a @$(glew_OUTPUT)/libglew.a.args $(glew_ARFLAGS)
	$(ECHO) $(TOUCH) $(glew_OUTPUT)/libglew.a


glew-clean :: 
	$(INFO) Cleaning\ glew...
	$(ECHO) $(RM) -rf $(glew_OUTPUT)/libglew.a $(glew_OUTPUT)/glew.sym $(glew_OUTPUT)/bin/libc++_shared.so

glew-all :: -make-directories $(glew_OUTPUT)/libglew.a

