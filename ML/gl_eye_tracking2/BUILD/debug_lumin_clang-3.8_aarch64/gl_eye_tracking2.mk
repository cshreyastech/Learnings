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
gl_eye_tracking2_BASE=C:/lcb/Learnings/ML/gl_eye_tracking2
gl_eye_tracking2_CPPFLAGS=-I$(gl_eye_tracking2_BASE)/src/ -I$(stb_BASE)/stb-master/ -I$(MLSDK)/include -DML_LUMIN -DML_DEVICE -DML_DEFAULT_LOG_TAG=\"gl_eye_tracking2\"
gl_eye_tracking2_CXXFLAGS=--sysroot=$(MLSDK)/lumin -march=armv8-a -mcpu=cortex-a57+crypto -fPIE -fpic -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -Wa,--noexecstack -Wformat -Werror=format-security -Wno-invalid-command-line-argument -Wno-unused-command-line-argument -g -fno-limit-debug-info -O0 -nostdinc++ -I$(MLSDK)/lumin/stl/libc++/include -std=c++1z -fexceptions
gl_eye_tracking2_LDFLAGS=-Wl,-unresolved-symbols=ignore-in-shared-libs --sysroot=$(MLSDK)/lumin -pie -Wl,--gc-sections -Wl,-z,nocopyreloc -Wl,--warn-shared-textrel -Wl,--fatal-warnings -Wl,--build-id -no-canonical-prefixes -Wl,--no-undefined -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now -Wl,--enable-new-dtags '-Wl,-rpath=$$ORIGIN' -g -L$(MLSDK)/lumin/stl/libc++/lib
gl_eye_tracking2_LIBS=-L$(MLSDK)/lib/lumin -Wl,--start-group -Bstatic -Wl,--no-as-needed $(stb_OUTPUT)/libstb.a -Bdynamic -lc -lc++_shared -landroid_support -lml_graphics -lml_perception_client -lml_input -lml_lifecycle -lml_ext_logging -lEGL -lGLESv2 -lGLESv3 -lm -Wl,--end-group
gl_eye_tracking2_OUTPUT=$(samples_common_comp_BASE)/BUILD/$(SPEC)
samples_common_comp_BASE=C:/lcb/Learnings/ML/gl_eye_tracking2
stb_BASE=C:/lcb/Learnings/ML/gl_eye_tracking2
stb_OUTPUT=$(stb_BASE)/.out/$(SPEC)

$(gl_eye_tracking2_OUTPUT)/gl_eye_tracking2 : $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/main.cpp.o $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBShader.cpp.o $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBCylinder.cpp.o $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBSquare.cpp.o $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBCube.cpp.o $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBTexture.cpp.o $(stb_OUTPUT)/libstb.a $(gl_eye_tracking2_BASE)/gl_eye_tracking2.mabu $(MLSDK)/.metadata/components/ml_sdk.comp $(MLSDK)/.metadata/components/ml_sdk_common.comp $(MLSDK)/tools/mabu/data/components/OpenGL.comp $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/exceptions/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/gl_eye_tracking2/samples_common.comp
	$(INFO) \[gl_eye_tracking2\]\ Linking\ program\ 'gl_eye_tracking2'...
	$(ECHO) cd $(gl_eye_tracking2_OUTPUT) && $(LINKER_PREFIX) $(CC) -o gl_eye_tracking2 obj.gl_eye_tracking2/src/main.cpp.o obj.gl_eye_tracking2/src/RBShader.cpp.o obj.gl_eye_tracking2/src/RBCylinder.cpp.o obj.gl_eye_tracking2/src/RBSquare.cpp.o obj.gl_eye_tracking2/src/RBCube.cpp.o obj.gl_eye_tracking2/src/RBTexture.cpp.o $(gl_eye_tracking2_LIBS) $(gl_eye_tracking2_LDFLAGS)
	$(ECHO) $(OBJCOPY) --only-keep-debug $(gl_eye_tracking2_OUTPUT)/gl_eye_tracking2 $(gl_eye_tracking2_OUTPUT)/gl_eye_tracking2.sym
	$(ECHO) $(OBJCOPY) --add-gnu-debuglink $(gl_eye_tracking2_OUTPUT)/gl_eye_tracking2.sym $(gl_eye_tracking2_OUTPUT)/gl_eye_tracking2 $(gl_eye_tracking2_OUTPUT)/gl_eye_tracking2
	$(ECHO) $(STRIP) --strip-unneeded $(gl_eye_tracking2_OUTPUT)/gl_eye_tracking2

