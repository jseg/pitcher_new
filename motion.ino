bool motors(){
  if (pitchEn){
    pitch(scale(pitchSet, EncPitch.read(), 1750));
  }
  if (yawEn){
    yaw(scale(yawSet, EncYaw.read(), 1250));
  }
  if (springEn){
    spring(scale(springSet, ((EncSpring.read()/10)), 1450));
  }
  if((abs(pitchSet-EncPitch.read())<=2)&&(abs(yawSet-EncYaw.read())<=2)&&(abs(springSet-((EncSpring.read()/10))<=2))){
    return true; //at set point
  }
  else{
    return false; //not at set point
  }
}

int scale(int setPt, int EncPos, int minSpeed){
  
    int error = setPt - EncPos;
    if (error > 20){
      return(4096);
    }
    if ((error <= 20) && (error > 2)){
      return map(error,1,80,minSpeed,4096);
    }
    if (error < -20){
      return(-4096);
    }
    if ((error >= -20) && (error < -2)){
      return map(error,-80,-1,-4096,(-1 * minSpeed));
    }
    else return 0;
}

void encoders(){
    if (pitchPos != EncPitch.read()){
        pitchPos = EncPitch.read();
    }
    if (yawPos != EncYaw.read()){
        yawPos = EncYaw.read();
    }
    if (springPos != ((EncSpring.read()/10))){
        springPos = ((EncSpring.read()/10));
    } 
}

void runHome(){
    pitchEn = false;  //Turn off the control loops
    yawEn = false;
    springEn = false;    
    pitch(-4096);
    yaw(-4096);
    spring(-4096); 
}

void runPreset(int num){
  if(!pitchEn){
    pitchEn = true;
  }
  if(!yawEn){
    yawEn = true;
  }
  if(!springEn){
    springEn = true;
  }
  num = num + (batterHand*9);
  pitchSet = map(constrain(presets[num][0],0,100),0,100,PITCHMIN,PITCHMAX);
  yawSet = map(constrain(presets[num][1],0,100),0,100,YAWMIN,YAWMAX);
  springSet = map(constrain(presets[num][2],0,100),0,100,SPRINGMIN,SPRINGMAX);
  currentPreset = num;

  return;
}

void pitch(int duty){
  if (duty >= 0) {
    digitalWrite(PITCH_F, HIGH);
    digitalWrite(PITCH_R, LOW);
    Timer5.setPwmDuty(PITCH_PWM,duty);
  }
  else {
    digitalWrite(PITCH_F, LOW);
    digitalWrite(PITCH_R, HIGH);
    Timer5.setPwmDuty(PITCH_PWM,abs(duty));
  }
}

void yaw(int duty){
  if (duty >= 0) {
    digitalWrite(YAW_F, HIGH);
    digitalWrite(YAW_R, LOW);
    Timer5.setPwmDuty(YAW_PWM,duty);
  }
  else {
    digitalWrite(YAW_F, LOW);
    digitalWrite(YAW_R, HIGH);
    Timer5.setPwmDuty(YAW_PWM,abs(duty));
  }
}

void spring(int duty){
  if (duty >= 0) {
    digitalWrite(SPRING_D, HIGH);
    springDir = true;               //set a direction flag to be read by the spring ISR
    Timer5.setPwmDuty(SPRING_PWM,duty);
   }
  else {
    digitalWrite(SPRING_D, LOW);
    springDir = false;            ////set a direction flag to be read by the spring ISR
    Timer5.setPwmDuty(SPRING_PWM,abs(duty));
  }
return;
}

int totalPosErr(){
  int error = 0;
  error += abs(pitchSet-EncPitch.read());
  error += abs(yawSet-EncYaw.read());
  error += abs(springSet-((EncSpring.read()/10)));
  return error;
}
