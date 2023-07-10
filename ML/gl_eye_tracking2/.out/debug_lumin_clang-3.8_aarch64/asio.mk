# Generated Makefile -- DO NOT EDIT!

AR=C:/Users/cshre/MagicLeap/mlsdk/v0.26.0/tools/toolchains/bin/aarch64-linux-android-gcc-ar.exe
HOST=win64
RM=rm
SPEC=debug_lumin_clang-3.8_aarch64
TOUCH=touch
asio_ARFLAGS=
asio_BASE=C:/lcb/Learnings/ML/gl_eye_tracking2
asio_OUTPUT=$(asio_BASE)/.out/$(SPEC)

$(asio_OUTPUT)/libasio.a :  $(asio_BASE)/asio.mabu $(MLSDK)/tools/mabu/data/configs/debug.config $(MLSDK)/tools/mabu/data/options/debug/on.option $(MLSDK)/tools/mabu/data/options/magicleap.option $(MLSDK)/tools/mabu/data/options/optimize/off.option $(MLSDK)/tools/mabu/data/options/package/debuggable/on.option $(MLSDK)/tools/mabu/data/options/runtime/shared.option $(MLSDK)/tools/mabu/data/options/standard-c++/17.option $(MLSDK)/tools/mabu/data/options/warn/on.option
	$(INFO) \[asio\]\ Linking\ static\ library\ 'libasio.a'...
	$(ECHO) $(RM) -f $(asio_OUTPUT)/libasio.a
	$(ECHO) cd $(asio_OUTPUT) && $(AR) crs libasio.a @$(asio_OUTPUT)/libasio.a.args $(asio_ARFLAGS)
	$(ECHO) $(TOUCH) $(asio_OUTPUT)/libasio.a


asio-clean :: 
	$(INFO) Cleaning\ asio...
	$(ECHO) $(RM) -rf $(asio_OUTPUT)/libasio.a $(asio_OUTPUT)/asio.sym

asio-all :: -make-directories $(asio_OUTPUT)/libasio.a

