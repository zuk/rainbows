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
    Serial.println("Loading melody: "+melody);
    melody.toCharArray(&melodyChars[strlen(melodyChars)], melody.length()+1);

    pe = &melodyChars[strlen(melodyChars)];

    Serial.print("Combined melody is: ");
    Serial.println(melodyChars);
}


void Rainbows::start()
{
    p = melodyChars;
    const char *eof = pe;
    Serial.println("start");
    Serial.print("Starting with p: ");
    Serial.print(p);
    char buff[50];
    sprintf(buff,"[%p]",p);
    Serial.print(" -> ");
    Serial.println(buff);
    resume();
}

void Rainbows::resume() {
    const char *eof = pe;
    // Serial.println("resume");
    Serial.print("Resuming with p: ");
    Serial.print(p);
    char buff[50];
    sprintf(buff,"[%p]",p);
    Serial.print(" -> ");
    Serial.println(buff);
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
        if (currentVal != targetVal) {
            writeVal(targetVal);
            currentVal = targetVal;
        }
        resume();
    }
}
