@echo off
rem cls

rem mabu opengl_app.package -t device

mldb connect 192.168.86.21:5555
mldb uninstall com.sample.opengl_app
mldb install -u .out/opengl_app/opengl_app.mpk
mldb launch com.sample.opengl_app
rem mldb terminate com.sample.opengl_app