/* 
  A Bare script. Can be used on "any" RP2040 board.
  Writes 1-10 to a file, then reads file. 

  Before you compile and upload, you must set up the partitioning for the FLASH.
  Steps to partition:
   1. You must have the correct board selected in the "tools" menu. (RP2040)
   2. You will see a bunch of new buttons. Click "Flash Size"
   3. Select whatever one, except 8MB (No FS) My go to is 8MB (Sketch: 2MB, FS: 6MB)

   You usually don't need more than 2MB for a sketch.
*/
#include <LittleFS.h>

File file;

void setup() {
  Serial.begin(115200);
  // Must be called at the start. Sets up the partitioning so
  // data is not written into areas with code. Which would be bad.
  LittleFS.begin();

  // LittleFS and the Serial port need time to start. 
  // This isn't a problem while looping, but it is during setup. 
  delay(2000); // 2 seconds is good. (2000ms = 2s)

  // Opens file in "write" mode.
  // In systems were any data is good data DO NOT USE WRITE MODE.
  // Write deletes everything in the file. Think of write as "overwrite".
  // Use append (a) instead. New data doesn't replace old data, it's added to the end.
  file = LittleFS.open("/main/data/file.txt", "w");

  // Let's check if the file exists before trying to write anything.
  if (file) {
    // Writing to flash. Can your microcontroller count to 10? Mine can.
    for (int count = 1; count < 11; count++) {
      file.println(count);
    }
    // Flush moves all the data from the write buffer into actual storage.
    file.flush();
    Serial.println("Writing to file...");
    // Closes the file, and should save everything. SHOULD, not always.
    // If you don't close the file you run into the risk of corrupting the data.
    file.close();
    Serial.println("File closed.");
  } else {
    Serial.println("No file!");
  }

  // Opens the same file in "read" mode. You cannot write data in read mode, it will fail.
  file = LittleFS.open("/main/data/file.txt", "r");

  // It's best practice to check if the file exists before trying to do anything to it.
  if (file) {
    Serial.println("Opening file...");
    // WHILE there is data in the file we will write the data to the Serial monitor.
    while (file.available()) {
      // Here we are using Serial.write instead of print. 
      // This is because we want the RAW (byte) data.  
      Serial.write(file.read()); 
    }
    Serial.println("\nFile read.");
    // Let's not corrupt anything.
    file.close();
  } else {
    Serial.println("No file!");
  }
}

// Lonely. :'(
void loop() {
}
