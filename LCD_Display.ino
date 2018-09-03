int DI = 12;
int RW = 11;
int DB[] = {3, 4, 5, 6, 7, 8, 9, 10};//Use an array to define the pins
int Enable = 2;
char text[] = {"What the fuck did you just fucking say about me, you little bitch? I'll have you know I graduated top of my class in the Navy Seals, and I've been involved in numerous secret raids on Al-Quaeda, and I have over 300 confirmed kills. I am trained in gorilla warfare and I'm the top sniper in the entire US armed forces. You are nothing to me but just another target. I will wipe you the fuck out with precision the likes of which has never been seen before on this Earth, mark my fucking words. You think you can get away with saying that shit to me over the Internet? Think again, fucker. As we speak I am contacting my secret network of spies across the USA and your IP is being traced right now so you better prepare for the storm, maggot. The storm that wipes out the pathetic little thing you call your life. You're fucking dead, kid. I can be anywhere, anytime, and I can kill you in over seven hundred ways, and that's just with my bare hands. Not only am I extensively trained in unarmed combat, but I have access to the entire arsenal of the United States Marine Corps and I will use it to its full extent to wipe your miserable ass off the face of the continent, you little shit. If only you could have known what unholy retribution your little 'clever' comment was about to bring down upon you, maybe you would have held your fucking tongue. But you couldn't, you didn't, and now you're paying the price, you goddamn idiot. I will shit fury all over you and you will drown in it. You're fucking dead, kiddo."};

void LcdCommandWrite(int value) {
  // Define all pins
  int i = 0;
  for (i = DB[0]; i <= DI; i++) {
    digitalWrite(i, value & 01); //Because 1602 LCD signal identification is D7-D0 (not D0-D7), here is used to invert the signal.
    value >>= 1;
  }
  digitalWrite(Enable, LOW);
  delayMicroseconds(1);
  digitalWrite(Enable, HIGH);
  delayMicroseconds(1);
  digitalWrite(Enable, LOW);
  delayMicroseconds(1);
}

void LcdDataWrite(int value) {
  // Define all pins
  int i = 0;
  digitalWrite(DI, HIGH);
  digitalWrite(RW, LOW);
  for (i = DB[0]; i <= DB[7]; i++) {
    digitalWrite(i, value & 01);
    value >>= 1;
  }
  digitalWrite(Enable, LOW);
  delayMicroseconds(1);
  digitalWrite(Enable, HIGH);
  delayMicroseconds(1);
  digitalWrite(Enable, LOW);
  delayMicroseconds(1);
}
void setup (void) {
  randomSeed(analogRead(0));
  int i = 0;
  for (i = Enable; i <= DI; i++) {
    pinMode(i, OUTPUT);
  }
  delay(150);
  // Initialize the LCD
  LcdCommandWrite(0x3c);  // Set to 8-bit interface, 2 lines display, 5x10 text size
  delay(64);
  LcdCommandWrite(0x3c);  // Set to 8-bit interface, 2 lines display, 5x10 text size
  delay(50);
  LcdCommandWrite(0x3c);  // Set to 8-bit interface, 2 lines display, 5x10 text size
  delay(20);
  LcdCommandWrite(0x04);  // Set Cursor Move Direction 
  delay(20);
  LcdCommandWrite(0x0C);  // Enable Display/Cursor
  delay(20);
  LcdCommandWrite(0x10);  // Move Cursor/Shift Display
  delay(20);
  LcdCommandWrite(0x3c);  // Set to 8-bit interface, 2 lines display, 5x10 text size
  delay(20);
  LcdCommandWrite(0x01);  // The screen is empty and the cursor position is zeroed
  delay(100);
}

void LcdPrint32(char* value) {
  for (int j=0; j <= strlen(value); j+=32){
    for (int i=0; i <= 16; i++){
      LcdCommandWrite(0x80+i);
      LcdDataWrite(value[i+j]);
    }
    delay(250);
    for (int i=0; i <= 16; i++){
      LcdCommandWrite(0xc0+i);
      LcdDataWrite(value[i+j+16]);
    }
  delay(400);
  }
}

void LcdPrint16(char* value) {
  for (int j=0; j <= strlen(value); j+=16){
    for (int i=0; i <= 16; i++) {
      LcdCommandWrite(0x80+i);
      LcdDataWrite(value[i+j]);
    }
  delay(400);
  }
}

void LcdPrintWord(char* value) {
  delay(150);
  LcdCommandWrite(0x01);
  delay(150);
    for (int i = 0; i <strlen(text); i++) {
      if (text[i] == ' ') {
        delay(150);
        LcdCommandWrite(0x01);
        delay(150);
        Serial.print(" ln ");
      } else {
        LcdDataWrite(text[i]);
        Serial.print(text[i]);
      }
    }
}

void loop (void) {
  LcdPrintWord(text);
}
