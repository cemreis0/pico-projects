#include <SD.h>

const int chipSelect = 17; // GP pin ID on Pico for chip select

File dataLog; // Declare the file we're gonna read from

void setup() {
  Serial.begin(115200); // Initiate the serial monitor
  while(!Serial); // Wait for the serial monitor to initialize

  while (!SD.begin(chipSelect)) {
    Serial.println("Failed to initialize SD card.");
  }
  Serial.println("SD card initialized successfully.");

  dataLog = SD.open("dataLog.txt"); // Open the file named dataLog.txt
  if (dataLog) { // If dataLog is open
    Serial.println("Reading from dataLog.txt");
    while (dataLog.available()) { // While there are bytes that can be read
      Serial.print((char) dataLog.read()); // Read bytes from the dataLog, cast bytes to char, print to serial monitor
    }
    dataLog.close(); // Close the file after we're done with it.
  } else {
    Serial.println("Failed to open dataLog.txt");
  }
}

void loop() {
  // Nothing needs to be done here
}
