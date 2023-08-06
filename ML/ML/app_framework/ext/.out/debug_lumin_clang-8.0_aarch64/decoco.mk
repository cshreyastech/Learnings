# Generated Makefile -- DO NOT EDIT!

AR=C:/Users/cshre/MagicLeap/mlsdk/v0.26.0/tools/toolchains/llvm-8/bin/aarch64-linux-android-gcc-ar.exe
COMPILER_PREFIX=
CXX=C:/Users/cshre/MagicLeap/mlsdk/v0.26.0/tools/toolchains/llvm-8/bin/aarch64-linux-android-clang++
HOST=win64
RM=rm
SPEC=debug_lumin_clang-8.0_aarch64
TOUCH=touch
decoco_ARFLAGS=
decoco_BASE=C:/lcb/AutoECMControl/ML/app_framework/ext
decoco_CPPFLAGS=-I$(decoco_BASE)/decoco/include -I$(decoco_BASE)/decoco/src -DML_LUMIN
decoco_CXXFLAGS=--sysroot=$(MLSDK)/lumin/sysroot -march=armv8-a -mcpu=cortex-a57+crypto -fpic -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -Wa,--noexecstack -Wformat -Werror=format-security -Wno-invalid-command-line-argument -Wno-unused-command-line-argument -g -fno-limit-debug-info -O0 -fexceptions -nostdinc++ -I$(MLSDK)/lumin/stl/libc++-8/include -std=c++17
decoco_OUTPUT=$(decoco_BASE)/.out/$(SPEC)

$(decoco_OUTPUT)/libdecoco.a : $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/adler32.cpp.o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/crc32.cpp.o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/deflate.cpp.o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inffast.cpp.o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inflate.cpp.o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inftrees.cpp.o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/trees.cpp.o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/zutil.cpp.o $(decoco_OUTPUT)/obj.decoco/decoco/src/shared.cpp.o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib.cpp.o $(decoco_BASE)/decoco.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/AutoECMControl/ML/app_framework/common.comp
	$(INFO) \[decoco\]\ Linking\ static\ library\ 'libdecoco.a'...
	$(ECHO) $(RM) -f $(decoco_OUTPUT)/libdecoco.a
	$(ECHO) cd $(decoco_OUTPUT) && $(AR) crs libdecoco.a obj.decoco/decoco/src/zlib/adler32.cpp.o obj.decoco/decoco/src/zlib/crc32.cpp.o obj.decoco/decoco/src/zlib/deflate.cpp.o obj.decoco/decoco/src/zlib/inffast.cpp.o obj.decoco/decoco/src/zlib/inflate.cpp.o obj.decoco/decoco/src/zlib/inftrees.cpp.o obj.decoco/decoco/src/zlib/trees.cpp.o obj.decoco/decoco/src/zlib/zutil.cpp.o obj.decoco/decoco/src/shared.cpp.o obj.decoco/decoco/src/zlib.cpp.o $(decoco_ARFLAGS)
	$(ECHO) $(TOUCH) $(decoco_OUTPUT)/libdecoco.a

