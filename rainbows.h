#include <stdio.h>
#include "Arduino.h"

struct RainbowFSM
{
    int cs;

    void init( );
    void exec(const String rainbow);
};