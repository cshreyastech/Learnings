# /bin/bash


# mabu gl_eye_tracking5.package -t device
mldb install -u BUILD/gl_eye_tracking5.mpk

mldb connect 192.168.86.44:5555
mldb terminate com.magicleap.capi.sample.gl_eye_tracking5
mldb uninstall com.magicleap.capi.sample.gl_eye_tracking5
mldb install -u BUILD/gl_eye_tracking5.mpk
mldb launch com.magicleap.capi.sample.gl_eye_tracking5
# mldb terminate com.magicleap.capi.sample.gl_eye_tracking5
