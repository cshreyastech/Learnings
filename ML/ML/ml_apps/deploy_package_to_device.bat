@echo off
rem cls

rem set /p "mpk"="com.magicleap.capi.sample.eye_tracking"
rem echo %mpk%

python build.py

mldb connect 192.168.86.32:5555
mldb uninstall com.magicleap.capi.sample.ros_ml_server
mldb install -u BUILD\com.magicleap.capi.sample.ros_ml_server.mpk
rem mldb launch com.magicleap.capi.sample.ros_ml_server
rem mldb terminate com.magicleap.capi.sample.ros_ml_server

rem mldb uninstall %mpk%
rem mldb install -u BUILD\%mpk%.mpk
rem mldb launch %mpk%