$(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/adler32.cpp.o : $(decoco_BASE)/decoco/src/zlib/adler32.cpp $(decoco_BASE)/decoco.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/AutoECMControl/ML/app_framework/common.comp
	$(INFO) \[decoco\]\ Compiling\ 'adler32.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(decoco_BASE)/decoco/src/zlib/adler32.cpp -o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/adler32.cpp.o -MD -MP -MF $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/adler32.cpp.d $(decoco_CPPFLAGS) $(decoco_CXXFLAGS)
	$(ECHO) echo $(decoco_BASE)/decoco/src/zlib/adler32.cpp : >> $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/adler32.cpp.d

-include $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/adler32.cpp.d
$(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/crc32.cpp.o : $(decoco_BASE)/decoco/src/zlib/crc32.cpp $(decoco_BASE)/decoco.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/AutoECMControl/ML/app_framework/common.comp
	$(INFO) \[decoco\]\ Compiling\ 'crc32.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(decoco_BASE)/decoco/src/zlib/crc32.cpp -o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/crc32.cpp.o -MD -MP -MF $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/crc32.cpp.d $(decoco_CPPFLAGS) $(decoco_CXXFLAGS)
	$(ECHO) echo $(decoco_BASE)/decoco/src/zlib/crc32.cpp : >> $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/crc32.cpp.d

-include $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/crc32.cpp.d
$(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/deflate.cpp.o : $(decoco_BASE)/decoco/src/zlib/deflate.cpp $(decoco_BASE)/decoco.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/AutoECMControl/ML/app_framework/common.comp
	$(INFO) \[decoco\]\ Compiling\ 'deflate.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(decoco_BASE)/decoco/src/zlib/deflate.cpp -o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/deflate.cpp.o -MD -MP -MF $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/deflate.cpp.d $(decoco_CPPFLAGS) $(decoco_CXXFLAGS)
	$(ECHO) echo $(decoco_BASE)/decoco/src/zlib/deflate.cpp : >> $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/deflate.cpp.d

-include $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/deflate.cpp.d
$(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inffast.cpp.o : $(decoco_BASE)/decoco/src/zlib/inffast.cpp $(decoco_BASE)/decoco.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/AutoECMControl/ML/app_framework/common.comp
	$(INFO) \[decoco\]\ Compiling\ 'inffast.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(decoco_BASE)/decoco/src/zlib/inffast.cpp -o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inffast.cpp.o -MD -MP -MF $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inffast.cpp.d $(decoco_CPPFLAGS) $(decoco_CXXFLAGS)
	$(ECHO) echo $(decoco_BASE)/decoco/src/zlib/inffast.cpp : >> $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inffast.cpp.d

-include $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inffast.cpp.d
$(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inflate.cpp.o : $(decoco_BASE)/decoco/src/zlib/inflate.cpp $(decoco_BASE)/decoco.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/AutoECMControl/ML/app_framework/common.comp
	$(INFO) \[decoco\]\ Compiling\ 'inflate.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(decoco_BASE)/decoco/src/zlib/inflate.cpp -o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inflate.cpp.o -MD -MP -MF $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inflate.cpp.d $(decoco_CPPFLAGS) $(decoco_CXXFLAGS)
	$(ECHO) echo $(decoco_BASE)/decoco/src/zlib/inflate.cpp : >> $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inflate.cpp.d

-include $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inflate.cpp.d
$(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inftrees.cpp.o : $(decoco_BASE)/decoco/src/zlib/inftrees.cpp $(decoco_BASE)/decoco.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/AutoECMControl/ML/app_framework/common.comp
	$(INFO) \[decoco\]\ Compiling\ 'inftrees.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(decoco_BASE)/decoco/src/zlib/inftrees.cpp -o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inftrees.cpp.o -MD -MP -MF $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inftrees.cpp.d $(decoco_CPPFLAGS) $(decoco_CXXFLAGS)
	$(ECHO) echo $(decoco_BASE)/decoco/src/zlib/inftrees.cpp : >> $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inftrees.cpp.d

-include $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inftrees.cpp.d
$(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/trees.cpp.o : $(decoco_BASE)/decoco/src/zlib/trees.cpp $(decoco_BASE)/decoco.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/AutoECMControl/ML/app_framework/common.comp
	$(INFO) \[decoco\]\ Compiling\ 'trees.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(decoco_BASE)/decoco/src/zlib/trees.cpp -o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/trees.cpp.o -MD -MP -MF $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/trees.cpp.d $(decoco_CPPFLAGS) $(decoco_CXXFLAGS)
	$(ECHO) echo $(decoco_BASE)/decoco/src/zlib/trees.cpp : >> $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/trees.cpp.d

-include $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/trees.cpp.d
$(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/zutil.cpp.o : $(decoco_BASE)/decoco/src/zlib/zutil.cpp $(decoco_BASE)/decoco.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/AutoECMControl/ML/app_framework/common.comp
	$(INFO) \[decoco\]\ Compiling\ 'zutil.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(decoco_BASE)/decoco/src/zlib/zutil.cpp -o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/zutil.cpp.o -MD -MP -MF $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/zutil.cpp.d $(decoco_CPPFLAGS) $(decoco_CXXFLAGS)
	$(ECHO) echo $(decoco_BASE)/decoco/src/zlib/zutil.cpp : >> $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/zutil.cpp.d

-include $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/zutil.cpp.d
$(decoco_OUTPUT)/obj.decoco/decoco/src/shared.cpp.o : $(decoco_BASE)/decoco/src/shared.cpp $(decoco_BASE)/decoco.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/AutoECMControl/ML/app_framework/common.comp
	$(INFO) \[decoco\]\ Compiling\ 'shared.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(decoco_BASE)/decoco/src/shared.cpp -o $(decoco_OUTPUT)/obj.decoco/decoco/src/shared.cpp.o -MD -MP -MF $(decoco_OUTPUT)/obj.decoco/decoco/src/shared.cpp.d $(decoco_CPPFLAGS) $(decoco_CXXFLAGS)
	$(ECHO) echo $(decoco_BASE)/decoco/src/shared.cpp : >> $(decoco_OUTPUT)/obj.decoco/decoco/src/shared.cpp.d

-include $(decoco_OUTPUT)/obj.decoco/decoco/src/shared.cpp.d
$(decoco_OUTPUT)/obj.decoco/decoco/src/zlib.cpp.o : $(decoco_BASE)/decoco/src/zlib.cpp $(decoco_BASE)/decoco.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/AutoECMControl/ML/app_framework/common.comp
	$(INFO) \[decoco\]\ Compiling\ 'zlib.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(decoco_BASE)/decoco/src/zlib.cpp -o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib.cpp.o -MD -MP -MF $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib.cpp.d $(decoco_CPPFLAGS) $(decoco_CXXFLAGS)
	$(ECHO) echo $(decoco_BASE)/decoco/src/zlib.cpp : >> $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib.cpp.d

-include $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib.cpp.d

decoco-clean :: 
	$(INFO) Cleaning\ decoco...
	$(ECHO) $(RM) -rf $(decoco_OUTPUT)/libdecoco.a $(decoco_OUTPUT)/decoco.sym $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/adler32.cpp.o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/adler32.cpp.d $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/crc32.cpp.o
	$(ECHO) $(RM) -rf $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/crc32.cpp.d $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/deflate.cpp.o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/deflate.cpp.d $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inffast.cpp.o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inffast.cpp.d
	$(ECHO) $(RM) -rf $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inflate.cpp.o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inflate.cpp.d $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inftrees.cpp.o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/inftrees.cpp.d $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/trees.cpp.o
	$(ECHO) $(RM) -rf $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/trees.cpp.d $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/zutil.cpp.o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib/zutil.cpp.d $(decoco_OUTPUT)/obj.decoco/decoco/src/shared.cpp.o $(decoco_OUTPUT)/obj.decoco/decoco/src/shared.cpp.d
	$(ECHO) $(RM) -rf $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib.cpp.o $(decoco_OUTPUT)/obj.decoco/decoco/src/zlib.cpp.d $(decoco_OUTPUT)/bin/libc++_shared.so

decoco-all :: -make-directories $(decoco_OUTPUT)/libdecoco.a

