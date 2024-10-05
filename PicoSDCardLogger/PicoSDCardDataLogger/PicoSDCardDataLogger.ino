#include <SD.h>

const int chipSelect = 17; // GP pin ID on Pico for chip select

// Sample data logging values
const String dataValues[] = {
  "<D: 12.5, 23.1, 34.2>",
  "<D: 13.6, 22.5, 31.9>",
  "<D: 11.4, 25.6, 30.0>",
  "<D: 14.1, 24.3, 29.8>",
  "<D: 10.9, 22.0, 32.5>"
};

int randomIndex; // A random index to retrieve data from the array

File dataLog; // Declare the log file to be used in the loop

void setup() {
  Serial.begin(115200); // Initiate the serial monitor
  while(!Serial); // Wait for the serial monitor to initialize

  while (!SD.begin(chipSelect)) {
    Serial.println("Failed to initialize SD card.");
  }
  Serial.println("SD card initialized successfully.");
}

void loop() {
  // Open a file in the SD card
  // Only one file can be open at a time
  // Specifying only the name or having a single forward
  // slash means the file will be located in the root directory
  dataLog = SD.open("dataLog.txt", FILE_WRITE);
  // If the file is OK, write to it
  if (dataLog) {
    randomIndex = random(0, 5); // A random index between 0 and 4
    dataLog.println(dataValues[randomIndex]); // Write a random data line to the file
    dataLog.close(); // Close the file after we're done with it
    Serial.println(dataValues[randomIndex]); // Display the same line in the serial monitor to compare the integrity
  } else {
    Serial.println("Failed to open dataLog.txt."); // Display error message in the serial monitor
  }

  delay(1000); // Wait for a second between loggings
}
