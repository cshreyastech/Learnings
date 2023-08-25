# Generated Makefile -- DO NOT EDIT!

AR=C:/Users/cshre/MagicLeap/mlsdk/v0.26.0/tools/toolchains/llvm-8/bin/aarch64-linux-android-gcc-ar.exe
COMPILER_PREFIX=
CXX=C:/Users/cshre/MagicLeap/mlsdk/v0.26.0/tools/toolchains/llvm-8/bin/aarch64-linux-android-clang++
HOST=win64
RM=rm
SPEC=debug_lumin_clang-8.0_aarch64
TOUCH=touch
snappy_ARFLAGS=
snappy_BASE=C:/lcb/Learnings/ML/ML/app_framework/ext
snappy_CPPFLAGS=-I$(snappy_BASE)/snappy/ -DML_LUMIN
snappy_CXXFLAGS=--sysroot=$(MLSDK)/lumin/sysroot -march=armv8-a -mcpu=cortex-a57+crypto -fpic -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -Wa,--noexecstack -Wformat -Werror=format-security -Wno-invalid-command-line-argument -Wno-unused-command-line-argument -g -fno-limit-debug-info -O0 -nostdinc++ -I$(MLSDK)/lumin/stl/libc++-8/include -std=c++17 -fexceptions
snappy_OUTPUT=$(snappy_BASE)/.out/$(SPEC)

$(snappy_OUTPUT)/libsnappy.a : $(snappy_OUTPUT)/obj.snappy/snappy/snappy-c.cc.o $(snappy_OUTPUT)/obj.snappy/snappy/snappy-sinksource.cc.o $(snappy_OUTPUT)/obj.snappy/snappy/snappy-stubs-internal.cc.o $(snappy_OUTPUT)/obj.snappy/snappy/snappy.cc.o $(snappy_BASE)/snappy.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/ML/app_framework/common.comp
	$(INFO) \[snappy\]\ Linking\ static\ library\ 'libsnappy.a'...
	$(ECHO) $(RM) -f $(snappy_OUTPUT)/libsnappy.a
	$(ECHO) cd $(snappy_OUTPUT) && $(AR) crs libsnappy.a obj.snappy/snappy/snappy-c.cc.o obj.snappy/snappy/snappy-sinksource.cc.o obj.snappy/snappy/snappy-stubs-internal.cc.o obj.snappy/snappy/snappy.cc.o $(snappy_ARFLAGS)
	$(ECHO) $(TOUCH) $(snappy_OUTPUT)/libsnappy.a

$(snappy_OUTPUT)/obj.snappy/snappy/snappy-c.cc.o : $(snappy_BASE)/snappy/snappy-c.cc $(snappy_BASE)/snappy.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/ML/app_framework/common.comp
	$(INFO) \[snappy\]\ Compiling\ 'snappy-c.cc'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(snappy_BASE)/snappy/snappy-c.cc -o $(snappy_OUTPUT)/obj.snappy/snappy/snappy-c.cc.o -MD -MP -MF $(snappy_OUTPUT)/obj.snappy/snappy/snappy-c.cc.d $(snappy_CPPFLAGS) $(snappy_CXXFLAGS)
	$(ECHO) echo $(snappy_BASE)/snappy/snappy-c.cc : >> $(snappy_OUTPUT)/obj.snappy/snappy/snappy-c.cc.d

-include $(snappy_OUTPUT)/obj.snappy/snappy/snappy-c.cc.d
$(snappy_OUTPUT)/obj.snappy/snappy/snappy-sinksource.cc.o : $(snappy_BASE)/snappy/snappy-sinksource.cc $(snappy_BASE)/snappy.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/ML/app_framework/common.comp
	$(INFO) \[snappy\]\ Compiling\ 'snappy-sinksource.cc'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(snappy_BASE)/snappy/snappy-sinksource.cc -o $(snappy_OUTPUT)/obj.snappy/snappy/snappy-sinksource.cc.o -MD -MP -MF $(snappy_OUTPUT)/obj.snappy/snappy/snappy-sinksource.cc.d $(snappy_CPPFLAGS) $(snappy_CXXFLAGS)
	$(ECHO) echo $(snappy_BASE)/snappy/snappy-sinksource.cc : >> $(snappy_OUTPUT)/obj.snappy/snappy/snappy-sinksource.cc.d

-include $(snappy_OUTPUT)/obj.snappy/snappy/snappy-sinksource.cc.d
$(snappy_OUTPUT)/obj.snappy/snappy/snappy-stubs-internal.cc.o : $(snappy_BASE)/snappy/snappy-stubs-internal.cc $(snappy_BASE)/snappy.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/ML/app_framework/common.comp
	$(INFO) \[snappy\]\ Compiling\ 'snappy-stubs-internal.cc'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(snappy_BASE)/snappy/snappy-stubs-internal.cc -o $(snappy_OUTPUT)/obj.snappy/snappy/snappy-stubs-internal.cc.o -MD -MP -MF $(snappy_OUTPUT)/obj.snappy/snappy/snappy-stubs-internal.cc.d $(snappy_CPPFLAGS) $(snappy_CXXFLAGS)
	$(ECHO) echo $(snappy_BASE)/snappy/snappy-stubs-internal.cc : >> $(snappy_OUTPUT)/obj.snappy/snappy/snappy-stubs-internal.cc.d

-include $(snappy_OUTPUT)/obj.snappy/snappy/snappy-stubs-internal.cc.d
$(snappy_OUTPUT)/obj.snappy/snappy/snappy.cc.o : $(snappy_BASE)/snappy/snappy.cc $(snappy_BASE)/snappy.mabu $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/ML/app_framework/common.comp
	$(INFO) \[snappy\]\ Compiling\ 'snappy.cc'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(snappy_BASE)/snappy/snappy.cc -o $(snappy_OUTPUT)/obj.snappy/snappy/snappy.cc.o -MD -MP -MF $(snappy_OUTPUT)/obj.snappy/snappy/snappy.cc.d $(snappy_CPPFLAGS) $(snappy_CXXFLAGS)
	$(ECHO) echo $(snappy_BASE)/snappy/snappy.cc : >> $(snappy_OUTPUT)/obj.snappy/snappy/snappy.cc.d

-include $(snappy_OUTPUT)/obj.snappy/snappy/snappy.cc.d

snappy-clean :: 
	$(INFO) Cleaning\ snappy...
	$(ECHO) $(RM) -rf $(snappy_OUTPUT)/libsnappy.a $(snappy_OUTPUT)/snappy.sym $(snappy_OUTPUT)/obj.snappy/snappy/snappy-c.cc.o $(snappy_OUTPUT)/obj.snappy/snappy/snappy-c.cc.d $(snappy_OUTPUT)/obj.snappy/snappy/snappy-sinksource.cc.o
	$(ECHO) $(RM) -rf $(snappy_OUTPUT)/obj.snappy/snappy/snappy-sinksource.cc.d $(snappy_OUTPUT)/obj.snappy/snappy/snappy-stubs-internal.cc.o $(snappy_OUTPUT)/obj.snappy/snappy/snappy-stubs-internal.cc.d $(snappy_OUTPUT)/obj.snappy/snappy/snappy.cc.o $(snappy_OUTPUT)/obj.snappy/snappy/snappy.cc.d
	$(ECHO) $(RM) -rf $(snappy_OUTPUT)/bin/libc++_shared.so

snappy-all :: -make-directories $(snappy_OUTPUT)/libsnappy.a

