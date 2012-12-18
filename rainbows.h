//#include <stdio.h>
#include "Arduino.h"

#define MAX_MELODY_SIZE 64
#define FPS 2

// static const char _rainbowParser_actions[];
// static const char _rainbowParser_key_offsets[];
// static const char _rainbowParser_trans_keys[];
// static const char _rainbowParser_single_lengths[];
// static const char _rainbowParser_range_lengths[];
// static const char _rainbowParser_index_offsets[];
// static const char _rainbowParser_trans_targs[];
// static const char _rainbowParser_trans_actions[];
// static const int rainbowParser_start;
// static const int rainbowParser_first_final;
// static const int rainbowParser_error;
// static const int rainbowParser_en_main;

class Rainbows
{

    enum MODE { INSTANT = 'I', LINEAR = 'L' };

    public:
        Rainbows();
        void load(const String melody);
        // void load(char *melody);
        void start();
        void resume();
        void update();
        void debug(int state);
        void debugState(int state);

        void (*writeVal)(int val);

    protected:
        int cs;
        char *p;
        char *pe;

        int targetVal; // target value
        int currentVal; // current value

        int tweenFrames;
        int nextIncrement;
        MODE mode;

        unsigned long nextUpdateAt; // the next update will run when millis() reaches this

        //String melody;
        char melodyChars[MAX_MELODY_SIZE];
        //prog_uchar melodyChars[MAX_MELODY_SIZE] PROGMEM;

};