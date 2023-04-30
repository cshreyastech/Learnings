@echo off

:: python build.py

:: mldb connect 192.168.86.25:5555
mldb uninstall com.magicleap.capi.sample.learn_gl
mldb install -u BUILD\com.magicleap.capi.sample.learn_gl.mpk
mldb launch com.magicleap.capi.sample.learn_gl