$(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/main.cpp.o : $(gl_eye_tracking2_BASE)/src/main.cpp $(gl_eye_tracking2_BASE)/gl_eye_tracking2.mabu $(MLSDK)/.metadata/components/ml_sdk.comp $(MLSDK)/.metadata/components/ml_sdk_common.comp $(MLSDK)/tools/mabu/data/components/OpenGL.comp $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/exceptions/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/gl_eye_tracking2/samples_common.comp
	$(INFO) \[gl_eye_tracking2\]\ Compiling\ 'main.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(gl_eye_tracking2_BASE)/src/main.cpp -o $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/main.cpp.o -MD -MP -MF $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/main.cpp.d $(gl_eye_tracking2_CPPFLAGS) $(gl_eye_tracking2_CXXFLAGS)
	$(ECHO) echo $(gl_eye_tracking2_BASE)/src/main.cpp : >> $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/main.cpp.d

-include $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/main.cpp.d
$(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBShader.cpp.o : $(gl_eye_tracking2_BASE)/src/RBShader.cpp $(gl_eye_tracking2_BASE)/gl_eye_tracking2.mabu $(MLSDK)/.metadata/components/ml_sdk.comp $(MLSDK)/.metadata/components/ml_sdk_common.comp $(MLSDK)/tools/mabu/data/components/OpenGL.comp $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/exceptions/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/gl_eye_tracking2/samples_common.comp
	$(INFO) \[gl_eye_tracking2\]\ Compiling\ 'RBShader.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(gl_eye_tracking2_BASE)/src/RBShader.cpp -o $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBShader.cpp.o -MD -MP -MF $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBShader.cpp.d $(gl_eye_tracking2_CPPFLAGS) $(gl_eye_tracking2_CXXFLAGS)
	$(ECHO) echo $(gl_eye_tracking2_BASE)/src/RBShader.cpp : >> $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBShader.cpp.d

-include $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBShader.cpp.d
$(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBCylinder.cpp.o : $(gl_eye_tracking2_BASE)/src/RBCylinder.cpp $(gl_eye_tracking2_BASE)/gl_eye_tracking2.mabu $(MLSDK)/.metadata/components/ml_sdk.comp $(MLSDK)/.metadata/components/ml_sdk_common.comp $(MLSDK)/tools/mabu/data/components/OpenGL.comp $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/exceptions/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/gl_eye_tracking2/samples_common.comp
	$(INFO) \[gl_eye_tracking2\]\ Compiling\ 'RBCylinder.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(gl_eye_tracking2_BASE)/src/RBCylinder.cpp -o $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBCylinder.cpp.o -MD -MP -MF $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBCylinder.cpp.d $(gl_eye_tracking2_CPPFLAGS) $(gl_eye_tracking2_CXXFLAGS)
	$(ECHO) echo $(gl_eye_tracking2_BASE)/src/RBCylinder.cpp : >> $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBCylinder.cpp.d

-include $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBCylinder.cpp.d
$(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBSquare.cpp.o : $(gl_eye_tracking2_BASE)/src/RBSquare.cpp $(gl_eye_tracking2_BASE)/gl_eye_tracking2.mabu $(MLSDK)/.metadata/components/ml_sdk.comp $(MLSDK)/.metadata/components/ml_sdk_common.comp $(MLSDK)/tools/mabu/data/components/OpenGL.comp $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/exceptions/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/gl_eye_tracking2/samples_common.comp
	$(INFO) \[gl_eye_tracking2\]\ Compiling\ 'RBSquare.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(gl_eye_tracking2_BASE)/src/RBSquare.cpp -o $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBSquare.cpp.o -MD -MP -MF $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBSquare.cpp.d $(gl_eye_tracking2_CPPFLAGS) $(gl_eye_tracking2_CXXFLAGS)
	$(ECHO) echo $(gl_eye_tracking2_BASE)/src/RBSquare.cpp : >> $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBSquare.cpp.d

-include $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBSquare.cpp.d
$(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBCube.cpp.o : $(gl_eye_tracking2_BASE)/src/RBCube.cpp $(gl_eye_tracking2_BASE)/gl_eye_tracking2.mabu $(MLSDK)/.metadata/components/ml_sdk.comp $(MLSDK)/.metadata/components/ml_sdk_common.comp $(MLSDK)/tools/mabu/data/components/OpenGL.comp $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/exceptions/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/gl_eye_tracking2/samples_common.comp
	$(INFO) \[gl_eye_tracking2\]\ Compiling\ 'RBCube.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(gl_eye_tracking2_BASE)/src/RBCube.cpp -o $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBCube.cpp.o -MD -MP -MF $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBCube.cpp.d $(gl_eye_tracking2_CPPFLAGS) $(gl_eye_tracking2_CXXFLAGS)
	$(ECHO) echo $(gl_eye_tracking2_BASE)/src/RBCube.cpp : >> $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBCube.cpp.d

-include $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBCube.cpp.d
$(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBTexture.cpp.o : $(gl_eye_tracking2_BASE)/src/RBTexture.cpp $(gl_eye_tracking2_BASE)/gl_eye_tracking2.mabu $(MLSDK)/.metadata/components/ml_sdk.comp $(MLSDK)/.metadata/components/ml_sdk_common.comp $(MLSDK)/tools/mabu/data/components/OpenGL.comp $(MLSDK)/tools/mabu/data/components/stdc++.comp $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/exceptions/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option C:/lcb/Learnings/ML/gl_eye_tracking2/samples_common.comp
	$(INFO) \[gl_eye_tracking2\]\ Compiling\ 'RBTexture.cpp'...
	$(ECHO) $(COMPILER_PREFIX) $(CXX) -c $(gl_eye_tracking2_BASE)/src/RBTexture.cpp -o $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBTexture.cpp.o -MD -MP -MF $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBTexture.cpp.d $(gl_eye_tracking2_CPPFLAGS) $(gl_eye_tracking2_CXXFLAGS)
	$(ECHO) echo $(gl_eye_tracking2_BASE)/src/RBTexture.cpp : >> $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBTexture.cpp.d

-include $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBTexture.cpp.d

gl_eye_tracking2-clean :: 
	$(INFO) Cleaning\ gl_eye_tracking2...
	$(ECHO) $(RM) -rf $(gl_eye_tracking2_OUTPUT)/gl_eye_tracking2 $(gl_eye_tracking2_OUTPUT)/gl_eye_tracking2.sym $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/main.cpp.o $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/main.cpp.d $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBShader.cpp.o
	$(ECHO) $(RM) -rf $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBShader.cpp.d $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBCylinder.cpp.o $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBCylinder.cpp.d $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBSquare.cpp.o $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBSquare.cpp.d
	$(ECHO) $(RM) -rf $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBCube.cpp.o $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBCube.cpp.d $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBTexture.cpp.o $(gl_eye_tracking2_OUTPUT)/obj.gl_eye_tracking2/src/RBTexture.cpp.d $(gl_eye_tracking2_OUTPUT)/bin/libc++_shared.so
	$(ECHO) $(RM) -rf $(gl_eye_tracking2_OUTPUT)/data/DeepSeaExploration.png $(gl_eye_tracking2_OUTPUT)/data/DeepSpaceExploration.png $(gl_eye_tracking2_OUTPUT)/data/res/shaders/standard.frag $(gl_eye_tracking2_OUTPUT)/data/res/shaders/standard3D.vert $(gl_eye_tracking2_OUTPUT)/data/res/shaders/texture.frag
	$(ECHO) $(RM) -rf $(gl_eye_tracking2_OUTPUT)/data/res/shaders/texture.vert $(gl_eye_tracking2_OUTPUT)/data/res/texture/container.jpg $(gl_eye_tracking2_OUTPUT)/data/res/texture/dynamic_textures/container0.jpg $(gl_eye_tracking2_OUTPUT)/data/res/texture/dynamic_textures/container1.jpg $(gl_eye_tracking2_OUTPUT)/data/res/texture/dynamic_textures/container2.jpg
	$(ECHO) $(RM) -rf $(gl_eye_tracking2_OUTPUT)/data/res/texture/dynamic_textures/container3.jpg $(gl_eye_tracking2_OUTPUT)/data/res/texture/dynamic_textures/container4.jpg $(gl_eye_tracking2_OUTPUT)/data/res/texture/dynamic_textures/container5.jpg $(gl_eye_tracking2_OUTPUT)/data/res/texture/dynamic_textures/container6.jpg $(gl_eye_tracking2_OUTPUT)/data/res/texture/dynamic_textures/container7.jpg
	$(ECHO) $(RM) -rf $(gl_eye_tracking2_OUTPUT)/data/res/texture/dynamic_textures/container8.jpg $(gl_eye_tracking2_OUTPUT)/data/res/texture/dynamic_textures/container9.jpg

gl_eye_tracking2-all :: -make-directories $(gl_eye_tracking2_OUTPUT)/gl_eye_tracking2

