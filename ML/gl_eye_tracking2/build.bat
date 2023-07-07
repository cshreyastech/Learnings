@echo off
rem cls

rem mldb install -u BUILD/gl_eye_tracking2.mpk

mldb connect 192.168.86.242:5555
mldb uninstall com.magicleap.capi.sample.gl_eye_tracking2
mldb install -u BUILD/gl_eye_tracking2.mpk
mldb launch com.magicleap.capi.sample.gl_eye_tracking2
rem mldb terminate com.magicleap.capi.sample.gl_eye_tracking2
