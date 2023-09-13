# /bin/bash


# mabu gl_eye_tracking4.package -t device
mldb install -u BUILD/gl_eye_tracking4.mpk

# mldb connect 192.168.86.37:5555
mldb terminate com.magicleap.capi.sample.gl_eye_tracking4
mldb uninstall com.magicleap.capi.sample.gl_eye_tracking4
mldb install -u BUILD/gl_eye_tracking4.mpk
mldb launch com.magicleap.capi.sample.gl_eye_tracking4
# mldb terminate com.magicleap.capi.sample.gl_eye_tracking4
