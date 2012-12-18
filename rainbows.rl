#include "rainbows.h"

%%{
    machine RainbowParser;
    include RainbowParser "rainbow_parser_fsm.rl";
}%%

%% write data;

//Rainbows::Rainbows(int pin) : pin(pin)
Rainbows::Rainbows()
{
    %% write init;
    nextUpdateAt = 0;
    p = &melodyChars[0];
    pe = &melodyChars[0];
    tweenFrames = 0;
    mode = INSTANT;
    currentVal = 0;
    //melodyChars = "";
}

// void Rainbows::load(const String melody)
// {
//     this->melody = melody;

//     int len = melody.length();
//     melody.toCharArray(melodyChars, len+1);

//     Serial.println("Loaded melody: "+melody);
// }

void Rainbows::load(const String melody) {
    p = &melodyChars[0];
    pe = &melodyChars[0];

    Serial.print("Initial melody is: ");
    Serial.println(melodyChars);
    char buff[50];
    sprintf(buff,"[%p]",&melodyChars[0]);
    Serial.print(" -> ");
    Serial.println(buff);

    Serial.println("Loading melody: "+melody);
    melody.toCharArray(melodyChars, melody.length()+1);

    pe = pe + melody.length();
    //*pe = '\0';

    char pb[10];
    char peb[10];
    sprintf(pb,"[%p]",p);
    sprintf(peb,"[%p]",pe);


    Serial.print("Combined melody is: ");
    Serial.print(melodyChars);
    Serial.print(" ");

    Serial.print(pb);
    Serial.print("-");
    Serial.println(peb);

}

void Rainbows::debugState(int state) {
    Serial.print("(");
    Serial.print(state);
    Serial.print(")");
}

void Rainbows::debug(int state) {
    char pb[10];
    sprintf(pb,"[%p]",p);
    debugState(state);
    Serial.print(pb);
    Serial.print(":");
    Serial.println(p);
}


void Rainbows::start()
{
    p = &melodyChars[0];
     char pb[10];
    char peb[10];
    sprintf(pb,"<%p>",&melodyChars[0]);
    sprintf(peb,"<%p>",p);
    Serial.print(pb);
    Serial.print("-");
    Serial.println(peb);
    resume();
}

void Rainbows::resume() {
    const char *eof = pe;

    char eofb[10];
    sprintf(eofb,"<%p>",eof);
    Serial.print("resuming with EOF:");
    Serial.println(eofb);
    debug(cs);

    %% write exec;
}

void Rainbows::update()
{
    // if (millis() % 1000 || millis() == nextUpdateAt) {
    //     Serial.print(millis());
    //     Serial.print(" ... next at ");
    //     Serial.println(nextUpdateAt);
    // }
    if (millis() >= nextUpdateAt && pe != p) {
        if (currentVal == targetVal) {
            resume();
        } else {
            if (mode == INSTANT) {
                currentVal = targetVal;
            } else {
                if (currentVal + nextIncrement >= 255 || currentVal + nextIncrement <= 0) {
                    Serial.println("overvlow");
                    currentVal = targetVal;
                    tweenFrames = 0;
                } else {
                    currentVal += nextIncrement;
                    Serial.print("+");
                    Serial.print(nextIncrement);
                    Serial.print("=");
                    Serial.println(currentVal);
                }
            }

            Serial.print("writeVal:");
            Serial.println(currentVal);
            writeVal(currentVal);
        }
    }
}
