@echo off
rem cls

rem set /p "mpk"="com.magicleap.capi.sample.eye_tracking"
rem echo %mpk%

python build.py

mldb connect 192.168.86.37:5555
mldb uninstall com.magicleap.capi.sample.snappy_poc
mldb install -u BUILD\com.magicleap.capi.sample.snappy_poc.mpk
mldb launch com.magicleap.capi.sample.snappy_poc
rem mldb terminate com.magicleap.capi.sample.snappy_poc

rem mldb uninstall %mpk%
rem mldb install -u BUILD\%mpk%.mpk
rem mldb launch %mpk%