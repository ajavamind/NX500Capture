# NX500 Capture

This repository contains code for the Samsung NX500 camera with the NX-KS modification. With this code multiple cameras can take photos simultaneously. For information about the camera modifications See https://www.facebook.com/NXKS2/ and https://github.com/ottokiksmaler/nx500_nx1_modding

The code consists of two parts, 1) Broadcast message receiver in the NX500 camera and 2) Processing Android Broadcast Sender App. The Broadcast receiver on the NX500 runs in the background to respond to commands. The Android app sender transmits broadcast messages over a local network to control the NX500 camera focus and shutter operations via simulated key presses. 

The NX500 commands are:

F  system("st key push s1") // focus press hold

C  system("st key push s2; st key release s2; st key release s1") // capture: shutter press and release all

S  system("st key push s2; st key release s2") // shutter press and release

R  system("st key release s2; st key release s1") // focus and shutter release

![App Screen](./NX500Capture/NX500app.png)
