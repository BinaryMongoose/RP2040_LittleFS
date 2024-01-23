#include <Adafruit_GPS.h>
#include <Adafruit_PMTK.h>
#include <NMEA_data.h>

#include <LittleFS.h>

// what's the name of the hardware serial port?
#define GPSSerial Serial1

// Connect to the GPS on the hardware port
Adafruit_GPS GPS(&GPSSerial);

unsigned long gpsTimer = 0;
int gpsInterval = 1000;

File file;

void setup() {
  Serial.begin(115200);
  setup_gps();
  
  delay(1000);
  LittleFS.begin();

  Dir dir = LittleFS.openDir(".");
  while (dir.next()) {
      Serial.println(dir.fileName());
      if(dir.fileSize()) {
          File f = dir.openFile("r");
          Serial.println(f.size());
      }
  }  
  
  if(dir.next()) {
    Serial.println("Files exist.");
  } else {
    Serial.println("Nothing here!");
  }

}

int count = 0;
String input;

void loop() {
  // update_gps();

  if (Serial.available()) {
    input = Serial.readStringUntil('\n');
    if (input == "hello") {
      write_file(file);
    }
  }

  // if (millis() - gpsTimer > gpsInterval) {
  //   gpsTimer = millis();

  //   if(GPS.fix) {
  //     Serial.print(GPS.latitudeDegrees, 6); Serial.print(GPS.lat);
  //     Serial.print(", ");
  //     Serial.print(GPS.longitudeDegrees, 6); Serial.println(GPS.lon);
  //   }

    // if(file) {
    //   count++;
    //   Serial.println(count);
      
    // file.print(GPS.latitudeDegrees, 6); file.print(GPS.lat);
    // file.print(",");
    // file.print(GPS.longitudeDegrees, 6); file.println(GPS.lon);

    // file.flush();
    // }

    // if (count > 60) {
    //   finish(file);
    // }
    // }
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


void finish(File file) {
  file.close();
  Serial.print("Done!");
  while(true) {
    delay(1000);
  }
}


void setup_gps(){
  // 9600 baud is the default rate for the Ultimate GPS
  GPSSerial.begin(9600);

  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate. Don't use anything lower.

  delay(1000);  // Wait for everyone to catch up.
  
  // Ask for firmware version
  GPSSerial.println(PMTK_Q_RELEASE);
}


void update_gps() {
  GPS.read();

  if (GPS.newNMEAreceived()) {
    GPS.parse(GPS.lastNMEA());
  }
}
