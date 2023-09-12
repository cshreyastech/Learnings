#!/bin/bash 

rm -rf BUILD/*


python3 build.py

mldb connect 192.168.86.44:5555
mldb uninstall com.magicleap.capi.sample.ros_ml_client
mldb install -u BUILD/com.magicleap.capi.sample.ros_ml_client.mpk
# 30mldb launch com.magicleap.capi.sample.ros_ml_client
