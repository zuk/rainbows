
#line 1 "rainbows.rl"
#include "rainbows.h"


#line 6 "rainbows.rl"



#line 11 "rainbows.cpp"
static const char _RainbowParser_actions[] = {
	0, 1, 0, 1, 1
};

static const char _RainbowParser_key_offsets[] = {
	0, 0, 4
};

static const char _RainbowParser_trans_keys[] = {
	48, 57, 97, 102, 32, 45, 48, 57, 
	97, 102, 0
};

static const char _RainbowParser_single_lengths[] = {
	0, 0, 2
};

static const char _RainbowParser_range_lengths[] = {
	0, 2, 2
};

static const char _RainbowParser_index_offsets[] = {
	0, 0, 3
};

static const char _RainbowParser_trans_targs[] = {
	2, 2, 0, 2, 2, 1, 1, 0, 
	0
};

static const char _RainbowParser_trans_actions[] = {
	3, 3, 0, 0, 0, 1, 1, 0, 
	0
};

static const int RainbowParser_start = 2;
static const int RainbowParser_first_final = 2;
static const int RainbowParser_error = 0;

static const int RainbowParser_en_main = 2;


#line 9 "rainbows.rl"

//Rainbows::Rainbows(int pin) : pin(pin)
Rainbows::Rainbows()
{
    
#line 60 "rainbows.cpp"
	{
	cs = RainbowParser_start;
	}

#line 14 "rainbows.rl"
    nextUpdateAt = 0;
    melodyChars = "ff-00ff";
}

// void Rainbows::load(const String melody)
// {
//     this->melody = melody;

//     int len = melody.length();
//     melody.toCharArray(melodyChars, len+1);

//     Serial.println("Loaded melody: "+melody);
// }


void Rainbows::start()
{
    p = melodyChars;
    pe = melodyChars + 7;
    const char *eof = pe;
    Serial.println("start");
    Serial.print("Starting with p: ");
    Serial.print(p);
    char buff[50];
    sprintf(buff,"[%p]" ,p);
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
    sprintf(buff,"[%p]" ,p);
    Serial.print(" -> ");
    Serial.println(buff);
    
#line 106 "rainbows.cpp"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_keys = _RainbowParser_trans_keys + _RainbowParser_key_offsets[cs];
	_trans = _RainbowParser_index_offsets[cs];

	_klen = _RainbowParser_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _RainbowParser_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	cs = _RainbowParser_trans_targs[_trans];

	if ( _RainbowParser_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _RainbowParser_actions + _RainbowParser_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 4 "rainbow_parser_fsm.rl"
	{
        char c = (*p);
        const char cp[2] = {p[0], '\0'};
        sscanf(p, "%1x", &targetVal);
        Serial.print("start_val ");
        Serial.print(cp);
        Serial.print(" ");
        Serial.println(targetVal);
    }
	break;
	case 1:
#line 14 "rainbow_parser_fsm.rl"
	{
        char c = (*p);
        int second;
        const char cp[2] = {p[0], '\0'};
        sscanf(cp, "%x", &second);
        targetVal = targetVal * 16 + second;
        Serial.print("end_val ");
        Serial.print(cp);
        Serial.print(" ");
        Serial.println(targetVal);
        nextUpdateAt = millis() + 2000;
        {p++; goto _out; }
    }
	break;
#line 207 "rainbows.cpp"
		}
	}

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 54 "rainbows.rl"
}

void Rainbows::update()
{
    // if (millis() % 1000 || millis() == nextUpdateAt) {
    //     Serial.print(millis());
    //     Serial.print(" ... next at ");
    //     Serial.println(nextUpdateAt);
    // }
    if (millis() >= nextUpdateAt) {
        if (currentVal != targetVal) {
            writeVal(targetVal);
            currentVal = targetVal;
        }
        resume();
    }
}
