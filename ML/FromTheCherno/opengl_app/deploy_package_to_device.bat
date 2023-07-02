@echo off
rem cls


rem mldb connect 192.168.86.247:5555
mabu opengl_app.package -t device
mldb uninstall opengl_app
mldb install -u .out/opengl_app/opengl_app.mpk
mldb launch com.sample.opengl_app
rem mldb terminate com.sample.opengl_app