#!/bin/bash 

rm -rf BUILD/*


python3 build.py

mldb connect 192.168.86.24:5555
mldb uninstall com.magicleap.capi.sample.ros_ml_client_heap
mldb install -u BUILD/com.magicleap.capi.sample.ros_ml_client_heap.mpk

# mldb launch com.magicleap.capi.sample.ros_ml_client_heap
# mldb terminate com.magicleap.capi.sample.ros_ml_client_heap
