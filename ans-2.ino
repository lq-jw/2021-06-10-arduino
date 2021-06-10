// C++ code
//
#define NOTE_C3 131
#define NOTE_D3 147
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_G3 196
#define NOTE_A3 220
#define NOTE_B3 247
#define NOTE_C4 262

int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

int melody[] = {
  NOTE_C3,
  NOTE_D3,
  NOTE_E3,
  NOTE_D3,
  NOTE_E3,
  NOTE_G3,
  NOTE_D3,
  0
};

int noteDurartions[] = {
  8,8,2,8,4,4,2,2};

byte colDataMatrix[8] = {
   B11111110,
   B11111101,
   B11111011,
   B11110111,
   B11101111,
   B11011111,
   B10111111,
   B01111111
}; //掃描

byte rowDataMatrix[8] = {
   B00000000,
   B01000010,
   B10100101,
   B00000000,
   B00111100,
   B01000010,
   B01111110,
   B00000000
}; //圖案

byte rowDataMatrix2[8] = {
   B00000000,
   B00100000,
   B10010000,
   B00001000,
   B00001000,
   B10010000,
   B00100000,
   B00000000
}; //圖案2

int thisNote = -1,noteDurartion = 0;
long previousTime = 0,
	 presentTime = 0,
	 pauseBetweenNotes = 0;

	
void chackToPlay(){
  presentTime = millis();
  if(presentTime - previousTime >= pauseBetweenNotes){
    thisNote += 1;
    if(thisNote >= 8){
      thisNote = -1;
      pauseBetweenNotes = 100;
      previousTime = millis();
    }else{
      noteDurartion = 500 / noteDurartions[thisNote];
      tone(9,melody[thisNote],noteDurartion);
      pauseBetweenNotes = noteDurartion * 1.2;
      previousTime = millis();
    }
  }
}

int buttonPin = 2;

void setup()
{
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(2, INPUT_PULLUP);
}

byte previousState = 1,presentState = 1, patternNumber = 0;

void loop()
{
  presentState = digitalRead(buttonPin);
  if(presentState == 0 && previousState == 1){
    patternNumber++;
    if(patternNumber > 1)
      patternNumber = 0;
  }
  if(patternNumber == 0){
    for(int i = 0; i < 8; i++){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix[i]);
    digitalWrite(latchPin, HIGH);
    chackToPlay();
    delay(1);
  }}
  else{
   for(int i = 0; i < 8; i++){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix2[i]);
    digitalWrite(latchPin, HIGH);
    chackToPlay();
    delay(1);
   }}
  delay(2);
  previousState = presentState;
}