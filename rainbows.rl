#include "rainbows.h"

%%{
    machine rainbowParser;


    action start_val {
        sscanf(p, "%x", &val);
    }

    action end_val {
        int second;
        sscanf(p, "%x", &second);
        val = val * 16 + second;
        Serial.println("setting val to "+val);
        setValue(val);
    }

    val = ([0-9a-f]{2}) >start_val @end_val;
    tween = ('-'+);
    nada = (' '+);

    main := ( val+ | tween | nada)* ;
}%%

%% write data;

//Rainbows::Rainbows(int pin) : pin(pin)
Rainbows::Rainbows()
{
    %% write init;   
}

void Rainbows::exec(const String rainbow)
{
    int len = rainbow.length();
    char rainbowChars[len+1];
    rainbow.toCharArray(rainbowChars, len);
    const char *p = rainbowChars;
    const char *pe = rainbowChars + len;

    %% write exec;
}
