//Update Hardware Inputs
void updateInputs(){
  armReturn.update();
  ballin.update();
  doorSense.update();
}

//Load Factory Defaults to Memory
void loadDefaultPresets(){
  Serial.println(F("Loading Factory Defaults to Memory"));
  for( int i = 0; i< NUM_PRESETS; i++){
   for( int j = 0; j < NUM_MOTORS ;j++){
     presets[i][j] = defaultPresets[i][j];
     Serial.print(presets[i][j]);
     Serial.print(F(" "));
   }
   Serial.println(F(" "));
 }
}

//Load Factory Defaults to EEPROM
void loadFactoryPresets(){
 Serial.println(F("Loading Factory Defaults to EEPROM"));
 for( int i = 0; i< NUM_PRESETS; i++){
   for( int j = 0; j < NUM_MOTORS ;j++){
     presets[i][j] = defaultPresets[i][j];
     Serial.print(presets[i][j]);
     Serial.print(F(" "));
   }
   Serial.println(F(" "));
 }
 savePreset();
}

//Load Presets from EEProm
void loadEEPromPresets(int idx, int v, int up){
  Serial.println(F("Load Presets from EEProm"));
  int b = 0; //right
  for(int i = 0; i< NUM_PRESETS; i++){
    for(int j = 0; j < NUM_MOTORS ;j++){
      int val = EEPROM.read(b);
      presets[i][j] = val;
      Serial.print(val);
      Serial.print(F(" "));
      b++;
    }
    Serial.println(F(" "));
  }
  pitchSet = map(presets[currentPreset][0],0,100,PITCHMIN,PITCHMAX);  //Update motor setpoints
  yawSet = map(presets[currentPreset][1],0,100,YAWMIN,YAWMAX);
  springSet =map(presets[currentPreset][2],0,100,SPRINGMIN,SPRINGMAX);
}

//Save Presets to EEPROM
void savePreset(){ // 1 right 0 left
  Serial.println(F("Save presets to EEPROM:" ));
  int b = 0;
  for(int i = 0; i< NUM_PRESETS; i++){    
    for( int j = 0; j < NUM_MOTORS ;j++){       
      int val = presets[i][j];
      EEPROM.write(b, val);
      Serial.print(val);
      Serial.print(F(" "));
      b++;
    }
    Serial.println(F(" "));
  }
}

//Send Feedback to ESP
void feedback(){
  if(updateUI>2000){
    syncUI();
    updateUI -= 2000;
  }
}

//Nudge preset positions (not saved to EEPROM)
void nudge(int p, int y, int s){
  presets[currentPreset][0] = constrain(presets[currentPreset][0]+p,0,100);
  presets[currentPreset][1] = constrain(presets[currentPreset][1]+y,0,100);
  presets[currentPreset][2] = constrain(presets[currentPreset][2]+s,0,100);
  pitchSet = map(constrain(presets[currentPreset][0],0,100),0,100,PITCHMIN,PITCHMAX);
  yawSet = map(constrain(presets[currentPreset][1],0,100),0,100,YAWMIN,YAWMAX);
  springSet = map(constrain(presets[currentPreset][2],0,100),0,100,SPRINGMIN,SPRINGMAX); 
}

//Not sure why this is here
int whatPitch(){
  if (currentPreset == 0){
    return lastPreset-1;
  }
  else {
    return currentPreset-1;
  }
}

//Computes time offsets for speed timing
int timeOfFlight(int s){
  return (int)((-5.4*s)+945);
}

//Play sounds
void sound(int s){
  static unsigned long t1 = 0;
  static unsigned long t2 = 0;
  static unsigned long t3 = 0;
  static unsigned long t4 = 0; 
  static unsigned long t5 = 0;
  switch(s){
    case 0:
        if(t1>0){
          if((long)((millis() - t1)) >= 0){
            digitalWrite(SOUND_READY, LOW);
          }
        }
        if(t2>0){
          if((long)((millis() - t2)) >= 0){
            digitalWrite(SOUND_EXPLODE, LOW);
          }
        }
        if(t3>0){
          if((long)((millis() - t3)) >= 0){
            digitalWrite(SOUND_GRUNT, LOW);
          }
        }
        if(t4>0){
          if((long)((millis() - t4)) >= 0){
            digitalWrite(SOUND_CRACK, LOW);
          }
        }
        if(t5>0){
          if((long)((millis() - t5)) >= 0){
            digitalWrite(FIRE_SOL, HIGH);
            }
        }
      break;
    case 1:
      t1 = millis()+10;
      digitalWrite(SOUND_READY, HIGH);
      break;
    case 2:
      t2 = millis()+10;
      digitalWrite(SOUND_EXPLODE, HIGH);
      break;
    case 3:
      t3 = millis()+10;
      digitalWrite(SOUND_GRUNT, HIGH);
      break;
    case 4:
      t4 = millis()+10;
      digitalWrite(SOUND_CRACK, HIGH);
      break;
    case 5:
      t5 = millis()+200;
      digitalWrite(FIRE_SOL, LOW);
      break;
  }
}



