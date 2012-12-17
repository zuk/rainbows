#include <stdio.h>
#include "Arduino.h"

#define MAX_MELODY_SIZE 1024

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

    public:
        Rainbows();
        void load(const String melody);
        // void load(char *melody);
        void start();
        void resume();
        void update();

        void (*writeVal)(int val);

    protected:
        int cs;
        const char *p;
        const char *pe;

        int targetVal; // target value
        int currentVal; // current value

        unsigned long nextUpdateAt; // the next update will run when millis() reaches this

        String melody;
        char melodyChars[MAX_MELODY_SIZE];

};