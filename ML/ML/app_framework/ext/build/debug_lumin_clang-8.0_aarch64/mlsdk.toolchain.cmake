set(LUMIN TRUE)

set(MLSDK "C:/Users/cshre/MagicLeap/mlsdk/v0.26.0" CACHE PATH "Path to Lumin SDK")

# canonicalize
string(REPLACE "\\" "/" LUMIN_SDK "${MLSDK}")

set(CMAKE_SYSTEM_NAME    Linux)
set(CMAKE_SYSTEM_VERSION 1)

SET(TOOL_OS_SUFFIX "")

set(CMAKE_SYSTEM_PROCESSOR "aarch64")
set(CMAKE_SYSROOT          "${LUMIN_SDK}/lumin/sysroot")

set(CMAKE_MAKE_PROGRAM     "${LUMIN_SDK}/tools/mabu/tools/mingw/msys/1.0/bin/make" CACHE PATH "make executable" FORCE)
set(CMAKE_C_COMPILER       "${LUMIN_SDK}/tools/toolchains/llvm-8/bin/aarch64-linux-android-clang${TOOL_OS_SUFFIX}"  CACHE PATH "C compiler" FORCE)
set(CMAKE_CXX_COMPILER     "${LUMIN_SDK}/tools/toolchains/llvm-8/bin/aarch64-linux-android-clang++${TOOL_OS_SUFFIX}" CACHE PATH "C++ compiler" FORCE)
set(CMAKE_AR               "${LUMIN_SDK}/tools/toolchains/llvm-8/bin/aarch64-linux-android-gcc-ar.exe" CACHE PATH "C/C++ archiver" FORCE)
set(CMAKE_RANLIB           "${LUMIN_SDK}/tools/toolchains/llvm-8/bin/aarch64-linux-android-ranlib.exe" CACHE PATH "C/C++ ranlib" FORCE)

# Configure the behaviour of the find commands
set(CMAKE_PROGRAM_PATH "${LUMIN_SDK}/tools/toolchains/llvm-8/bin")
set(CMAKE_FIND_ROOT_PATH "${CMAKE_SYSROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_C_FLAGS " --sysroot=${LUMIN_SDK}/lumin/sysroot -march=armv8-a -mcpu=cortex-a57+crypto -fPIE" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_FLAGS " --sysroot=${LUMIN_SDK}/lumin/sysroot -march=armv8-a -mcpu=cortex-a57+crypto -fPIE -std=c++11 -nostdinc++ -I${LUMIN_SDK}/lumin/stl/libc++-8/include" CACHE INTERNAL "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--start-group -Bdynamic -lc -lm -lc++_shared -Wl,--end-group --sysroot=${LUMIN_SDK}/lumin/sysroot -pie -Wl,--gc-sections -Wl,-z,nocopyreloc -Wl,--warn-shared-textrel -Wl,--fatal-warnings -Wl,--build-id -L${LUMIN_SDK}/lumin/stl/libc++-8/lib" CACHE INTERNAL "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--start-group -Bdynamic -lc -lm -lc++_shared -Wl,--end-group --sysroot=${LUMIN_SDK}/lumin/sysroot -Wl,--warn-shared-textrel -Wl,--fatal-warnings -Wl,--build-id -L${LUMIN_SDK}/lumin/stl/libc++-8/lib" CACHE INTERNAL "" FORCE)
set(CMAKE_STATIC_LINKER_FLAGS "" CACHE INTERNAL "" FORCE)
set(CMAKE_LIBRARY_PATH "${LUMIN_SDK}/lumin/stl/libc++-8/lib" CACHE INTERNAL "" FORCE)

include_directories(SYSTEM )

#
# The following file was used by `mabu --create-cmake-toolchain` to determine what
# compiler and linker settings to use.
# You can pass `--path ...` or set the env var MABU_PATH=... to override where "base.comp" is discovered.
#
# MABU_TEMPLATE = C:\Users\cshre\MagicLeap\mlsdk\v0.26.0\tools\mabu\data\templates\empty_program.mabu
# MABU_BASE = C:/lcb/Learnings/ML/ML/app_framework/base.comp
# MABU_SETTINGS = # empty_program.mabu
#  CFLAGS=--sysroot=${LUMIN_SDK}/lumin/sysroot -march=armv8-a -mcpu=cortex-a57+crypto -fPIE
#  CPPFLAGS=
#  CXXFLAGS=--sysroot=${LUMIN_SDK}/lumin/sysroot -march=armv8-a -mcpu=cortex-a57+crypto -fPIE -std=c++11 -nostdinc++ -I${LUMIN_SDK}/lumin/stl/libc++-8/include
#  LDFLAGS=--sysroot=${LUMIN_SDK}/lumin/sysroot -pie -Wl,--gc-sections -Wl,-z,nocopyreloc -Wl,--warn-shared-textrel -Wl,--fatal-warnings -Wl,--build-id -L${LUMIN_SDK}/lumin/stl/libc++-8/lib
#  LIBS=-Wl,--start-group -Bdynamic -lc -lm -lc++_shared -Wl,--end-group
#  
#  
#