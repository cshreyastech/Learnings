# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/lcb/Learnings/ML/ML/app_framework/ext

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/lcb/Learnings/ML/ML/app_framework/ext/build/debug_lumin_clang-8.0_aarch64

# Include any dependencies generated for this target.
include snappy/CMakeFiles/snappy.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include snappy/CMakeFiles/snappy.dir/compiler_depend.make

# Include the progress variables for this target.
include snappy/CMakeFiles/snappy.dir/progress.make

# Include the compile flags for this target's objects.
include snappy/CMakeFiles/snappy.dir/flags.make

snappy/CMakeFiles/snappy.dir/snappy-c.cc.o: snappy/CMakeFiles/snappy.dir/flags.make
snappy/CMakeFiles/snappy.dir/snappy-c.cc.o: C:/lcb/Learnings/ML/ML/app_framework/ext/snappy/snappy-c.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/lcb/Learnings/ML/ML/app_framework/ext/build/debug_lumin_clang-8.0_aarch64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object snappy/CMakeFiles/snappy.dir/snappy-c.cc.o"
	cd C:/lcb/Learnings/ML/ML/app_framework/ext/build/debug_lumin_clang-8.0_aarch64/snappy && C:/Users/cshre/MagicLeap/mlsdk/v0.26.0/tools/toolchains/llvm-8/bin/aarch64-linux-android-clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/snappy.dir/snappy-c.cc.o -c C:/lcb/Learnings/ML/ML/app_framework/ext/snappy/snappy-c.cc

snappy/CMakeFiles/snappy.dir/snappy-c.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/snappy.dir/snappy-c.cc.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_PREPROCESSED_SOURCE

snappy/CMakeFiles/snappy.dir/snappy-c.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/snappy.dir/snappy-c.cc.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_ASSEMBLY_SOURCE

snappy/CMakeFiles/snappy.dir/snappy-sinksource.cc.o: snappy/CMakeFiles/snappy.dir/flags.make
snappy/CMakeFiles/snappy.dir/snappy-sinksource.cc.o: C:/lcb/Learnings/ML/ML/app_framework/ext/snappy/snappy-sinksource.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/lcb/Learnings/ML/ML/app_framework/ext/build/debug_lumin_clang-8.0_aarch64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object snappy/CMakeFiles/snappy.dir/snappy-sinksource.cc.o"
	cd C:/lcb/Learnings/ML/ML/app_framework/ext/build/debug_lumin_clang-8.0_aarch64/snappy && C:/Users/cshre/MagicLeap/mlsdk/v0.26.0/tools/toolchains/llvm-8/bin/aarch64-linux-android-clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/snappy.dir/snappy-sinksource.cc.o -c C:/lcb/Learnings/ML/ML/app_framework/ext/snappy/snappy-sinksource.cc

snappy/CMakeFiles/snappy.dir/snappy-sinksource.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/snappy.dir/snappy-sinksource.cc.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_PREPROCESSED_SOURCE

snappy/CMakeFiles/snappy.dir/snappy-sinksource.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/snappy.dir/snappy-sinksource.cc.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_ASSEMBLY_SOURCE

snappy/CMakeFiles/snappy.dir/snappy-stubs-internal.cc.o: snappy/CMakeFiles/snappy.dir/flags.make
snappy/CMakeFiles/snappy.dir/snappy-stubs-internal.cc.o: C:/lcb/Learnings/ML/ML/app_framework/ext/snappy/snappy-stubs-internal.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/lcb/Learnings/ML/ML/app_framework/ext/build/debug_lumin_clang-8.0_aarch64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object snappy/CMakeFiles/snappy.dir/snappy-stubs-internal.cc.o"
	cd C:/lcb/Learnings/ML/ML/app_framework/ext/build/debug_lumin_clang-8.0_aarch64/snappy && C:/Users/cshre/MagicLeap/mlsdk/v0.26.0/tools/toolchains/llvm-8/bin/aarch64-linux-android-clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/snappy.dir/snappy-stubs-internal.cc.o -c C:/lcb/Learnings/ML/ML/app_framework/ext/snappy/snappy-stubs-internal.cc

