#include <stdio.h>
#include "Arduino.h"

class RainbowFSM
{
    public:
        RainbowFSM( );
        void exec(const String rainbow);

    protected:
        int cs;
};