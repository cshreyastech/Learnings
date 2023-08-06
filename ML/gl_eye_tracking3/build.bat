@echo off
rem cls


rem mabu gl_eye_tracking3.package -t device
rem mldb install -u BUILD/gl_eye_tracking3.mpk

mldb connect 192.168.86.32:5555
mldb terminate com.magicleap.capi.sample.gl_eye_tracking3
mldb uninstall com.magicleap.capi.sample.gl_eye_tracking3
mldb install -u BUILD/gl_eye_tracking3.mpk
mldb launch com.magicleap.capi.sample.gl_eye_tracking3
rem mldb terminate com.magicleap.capi.sample.gl_eye_tracking3
