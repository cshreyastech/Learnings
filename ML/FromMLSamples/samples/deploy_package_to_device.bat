@echo off

python build.py

mldb connect 192.168.86.247:5555
mldb uninstall com.magicleap.capi.sample.meshing2
mldb install -u BUILD\com.magicleap.capi.sample.meshing2.mpk
mldb launch com.magicleap.capi.sample.meshing2