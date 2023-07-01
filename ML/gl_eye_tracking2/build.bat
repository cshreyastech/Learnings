@echo off

rem mabu ctest.package -t device

rem mldb connect 192.168.86.247:5555

mldb uninstall com.magicleap.capi.sample.gl_eye_tracking2
mldb install -u BUILD\gl_eye_tracking2.mpk
mldb launch com.magicleap.capi.sample.gl_eye_tracking2