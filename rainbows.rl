%%{
    machine rainbowParser;

    action found_val {
        setLED(R, fpc);
    }

    val = ([0-9a-f]{2}) @found_val;
    tween = ('-'+);
    nada = (' '+);

    main := ( val+ | tween | nada)* ;
}%%

%% write data;

%% write init;
%% write exec;