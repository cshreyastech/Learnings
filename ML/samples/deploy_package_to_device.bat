@echo off

python build.py

mldb connect 192.168.86.237:5555
mldb uninstall com.magicleap.capi.sample.gl_eye_tracking
mldb install -u BUILD\com.magicleap.capi.sample.gl_eye_tracking.mpk
mldb launch com.magicleap.capi.sample.gl_eye_tracking