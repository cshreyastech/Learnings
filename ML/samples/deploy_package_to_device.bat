@echo off

python build.py

rem mldb connect 192.168.86.247:5555
mldb uninstall com.magicleap.capi.sample.eye_tracking2
mldb install -u BUILD\com.magicleap.capi.sample.eye_tracking2.mpk
mldb launch com.magicleap.capi.sample.eye_tracking2