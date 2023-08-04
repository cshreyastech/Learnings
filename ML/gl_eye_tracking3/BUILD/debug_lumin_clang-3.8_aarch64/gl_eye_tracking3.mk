# Generated Makefile -- DO NOT EDIT!

CC=C:/Users/cshre/MagicLeap/mlsdk/v0.26.0/tools/toolchains/bin/aarch64-linux-android-clang
COMPILER_PREFIX=
CXX=C:/Users/cshre/MagicLeap/mlsdk/v0.26.0/tools/toolchains/bin/aarch64-linux-android-clang++
HOST=win64
LINKER_PREFIX=
MLSDK=C:/Users/cshre/MagicLeap/mlsdk/v0.26.0
OBJCOPY=C:/Users/cshre/MagicLeap/mlsdk/v0.26.0/tools/toolchains/bin/aarch64-linux-android-objcopy.exe
RM=rm
SPEC=debug_lumin_clang-3.8_aarch64
STRIP=C:/Users/cshre/MagicLeap/mlsdk/v0.26.0/tools/toolchains/bin/aarch64-linux-android-strip.exe
gl_eye_tracking3_BASE=C:/lcb/Learnings/ML/gl_eye_tracking3
gl_eye_tracking3_CPPFLAGS=-I$(gl_eye_tracking3_BASE)/src/ -I$(MLSDK)/include -DML_DEVICE -DML_DEFAULT_LOG_TAG=\"gl_eye_tracking3\"
gl_eye_tracking3_CXXFLAGS=--sysroot=$(MLSDK)/lumin -march=armv8-a -mcpu=cortex-a57+crypto -fPIE -fpic -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -Wa,--noexecstack -Wformat -Werror=format-security -Wno-invalid-command-line-argument -Wno-unused-command-line-argument -g -fno-limit-debug-info -O0 -nostdinc++ -I$(MLSDK)/lumin/stl/libc++/include -std=c++1z -fexceptions
gl_eye_tracking3_LDFLAGS=-Wl,-unresolved-symbols=ignore-in-shared-libs --sysroot=$(MLSDK)/lumin -pie -Wl,--gc-sections -Wl,-z,nocopyreloc -Wl,--warn-shared-textrel -Wl,--fatal-warnings -Wl,--build-id -no-canonical-prefixes -Wl,--no-undefined -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now -Wl,--enable-new-dtags '-Wl,-rpath=$$ORIGIN' -g -L$(MLSDK)/lumin/stl/libc++/lib
gl_eye_tracking3_LIBS=-L$(MLSDK)/lib/lumin -Wl,--start-group -Bdynamic -lc -lc++_shared -landroid_support -lml_graphics -lml_perception_client -lml_input -lml_lifecycle -lml_ext_logging -lEGL -lGLESv2 -lGLESv3 -lm -Wl,--end-group
gl_eye_tracking3_OUTPUT=$(samples_common_comp_BASE)/BUILD/$(SPEC)
samples_common_comp_BASE=C:/lcb/Learnings/ML/gl_eye_tracking3

$(gl_eye_tracking3_OUTPUT)/gl_eye_tracking3 : $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/main.cpp.o $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBShader.cpp.o $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBCylinder.cpp.o $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBSquare.cpp.o $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBCube.cpp.o $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBPointDynamic.cpp.o $(gl_eye_tracking3_BASE)/gl_eye_tracking3.mabu $(MLSDK)/.metadata/components/ml_sdk.comp $(MLSDK)/.metadata/components/ml_sdk_common.comp $(MLSDK)/tools/mabu/data/components/OpenGL.comp $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/exceptions/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/gl_eye_tracking3/samples_common.comp
	$(INFO) \[gl_eye_tracking3\]\ Linking\ program\ 'gl_eye_tracking3'...
	$(ECHO) cd $(gl_eye_tracking3_OUTPUT) && $(LINKER_PREFIX) $(CC) -o gl_eye_tracking3 obj.gl_eye_tracking3/src/main.cpp.o obj.gl_eye_tracking3/src/RBShader.cpp.o obj.gl_eye_tracking3/src/RBCylinder.cpp.o obj.gl_eye_tracking3/src/RBSquare.cpp.o obj.gl_eye_tracking3/src/RBCube.cpp.o obj.gl_eye_tracking3/src/RBPointDynamic.cpp.o $(gl_eye_tracking3_LIBS) $(gl_eye_tracking3_LDFLAGS)
	$(ECHO) $(OBJCOPY) --only-keep-debug $(gl_eye_tracking3_OUTPUT)/gl_eye_tracking3 $(gl_eye_tracking3_OUTPUT)/gl_eye_tracking3.sym
	$(ECHO) $(OBJCOPY) --add-gnu-debuglink $(gl_eye_tracking3_OUTPUT)/gl_eye_tracking3.sym $(gl_eye_tracking3_OUTPUT)/gl_eye_tracking3 $(gl_eye_tracking3_OUTPUT)/gl_eye_tracking3
	$(ECHO) $(STRIP) --strip-unneeded $(gl_eye_tracking3_OUTPUT)/gl_eye_tracking3

