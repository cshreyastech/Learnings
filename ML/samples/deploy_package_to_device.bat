@echo off

python build.py

mldb connect 192.168.86.25:5555
mldb uninstall com.magicleap.capi.sample.ros_ml
mldb install -u BUILD\com.magicleap.capi.sample.ros_ml.mpk
rem mldb launch com.magicleap.capi.sample.ros_ml