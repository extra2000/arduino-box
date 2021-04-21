/**
 *
 * For microSD, connect Arduino Uno to the following pins:
 *   - PIN 10 -> CS
 *   - PIN 11 -> MOSI
 *   - PIN 12 -> MISO
 *   - PIN 13 -> SCK
 *   - 5V -> VCC
 *   - GND -> GND
 *
 * Note that these pin numbers are hardware pins and cannot be changed.
 *
 * For GPS, connect Arduino Uno to the following pins:
 *   - 5v -> VSS
 *   - PIN 3 -> RX
 *   - PIN 4 -> TX
 *   - GND -> GND
 */

#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

#include "TinyGPS++.h"

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

File gpsFile;
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
    Serial.begin(115200);
    ss.begin(GPSBaud);

    Serial.println(F("DeviceExample.ino"));
    Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
    Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
    Serial.println(F("by Mikal Hart"));
    Serial.println();

    Serial.print("Initializing SD card...");
    if (!SD.begin(10)) {
        Serial.println("initialization failed!");
        while (1);
    }
    Serial.println("initialization done.");
}

void loop()
{
    // This sketch displays information every time a new sentence is correctly encoded.
    while (ss.available() > 0)
        if (gps.encode(ss.read()))
            writeInfo();

    if (millis() > 5000 && gps.charsProcessed() < 10)
    {
        Serial.println(F("No GPS detected: check wiring."));
        while(true);
    }
}

void writeInfo()
{
    Serial.print(F("Location: ")); 
    if (gps.location.isValid())
    {
        Serial.print(gps.location.lat(), 6);
        Serial.print(F(","));
        Serial.print(gps.location.lng(), 6);

        gpsFile = SD.open("gps.csv", FILE_WRITE);
        if (gpsFile) {
            gpsFile.seek(EOF);
            gpsFile.print(gps.location.lat(), 6);
            gpsFile.print(F(","));
            gpsFile.print(gps.location.lng(), 6);
            gpsFile.println();
            gpsFile.close();
        }
    }
    else
    {
        Serial.print(F("INVALID"));
    }

    Serial.print(F("  Date/Time: "));
    if (gps.date.isValid())
    {
        Serial.print(gps.date.month());
        Serial.print(F("/"));
        Serial.print(gps.date.day());
        Serial.print(F("/"));
        Serial.print(gps.date.year());
    }
    else
    {
        Serial.print(F("INVALID"));
    }

    Serial.print(F(" "));
    if (gps.time.isValid())
    {
        if (gps.time.hour() < 10) Serial.print(F("0"));
        Serial.print(gps.time.hour());
        Serial.print(F(":"));
        if (gps.time.minute() < 10) Serial.print(F("0"));
        Serial.print(gps.time.minute());
        Serial.print(F(":"));
        if (gps.time.second() < 10) Serial.print(F("0"));
        Serial.print(gps.time.second());
        Serial.print(F("."));
        if (gps.time.centisecond() < 10) Serial.print(F("0"));
        Serial.print(gps.time.centisecond());
    }
    else
    {
        Serial.print(F("INVALID"));
    }

    Serial.println();
}
