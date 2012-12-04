#include "rainbows.h"

%%{
    machine rainbowParser;

    action found_val {
        setLED(R, fpc);
    }

    val = ([0-9a-f]{2}) @found_val;
    tween = ('-'+);
    nada = (' '+);

    main := ( val+ | tween | nada)* ;
}%%

%% write data;

void RainbowFSM::init( ) 
{
    %% write init;   
}

void RainbowFSM::exec(const String rainbow) 
{
    int len = rainbow.length();
    char rainbowChars[len+1];
    rainbow.toCharArray(rainbowChars, len);
    const char *p = rainbowChars;
    const char *pe = rainbowChars + len;

    %% write exec;
}
