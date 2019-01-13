/*
  KeyboardAndMouseControl

  Controls the mouse from five pushbuttons on an Arduino Leonardo, Micro or Due.

  Hardware:
   5 pushbuttons attached to D2, D3, D4, D5, D6

  The mouse movement is always relative. This sketch reads
  four pushbuttons, and uses them to set the movement of the mouse.

  WARNING:  When you use the Mouse.move() command, the Arduino takes
  over your mouse!  Make sure you have control before you use the mouse commands.

  created 15 Mar 2012
  modified 27 Mar 2012
  by Tom Igoe

  this code is in the public domain

*/


/*
  Key Hexadecimal value Decimal value
  //   №

  KEY_SPACE   32
  KEY_!       33
  KEY_"       34
  KEY_#       35
  KEY_$       36
  KEY_%       37
  KEY_&       38
  KEY_(       40
  KEY_)       41
  KEY_*       42
  KEY_+       43
  KEY_,       44
  KEY_-       45
  KEY_.       46
  KEY_/       47
  KEY_0       48
  KEY_1       49
  KEY_2       50
  KEY_3       51
  KEY_4       52
  KEY_5       53
  KEY_6       54
  KEY_7       55
  KEY_8       56
  KEY_9       57
  KEY_:       58
  KEY_;       59
  KEY_<       60
  KEY_=       61
  KEY_>       52
  KEY_?       63
  KEY_@       64
  KEY_A       65
  KEY_B       66
  KEY_C       67
  KEY_D       68
  KEY_E       69
  KEY_F       70
  KEY_G       71
  KEY_H       72
  KEY_I       73
  KEY_J       74
  KEY_K       75
  KEY_L       76
  KEY_M       77
  KEY_N       78
  KEY_O       79
  KEY_P       80
  KEY_Q       81
  KEY_R       82
  KEY_S       83
  KEY_T       84
  KEY_U       85
  KEY_V       86
  KEY_W       87
  KEY_X       88
  KEY_Y       89    Н
  KEY_Z       90    Я
  KEY_[       91    х
  KEY_\       92    \
  KEY_]       93    ъ
  KEY_^       94    :
  KEY__       95    _
  KEY_`       96    ё    // Apostrof
  KEY_a       97
  KEY_b       98
  KEY_c       99
  KEY_d       100
  KEY_e       101
  KEY_f       102
  KEY_g       103

  KEY_w       119
  KEY_z       120


  KEY_{       123
  KEY_|       124
  KEY_}       125
  KEY_~       126     // Tilda



  KEY_LEFT_CTRL   0x80  128
  KEY_LEFT_SHIFT  0x81  129
  KEY_LEFT_ALT    0x82  130
  KEY_LEFT_GUI    0x83  131
  KEY_RIGHT_CTRL  0x84  132
  KEY_RIGHT_SHIFT 0x85  133
  KEY_RIGHT_ALT   0x86  134
  KEY_RIGHT_GUI   0x87  135

  KEY_RETURN      0xB0  176     // KEY_RETURN_ENTER
  KEY_ESC         0xB1  177
  KEY_BACKSPACE   0xB2  178
  KEY_TAB         0xB3  179

  //KEY_<   190
  //KEY_>   191


  KEY_CAPS_LOCK   0xC1  193
  KEY_F1          0xC2  194
  KEY_F2          0xC3  195
  KEY_F3          0xC4  196
  KEY_F4          0xC5  197
  KEY_F5          0xC6  198
  KEY_F6          0xC7  199
  KEY_F7          0xC8  200
  KEY_F8          0xC9  201
  KEY_F9          0xCA  202
  KEY_F10         0xCB  203
  KEY_F11         0xCC  204
  KEY_F12         0xCD  205

  // PrintScreen? POWER!!!!

  KEY_INSERT      0xD1  209
  KEY_HOME        0xD2  210
  KEY_PAGE_UP     0xD3  211
  KEY_DELETE      0xD4  212
  KEY_END         0xD5  213
  KEY_PAGE_DOWN   0xD6  214
  KEY_RIGHT_ARROW 0xD7  215
  KEY_LEFT_ARROW  0xD8  216
  KEY_DOWN_ARROW  0xD9  217
  KEY_UP_ARROW    0xDA  218







*/



