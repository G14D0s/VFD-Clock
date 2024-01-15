
#include <Wire.h>
#include <Adafruit_MCP23X17.h>
Adafruit_MCP23X17 mcp1;

#include <TimeLib.h>
#include <DS1307RTC.h> // gilt auch für DS3231

// externe variablen können über verschiedene Sketche in einem ordner verwendet werden.
extern unsigned long currentMillis;
extern unsigned long seconds;
extern unsigned long minutes;
extern unsigned long hours;
extern unsigned long days;

extern bool VFDTabelle[11][10];
extern bool Zahlen[10] [7];

void setup() {
  Serial.begin(115200);

  if (!mcp1.begin_I2C(0x21)) { //0,&Wire
    Serial.println("Error.");
    while (1);
  }else{
    Serial.println("I2C Success!");
  }

  // initialisieren aller Ausgänge
  for (byte i = 0; i <=  15; i++) {
    mcp1.pinMode(i, OUTPUT);
  }
  for (byte i = 0; i <= 13; i++){
    pinMode(i, OUTPUT);
  }
}

void loop() {
  RTC_UhrzeitErfassen();  // abspeichern der Zeit in Variabeln
  //printTime();
  UhrzeitZuArray();       // Übersetzen der Zeit in Array
  //ArrayAusdruck(VFDTabelle);
                          // Ansteuern des Displays mit Werten aus dem Array 
  VFDAnsteuerung(50,100); // frequenz von 50 und Helligkeit von 100%
}