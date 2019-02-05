void cmd_callback( int idx, int v, int up ) {
  int arg1 = atoi( cmd.arg(1));
  int arg2 = atoi( cmd.arg(2));
  int arg3 = atoi( cmd.arg(3));
  switch ( v ) {
    case CMD_LOAD:
      state = 0;
      // //TODO: add logic to insure that the events cannot run if a ball is already loaded.
      break;
    case CMD_PRESET:     
        keyedPreset = arg1;
        keyed = true;   
      break;
    case CMD_FIRE: //format: "fire (bool)FIRE (bool)RETHROW (int)SPEED"
      fireOK = (bool)arg1;
      throwSpeed = arg3;
      flightTime = timeOfFlight(throwSpeed);
      rethrow = (bool)arg2;
      Serial.print("Rethrow: ");
      Serial.println(rethrow);
      // if(arg1){
      //   if(Aiming.state()){
      //         if(currentPreset != 0 && atSetPoint){
      //           soundExplode.trigger(soundExplode.EVT_BLINK);
      //           automaton.delay(3000);
      //           Aiming.trigger(Aiming.EVT_OFF);  //Finished Aiming
      //           Main.trigger(Main.EVT_STEP);     //Now Firing
      //         }
      //         //else play an "Error" sound
      //       }
      //   }
          break;
    case CMD_HAND:
       batterHand = arg1;
      // loadEEPromPresets(0,0,0);
      break;
    case CMD_EEPROMSETUP:  //Comand to set-up eeprom on a new unit
      loadFactoryPresets();
      break;
    case CMD_PITCH:
      pitch(arg1);
      Serial.print(F("Pitch: "));
      Serial.println(arg1);
      return;
      
    case CMD_YAW:
      yaw(arg1);
      Serial.print(F("Yaw: "));
      Serial.println(arg1);
      return;
    case CMD_SPRING:
      spring(arg1);
      Serial.print(F("Spring: "));
      Serial.println(arg1);
      return;
    case CMD_HOME:
      runHome();
      state = 0;
      return;
    case CMD_MOVE:
      pitchSet = arg1;
      yawSet = arg2;
      springSet = arg3;
      Serial.print(F("Pitch Setpoint: "));
      Serial.println(arg1);
      Serial.print(F("Yaw Setpoint: "));
      Serial.println(arg2);
      Serial.print(F("Sprint Setpoint: "));
      Serial.println(arg3);
      return;
    case CMD_STATE:
      Serial.print(F("sync "));
      Serial.print(state);
      Serial.print(F(" "));
      Serial.print(batterHand);
      Serial.print(F(" "));
      Serial.print(keyed);
      Serial.print(F(" "));
      Serial.print(rethrow);
      Serial.print(F(" "));
      Serial.print(keyedPreset);
      Serial.print(F(" "));
      Serial.print(currentPreset);
      Serial.print(F(" "));
      Serial.print(throwSpeed);
      Serial.print(F(" "));
      Serial.print(totalPosErr());
      Serial.print(F(" "));
      Serial.print(errorCode);
      Serial.println(F(" "));
      return;
    case CMD_SERIAL:
      // printEncoders.start();
      return;
    case CMD_NUDGE:
      nudge(arg1, arg2, arg3);
      return;
    case CMD_SAVE:
      savePreset();
      return;
    case CMD_HANDLE_ERROR:
       switch(arg1){
         case 1:
            state = 0;
            errorCode = 0;
            break;  
       }
       return;
    case CMD_FACTORY:
      loadDefaultPresets();
      return;
  }
  
}

void syncUI(){
  Serial3.print(F("sync "));
  Serial3.print(state);
  Serial3.print(F(" "));
  Serial3.print(batterHand);
  Serial3.print(F(" "));
  Serial3.print(keyed);
  Serial3.print(F(" "));
  Serial3.print(rethrow);
  Serial3.print(F(" "));
  Serial3.print(keyedPreset);
  Serial3.print(F(" "));
  Serial3.print(currentPreset);
  Serial3.print(F(" "));
  Serial3.print(throwSpeed);
  Serial3.print(F(" "));
  Serial3.print(totalPosErr());
  Serial3.print(F(" "));
  Serial3.print(errorCode);
  Serial3.println(F(" "));
  Serial3.print(isNudge);
  Serial3.println(F(" "));
  Serial3.print(presets[currentPreset][0]);
  Serial3.println(F(" "));
  Serial3.print(presets[currentPreset][1]);
  Serial3.println(F(" "));
  Serial3.print(presets[currentPreset][2]);
  Serial3.println(F(" "));
  Serial.print(F("sync "));
  Serial.print(state);
  Serial.print(F(" "));
  Serial.print(batterHand);
  Serial.print(F(" "));
  Serial.print(keyed);
  Serial.print(F(" "));
  Serial.print(rethrow);
  Serial.print(F(" "));
  Serial.print(keyedPreset);
  Serial.print(F(" "));
  Serial.print(currentPreset);
  Serial3.print(F(" "));
  Serial.print(throwSpeed);
  Serial.print(F(" "));
  Serial.print(totalPosErr());
  Serial.print(F(" "));
  Serial.print(errorCode);
  Serial.println(F(" "));
  Serial.print(isNudge);
  Serial.println(F(" "));
  Serial.print(presets[currentPreset][0]);
  Serial.println(F(" "));
  Serial.print(presets[currentPreset][1]);
  Serial.println(F(" "));
  Serial.print(presets[currentPreset][2]);
  Serial.println(F(" "));
}

void help(){
  Serial.println(F("Recognized commands:"));
  Serial.println(F("high pin         *set a pin to HIGH"));
  Serial.println(F("low pin          *set a pin to LOW"));
  Serial.println(F("read pin         *read the current state of a pin"));
  Serial.println(F("aread pin        *read an analog pin"));
  Serial.println(F("awrite pin       *write an analog value to a pin"));
  Serial.println(F("mode_input pin   *set a pin to input mode"));
  Serial.println(F("mode_output pin  *set a pin to output mode"));
  Serial.println(F("mode_pullup pin  *turn on an internal pullup"));
  Serial.println(F("load             *load a ball in the launcher"));
  Serial.println(F("num_key num      *simulate a number key"));
  Serial.println(F("pitch num        *run pitch motor at speed num"));
  Serial.println(F("yaw num          *run yaw motor at speed num"));
  Serial.println(F("spring num       *run spring motor at speed num"));
  Serial.println(F("home             *run run all motors home"));
  Serial.println(F("pid bool         *enable (1) or disable (0) position control"));
  Serial.println(F("move num num num *run to position num num num"));
  
}
