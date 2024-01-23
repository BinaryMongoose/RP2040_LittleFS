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


void setup() {
  Serial.begin(115200);
  LittleFS.begin();
  delay(2000);

  file = LittleFS.open("/main/data/file.txt", "r");
}


void loop() {
  if (Serial.available()) {
    input = Serial.readStringUntil('\n');
    if (input == "hello") {
      write_file(file);
    }
  }
}


void write_file(File file){
  if (file) {
    while (file.available()) {
      Serial.write(file.read());
    }
    Serial.println("---------------");
    file.close();
  }
}