
#line 1 "rainbows.rl"
#include "rainbows.h"


#line 6 "rainbows.rl"



#line 11 "rainbows.cpp"
static const char _RainbowParser_actions[] = {
	0, 1, 0, 2, 1, 6, 2, 2, 
	6, 2, 3, 6, 3, 0, 1, 6, 
	3, 0, 3, 6, 3, 4, 5, 0, 
	4, 4, 0, 1, 6, 4, 4, 0, 
	3, 6
};

static const char _RainbowParser_eof_actions[] = {
	0, 0, 0, 0, 0, 1, 20
};

static const int RainbowParser_start = 4;
static const int RainbowParser_first_final = 4;
static const int RainbowParser_error = 0;

static const int RainbowParser_en_main = 4;


#line 9 "rainbows.rl"

//Rainbows::Rainbows(int pin) : pin(pin)
Rainbows::Rainbows()
{
    
#line 37 "rainbows.cpp"
	{
	cs = RainbowParser_start;
	}

#line 14 "rainbows.rl"
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

    
#line 134 "rainbows.cpp"
	{
	const char *_acts;
	unsigned int _nacts;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	switch ( cs ) {
case 4:
	if ( (*p) == 62 )
		goto tr3;
	if ( (*p) > 57 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr5;
	} else if ( (*p) >= 48 )
		goto tr5;
	goto tr1;
case 0:
	goto _out;
case 1:
	if ( (*p) > 57 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr0;
	} else if ( (*p) >= 48 )
		goto tr0;
	goto tr1;
case 5:
	if ( (*p) == 62 )
		goto tr7;
	if ( (*p) > 57 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr6;
	} else if ( (*p) >= 48 )
		goto tr6;
	goto tr1;
case 2:
	if ( (*p) == 62 )
		goto tr3;
	if ( (*p) > 57 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr2;
	} else if ( (*p) >= 48 )
		goto tr2;
	goto tr1;
case 3:
	if ( (*p) > 57 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr4;
	} else if ( (*p) >= 48 )
		goto tr4;
	goto tr1;
case 6:
	if ( (*p) == 62 )
		goto tr9;
	if ( (*p) > 57 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr8;
	} else if ( (*p) >= 48 )
		goto tr8;
	goto tr1;
	}

	tr1: cs = 0; goto _again;
	tr5: cs = 1; goto f1;
	tr6: cs = 1; goto f4;
	tr8: cs = 1; goto f7;
	tr3: cs = 2; goto f2;
	tr7: cs = 2; goto f5;
	tr9: cs = 2; goto f8;
	tr2: cs = 3; goto f1;
	tr0: cs = 5; goto f0;
	tr4: cs = 6; goto f0;

	f1: _acts = _RainbowParser_actions + 3; goto execFuncs;
	f0: _acts = _RainbowParser_actions + 6; goto execFuncs;
	f2: _acts = _RainbowParser_actions + 9; goto execFuncs;
	f4: _acts = _RainbowParser_actions + 12; goto execFuncs;
	f5: _acts = _RainbowParser_actions + 16; goto execFuncs;
	f7: _acts = _RainbowParser_actions + 24; goto execFuncs;
	f8: _acts = _RainbowParser_actions + 29; goto execFuncs;

execFuncs:
	_nacts = *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 4 "rainbow_parser_fsm.rl"
	{
        Serial.println(";");
        debug(cs);
        nextUpdateAt = millis() + 1000/FPS;
        {p++; goto _out; }
    }
	break;
	case 1:
#line 11 "rainbow_parser_fsm.rl"
	{
        Serial.print((*p));
        char c = (*p);
        const char cp[2] = {p[0], '\0'};
        sscanf(p, "%1x", &targetVal);
        /*Serial.print("begin_intensity ");
        Serial.print(cp);
        Serial.print(" ");
        Serial.println(targetVal);*/
    }
	break;
	case 2:
#line 22 "rainbow_parser_fsm.rl"
	{
        //Serial.print(fc);
        char c = (*p);
        int second;
        const char cp[2] = {p[0], '\0'};
        sscanf(cp, "%x", &second);
        targetVal = targetVal * 16 + second;
        /*Serial.print("finish_intensity ");
        Serial.print(cp);
        Serial.print(" ");
        Serial.println(targetVal);*/
    }
	break;
	case 3:
#line 35 "rainbow_parser_fsm.rl"
	{
        Serial.print((*p));
        tweenFrames++;
    }
	break;
	case 4:
#line 40 "rainbow_parser_fsm.rl"
	{
        //Serial.println("ignoring tween...");
        mode = LINEAR;
        Serial.print("tv:");
        Serial.print(targetVal);
        Serial.print(" - ");
        Serial.print("cv:");
        Serial.print(currentVal);
        Serial.print(" / ");
        Serial.print(tweenFrames * FPS);
        nextIncrement = (targetVal - currentVal) / (tweenFrames * FPS);
        Serial.print(" ni: ");
        Serial.println(nextIncrement);
    }
	break;
	case 6:
#line 62 "rainbow_parser_fsm.rl"
	{
        debug(cs);
    }
	break;
#line 289 "rainbows.cpp"
		}
	}
	goto _again;

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	const char *__acts = _RainbowParser_actions + _RainbowParser_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 0:
#line 4 "rainbow_parser_fsm.rl"
	{
        Serial.println(";");
        debug(cs);
        nextUpdateAt = millis() + 1000/FPS;
        {p++; goto _out; }
    }
	break;
	case 4:
#line 40 "rainbow_parser_fsm.rl"
	{
        //Serial.println("ignoring tween...");
        mode = LINEAR;
        Serial.print("tv:");
        Serial.print(targetVal);
        Serial.print(" - ");
        Serial.print("cv:");
        Serial.print(currentVal);
        Serial.print(" / ");
        Serial.print(tweenFrames * FPS);
        nextIncrement = (targetVal - currentVal) / (tweenFrames * FPS);
        Serial.print(" ni: ");
        Serial.println(nextIncrement);
    }
	break;
	case 5:
#line 55 "rainbow_parser_fsm.rl"
	{
        Serial.println("&");
        cs = 4;
        debug(cs);
        {p = (( melodyChars))-1;}
    }
	break;
#line 341 "rainbows.cpp"
		}
	}
	}

	_out: {}
	}

#line 105 "rainbows.rl"
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
