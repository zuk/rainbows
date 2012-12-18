%%{
    machine RainbowParser;

    action release {
        Serial.println(";");
        debug(cs);
        nextUpdateAt = millis() + 1000/FPS;
        fbreak;
    }

    action begin_intensity {
        Serial.print(fc);
        char c = fc;
        const char cp[2] = {fpc[0], '\0'};
        sscanf(fpc, "%1x", &targetVal);
        /*Serial.print("begin_intensity ");
        Serial.print(cp);
        Serial.print(" ");
        Serial.println(targetVal);*/
    }

    action finish_intensity {
        //Serial.print(fc);
        char c = fc;
        int second;
        const char cp[2] = {fpc[0], '\0'};
        sscanf(cp, "%x", &second);
        targetVal = targetVal * 16 + second;
        /*Serial.print("finish_intensity ");
        Serial.print(cp);
        Serial.print(" ");
        Serial.println(targetVal);*/
    }

    action tween_accumulate {
        Serial.print(fc);
        tweenFrames++;
    }

    action tween {
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

    action loopback {
        Serial.println("&");
        fnext main;
        debug(cs);
        fexec melodyChars;
    }

    action debug {
        debug(cs);
    }

    hex = ([0-9a-f]);
    intensity = (hex $begin_intensity hex $finish_intensity);
    
    nada = (' '+);

    set = (intensity) %release;
    tween = (('>'+ $tween_accumulate intensity) %tween %eof(loopback)) %release;
    
    frame = (set | tween);

    main := (frame)* $debug;
}%%