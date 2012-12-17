#include "rainbows.h"

# define L1 5
# define L2 6

Rainbows rainbow;

boolean played = false;

void writeVal(int val) {
    analogWrite(L1, val);
}

void setup()
{
    Serial.begin(9600);
    Serial.println("-----------------");

    rainbow = Rainbows();
    //Serial.flush();


    rainbow.writeVal = *writeVal;

    //rainbow.load("ff      00------ff-<~>---");
    rainbow.load("ff-00ff");
    rainbow.load("112233445566778899aabbccddeeff");
}

void loop() 
{
    if (!played) {
        rainbow.start();
        played = true;
    }
    rainbow.update();
}