snappy/CMakeFiles/snappy.dir/snappy-stubs-internal.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/snappy.dir/snappy-stubs-internal.cc.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_PREPROCESSED_SOURCE

snappy/CMakeFiles/snappy.dir/snappy-stubs-internal.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/snappy.dir/snappy-stubs-internal.cc.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_ASSEMBLY_SOURCE

snappy/CMakeFiles/snappy.dir/snappy.cc.o: snappy/CMakeFiles/snappy.dir/flags.make
snappy/CMakeFiles/snappy.dir/snappy.cc.o: C:/lcb/Learnings/ML/ML/app_framework/ext/snappy/snappy.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/lcb/Learnings/ML/ML/app_framework/ext/build/debug_lumin_clang-8.0_aarch64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object snappy/CMakeFiles/snappy.dir/snappy.cc.o"
	cd C:/lcb/Learnings/ML/ML/app_framework/ext/build/debug_lumin_clang-8.0_aarch64/snappy && C:/Users/cshre/MagicLeap/mlsdk/v0.26.0/tools/toolchains/llvm-8/bin/aarch64-linux-android-clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/snappy.dir/snappy.cc.o -c C:/lcb/Learnings/ML/ML/app_framework/ext/snappy/snappy.cc

snappy/CMakeFiles/snappy.dir/snappy.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/snappy.dir/snappy.cc.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_PREPROCESSED_SOURCE

snappy/CMakeFiles/snappy.dir/snappy.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/snappy.dir/snappy.cc.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_ASSEMBLY_SOURCE

# Object files for target snappy
snappy_OBJECTS = \
"CMakeFiles/snappy.dir/snappy-c.cc.o" \
"CMakeFiles/snappy.dir/snappy-sinksource.cc.o" \
"CMakeFiles/snappy.dir/snappy-stubs-internal.cc.o" \
"CMakeFiles/snappy.dir/snappy.cc.o"

# External object files for target snappy
snappy_EXTERNAL_OBJECTS =

snappy/libsnappy.a: snappy/CMakeFiles/snappy.dir/snappy-c.cc.o
snappy/libsnappy.a: snappy/CMakeFiles/snappy.dir/snappy-sinksource.cc.o
snappy/libsnappy.a: snappy/CMakeFiles/snappy.dir/snappy-stubs-internal.cc.o
snappy/libsnappy.a: snappy/CMakeFiles/snappy.dir/snappy.cc.o
snappy/libsnappy.a: snappy/CMakeFiles/snappy.dir/build.make
snappy/libsnappy.a: snappy/CMakeFiles/snappy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:/lcb/Learnings/ML/ML/app_framework/ext/build/debug_lumin_clang-8.0_aarch64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libsnappy.a"
	cd C:/lcb/Learnings/ML/ML/app_framework/ext/build/debug_lumin_clang-8.0_aarch64/snappy && $(CMAKE_COMMAND) -P CMakeFiles/snappy.dir/cmake_clean_target.cmake
	cd C:/lcb/Learnings/ML/ML/app_framework/ext/build/debug_lumin_clang-8.0_aarch64/snappy && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/snappy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
snappy/CMakeFiles/snappy.dir/build: snappy/libsnappy.a
.PHONY : snappy/CMakeFiles/snappy.dir/build

snappy/CMakeFiles/snappy.dir/clean:
	cd C:/lcb/Learnings/ML/ML/app_framework/ext/build/debug_lumin_clang-8.0_aarch64/snappy && $(CMAKE_COMMAND) -P CMakeFiles/snappy.dir/cmake_clean.cmake
.PHONY : snappy/CMakeFiles/snappy.dir/clean

snappy/CMakeFiles/snappy.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/lcb/Learnings/ML/ML/app_framework/ext C:/lcb/Learnings/ML/ML/app_framework/ext/snappy C:/lcb/Learnings/ML/ML/app_framework/ext/build/debug_lumin_clang-8.0_aarch64 C:/lcb/Learnings/ML/ML/app_framework/ext/build/debug_lumin_clang-8.0_aarch64/snappy C:/lcb/Learnings/ML/ML/app_framework/ext/build/debug_lumin_clang-8.0_aarch64/snappy/CMakeFiles/snappy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : snappy/CMakeFiles/snappy.dir/depend

