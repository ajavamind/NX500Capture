# NX500 Capture

This repository contains code for the Samsung NX500 camera with the NX-KS modification. With this code multiple cameras can take photos simultaneously. For information about the camera modifications See https://www.facebook.com/NXKS2/ and https://github.com/ottokiksmaler/nx500_nx1_modding

The code consists of two parts, 1) Broadcast message receiver in the NX500 camera and 2) Processing Android Broadcast Sender App. The Broadcast receiver on the NX500 runs in the background to respond to commands. The Android app sender transmits broadcast messages over a local network to control the NX500 camera focus and shutter operations via simulated key presses. 


![App Screen](./NX500Capture/NX500app.png)


The NX500 commands are:

F  system("st key push s1") // focus press hold

C  system("st key push s2; st key release s2; st key release s1") // capture: shutter press and release all

S  system("st key push s2; st key release s2") // shutter press and release

R  system("st key release s2; st key release s1") // focus and shutter release

Notes:

The Processing library OSCP5 reference information used for UDP broadcast is available at http://www.sojamo.de/libraries/oscp5/reference/index.html

https://www.processing.org for the Processing 3+ SDK, Android Mode

Broadcast receiver code based on:

https://www.experts-exchange.com/viewCodeSnippet.jsp?codeSnippetId=23948

https://www.experts-exchange.com/questions/23074851/Sending-Broadcast-packets-using-UDP-in-Linux-C.html
