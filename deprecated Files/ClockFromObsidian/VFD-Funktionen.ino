
extern bool VFDTabelle[11][10];

//                      a,  b,  c, d, e, f, g
int AnodenPins[10] = { 12, 11, 10, 9, 8, 7, 6, 5, 4, 3 };


void VFDAnsteuerung(int f, int AnPerc) {
  //f - Bildschirmfrequenz
  //AnPerc - Helligkeit in %


  for (int Spalte = 0; Spalte < 11; Spalte++) {
    AnodenDurchLauf(Spalte, f, AnPerc);
  }
}

void AnodenDurchLauf(int Spalte, int f, int AnPerc) {
  long ONProzent = AnPerc / 100;

  long fp = f / 10 + f % 10;
  long ontime = fp * ONProzent;
  long offtime = fp - fp * ONProzent;


  // Serial.print("Helligkeit: ");
  // Serial.print(ONProzent);
  // Serial.println("%");

  // Serial.print("FP: ");
  // Serial.println(fp);

  // Serial.print("On-Time: ");
  // Serial.println(ontime);
  // Serial.print("Off-Time: ");
  // Serial.println(offtime);

  SchreibAnodeUndFelder(Spalte, true);

  delay(500);// 
  delayMicroseconds(ontime *10-200);

  SchreibAnodeUndFelder(Spalte, false);

  delay(500);// 
  delayMicroseconds(offtime*10+200);
  
}

void SchreibAnodeUndFelder(int Spalte, bool AnOAus) {

  digitalWrite(AnodenPins[Spalte], AnOAus);

  for (int AktuellesFeld = 0; AktuellesFeld < 10; AktuellesFeld++) {
    mcp1.digitalWrite(Spalte, VFDTabelle[Spalte][AktuellesFeld]);
  }
}