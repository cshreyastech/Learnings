@echo off

python build.py

mldb connect 192.168.86.32:5555
mldb uninstall com.magicleap.capi.sample.controller2
mldb install -u BUILD\com.magicleap.capi.sample.controller2.mpk
mldb launch com.magicleap.capi.sample.controller2