$(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/main.cpp.o : $(gl_eye_tracking3_BASE)/src/main.cpp $(gl_eye_tracking3_BASE)/gl_eye_tracking3.mabu $(MLSDK)/.metadata/components/ml_sdk.comp $(MLSDK)/.metadata/components/ml_sdk_common.comp $(MLSDK)/tools/mabu/data/components/OpenGL.comp $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/exceptions/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/gl_eye_tracking3/samples_common.comp
	$(INFO) \[gl_eye_tracking3\]\ Compiling\ 'main.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(gl_eye_tracking3_BASE)/src/main.cpp -o $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/main.cpp.o -MD -MP -MF $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/main.cpp.d $(gl_eye_tracking3_CPPFLAGS) $(gl_eye_tracking3_CXXFLAGS)
	$(ECHO) echo $(gl_eye_tracking3_BASE)/src/main.cpp : >> $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/main.cpp.d

-include $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/main.cpp.d
$(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBShader.cpp.o : $(gl_eye_tracking3_BASE)/src/RBShader.cpp $(gl_eye_tracking3_BASE)/gl_eye_tracking3.mabu $(MLSDK)/.metadata/components/ml_sdk.comp $(MLSDK)/.metadata/components/ml_sdk_common.comp $(MLSDK)/tools/mabu/data/components/OpenGL.comp $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/exceptions/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/gl_eye_tracking3/samples_common.comp
	$(INFO) \[gl_eye_tracking3\]\ Compiling\ 'RBShader.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(gl_eye_tracking3_BASE)/src/RBShader.cpp -o $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBShader.cpp.o -MD -MP -MF $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBShader.cpp.d $(gl_eye_tracking3_CPPFLAGS) $(gl_eye_tracking3_CXXFLAGS)
	$(ECHO) echo $(gl_eye_tracking3_BASE)/src/RBShader.cpp : >> $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBShader.cpp.d

-include $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBShader.cpp.d
$(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBCylinder.cpp.o : $(gl_eye_tracking3_BASE)/src/RBCylinder.cpp $(gl_eye_tracking3_BASE)/gl_eye_tracking3.mabu $(MLSDK)/.metadata/components/ml_sdk.comp $(MLSDK)/.metadata/components/ml_sdk_common.comp $(MLSDK)/tools/mabu/data/components/OpenGL.comp $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/exceptions/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/gl_eye_tracking3/samples_common.comp
	$(INFO) \[gl_eye_tracking3\]\ Compiling\ 'RBCylinder.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(gl_eye_tracking3_BASE)/src/RBCylinder.cpp -o $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBCylinder.cpp.o -MD -MP -MF $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBCylinder.cpp.d $(gl_eye_tracking3_CPPFLAGS) $(gl_eye_tracking3_CXXFLAGS)
	$(ECHO) echo $(gl_eye_tracking3_BASE)/src/RBCylinder.cpp : >> $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBCylinder.cpp.d

-include $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBCylinder.cpp.d
$(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBSquare.cpp.o : $(gl_eye_tracking3_BASE)/src/RBSquare.cpp $(gl_eye_tracking3_BASE)/gl_eye_tracking3.mabu $(MLSDK)/.metadata/components/ml_sdk.comp $(MLSDK)/.metadata/components/ml_sdk_common.comp $(MLSDK)/tools/mabu/data/components/OpenGL.comp $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/exceptions/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/gl_eye_tracking3/samples_common.comp
	$(INFO) \[gl_eye_tracking3\]\ Compiling\ 'RBSquare.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(gl_eye_tracking3_BASE)/src/RBSquare.cpp -o $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBSquare.cpp.o -MD -MP -MF $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBSquare.cpp.d $(gl_eye_tracking3_CPPFLAGS) $(gl_eye_tracking3_CXXFLAGS)
	$(ECHO) echo $(gl_eye_tracking3_BASE)/src/RBSquare.cpp : >> $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBSquare.cpp.d

-include $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBSquare.cpp.d
$(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBCube.cpp.o : $(gl_eye_tracking3_BASE)/src/RBCube.cpp $(gl_eye_tracking3_BASE)/gl_eye_tracking3.mabu $(MLSDK)/.metadata/components/ml_sdk.comp $(MLSDK)/.metadata/components/ml_sdk_common.comp $(MLSDK)/tools/mabu/data/components/OpenGL.comp $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/exceptions/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/gl_eye_tracking3/samples_common.comp
	$(INFO) \[gl_eye_tracking3\]\ Compiling\ 'RBCube.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(gl_eye_tracking3_BASE)/src/RBCube.cpp -o $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBCube.cpp.o -MD -MP -MF $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBCube.cpp.d $(gl_eye_tracking3_CPPFLAGS) $(gl_eye_tracking3_CXXFLAGS)
	$(ECHO) echo $(gl_eye_tracking3_BASE)/src/RBCube.cpp : >> $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBCube.cpp.d

-include $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBCube.cpp.d
$(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBPointDynamic.cpp.o : $(gl_eye_tracking3_BASE)/src/RBPointDynamic.cpp $(gl_eye_tracking3_BASE)/gl_eye_tracking3.mabu $(MLSDK)/.metadata/components/ml_sdk.comp $(MLSDK)/.metadata/components/ml_sdk_common.comp $(MLSDK)/tools/mabu/data/components/OpenGL.comp $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/exceptions/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/gl_eye_tracking3/samples_common.comp
	$(INFO) \[gl_eye_tracking3\]\ Compiling\ 'RBPointDynamic.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(gl_eye_tracking3_BASE)/src/RBPointDynamic.cpp -o $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBPointDynamic.cpp.o -MD -MP -MF $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBPointDynamic.cpp.d $(gl_eye_tracking3_CPPFLAGS) $(gl_eye_tracking3_CXXFLAGS)
	$(ECHO) echo $(gl_eye_tracking3_BASE)/src/RBPointDynamic.cpp : >> $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBPointDynamic.cpp.d

-include $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBPointDynamic.cpp.d

gl_eye_tracking3-clean :: 
	$(INFO) Cleaning\ gl_eye_tracking3...
	$(ECHO) $(RM) -rf $(gl_eye_tracking3_OUTPUT)/gl_eye_tracking3 $(gl_eye_tracking3_OUTPUT)/gl_eye_tracking3.sym $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/main.cpp.o $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/main.cpp.d $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBShader.cpp.o
	$(ECHO) $(RM) -rf $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBShader.cpp.d $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBCylinder.cpp.o $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBCylinder.cpp.d $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBSquare.cpp.o $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBSquare.cpp.d
	$(ECHO) $(RM) -rf $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBCube.cpp.o $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBCube.cpp.d $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBPointDynamic.cpp.o $(gl_eye_tracking3_OUTPUT)/obj.gl_eye_tracking3/src/RBPointDynamic.cpp.d $(gl_eye_tracking3_OUTPUT)/bin/libc++_shared.so
	$(ECHO) $(RM) -rf $(gl_eye_tracking3_OUTPUT)/data/res/cloud/depth_data.txt $(gl_eye_tracking3_OUTPUT)/data/res/cloud/depth_data.zip $(gl_eye_tracking3_OUTPUT)/data/res/cloud/depth_data_test.txt $(gl_eye_tracking3_OUTPUT)/data/res/shaders/basic.frag $(gl_eye_tracking3_OUTPUT)/data/res/shaders/basic3D.vert
	$(ECHO) $(RM) -rf $(gl_eye_tracking3_OUTPUT)/data/res/shaders/standard.frag $(gl_eye_tracking3_OUTPUT)/data/res/shaders/standard3D.vert $(gl_eye_tracking3_OUTPUT)/data/res/shaders/texture.frag $(gl_eye_tracking3_OUTPUT)/data/res/shaders/texture.vert $(gl_eye_tracking3_OUTPUT)/data/res/texture/container.jpg

gl_eye_tracking3-all :: -make-directories $(gl_eye_tracking3_OUTPUT)/gl_eye_tracking3
