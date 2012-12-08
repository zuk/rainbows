#include "rainbows.h"
Rainbows rainbow = Rainbows();

void setValue(int val) {
    analogWrite(5, val);
}

void setup()
{
    rainbow.setValue = *setValue;

    rainbow.load("ff      00------ff-<~>---");
}

void loop() 
{
    // also do nothing
}