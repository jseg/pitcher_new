
void initializeInputs(){
 pinMode(BALL_IN,INPUT);
 ballin.attach(BALL_IN);
 ballin.interval(BOUNCE);
 pinMode(LOADED,INPUT);
 armReturn.attach(LOADED);
 armReturn.interval(BOUNCE);
 //pinMode(HAND, INPUT);
 pinMode(DOOR_SENSE, INPUT);
 doorSense.attach(DOOR_SENSE);
 doorSense.interval(BOUNCE);
 pinMode(PHOTOSENSE, INPUT);

}

void initializeOutputs(){  //set pin modes and intial states
  //Sounds
  pinMode(SOUND_ON,OUTPUT);
  digitalWrite(SOUND_ON,HIGH);
  pinMode(SOUND_CRACK,OUTPUT);
  digitalWrite(SOUND_CRACK,HIGH);
  pinMode(SOUND_GRUNT,OUTPUT);
  digitalWrite(SOUND_GRUNT,HIGH);
  pinMode(SOUND_EXPLODE,OUTPUT);
  digitalWrite(SOUND_EXPLODE,HIGH);
  pinMode(SOUND_READY,OUTPUT);
  digitalWrite(SOUND_READY,HIGH);
  pinMode(SOUND_SIX,OUTPUT);
  digitalWrite(SOUND_SIX,HIGH);
  pinMode(SOUND_SEVEN,OUTPUT);
  digitalWrite(SOUND_SEVEN,HIGH);
  pinMode(SOUND_EIGHT,OUTPUT);
  digitalWrite(SOUND_EIGHT,HIGH);

  //Motors
  pinMode(SPRING_D,OUTPUT);
  digitalWrite(SPRING_D,LOW);
  pinMode(PITCH_F,OUTPUT);
  digitalWrite(PITCH_F,LOW);
  pinMode(PITCH_R,OUTPUT);
  digitalWrite(PITCH_R,LOW);
  pinMode(YAW_F,OUTPUT);
  digitalWrite(YAW_F,LOW);
  pinMode(YAW_R,OUTPUT);
  digitalWrite(YAW_R,LOW);

  //Relay
  pinMode(BALL_LOAD,OUTPUT);
  digitalWrite(BALL_LOAD,HIGH);
  pinMode(SAFETY_DOOR,OUTPUT);
  digitalWrite(SAFETY_DOOR,HIGH);
  pinMode(REJECT_SOL,OUTPUT);
  digitalWrite(REJECT_SOL,HIGH);
  pinMode(FIRE_SOL,OUTPUT);
  digitalWrite(FIRE_SOL,HIGH);
  pinMode(POWER_CUT,OUTPUT);
  digitalWrite(POWER_CUT,HIGH);

  //Digital Signals
  pinMode(LATCH,OUTPUT);
  digitalWrite(LATCH,LOW);
  pinMode(LASER,OUTPUT);
  digitalWrite(LASER,LOW);
}
