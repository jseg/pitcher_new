#include "Arduino.h"
/////////////////////////////////
//Pin Definitions
/////////////////////////////////

//Inputs  

#define BALL_IN             24      // Microswitch sensor pulled low N.O.
#define LOADED              25      // Microswitch sensor pulled low N.O.
#define HAND               27      //Switch to set the handedness of the batter
#define ADJUST              30

#define PITCH_A            18      // the pin number of the Pitch Encoder A     Sensor
#define PITCH_B            A7      // the pin number of the Pitch Encoder B     Sensor was 19
#define YAW_A               2       // the pin number of the Yaw Encoder A       Sensor
#define YAW_B              A6       // the pin number of the Yaw Encoder B       Sensor was 3
#define SPRING_A           19
#define SPRING_B           A9
//#define SPRING_COUNTER      18    //pseudo encoder
#define SPRING_COUNTER      A8      //pseudo encoder
#define DOOR_SENSE          26     // Safety door signal goes low when OK to Fire
#define PHOTOSENSE          28

//#define KEY_PAD             (31,32,33,34,35,36,37,38,39)    
//                                    // the pin numbers of the
//                                    // 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F,G,H,*,# Keypad
                                   
                             
//Outputs

//Sounds

#define SOUND_ON            13     // the pin number for "ON"                    Sound    input PIn
#define SOUND_CRACK         9      // the pin number for "Crack"                  Sound    input PIn
#define SOUND_GRUNT         10     // the pin number for "GRUNT"                 Sound    input PIn
#define SOUND_EXPLODE       11     // the pin number for "Load To Explode"       Sound    input PIn
#define SOUND_READY         12     // the pin number for "Ready"                Sound    input PIn
#define SOUND_SIX           8      // the pin number of the                      Sound 6  input PIn
#define SOUND_SEVEN         7      // the pin number of the                      Sound 7  input PIn
#define SOUND_EIGHT         6      // the pin number of the                      Sound 8  input PIn  

//Motor Controls
#define SPRING_PWM         44     // the pin number of the Pull Grab           Servo PWM
#define SPRING_D           48     // direction of pullgrab                     
#define PITCH_PWM           46     // the pin number of the Up Down             Servo PWM SPEED  UpDownPWM
#define PITCH_F             52     // the pin number of the Up Down             Servo Rev DIR1   UpDownF
#define PITCH_R             53     // the pin number of the Up Down             Servo Fwd DIR2   UpDownR
#define YAW_PWM             45     // the pin number of the Left Right          Servo PWM        LeftRightPWM
#define YAW_F               50     // the pin number of the Left Right          Servo Rev        LeftRightF
#define YAW_R               51     // the pin number of the Left Right          Servo Fwd        LeftRightR


//Relays
#define BALL_LOAD           42     // the pin number of the Ball load motor      Relay
#define SAFETY_DOOR         43     // the pin number of the Safety Door          Relay
#define REJECT_SOL          41     // reject solenoid function?                  Relay
#define FIRE_SOL            40     // the pin number of the Ball eject           Solonoid
#define POWER_CUT           22     // out

//Digital Signals
#define LATCH               23      // Signal to call for a new ball
#define LCD                 (2,3) // the pin numbers of the 4X20 LCD Display
#define LASER               29


/////////////////////////////////
//Pin Initialization
/////////////////////////////////
//void initializeInputs(void){
//}
//
//void initializeOutputs(void){  //set pin modes and intial states
//}

