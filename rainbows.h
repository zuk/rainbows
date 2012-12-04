#include <stdio.h>
#include "Arduino.h"

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
        void exec(const String rainbow);

        void (*setValue)(int val);

    protected:
        int cs;
        int pin;
        int val;

};