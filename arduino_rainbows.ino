#include "rainbows.h"
Rainbows rainbow = Rainbows();

# define L1 5
# define L2 6

boolean played = false;

void writeVal(int val) {
    analogWrite(L1, val);
}

void setup()
{
    Serial.begin(9600);
    Serial.println("-----------------");
    //Serial.flush();


    rainbow.writeVal = *writeVal;

    //rainbow.load("ff      00------ff-<~>---");
    //rainbow.load("ff-00ff00");
}

void loop() 
{
    if (!played) {
        rainbow.start();
        played = true;
    }
    rainbow.update();
}