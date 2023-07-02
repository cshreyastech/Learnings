# learn_gl Sample


This example demonstrates a simple OpenGL application which can be built and run
on host and on device using the Virtual Device and Zero Iteration systems.

## Project Structure

The project consists of the files:

  * `main.cpp` -- source
  * `learn_gl.mabu` -- project for building the executable on all platforms
  * `com.magicleap.capi.sample.learn_gl.package` -- package project for building the device package and host-side layout.

## Building for Host

  * Set up the build environment (`envsetup.bat` or `envsetup.sh` from the MLSDK folder).
  * Build with `mabu com.magicleap.capi.sample.learn_gl.package`.

## Building for Device

All the requisite sources are available in MLSDK for EGL builds.

  * Set up the build environment (`envsetup.bat` or `envsetup.sh` from the MLSDK folder).
  * Build with `mabu -t lumin learn_gl.package`.
