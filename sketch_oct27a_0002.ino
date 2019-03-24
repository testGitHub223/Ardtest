/*
 * v0.0.0.1
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
  KEY_'       39
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
  KEY_`       96    ё    // Apostrof DO NOT USE FATALL WITH PRESSED KEY
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
              127     // DO NOT USE FATALL


  KEY_LEFT_CTRL   0x80  128
  KEY_LEFT_SHIFT  0x81  129
  KEY_LEFT_ALT    0x82  130
  KEY_LEFT_GUI    0x83  131
  KEY_RIGHT_CTRL  0x84  132
  KEY_RIGHT_SHIFT 0x85  133
  KEY_RIGHT_ALT   0x86  134
  KEY_RIGHT_GUI   0x87  135
                        136   //
  

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

////int tt = 1;
////int tt_MAX = 3;
////int tt_Enter = 0;

////unsigned long ttt;

////String serialReadInChar = "";
////int LEDDING = 0;
////int moveing = 0;


////unsigned long prevTime = 0;
////unsigned long curentTime = 0;



//------ ДЛЯ МИГАНИЯ ЧТО ПЛАТА РАБОТАЕТ -----
const int buttonPin = 2;     // номер входа, подключенный к кнопке
const int ledPin =  12;      // номер выхода светодиода
//------ ДЛЯ МИГАНИЯ ЧТО ПЛАТА РАБОТАЕТ -----


//------ ДЛЯ ОТОБРАЖЕНИЯ МОЖЕТ ЛИ ПЛАТА ПРИНИМАТЬ СООБЩЕНИЯ -----
int buttonState = LOW;         // переменная для хранения состояния кнопки
int buttonStateCount = 0;         // переменная для хранения состояния кнопки
//------ ДЛЯ ОТОБРАЖЕНИЯ МОЖЕТ ЛИ ПЛАТА ПРИНИМАТЬ СООБЩЕНИЯ -----




//------ ДАННЫЕ ДЛЯ ПЕРЕСЫЛКИ -----
int myDataId = 0; //int myDataId = 0;
int myData[19];
//------ ДАННЫЕ ДЛЯ ПЕРЕСЫЛКИ -----


//------ ОЧИСТКА ДАННЫХ ДЛЯ ПЕРЕСЫЛКИ -----
void clearMyData(){
  myData[0] = 0;
  myData[1] = 0;
  myData[2] = 0;
  myData[3] = 0;
  myData[4] = 0;
  myData[5] = 0;
  myData[6] = 0;
  myData[7] = 0;
  myData[8] = 0;
  myData[9] = 0;
  myData[10] = 0;
  myData[11] = 0;
  myData[12] = 0;
  myData[13] = 0;
  myData[14] = 0;
  myData[15] = 0;
  myData[16] = 0;
  myData[17] = 0;
  myData[18] = 0;
}
//------ ОЧИСТКА ДАННЫХ ДЛЯ ПЕРЕСЫЛКИ -----


//------ ЧТЕНИЕ С ПОРТА -----
String str;
String SerialRead() {
  String str = "";
  while (Serial.available() > 0) {
    str += Serial.read();
    //serialReadInChar += Serial.read();
  }
  return str;
}
//------ ЧТЕНИЕ С ПОРТА -----

int incomingByte;          /////????????????????



//----- РАБОТА С ВРЕМЕНЕМ -----
unsigned long maxULong = 4294967295;

unsigned long timeNextMsg = 0;  //время, когда в следующий раз запустить
unsigned long timeDiffMsg = 10000;  //период, через какое нужно отправлять запрос 1000 - 10000
unsigned long timeNextLed = 0;  //время, когда в следующий раз мигнуть
unsigned long timeDiffLed = 500000;  //период, через какое нужно мигать

//вычисление времени для следующего вызова
//доработать!!!!!!
unsigned long nextTime(unsigned long timeToAdd, unsigned long timeToDiff) {
  if (maxULong - timeToAdd < timeToDiff) {
    return timeToDiff - (maxULong - timeToAdd);
  } else {
    return timeToAdd + timeToDiff;
  }
}

// поддерживаются ли ссылки?
//boolean isTimeRedy(unsigned long eventTime, unsigned long timeToDiff) {
//  if (eventTime < micros()){
//    eventTime = nextTime(eventTime, timeToDiff);
//    return true;
//  } else {
//    return false;
//  }
//}

//----- РАБОТА С ВРЕМЕНЕМ -----



//------ ОТПРАВКА ДАННЫХ КЛАВИАТУРЫ -----
void kSend() {
  if (myData[1] > 10) {
    Keyboard.press(myData[1]);
    delay(1);
  }
  if (myData[2] > 10) {
    Keyboard.release(myData[2]);
    delay(1);
  }
  if (myData[3] > 10) {
    Keyboard.press(myData[3]);
    delay(1);
  }
  if (myData[4] > 10) {
    Keyboard.release(myData[4]);
    delay(1);
  }
  if (myData[5] > 10) {
    Keyboard.press(myData[5]);
    delay(1);
  }
  if (myData[6] > 10) {
    Keyboard.release(myData[6]);
    delay(1);
  }
  if (myData[7] > 10) {
    Keyboard.press(myData[7]);
    delay(1);
  }
  if (myData[8] > 10) {
    Keyboard.release(myData[8]);
    delay(1);
  }
  if (myData[9] > 10) {
    Keyboard.press(myData[9]);
    delay(1);
  }
  if (myData[10] > 10) {
    Keyboard.release(myData[10]);
    delay(1);
  }

  if (myData[11] > 10) {
    Keyboard.press(myData[11]);
    delay(1);
  }
  if (myData[12] > 10) {
    Keyboard.release(myData[12]);
    delay(1);
  }
  if (myData[13] > 10) {
    Keyboard.press(myData[13]);
    delay(1);
  }
  if (myData[14] > 10) {
    Keyboard.release(myData[14]);
    delay(1);
  }
  
  delay(9);//620000
  delay(10);
  clearMyData();
}
//------ ОТПРАВКА ДАННЫХ КЛАВИАТУРЫ -----


//------ ОТПРАВКА ДАННЫХ МЫШИ -----
int maskMOUSE_LEFT = 0000000000000001;
int maskMOUSE_RIGHT = 0000000000000010;
int maskMOUSE_MIDDLE = 0000000000000100;

void mSend() {
  if (myData[1] > 0 || myData[1] > 0) {
    if (maskMOUSE_LEFT & myData[1]) {
      Mouse.press(MOUSE_LEFT);
    }
    if (maskMOUSE_RIGHT & myData[1]) {
      Mouse.press(MOUSE_RIGHT);
    }
    if (maskMOUSE_MIDDLE & myData[1]) {
      Mouse.press(MOUSE_MIDDLE);
    }
  }

  if (myData[2] != 0 || myData[3] != 0 || myData[4] != 0) {
    Mouse.move(myData[2], myData[3], myData[4]);
  }

  if (myData[5] > 0) {
    if (maskMOUSE_LEFT & myData[5]) {
      Mouse.release(MOUSE_LEFT);
    }
    if (maskMOUSE_RIGHT & myData[5]) {
      Mouse.release(MOUSE_RIGHT);
    }
    if (maskMOUSE_MIDDLE & myData[5]) {
      Mouse.release(MOUSE_MIDDLE);
    }
  }
  delay(150);
  clearMyData();
}
//------ ОТПРАВКА ДАННЫХ МЫШИ -----








//int FFFFFFFF = 0;// delete
//byte isSend = 0;
//-----------------------------------------------------------------------------------




//------ ИНИЦИАЛИЗАЦИЯ ПЛАТЫ -----
void setup() { // initialize the buttons' inputs:

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  // initialize mouse control:
  Mouse.begin();
  Keyboard.begin();
  delay(3000);

  // сбрасываем Shift
  Keyboard.release(shiftKey);

  // для выключателя
  // инициализируем пин, подключенный к светодиоду, как выход
  pinMode(ledPin, OUTPUT);
  // инициализируем пин, подключенный к кнопке, как вход
  pinMode(buttonPin, INPUT); 

  // количество сообщений о готовности
  int timerr = 5;
  while (timerr > 0) {
    timerr--;
    int gg_1 = 42;
    String GGG_1 = String(gg_1);
    Keyboard.println(GGG_1);
    Keyboard.press(gg_1);
    delay(10);
    Keyboard.release(gg_1);
    Keyboard.press(176);
    delay(10);
    Keyboard.release(176);
  }
  timeNextMsg = nextTime(micros(), timeDiffMsg);
}
//------ ИНИЦИАЛИЗАЦИЯ ПЛАТЫ -----




int ttr0 = 0;
int rreeaadd = 251;
boolean isRead = false;
boolean isTest = false;
boolean is252 = false;
boolean is253 = false;
void loop() {


  //------ ОТОБРАЖЕНИЕ ЧТО ПЛАТА РАБОТАЕТ -----
  if (timeNextLed < micros()){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));    // turn the LED off by making the voltage LOW
    timeNextLed = nextTime(micros(), timeDiffLed);
  }
  //------ ОТОБРАЖЕНИЕ ЧТО ПЛАТА РАБОТАЕТ -----
  

  
  //------ ОТОБРАЖЕНИЕ КНОПКИ НА ПЛАТЕ -----
  //timeDiffMsg
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {
    buttonStateCount = -10;
    // выключаем светодиод
    digitalWrite(ledPin, LOW);
  }
  else {
    if (buttonStateCount > 0){
      // включаем светодиод
      digitalWrite(ledPin, HIGH);
    }
    else {
       buttonStateCount++;
    }
  }
  //------ ОТОБРАЖЕНИЕ КНОПКИ НА ПЛАТЕ -----


  //------ ПЛАТА В РЕЖИМЕ ЧТЕНИЯ -----

  if (Serial.available() > 0) {
    rreeaadd = Serial.read();
    if(rreeaadd == 251){
      if (digitalRead(ledPin) == LOW){
        Serial.print("[BUSY R][251 251]");
      } else {
        Serial.print("[REFRES][251 251]");
      }
      clearMyData();
      myDataId = 0; // обнуляем idx - готовы к приему нового пакета
      timeNextMsg = nextTime(micros(), timeDiffMsg);
    } else {
      myData[myDataId] = rreeaadd;
      myDataId++;
    }
  }
  //------ ПЛАТА В РЕЖИМЕ ЧТЕНИЯ -----


  //------ ПЛАТА В РЕЖИМЕ ОТПРАВКИ -----
  if (myDataId >= 19) {
    // В массиве x - все наши считанные 13 байт
    // делаем что-то с массивом,
    
    String str1 = String(myData[15]);
    String str2 = String(myData[16]);
    String str3 = str1 + " " + str2 + "]";
    if (digitalRead(ledPin) == LOW){
      Serial.print("[BUSY  ][" + str3);
    }
    else {
      if ((myData[17] == 254) && (myData[18] == 255)){
        int type = myData[0];
        switch (type) {
          case 75:
            kSend();  // "K"
            Serial.print("[KSEND ][" + str3);
            break; 
            case 77:
            mSend();  // "M"
            Serial.print("[MSEND ][" + str3);
            break;
          default:
            Serial.print("[DEFALT][" + str3);
            break;
        }
      }
      else {
        Serial.print("[ERREND][" + str3);
      }
    }
    clearMyData();
    myDataId = 0; // обнуляем idx - готовы к приему нового пакета
    timeNextMsg = nextTime(micros(), timeDiffMsg);
  }
  //------ ПЛАТА В РЕЖИМЕ ЧТЕНИЯ -----

}

