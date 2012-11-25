#include <stdio.h>

// the pin that controls the brightness of RED LEDs
#define PIN_R 9
// the pin that controls the brightness of GREEN LEDs
#define PIN_G 10
// the pin that controls the brightness of BLUE LEDs
#define PIN_B 11

// index in color array where the current RED value will be stored
#define R 0
// index in color array where the current GREEN value will be stored
#define G 1
// index in color array where the current BLUE value will be stored
#define B 2

#define CMD_TARGET_RED 'r'
#define CMD_TARGET_GREEN 'g'
#define CMD_TARGET_BLUE 'b'
#define CMD_SET_MODE 'm'
#define CMD_SET_RATE 't'
#define CMD_SET_FADEMODE 'f'

#define MODE_OFF '0'
#define MODE_STILL '1'
#define MODE_FADE 'f'
#define MODE_TEST 't'
#define MODE_RAINBOW 'r'
#define MODE_BREATHE 'b'
#define MODE_POLICE 'p'

#define FADEMODE_LINEAR '1'
#define FADEMODE_SQUARE '2'
#define FADEMODE_CUBIC '3'


int color[3] = {0,0,0};
int colorT[3] = {0,0,0};
byte colorF[3] = {0,0,0};

unsigned int i = 0;
unsigned int rate = 50;
unsigned int c = 0;

byte mode = MODE_FADE;
byte fademode = FADEMODE_LINEAR;

void setup() {
  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  analogWrite(PIN_R, color[R]);
  analogWrite(PIN_G, color[G]);
  analogWrite(PIN_B, color[B]);
  
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() >= 2) 
    command(Serial.read(), Serial.read());
  if (Serial.available() > 0) 
    Serial.flush(); // throw any extra unpaired byte
  
  frame();
  
  if (i % (500/rate) == 0) {
    char state[32];
    sprintf(state, "%05u %04i %c %c %02x%02x%02x %02x%02x%02x", 
                    i, rate, char(mode), char(fademode), color[R], color[G], color[B], colorT[R], colorT[G], colorT[B]);
    Serial.println(state);
  }
  
  delayMicroseconds(rate);
  i++;
}

void command(char cmd, int val) {
  char cmd = msg.readChar();
  
  switch (cmd) {
    case CMD_TARGET_RED:
      colorT[R] = msg.readInt();
      break;
    case CMD_TARGET_GREEN:
      colorT[G] = msg.readInt();
      break;
    case CMD_TARGET_BLUE:
      colorT[B] = msg.readInt();
      break;
    case CMD_SET_MODE:
      mode = msg.readChar();
      break;
    case CMD_SET_FADEMODE:
      fademode = msg.readChar();
      break;
    case CMD_SET_RATE:
      rate = msg.readInt();
      break;
  }
}

void frame() {
  switch (mode) {
    case MODE_OFF:
      rgbWrite(0,0,0);
      break;
    case MODE_STILL:
      rgbWrite(colorT[R],colorT[G],colorT[B]);
      break;
    case MODE_FADE:
      rgbFade();
      break;
    case MODE_TEST:
      test();
      break;
    case MODE_RAINBOW:
      rainbow();
      break;
    case MODE_BREATHE:
      breathe();
      break;
    case MODE_POLICE:
      police();
      break;
  }
}

boolean fade(int ledPin, int i) {
  if (colorT[i] > color[i]) {
    switch (fademode) {
      case FADEMODE_LINEAR:
        color[i] += 1;
        break;
      case FADEMODE_SQUARE:
        Serial.println(((colorT[i] - color[i]) / 2) + 1);
        color[i] += ((colorT[i] - color[i]) / 2) + 1;
        break;
      case FADEMODE_CUBIC:
        color[i] += (colorT[i] - color[i]) / 3;
        break;
    }
  } else if (colorT[i] < color[i]) {
    switch (fademode) {
      case FADEMODE_LINEAR:
        color[i] -= 1;
        break;
      case FADEMODE_SQUARE:
        Serial.println(((color[i] - colorT[i]) / 2) + 1);
        color[i] -= ((color[i] - colorT[i]) / 2) + 1;
        break;
      case FADEMODE_CUBIC:
        color[i] -= (color[i] - colorT[i]) / 3;
        break;
    }
  }
  if (color[i] > 255) color[i] = 255;
  if (color[i] < 0) color[i] = 0;
  analogWrite(ledPin, color[i]);
  
  return color[i] == colorT[i];
}

void rgbWrite(int rVal, int gVal, int bVal) { analogWrite(PIN_R, rVal); color[R] = rVal; analogWrite(PIN_G, gVal); color[G] = gVal; analogWrite(PIN_B, bVal); color[B] = bVal;};
void rgbTarget(int rTarget, int gTarget, int bTarget) { colorT[R] = rTarget; colorT[G] = gTarget; colorT[B] = bTarget; }
boolean rFade() { return fade(PIN_R, R); }
boolean gFade() { return fade(PIN_G, G); }
boolean bFade() { return fade(PIN_B, B); }
//void rFade() { if (rT > r) r++; else if (rT < r) r--; analogWrite(PIN_R, r); }
//void gFade() { if (gT > g) g++; else if (gT < g) g--; analogWrite(PIN_G, g); }
//void bFade() { if (bT > b) b++; else if (bT < b) b--; analogWrite(PIN_B, b); }
boolean rgbFade() { return rFade() | gFade() | bFade(); }

void rainbow() {
  if (color[B] == 255) rgbTarget(255,0,0);
  else if (color[R] == 255) rgbTarget(0,255,0);
  else if (color[G] == 255) rgbTarget(0,0,255);
  else if (color[R] == 0 && color[G] == 0 && color[B] == 0) rgbTarget(255,0,0);
  rgbFade();
}

void test() {
  if (rFade()) {
    colorT[R] = color[R] == 0 ? 255 : 0;
  }
}

void police() {
  c = i % 128;
  if (c == 0) {
    rgbWrite(255,0,0);
  } else if (c == 64) {
    rgbWrite(0,0,255);
  }
}

void breathe() {
  c = 0;
  if (rgbFade()) {
    c = c == 0 ? 255 : 0;
  }
  rgbTarget(c,c,c);
}
