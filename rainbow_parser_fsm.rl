%%{
    machine RainbowParser;

    action start_val {
        char c = fc;
        const char cp[2] = {fpc[0], '\0'};
        sscanf(fpc, "%1x", &targetVal);
        Serial.print("start_val ");
        Serial.print(cp);
        Serial.print(" ");
        Serial.println(targetVal);
    }

    action end_val {
        char c = fc;
        int second;
        const char cp[2] = {fpc[0], '\0'};
        sscanf(cp, "%x", &second);
        targetVal = targetVal * 16 + second;
        Serial.print("end_val ");
        Serial.print(cp);
        Serial.print(" ");
        Serial.println(targetVal);
        nextUpdateAt = millis() + 2000;
        fbreak;
    }

    hex = ([0-9a-f]);
    val = (hex $start_val hex $end_val);
    tween = ('-'+);
    nada = (' '+);

    main := (tween+ | nada+ | val+)* ;
}%%