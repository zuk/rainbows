
#line 1 "rainbows.rl"
#include "rainbows.h"


#line 23 "rainbows.rl"



#line 11 "rainbows.cpp"
static const char _rainbowParser_actions[] = {
	0, 1, 0, 1, 1
};

static const char _rainbowParser_key_offsets[] = {
	0, 0, 4
};

static const char _rainbowParser_trans_keys[] = {
	48, 57, 97, 102, 32, 45, 48, 57, 
	97, 102, 0
};

static const char _rainbowParser_single_lengths[] = {
	0, 0, 2
};

static const char _rainbowParser_range_lengths[] = {
	0, 2, 2
};

static const char _rainbowParser_index_offsets[] = {
	0, 0, 3
};

static const char _rainbowParser_trans_targs[] = {
	2, 2, 0, 2, 2, 1, 1, 0, 
	0
};

static const char _rainbowParser_trans_actions[] = {
	3, 3, 0, 0, 0, 1, 1, 0, 
	0
};

static const int rainbowParser_start = 2;
static const int rainbowParser_first_final = 2;
static const int rainbowParser_error = 0;

static const int rainbowParser_en_main = 2;


#line 26 "rainbows.rl"

//Rainbows::Rainbows(int pin) : pin(pin)
Rainbows::Rainbows()
{
    
#line 60 "rainbows.cpp"
	{
	cs = rainbowParser_start;
	}

#line 31 "rainbows.rl"
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

    
#line 82 "rainbows.cpp"
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
	_keys = _rainbowParser_trans_keys + _rainbowParser_key_offsets[cs];
	_trans = _rainbowParser_index_offsets[cs];

	_klen = _rainbowParser_single_lengths[cs];
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

	_klen = _rainbowParser_range_lengths[cs];
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
	cs = _rainbowParser_trans_targs[_trans];

	if ( _rainbowParser_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _rainbowParser_actions + _rainbowParser_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 7 "rainbows.rl"
	{
        sscanf(p, "%x", &val);
    }
	break;
	case 1:
#line 11 "rainbows.rl"
	{
        int second;
        sscanf(p, "%x", &second);
        val = val * 16 + second;
        Serial.println("setting val to "+val);
    }
	break;
#line 170 "rainbows.cpp"
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

#line 47 "rainbows.rl"
}
