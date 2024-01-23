/*
  This script shows you how to send data over serial. If you want to
  see the basic concepts of LittleFS, look at the "Bare.ino" script. 
  The script waits for an ask, such as "GIVE ME DATA", and then writes 
  all the data located in the file over the serial port.

  This is only one side of the program. You will need a script to 
  read the data from the serial port and store it in a file on your computer. 
*/
#include <LittleFS.h>

File file;
String input;

// The command that the program waits for to send the file.
String command = "please"

void setup() {
  Serial.begin(115200);
  LittleFS.begin();
  delay(2000);

  file = LittleFS.open("/main/data/file.txt", "r");
}


void loop() {
  // If the serial port is ready, check for input. 
  if (Serial.available()) {  
    // Looks like what it does. 
    // User enters a string, when the Serial port detects a "\n" (newline)
    // the program sends the file.
    input = Serial.readStringUntil('\n');

    // If the line that the Serial port reads in is the same as the command,
    // then it calls a function which writes the file to the Serial port. 
    if (input == command) {
      write_file(file);
    }
  }
}


void write_file(File file) {
  // Let's check if the file exists first.
  if (file) {
    // If it does, then while there is unread data in the file, 
    // write all the data into the Serial port.
    while (file.available()) {
      Serial.write(file.read());
    }
    // No corrupted files please!
    file.close();
  }
}