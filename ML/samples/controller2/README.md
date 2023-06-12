# controller2 Sample

This sample demonstrates how to get the state of the controller2s.
This includes getting the position and orientation of the controller2
through the MLSnapshot system as well as the state of the controller2s
buttons.

See the ml_input.h header for the MLInputcontroller2Callbacks, which
can also be used to get events on controller2 input.

## Prerequisites

## Gui
 - No gui

## Launch from Cmd Line

Host: ./controller2 --help
Device: mldb launch com.magicleap.capi.sample.controller2

## What to Expect

 - A cube is rendered at the 6dof position of the controller2. Also the
   controller2 information is shown as text next to the controller2.

 - This sample is using the MLInput API to get the controller2 information.
