/* 
  This is a semi-complicated program, so check out the function diagram in this folder.
  That's where you'll find most of the information regarding this program. 

  This script shows how to work with directories in LittleFS.
  Loops through each folder looking at what's stored in flash.
  Prints a handy tree, like if you opened the terminal and typed 'tree'. At least in powershell. 

  One thing to note, if you give it a bad directory it won't print anything other than the root. 
  This is because here is no error checking done, nothing will light on fire, but this is not ideal. 
  Though LittleFS does handle these internally, so calling dir.next doesn't return anything. 
*/
#include <LittleFS.h>


void setup() {
  Serial.begin(115200);
  LittleFS.begin();
  
  // Wait for Serial port to start...
  delay(3000);

  // For those familiar with working in command line, the "." (period/dot)
  // means to start in THIS directory. In this case, the root. 
  // A more readable approach would be:  
  //    start_tree("/");    With the slash standing for the root directory.
  // But the dot is good for educational purposes. 
  // This also shows some interesting things about LittleFS, if a slash is provided, 
  // LittleFS will start at the root directory. 
  // So "/main" will look in the root directory for a directory called "main" 
  start_tree(".");

}


void start_tree(String path) {
  // The only reason this function exists is so we can print the root folder.
  // We could make an if check in print_tree, but I'm much too lazy to figure that out.
  Serial.println(path);
  print_tree(path, 0); 
}


// This is a recursive function. Dangerous if left unchecked, but very usefull when employed correctelly. 
// More info in the function diagram. 
void print_tree(String dir_name, int level) {
  // Open the directory with LittleFS
  Dir dir = LittleFS.openDir(dir_name);

  // This actually caused a lot of headahes. You must keep note of the 
  // full path to the directory, or else it won't work. 
  String full_path = dir_name;

  while(true) {
    // If there are no more objects, exit.
    if (!dir.next()) {
      break;
    }

    // Indent the layers of the tree.
    for (uint8_t i = 0; i < level; i++) {
      Serial.print("|  ");
    }


    // For very file/directory, make a branch.
    Serial.print("|--");
    Serial.print(dir.fileName());

    // Checking if it's a directory.
    if (dir.isDirectory()) {
      // Print a newline, we want to nest the directories. 
      Serial.println();
      // Update the path, add the sub-directory we are going into to the directory we started in. 
      full_path = dir_name + "/" + dir.fileName();
      // Call the function for the sub-directory.
      print_tree(full_path, level + 1);
    } else {
      // Add a tab to seperate file name and size.
      Serial.print("\t");
      // Print the file size. 
      Serial.println(dir.fileSize());
    }
  }
}

// Once again, unused.
void loop() {
}