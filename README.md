# NX500 Capture

This repository contains code for the NX500 camera NX-KS modification. It consists of two parts, 1)Broadcast receiver and 2)Processing Android Broadcast Sender. The Android app sender transmits broadcast messages over a local network to control the NX500 camera focus and shutter operation via simulated key presses. The Broadcast receiver on the NX500 runs in the background to respond to commands.

The NX500 commands are:

F  system("st key push s1"); // focus press hold

C  system("st key push s2; st key release s2; st key release s1"); // capture: shutter press and release all

S  system("st key push s2; st key release s2"); // shutter press and release

R  system("st key release s2; st key release s1"); // focus and shutter release

