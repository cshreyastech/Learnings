# Generated Makefile -- DO NOT EDIT!

AR=C:/Users/cshre/MagicLeap/mlsdk/v0.26.0/tools/toolchains/bin/aarch64-linux-android-gcc-ar.exe
COMPILER_PREFIX=
CXX=C:/Users/cshre/MagicLeap/mlsdk/v0.26.0/tools/toolchains/bin/aarch64-linux-android-clang++
HOST=win64
RM=rm
SPEC=debug_lumin_clang-3.8_aarch64
TOUCH=touch
stb_image_ARFLAGS=
stb_image_BASE=C:/lcb/Learnings/ML/FromTheCherno/opengl_app/Dependencies
stb_image_CPPFLAGS=-I$(stb_image_BASE)/stb_image/
stb_image_CXXFLAGS=--sysroot=$(MLSDK)/lumin -march=armv8-a -mcpu=cortex-a57+crypto -fpic -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -Wa,--noexecstack -Wformat -Werror=format-security -Wno-invalid-command-line-argument -Wno-unused-command-line-argument -g -fno-limit-debug-info -O0 -nostdinc++ -I$(MLSDK)/lumin/stl/libc++/include
stb_image_OUTPUT=$(stb_image_BASE)/.out/$(SPEC)

$(stb_image_OUTPUT)/libstb_image.a : $(stb_image_OUTPUT)/obj.stb_image/stb_image/stb_image/stb_image.cpp.o $(stb_image_BASE)/stb_image.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/warn/on.option
	$(INFO) \[stb_image\]\ Linking\ static\ library\ 'libstb_image.a'...
	$(ECHO) $(RM) -f $(stb_image_OUTPUT)/libstb_image.a
	$(ECHO) cd $(stb_image_OUTPUT) && $(AR) crs libstb_image.a obj.stb_image/stb_image/stb_image/stb_image.cpp.o $(stb_image_ARFLAGS)
	$(ECHO) $(TOUCH) $(stb_image_OUTPUT)/libstb_image.a

$(stb_image_OUTPUT)/obj.stb_image/stb_image/stb_image/stb_image.cpp.o : $(stb_image_BASE)/stb_image/stb_image/stb_image.cpp $(stb_image_BASE)/stb_image.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/warn/on.option
	$(INFO) \[stb_image\]\ Compiling\ 'stb_image.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(stb_image_BASE)/stb_image/stb_image/stb_image.cpp -o $(stb_image_OUTPUT)/obj.stb_image/stb_image/stb_image/stb_image.cpp.o -MD -MP -MF $(stb_image_OUTPUT)/obj.stb_image/stb_image/stb_image/stb_image.cpp.d $(stb_image_CPPFLAGS) $(stb_image_CXXFLAGS)
	$(ECHO) echo $(stb_image_BASE)/stb_image/stb_image/stb_image.cpp : >> $(stb_image_OUTPUT)/obj.stb_image/stb_image/stb_image/stb_image.cpp.d

-include $(stb_image_OUTPUT)/obj.stb_image/stb_image/stb_image/stb_image.cpp.d

stb_image-clean :: 
	$(INFO) Cleaning\ stb_image...
	$(ECHO) $(RM) -rf $(stb_image_OUTPUT)/libstb_image.a $(stb_image_OUTPUT)/stb_image.sym $(stb_image_OUTPUT)/obj.stb_image/stb_image/stb_image/stb_image.cpp.o $(stb_image_OUTPUT)/obj.stb_image/stb_image/stb_image/stb_image.cpp.d
	$(ECHO) $(RM) -rf $(stb_image_OUTPUT)/bin/libc++_shared.so

stb_image-all :: -make-directories $(stb_image_OUTPUT)/libstb_image.a

