UART gps(0, 1); // Create UART object to read from the GPS
char gpsChar; // Used to read from the GPS

void setup() {
  Serial.begin(115200); // Initialize the serial monitor
  gps.begin(9600); // Begin UART communication for the GPS at 9600 baud rate
}

void loop() {
    while (gps.available()) { // Check if data is available from the GPS module
      gpsChar = (char) gps.read(); // Read one byte and cast it to a char
      Serial.print(gpsChar); // Print the character to the Serial Monitor
    }
}
