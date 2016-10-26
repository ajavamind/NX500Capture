// Creates a broadcast client that sends focus/shutter key commands to NX500 cameras
// requires Internet Android permissions
// requires oscP5 libary installed in Processing SDK 3.0+

// Written by Andy Modla
// last revision 2016/10/26
// use at you own risk with NX-KS2 hack for Samsung NX500 cameras
// turn on Wifi in camera

import netP5.*;
//import oscP5.*; // does not use this part of oscP5 library

UdpClient client; 
String BROADCAST = "255.255.255.255";
int port = 8000;

color black = color(0);   // black
color gray = color(128);
color white = color(255); // white
color red = color(255, 0, 0);
color lightblue = color(64, 64, 128);
color yellow = color(255, 204, 0); 

boolean focus = false;
boolean focusHold = false;
boolean shutter = false;
boolean first_tap = false;

int counter = 0;
int BUTTON_SIZE = 300;
int DELAY = 30;


void setup() { 
  size(800, 400);
  orientation(LANDSCAPE); 
  background(0);

  try {
    client = new UdpClient( BROADCAST, port);
    if (client == null) {
      println("Error UDP Client");
    }
  }
  catch (Exception e) {
    println("Wifi problem");
  }
} 

void draw() { 
  background(0);
  textSize(48);
  stroke(255);

  // focus hold button
  if (focusHold)
    fill(lightblue);
  else
    fill(white);
  rect(50, 50, BUTTON_SIZE, BUTTON_SIZE, 25);
  if (focusHold)
    fill(yellow);
  else
    fill(0);
  text("FOCUS", 130, 190);
  text("HOLD", 130, 240);

  // shutter button
  if (shutter && focus)
    fill(red);
  else if (shutter)
    fill(red);
  else if (focus)
    fill(lightblue);
  else
    fill(white);
  ellipse(600, 200, BUTTON_SIZE, BUTTON_SIZE);
  if (focus)
    fill(yellow);
  else
    fill(black);
  text("SHUTTER", 500, 220);

  if (counter > 0) {
    counter--;
    if (counter == 0) {
      if (focus) {
        focus = false;
      }
      if (shutter) {
        shutter = false;
      }
    }
  }
} 

void mousePressed() {
  if (mouseX > 400) {
    // shutter button
    if (first_tap && !focusHold) {
      first_tap = false;
      shutter = true;
      client.send("C");
      println("CAPTURE");
      counter = DELAY;
    } else {
      if (focusHold) {
        shutter = true;
        client.send("S");
        println("SHUTTER");
        counter = DELAY;
      } else {
        first_tap = true;
        focus = true;
        client.send("F");
        println("FOCUS");
      }
    }
  } else {
    // Focus hold toggle button
    focusHold = !focusHold;
    if (focusHold) {
      client.send("F");
      println("FOCUS HOLD");
    } else {
      client.send("R");
      focus = false;
      first_tap = false;
      println("FOCUS RELEASE");
    }
  }
}

// NX500 commands
//else if (*buf == 'F') {
//  system("st key push s1"); // focus press hold
//}
//else if (*buf == 'C') {
//  system("st key push s2; st key release s2; st key release s1"); // shutter press and release all
//}
//else if (*buf == 'S') {
//  system("st key push s2; st key release s2"); // shutter press and release
//}
//else if (*buf == 'R') {
//  system("st key release s2; st key release s1"); // shutter release all
//}