/*
  struct KEY_TIMED {
  unsigned char KEY_1;
  unsigned char KEY_2;
  unsigned char KEY_3;
  unsigned char impotant;
  unsigned char shift;
  unsigned char ctrl;
  unsigned char alt;
  unsigned long last_time_colled;
  unsigned long time_no_press_any;
  unsigned long time_no_press_this;

  };
  KEY_TIMED KEYZ_TIMED[50];
*/

/*
    int gg_1 = 33;
    String GGG_1 = String(gg_1);
    Keyboard.println(GGG_1);
    Keyboard.press(gg_1);
    delay(1);
    Keyboard.release(gg_1);
    Keyboard.press(176);
    delay(1);
    Keyboard.release(176);
*/







#include "Keyboard.h"
#include "Mouse.h"



//-----------------------------------------------------------------------
// Описание класса передаваемых кнопок
class Button {

    boolean flagPress;    // признак кнопка сейчас нажата
    boolean flagClick;    // признак кнопка была нажата (клик)
    byte  buttonCount;    // счетчик подтверждений стабильного состояния
    byte timeButton;      // время подтверждения состояния кнопки
    byte _pin;            // номер вывода
};
//-----------------------------------------------------------------------






// use this option for OSX:
// char ctrlKey = KEY_LEFT_GUI;
// use this option for Windows and Linux:
// char ctrlKey = KEY_LEFT_CTRL;

char shiftKey = KEY_LEFT_SHIFT;

int tt = 1;
int tt_MAX = 3;
int tt_Enter = 0;

unsigned long ttt;

String serialReadInChar = "";
int LEDDING = 0;
int moveing = 0;


unsigned long prevTime = 0;
unsigned long curentTime = 0;


void setup() { // initialize the buttons' inputs:

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  // initialize mouse control:
  Mouse.begin();
  Keyboard.begin();
  delay(3000);

  Keyboard.release(shiftKey);
}


int myData[6];
int myDataId = 0;


String str;
String SerialRead() {
  String str = "";
  while (Serial.available() > 0) {
    str += Serial.read();
    //serialReadInChar += Serial.read();
  }
  return str;
}


int incomingByte;





unsigned long timeDiff = 0;  //период, через какое нужно запускать
unsigned long time_next = 0;  //время, когда в следующий раз запустить

unsigned long maxULong = 4294967295;

//вычисление времени для следующего вызова
unsigned long nextTime(unsigned long timeToAdd, unsigned long timeToDiff) {

  if (maxULong - timeToAdd < timeToDiff) {
    return timeToDiff - (maxULong - timeToAdd);
  } else {
    return timeToAdd + timeToDiff;
  }
}

