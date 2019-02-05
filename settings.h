//Input Debounce
#define BOUNCE 10

//Sound Ajustments
#define TOSSTIME 200    //Amount of time required for the ball to travel from the pocket to strike zone plane
#define SIGNALTIME 230  //Amount of time require for the sound board to resond to a signal
#define OFFSETTIME 400  //Amount of time to shift the entire sequence to allow for faster pitches
#define PULSE 30

// declarations for motor control

#define ID  0
#define DIR1  1
#define DIR2  2
#define SPEED  450  
#define NUM_MOTORS  3
#define NUM_PRESETS  19
#define PITCHMIN 20
#define PITCHMAX 73
#define YAWMIN 4
#define YAWMAX 76
#define SPRINGMIN 200
#define SPRINGMAX 295
#define SOUND_DELAY 400

// Servo door adjustments
#define SERVO_OPEN 60
#define SERVO_CLOSED 0

/////////////////////////////////
//Global Variables
/////////////////////////////////
int presets[NUM_PRESETS][NUM_MOTORS]=
   {
    {0, 0, 0},    //0  Keys arranged like a phone keypad '1' top left
    //Right Set
    {100, 0, 100 },  //1
    {100, 50, 100 },  //2
    {100, 100, 100},  //3
    {50, 0, 90 },  //4
    {50, 50, 90 },  //5
    {50, 100, 90 },  //6
    {0, 0, 80 },  //7
    {0, 50, 80 },  //8
    {0, 100, 80 },   //9
    //Left Set
    {100, 0, 100 },  //1
    {100, 50, 100 },  //2
    {100, 100, 100 },  //3
    {50, 0, 90 },  //4
    {50, 50, 90 },  //5
    {50, 100, 90 },  //6
    {0, 0, 80 },  //7
    {0, 50, 80 },  //8
    {0, 100, 80 }   //9
  };
int defaultPresets[NUM_PRESETS][NUM_MOTORS] =
// {Pitch, Yaw, Spring}
  {
    {0, 0, 0},    //0  Keys arranged like a phone keypad '1' top left
    //Right Set
    {100, 0, 100 },  //1
    {100, 50, 100 },  //2
    {100, 100, 100},  //3
    {50, 0, 90 },  //4
    {50, 50, 90 },  //5
    {50, 100, 90 },  //6
    {0, 0, 80 },  //7
    {0, 50, 80 },  //8
    {0, 100, 80 },   //9
    //Left Set
    {100, 0, 100 },  //1
    {100, 50, 100 },  //2
    {100, 100, 100 },  //3
    {50, 0, 90 },  //4
    {50, 50, 90 },  //5
    {50, 100, 90 },  //6
    {0, 0, 80 },  //7
    {0, 50, 80 },  //8
    {0, 100, 80 }   //9
  };


//  int rightPresets[NUM_PRESETS][NUM_MOTORS] =
// // {Pitch, Yaw, Spring}
// {
//    {0, 0, 0},    //0  Keys arranged like a phone keypad '1' top left
//    {100, 0, 100 },  //1
//    {100, 50, 100 },  //2
//    {100, 100, 100 },  //3
//    {50, 0, 90 },  //4
//    {50, 50, 90 },  //5
//    {50, 100, 90 },  //6
//    {0, 10, 80 },  //7
//    {0, 50, 80 },  //8
//    {0, 100, 80 }   //9
//  };

//  int leftPresets[NUM_PRESETS][NUM_MOTORS] =
// // {Pitch, Yaw, Spring}
// {
//    {0, 0, 0},    //0  Keys arranged like a phone keypad '1' top left
//    {100, 100, 100 },  //1
//    {100, 50, 100 },  //2
//    {100, 0, 100 },  //3
//    {50, 100, 90 },  //4
//    {50, 50, 90 },  //5
//    {50, 0, 90 },  //6
//    {0, 100, 80 },  //7
//    {0, 50, 80 },  //8
//    {0, 0, 80 }   //9
//  };

const char rc1[] PROGMEM = "High Outside";
const char rc2[] PROGMEM = "High Middle";
const char rc3[] PROGMEM = "High Inside";
const char rc4[] PROGMEM = "Middle Outside";
const char rc5[] PROGMEM = "Middle Middle";
const char rc6[] PROGMEM = "Middle Inside";
const char rc7[] PROGMEM = "Low Outside ";
const char rc8[] PROGMEM = "Low Middle";
const char rc9[] PROGMEM = "Low Inside";

PGM_P const right_table[] PROGMEM = {
  rc1, rc2, rc3, rc4, rc5, rc6, rc7, rc8, rc9};

const char lc1[] PROGMEM = "High Inside";
const char lc2[] PROGMEM = "High Middle";
const char lc3[] PROGMEM = "High Outside";
const char lc4[] PROGMEM = "Middle Inside";
const char lc5[] PROGMEM = "Middle Middle";
const char lc6[] PROGMEM = "Middle Outside";
const char lc7[] PROGMEM = "Low Inside ";
const char lc8[] PROGMEM = "Low Middle";
const char lc9[] PROGMEM = "Low Outside";

PGM_P const left_table[] PROGMEM = {
  lc1, lc2, lc3, lc4, lc5, lc6, lc7, lc8, lc9};


 

