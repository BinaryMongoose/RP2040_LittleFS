/* 
  This script shows how to work with directories in LittleFS.
  
  Loops through each folder looking at what's stored in flash.
*/
#include <LittleFS.h>


File file;


void setup() {
  Serial.begin(115200);
  LittleFS.begin();
  
  delay(3000);

  print_tree(".", 0); 

}


void loop() {
}


void print_tree(String dir_name, int numTabs) {
  Dir dir = LittleFS.openDir(dir_name);

  String full_path = dir_name;

  while(true) {
    // No more files.
    if (!dir.next()) {
      break;
    }

    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }

    Serial.print(dir.fileName());

    if (dir.isDirectory()) {
      Serial.println("/");
      full_path = dir_name + "/" + dir.fileName();
      print_tree(full_path, numTabs + 1);
    } else {
      Serial.print("\t");
      Serial.println(dir.fileSize());
    }
  }
}
