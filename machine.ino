int machine(int s){
    switch(s){
        //LOADING SEQUENCE
        case 0: //send motors toward home pos
            syncUI();
            runHome(); //run alll motors toward stops
            stateTimeout = 0;
            state++;
            break;
        //Home Motors Sequence Set-up
        case 1:  //wait for motors to reach home
            if(stateTimeout>4000){
                yaw(0);                                           //turn motor off
                EncYaw.write(0);                                  //set the encoder to zero
                yawSet = EncYaw.read();                           //Yaw setpoint equals encoder value (0)
                yawPos = EncYaw.read();                           //Sync control loop sample with new home
                yawEn = true; 
                pitch(0);                                         //turn the motor off
                EncPitch.write(0);                                //set the encoder to zero
                pitchSet = EncPitch.read();                       //Pitch setpoint equals encoder value (0)
                pitchPos = EncPitch.read();                       //Sync control loop sample with new home
                pitchEn = true;
                spring(0);                                        //turn the motor off
                EncSpring.write(0);                             //set the encoder to the top position 
                springSet = 0;                                    //this line might be vestigial
                springEn = true;                                  
                stateTimeout = 0;    
                state++;                               
            }
        break;
        
        case 2:     //run the carriage down to the ball and call for a ball
            springEn = false;
            spring(4096);           //move carriage into position
            yawSet = 35;            //helps prevent the ball from bouncing out
            digitalWrite(LATCH, HIGH);
            stateTimeout = 0;
            state++;
        break;
        
        case 3:     //must check for spring motor timeout and listen for ball in switch
                    //normally 'loaded' will be true long before 'cocked' the exception is
                    //on the first load or when balls are reloaded into the hopper
            {
                static bool loaded = false;           //flags to track state completion
                static bool cocked = false;
                if(stateTimeout>4000){                //carriage is in load position, turn off motor and set encoder
                    if(!cocked){
                        cocked = true;
                        spring(0);
                        EncSpring.write(3000);
                        springSet = 300;
                        springEn = false;
                    }
                }
                if (ballin.fell()){
                    loaded = true;
                    digitalWrite(LATCH, LOW);
                }
                if (cocked && loaded){
                    loaded = false;
                    cocked = false;
                    stateTimeout = 0;
                    state ++;
                }
            }
        break;
        
        case 4: //allow the ball to settle in the lift arm         
            if(stateTimeout>1000){                  //delay to allow the ball to settle
                stateTimeout = 0;
                state++;
            }
        break;
        
        case 5: //lift the ball into the pocket
            digitalWrite(BALL_LOAD, LOW);       //turn on the lift arm
            state++;
        break;
        
        case 6: //detect lift arm return and turn off motor
            if(loaded.rose()){
                digitalWrite(BALL_LOAD, HIGH); //turn off the lift arm
                state++;
            }
        break;

        case 7:
            digitalWrite(LASER, HIGH);
            stateTimeout = 0;
            state++;
        break;

        case 8:
            if (stateTimeout > 50){
                if(!digitalRead(PHOTOSENSE)){
                    Serial.println(F("The ball is in the pocket!"));
                    state++;
                }
                else{
                    Serial.print(F("Ball not detected! (No error handling available)"));
                    state++;
                }
            }
            break;
        
        case 9:     //either start moving to the previous preset or play ready sound
            if (rethrow){
                currentPreset = lastPreset;
                runPreset(currentPreset);
                //motors();
                fireOK = true;
                state = 9;
            }
            else{
                sound(1); //start READY sound
                //currentPreset = 0;
                syncUI();
                state++;
            }      
        break;
        //AIMING SEQUENCE
        case 10:     //wait for user input to assign preset
            if(keyed){
                lastPreset = currentPreset;
                currentPreset = keyedPreset;
                runPreset(currentPreset);
                keyed = false;
                keyedPreset = 0;
                state++;
                //syncUI();
            }
        break;
        
        case 11: //wait for machine to arrive at preset
            if(totalPosErr() < 6){
                state++;
                syncUI(); //showing case 12 on IPAD
            }
        break;

        case 12:    //wait for fire command
             if(fireOK){
                sound(4); //load to explode
                fireOK = false;
                stateTimeout = 0;
                state++;
                syncUI();
             }
        break;
        //FIRING SEQUENCE
        case 13:    //open the safety door after a short delay
            if(stateTimeout>1000){
                doorServo.position(SERVO_OPEN);
                state++;
            }
        break;

        case 14:    //wait for door to open
            if(doorSense.rose()){
                state++;
            }
        break;

        case 15:  // reset timing for sounds and ball release;
            {
                crackTime = 0;
                gruntTime = 0;
                solTime =0;
                state++;
            }

        break;

        case 16:
        {
            static bool grunted = false;
            static bool cracked = false;
            static bool soled = false;

            if(!grunted){
                if(gruntTime > (OFFSETTIME-SIGNALTIME)){
                    sound(3); //grunt Sound
                    grunted = true;
                }
            }
            if(!cracked){
                if(crackTime > (flightTime+OFFSETTIME)){
                    sound(4); //crack Sound
                    cracked = true;
                }
            }
            if(!soled){
                if(solTime > (flightTime+OFFSETTIME-TOSSTIME+SIGNALTIME)){ //release the ball
                    sound(5); //soleniod fire, not actually a sound but uses the same logic
                    soled = true;
                }
            }
            if(grunted && cracked && soled){
                grunted = false;
                cracked = false;
                soled = false;
                stateTimeout=0;
                state++;
            }
        }
        break;

        case 17:
            if(stateTimeout > TOSSTIME){
                doorServo.position(SERVO_CLOSED);
                stateTimeout = 0;
                state = 0;
            }
        break;
    }

}