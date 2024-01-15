
extern bool VFDTabelle[11][10];

//                      a,  b,  c, d, e, f, g
int AnodenPins[10] = { 12, 11, 10, 9, 8, 7, 6, 5, 4, 3 };


void VFDAnsteuerung(int f, int AnPerc) {
  //f - Bildschirmfrequenz
  //AnPerc - Helligkeit in %


  for (int Feld = 0; Feld <= 10; Feld++) {
    //AnodenDurchLauf(Feld, f, AnPerc);
    FelderDurchLauf(Feld, f, AnPerc);
  }
}


void FelderDurchLauf(int Feld, int f, int AnPerc){
  long ONProzent = AnPerc / 100;
  long t = (1/f)*10000000;
  long fp = t/11;
  long ontime = fp * ONProzent;
  long offtime = fp - fp * ONProzent;



  ///////////////////////////////////////
  SchreibFeldUndAnoden(Feld, true);

  //delay(500);
  delayMicroseconds(ontime);

  ///////////////////////////////////////

  SchreibFeldUndAnoden(Feld, false);
    //digitalWrite(13,HIGH);
  //delay(500);
  delayMicroseconds(offtime);
    //digitalWrite(13,LOW);
}


void SchreibFeldUndAnoden(int Feld, bool AnOAus) {

    mcp1.digitalWrite(Feld,AnOAus);

    for (int AktuelleAnode = 0; AktuelleAnode < 10; AktuelleAnode++) {
      /*
      Serial.print("Internal Address: ");
      Serial.println(AktuelleAnode);
      Serial.print("actual Pin: ");
      Serial.println(AnodenPins[AktuelleAnode]);
      Serial.print("Array Value for Pin: ");
      Serial.println(VFDTabelle[Feld][AktuelleAnode]);
      */
      digitalWrite(AnodenPins[AktuelleAnode], VFDTabelle[Feld][AktuelleAnode]);
    }

}


















void AnodenDurchLauf(int Spalte, int f, int AnPerc) {
  long ONProzent = AnPerc / 100;

  long fp = f / 10 + f % 10;
  long ontime = fp * ONProzent;
  long offtime = fp - fp * ONProzent;

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