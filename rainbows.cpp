
#line 1 "rainbows.rl"
#include "rainbows.h"


#line 15 "rainbows.rl"



#line 11 "rainbows.cpp"
static const char _rainbowParser_actions[] = {
	0, 1, 0
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
	1, 1, 0, 0, 0, 0, 0, 0, 
	0
};

static const int rainbowParser_start = 2;
static const int rainbowParser_first_final = 2;
static const int rainbowParser_error = 0;

static const int rainbowParser_en_main = 2;


#line 18 "rainbows.rl"

RainbowFSM::RainbowFSM( ) 
{
    
#line 59 "rainbows.cpp"
	{
	cs = rainbowParser_start;
	}

#line 22 "rainbows.rl"
}

void RainbowFSM::exec(const String rainbow) 
{
    int len = rainbow.length();
    char rainbowChars[len+1];
    rainbow.toCharArray(rainbowChars, len);
    const char *p = rainbowChars;
    const char *pe = rainbowChars + len;

    
#line 76 "rainbows.cpp"
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
#line 6 "rainbows.rl"
	{
        setLED(R, p);
    }
	break;
#line 155 "rainbows.cpp"
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

#line 33 "rainbows.rl"
}
