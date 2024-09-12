#include <TinyGPSPlus.h>

// GPS module configuration constants
static const int TXPin = 0, RXPin = 1;
static const uint32_t GPSBaud = 9600;

UART gpsSerial(TXPin, RXPin); // The UART object for the GPS
TinyGPSPlus tinyGPSPlus; // The TinyGPSPlus object

void setup()
{
  Serial.begin(115200); // Initialize the serial monitor
  gpsSerial.begin(GPSBaud); // Initialize the GPS connection at 9600 baud and 8N1

  // Print table header
  Serial.println(F("+--------------+--------+------------+-------------+-----+------------+--------+--------------+--------+--------+"));
  Serial.println(F("| # Satellites | HDOP   | Latitude   | Longitude   | Age | Date       | Time       | Altitude | Speed  | Course |"));
  Serial.println(F("|              |        | (deg)      | (deg)       | (ms)| (dd/mm/yy) | (hh:mm:ss) | (m)      | (km/h) | (deg)  |"));
  Serial.println(F("+--------------+--------+------------+-------------+-----+------------+------------+----------+--------+--------+"));
}

void loop()
{
  // Read from the GPS module, encode in TinyGPSPlus
  while (gpsSerial.available())
  {
    tinyGPSPlus.encode(gpsSerial.read());
  }

  // Extract and print formatted data using TinyGPSPlus
  // Use the ternary operator to check if each value is valid.
  // If the value is valid, print it out. If not, use an asterisk instead.
  Serial.print(F("| "));
  Serial.print(tinyGPSPlus.satellites.isValid() ? tinyGPSPlus.satellites.value() : '*');
  Serial.print(F("           | "));
  Serial.print(tinyGPSPlus.hdop.isValid() ? tinyGPSPlus.hdop.hdop() : '*');
  Serial.print(F("    | "));
  Serial.print(tinyGPSPlus.location.isValid() ? tinyGPSPlus.location.lat() : '*', 6); // Display 6 decimal places
  Serial.print(F("  | "));
  Serial.print(tinyGPSPlus.location.isValid() ? tinyGPSPlus.location.lng() : '*', 6); // Display 6 decimal places
  Serial.print(F(" | "));
  Serial.print(tinyGPSPlus.location.isValid() ? tinyGPSPlus.location.age() : '*');
  Serial.print(F("  | "));
  Serial.print(tinyGPSPlus.date.isValid() ? String(tinyGPSPlus.date.day()) + "/" + String(tinyGPSPlus.date.month()) + "/" + String(tinyGPSPlus.date.year()) : "*");
  Serial.print(F("   | "));
  Serial.print(tinyGPSPlus.time.isValid() ? String(tinyGPSPlus.time.hour()) + ":" + String(tinyGPSPlus.time.minute()) + ":" + String(tinyGPSPlus.time.second()) : "*");
  Serial.print(F("    | "));
  Serial.print(tinyGPSPlus.altitude.isValid() ? tinyGPSPlus.altitude.meters() : '*');
  Serial.print(F("  | "));
  Serial.print(tinyGPSPlus.speed.isValid() ? tinyGPSPlus.speed.kmph() : '*', 2); // Display 2 decimal places
  Serial.print(F("  | "));
  Serial.print(tinyGPSPlus.course.isValid() ? tinyGPSPlus.course.deg() : '*', 6); // Display 6 decimal places
  Serial.println(F(" |"));

  delay(1000);
}
