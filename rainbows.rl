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

void Rainbows::load(const String melody)
{
    this->melody = melody;
}

void Rainbows::exec()
{
    int len = melody.length();
    char rainbowChars[len+1];
    melody.toCharArray(rainbowChars, len);
    const char *p = rainbowChars;
    const char *pe = rainbowChars + len;

    %% write exec;
}
