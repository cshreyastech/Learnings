# /bin/bash

rm -rf BUILD/*

mabu gl_eye_tracking5.package -t device
# mldb connect 192.168.86.44:5555

mldb install -u BUILD/gl_eye_tracking5.mpk

mldb terminate com.magicleap.capi.sample.gl_eye_tracking5
mldb uninstall com.magicleap.capi.sample.gl_eye_tracking5
mldb install -u BUILD/gl_eye_tracking5.mpk
mldb launch com.magicleap.capi.sample.gl_eye_tracking5

# mldb terminate com.magicleap.capi.sample.gl_eye_tracking5
