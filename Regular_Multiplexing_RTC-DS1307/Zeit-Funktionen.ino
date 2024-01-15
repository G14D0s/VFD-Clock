
bool VFDTabelle[11][10]{
// Anoden: 
// A,B,C,D,E,F,G,7,8,9     Grids:
  {0,0,0,0,0,0,0,0,0,0},// 0
  {0,0,0,0,0,0,0,0,0,0},// 1
  {0,0,0,0,0,0,0,0,0,0},// 2
  {0,0,0,0,0,0,0,0,0,0},// 3
  {0,0,0,0,0,0,0,0,0,0},// 4 
  {0,0,0,0,0,0,0,0,0,0},// 5 H
  {0,0,0,0,0,0,0,0,0,0},// 6 M
  {0,0,0,0,0,0,0,0,0,0},// 7 M
  {0,0,0,0,0,0,0,0,0,0},// 8 S
  {0,0,0,0,0,0,0,0,0,0},// 9 S
  {0,0,0,0,0,0,0,0,0,0} //10 M
};

// zum übersetzen der zahlen in 7-Segment
bool Zahlen[10] [7] =
{
  //a, b, c, d, e, f, g
  {1, 1, 1, 1, 1, 1, 0}, //0
  {0, 1, 1, 0, 0, 0, 0}, //1
  {1, 1, 0, 1, 1, 0, 1}, //2
  {1, 1, 1, 1, 0, 0, 1}, //3
  {0, 1, 1, 0, 0, 1, 1}, //4
  {1, 0, 1, 1, 0, 1, 1}, //5
  {1, 0, 1, 1, 1, 1, 1}, //6
  {1, 1, 1, 0, 0, 0, 0}, //7
  {1, 1, 1, 1, 1, 1, 1}, //8
  {1, 1, 1, 1, 0, 1, 1}  //9
};

  unsigned long currentMillis;
  unsigned long seconds;
  unsigned long minutes;
  unsigned long hours;
  unsigned long days;


void UhrzeitErfassen(){
  currentMillis = millis();
  seconds = currentMillis / 1000;
  minutes = seconds / 60;
  hours = minutes / 60;
  days = hours / 24;
  currentMillis %= 1000;
  seconds %= 60;
  minutes %= 60;
  hours %= 24;
}

void printTime(){
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.println(seconds);
  Serial.print(days);
  Serial.println(" Days");
}


void UhrzeitZuArray(){

  PartAndPassValue(hours,   5, 6);
  PartAndPassValue(minutes, 7,10);
  PartAndPassValue(seconds, 8, 9);
  LightUpBigDIv(seconds,6);


}
void LightUpBigDIv(int Time, int Pos){
  if(Time%2==0||Time==0){
    VFDTabelle[Pos][7]=1;
  }else{
    VFDTabelle[Pos][7]=0;
  }
}
void PartAndPassValue(int Time, int Pos1, int Pos2){
  int T1 = Time/10;
  int T2 = Time%10;

  WriteInArray(T1,Pos1);
  WriteInArray(T2,Pos2);
}

void WriteInArray(int ZahlWert,int ChosenRow){
  for(int i=0;i<7;i++){
    VFDTabelle[ChosenRow][i] = Zahlen[ZahlWert][i];
  }
}


void ArrayAusdruck(bool PrintArray[11][10]){
  Serial.println("Array:");
  for(int PrintRows = 0;PrintRows<11;PrintRows++){
    for(int PrintCols = 0;PrintCols<9;PrintCols++){
      Serial.print(PrintArray[PrintRows][PrintCols]);
      Serial.print(",");
    }
    Serial.println(PrintArray[PrintRows][9]);
  }
  Serial.println();
}


//################### RTC-DS1307 ###################
void RTC_UhrzeitErfassen(){
  tmElements_t tm;

  if (RTC.read(tm)) {
    // Serial.print("Ok, Time = ");
    // print2digits(tm.Hour);
    // Serial.write(':');
    // print2digits(tm.Minute);
    // Serial.write(':');
    // print2digits(tm.Second);
    // Serial.print(", Date (D/M/Y) = ");
    // Serial.print(tm.Day);
    // Serial.write('/');
    // Serial.print(tm.Month);
    // Serial.write('/');
    // Serial.print(tmYearToCalendar(tm.Year));
    // Serial.println();
    hours=tm.Hour;
    minutes=tm.Minute;
    seconds=tm.Second;
  } 
  else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
      UhrzeitErfassen();
    }
  }
}


void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}


