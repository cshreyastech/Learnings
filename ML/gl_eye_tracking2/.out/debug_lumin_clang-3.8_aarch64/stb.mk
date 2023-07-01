# Generated Makefile -- DO NOT EDIT!

AR=C:/Users/cshre/MagicLeap/mlsdk/v0.26.0/tools/toolchains/bin/aarch64-linux-android-gcc-ar.exe
COMPILER_PREFIX=
CXX=C:/Users/cshre/MagicLeap/mlsdk/v0.26.0/tools/toolchains/bin/aarch64-linux-android-clang++
HOST=win64
RM=rm
SPEC=debug_lumin_clang-3.8_aarch64
TOUCH=touch
stb_ARFLAGS=
stb_BASE=C:/lcb/Learnings/ML/gl_eye_tracking2
stb_CPPFLAGS=-I$(stb_BASE)/stb-master/ -DML_LUMIN
stb_CXXFLAGS=--sysroot=$(MLSDK)/lumin -march=armv8-a -mcpu=cortex-a57+crypto -fpic -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -Wa,--noexecstack -Wformat -Werror=format-security -Wno-invalid-command-line-argument -Wno-unused-command-line-argument -g -fno-limit-debug-info -O0 -std=c++1z -fexceptions -nostdinc++ -I$(MLSDK)/lumin/stl/libc++/include -Wno-parentheses-equality
stb_OUTPUT=$(stb_BASE)/.out/$(SPEC)

$(stb_OUTPUT)/libstb.a : $(stb_OUTPUT)/obj.stb/stb_lib/stblib.cpp.o $(stb_BASE)/stb.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/gl_eye_tracking2/common.comp
	$(INFO) \[stb\]\ Linking\ static\ library\ 'libstb.a'...
	$(ECHO) $(RM) -f $(stb_OUTPUT)/libstb.a
	$(ECHO) cd $(stb_OUTPUT) && $(AR) crs libstb.a obj.stb/stb_lib/stblib.cpp.o $(stb_ARFLAGS)
	$(ECHO) $(TOUCH) $(stb_OUTPUT)/libstb.a

$(stb_OUTPUT)/obj.stb/stb_lib/stblib.cpp.o : $(stb_BASE)/stb_lib/stblib.cpp $(stb_BASE)/stb.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/gl_eye_tracking2/common.comp
	$(INFO) \[stb\]\ Compiling\ 'stblib.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(stb_BASE)/stb_lib/stblib.cpp -o $(stb_OUTPUT)/obj.stb/stb_lib/stblib.cpp.o -MD -MP -MF $(stb_OUTPUT)/obj.stb/stb_lib/stblib.cpp.d $(stb_CPPFLAGS) $(stb_CXXFLAGS)
	$(ECHO) echo $(stb_BASE)/stb_lib/stblib.cpp : >> $(stb_OUTPUT)/obj.stb/stb_lib/stblib.cpp.d

-include $(stb_OUTPUT)/obj.stb/stb_lib/stblib.cpp.d

stb-clean :: 
	$(INFO) Cleaning\ stb...
	$(ECHO) $(RM) -rf $(stb_OUTPUT)/libstb.a $(stb_OUTPUT)/stb.sym $(stb_OUTPUT)/obj.stb/stb_lib/stblib.cpp.o $(stb_OUTPUT)/obj.stb/stb_lib/stblib.cpp.d $(stb_OUTPUT)/bin/libc++_shared.so

stb-all :: -make-directories $(stb_OUTPUT)/libstb.a

