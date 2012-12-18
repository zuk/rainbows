#include "rainbows.h"

# define RED 9
# define GREEN 10
# define BLUE 11

Rainbows red;
Rainbows green;
Rainbows blue;

boolean played = false;

void writeRedVal(int val) {
    analogWrite(RED, 255-val);
}

void writeGreenVal(int val) {
    analogWrite(GREEN, 255-val);
}

void writeBlueVal(int val) {
    analogWrite(BLUE, 255-val);
}


void setup()
{
    Serial.begin(9600);
    Serial.println("-----------------");

    red = Rainbows();
    green = Rainbows();
    blue = Rainbows();
    //Serial.flush();


    red.writeVal = *writeRedVal;
    green.writeVal = *writeGreenVal;
    blue.writeVal = *writeBlueVal;

    //red.load("ff      00------ff-<~>---");
    //red.  load("00&");
    //green.load("ff00ff00aa00&");
    red.  load("ff>>>>>>>>>>>00>>>>>>>>>>>00>>>>>>>>>>>ff");
    green.load("00>>>>>>>>>>>ff>>>>>>>>>>>00>>>>>>>>>>>00");
    blue. load("00>>>>>>>>>>>00>>>>>>>>>>>ff>>>>>>>>>>>00");
    //blue .load("00&");
}

void loop() 
{
    if (!played) {
        red.start();
        green.start();
        blue.start();
        played = true;
    }
    red.update();
    green.update();
    blue.update();
}