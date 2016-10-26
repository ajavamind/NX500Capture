package processing.test.nx500capture;

import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import netP5.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class NX500Capture extends PApplet {

// Creates a broadcast client that sends focus/shutter key commands to NX500 cameras
// requires Internet Android permissions
// requires oscP5 libary installed in Processing SDK 3.0+

// Written by Andy Modla
// last revision 2016/10/26
// use at you own risk with NX-KS2 hack for Samsung NX500 cameras
// turn on Wifi in camera


//import oscP5.*; // does not use this part of oscP5 library

UdpClient client; 
String BROADCAST = "255.255.255.255";
int port = 8000;

int black = color(0);   // black
int gray = color(128);
int white = color(255); // white
int red = color(255, 0, 0);
int lightblue = color(64, 64, 128);
int yellow = color(255, 204, 0); 

boolean focus = false;
boolean focusHold = false;
boolean shutter = false;
boolean first_tap = false;

int counter = 0;
int BUTTON_SIZE = 300;
int DELAY = 30;


public void setup() { 
  
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

public void draw() { 
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

public void mousePressed() {
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
  public void settings() {  size(800, 400); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "NX500Capture" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