//-----------------------------------------------------------------------------------
int timerr = 0;
int ttr0 = 0;
void loop() {

  //ledding to show that work
  LEDDING ++;
  if (LEDDING <= 0) {
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  }
  else {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    if (LEDDING >= 20000) {
      LEDDING = -20000;
    }
  }


  if (LEDDING == 10000) {
    Serial.flush();
    //Serial.println(inChar);
    unsigned long prevTime = micros();
    //unsigned long prevTime = millis();
    //String prevTimeStr = String(prevTime);
    Serial.print(" __");
    Serial.println(maxULong);
    Serial.print("_ _");
    Serial.println(prevTime);
    Serial.print("__ ");
    Serial.println(nextTime(prevTime, 100000000));
    //Serial.println(nextTime);
    //Serial.println(SerialRead());   // читаем и выводит в Serial
    Serial.flush();
    moveing ++;
  }




  if (timerr < 10) {
    timerr++;
    int gg_1 = 33;
    String GGG_1 = String(gg_1);
    Keyboard.println(GGG_1);
    Keyboard.press(gg_1);
    delay(1);
    Keyboard.release(gg_1);
    Keyboard.press(176);
    delay(1);
    Keyboard.release(176);
  }

  str = "";
  //str = SerialRead();
  int strLength = str.length();

  // K, M = 75, 77

  //if (strLength == )

  if (strLength > 0) {
    Serial.println("-----------------");
    for (int i = 0; i < strLength; i++) {
      int tt = str[i];
      Serial.print(tt);
      Serial.print("   ");
      Serial.println(strLength);
    }
  }

  if (str == "a") {
    Serial.print("!!!!!!!!!!!!");
  }

  
  if (ttr0 < 100000) {
    if (Serial.available() > 0) {
      incomingByte = Serial.read();

      if (incomingByte == 'A'){
        
      }
        //Serial.print(incomingByte);
      Serial.println("-----------------");
      //Keyboard.press(incomingByte);
      //delay(1);
      //Keyboard.release(incomingByte);
      Serial.print(incomingByte);
      int tt = 30000;
      Serial.println("^^^^");
      Serial.print(0);
      Serial.println("^^^^");
      
    }
    ttr0++;
  }







  /*
    for(int i = 0; i < strLength; i++) {
      Keyboard.press(str[i]);
      delay(1);
      Keyboard.release(str[i]);
    }
  */
  /*
    if (str.length() > 0){

    Serial.println(" __");
    Keyboard.press(str[0]);
    delay(1);
    Keyboard.release(str[0]);
    Serial.flush();
    }
  */


}


//  if (inChar[0] == 50) {
//    //Mouse.move(0, 4);
//  }

//    if (inChar[1] == 50) {
//    Mouse.move(0, 40);
//  }
//
//  if (inChar[2] == 50) {
//    Mouse.move(0, 140);
//  }

//inChar = "";


//
////------------------------
//  if (Serial.available() > 0) {
//    int Serial_n = Serial.available();
//    //int inChar = Serial.read();
//    //char inChar = Serial.read();
//    inChar += Serial.read();
//
//    Serial.println(inChar);
//
//    String GGG_1 = String(Serial_n);
//    Keyboard.println(GGG_1);
//    Keyboard.press(Serial_n);
//    delay(1);
//    Keyboard.release(Serial_n);
//
//    /*
//        String GGG_1 = String(inChar[0]);
//        Keyboard.println(GGG_1);
//        Keyboard.press(inChar[0]);
//        delay(1);
//        Keyboard.release(inChar[0]);
//    */
//    /*
//        if (inChar[0] == 33) {
//
//          String GGG_1 = String(inChar[0]);
//          Keyboard.println(GGG_1);
//          Keyboard.press(inChar[0]);
//          delay(1);
//          Keyboard.release(inChar[0]);
//        }
//    */
//    /*
//        String GGG_1 = String(inChar);
//        Keyboard.println(GGG_1);
//        Keyboard.press(inChar);
//        delay(1);
//        Keyboard.release(inChar);
//    */
//    String int33 = String(33);
//    String int34 = String(44);
//    switch (inChar[0]) {
//
//      /*
//                case 3:
//                  // move mouse up
//                  Mouse.move(0, -4);
//                  break;
//                case 4:
//                  // move mouse down
//                  Mouse.move(0, 4);
//                  break;
//      */
//
//      /*
//        case 'u':
//        // move mouse up
//        Mouse.move(0, -4);
//        break;
//        case 'd':
//        // move mouse down
//        Mouse.move(0, 4);
//        break;
//        case 'l':
//        // move mouse left
//        Mouse.move(-4, 0);
//        break;
//        case 'r':
//        // move mouse right
//        Mouse.move(4, 0);
//        break;
//        case 'm':
//        // perform mouse left click
//        Mouse.click(MOUSE_LEFT);
//        break;
//        case 'p':
//        // perform mouse right click
//        Mouse.click(MOUSE_RIGHT);
//        break;
//      */
//
//      ///*
//      case 33:
//        // move mouse up
//        Mouse.move(0, -4);
//        break;
//      case 55:
//        // move mouse down
//        Mouse.move(0, 4);
//        break;
//        //*/
//    }
//  }
//
////-------------------------------------
//
//
//
//
//

