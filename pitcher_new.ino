#include <Atm_servo.h>
#include <TimerFive.h>
#include <elapsedMillis.h>
#include <EEPROM.h>       //version 2.0 (built-in)
#include <Encoder.h>      //version 1.4
#include <Automaton.h>    //version 1.0.1
#include "pins.h"
#include "settings.h"
#include <Bounce2.h>

//GLOBAL STATES
int state;
bool keyed = false;   //flag to track wether a preset has been keyed in
int keyedPreset = 5;
int currentPreset = 5;
int lastPreset = 5;
int batterHand = 1; //0 = left 1 = right
bool rethrow = false;
bool atSetPoint = false;
int throwSpeed = 80;
int flightTime = 459; //magic number to make the ball cross the plane of home plate at the right moment. Move to settings?
bool fireOK = false;
int errorCode = 0;
int isNudge = 0;
bool isLoaded = false;


//timers
elapsedMillis stateTimeout;
//elapsedMillis sound;
elapsedMillis crackTime;
elapsedMillis gruntTime;
elapsedMillis solTime;
elapsedMillis updateUI;

//input debouncing
Bounce ballin;
Bounce armReturn;
Bounce doorSense;
Bounce adjust;

//Encoders
//Documentation: https://www.pjrc.com/teensy/td_libs_Encoder.html
int springPos;                                        //value of spring encoder
int pitchPos;
int yawPos;
int lastSpringPos;
bool springDir = true;                                //true for up, false for down
Encoder EncPitch(PITCH_A, PITCH_B);                   //instantiate pitch encoder, uses INT0 and INT1
Encoder EncYaw(YAW_A, YAW_B);                         //instantiate pitch encoder, uses INT4 and INT5
Encoder EncSpring(SPRING_A, SPRING_B);

//Motor Control Values 
bool pitchEn, yawEn, springEn;                        //Enable booleans for PID loops
int pitchSet = 0, yawSet = 0, springSet = 0;          //Motor Setpoints    

//Door Servo 
Atm_servo doorServo;


//Serial Command Line object 
//Documentation:https://github.com/tinkerspy/Automaton/wiki/The-command-machine
Atm_command cmd;  //This object is the primary way to control the machine during development     
char cmd_buffer[80];   // input buffer
Atm_command cmd1;  //This object is the primary way to control the machine during operation     
char cmd1_buffer[80];   // input buffer
enum {CMD_LOAD, CMD_PRESET, CMD_FIRE, CMD_HAND, CMD_EEPROMSETUP, CMD_PITCH, CMD_YAW, CMD_SPRING, CMD_HOME, CMD_MOVE, CMD_STATE, CMD_SERIAL, CMD_NUDGE, CMD_SAVE, CMD_HANDLE_ERROR, CMD_FACTORY };
const char cmdlist[] = //must be in the same order as enum
      "load preset fire hand eepromsetup pitch yaw spring home move state serial nudge save handleError factory"; 
      

/////////////////////////////////
//Setup
/////////////////////////////////
void setup() {
  //Pin Initialization
  initializeInputs();
  initializeOutputs();
  
  //Motor Setup
  Timer5.initialize(4096);                            //start timer five at ~4khz
  Timer5.pwm(PITCH_PWM,0);
  Timer5.pwm(YAW_PWM,0);
  Timer5.pwm(SPRING_PWM,0);

  //Serial UI set-up
  Serial.begin(115200); 
  Serial3.begin(115200);
  help();
  cmd.begin( Serial3, cmd_buffer, sizeof( cmd_buffer ) ) //start the serial ui
      .list( cmdlist)                                   //assign command list from above
      .onCommand( cmd_callback );                       //assign callback, located in UI.ino

  cmd1.begin( Serial, cmd1_buffer, sizeof( cmd1_buffer ) ) //start the serial ui
      .list( cmdlist)                                   //assign command list from above
      .onCommand( cmd_callback );                       //assign callback, located in UI.ino

  //Door Servo Setup 
  doorServo.begin(4)
           .step(180,0);

  loadEEPromPresets();

  digitalWrite(LASER, HIGH); //check if a ball is in the pocket from last power on
  delay(100);
  if(!digitalRead(PHOTOSENSE)){
    isLoaded = true;  //ball is in the pocket, skip loading
  }
  digitalWrite(LASER, LOW);
}

void loop(){
  encoders();                                           //Passes volatile encoder states to globals for use in control loop
  automaton.run();                                      //Run the communication state machines
  updateInputs();                                       //Check switches
  feedback();                                           //Send feedback to ESP
  machine(state);                                            //Main state machine
  atSetPoint = motors();                                //Motion control
  sound(0);                                             //Play sounds
}
