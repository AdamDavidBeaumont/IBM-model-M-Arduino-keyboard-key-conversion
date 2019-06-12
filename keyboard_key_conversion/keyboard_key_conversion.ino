#include "Keyboard.h"
#define CLK_PIN 10
#define DATA_PIN 16
#define CLK_READ_STATE LOW
#define CLK_READ true
#define CLK_UNREAD false
#define LED_PIN1 2
#define LED_PIN2 3
#define LED_PIN3 4
#define LED_PIN4 5
#define LED_PIN5 6
int keytable[0x1ff];


  
#define RELEASE_CODE 0x03F
#define LEFT_SHIFT_SCANCODE 0x091
int frame = 0;
int counter = 0;
int keyrelease = false;
#define FRAME_SIZE 11



void setup() {
  keytable[0x1B8] = 'j';
  keytable[0x1B1] = 's';
  keytable[0x1AC] = '4';
  keytable[0x1A9] = 'f';
  keytable[0x1A5] = 'l';
  keytable[0x1BD] = '+';
  keytable[0x1B4] = ']';
  keytable[0x1C9] = KEY_F5;
  keytable[0x1C5] = KEY_F9;
  keytable[0x1C0] = KEY_F1;
  keytable[0x1DD] = '/';
  keytable[0x1D8] = KEY_F7;
  keytable[0x1D4] = KEY_F23;
  keytable[0x1D1] = KEY_F3;
  keytable[0x1ED] = 0x037;
  keytable[0x1E8] = KEY_F6;
  keytable[0x1E4] = KEY_F10;
  keytable[0x1E1] = KEY_F2;
  keytable[0x1F9] = KEY_F8;
  keytable[0x1F5] = KEY_F24;
  keytable[0x1F0] = KEY_F4;
  keytable[0x19C] = '5';
  keytable[0x199] = 'h';
  keytable[0x195] = '\\';
 // keytable[0x190] = ;
  keytable[0x18D] = KEY_UP_ARROW;
  keytable[0x188] = 'd';
  keytable[0x184] = 'i';
  keytable[0x17D] = '9';
  keytable[0x178] = '7';
  keytable[0x171] = 'w';
  keytable[0x16C] = KEY_DELETE;
  keytable[0x169] = 'r';
  keytable[0x165] = 'p';
  keytable[0x160] = KEY_TAB;
  keytable[0x15C] = '8';
  keytable[0x159] = 'y';
  keytable[0x155] = '=';
  keytable[0x150] = 'q';
  keytable[0x14D] = KEY_INSERT;
  keytable[0x148] = '4';
  keytable[0x144] = '0';
  keytable[0x13C] = '\n';
  keytable[0x139] = KEY_RIGHT_ALT;
  keytable[0x135] = KEY_RIGHT_SHIFT;
  keytable[0x130] = KEY_LEFT_ALT;
  keytable[0x12D] = '1';
  keytable[0x128] = ' ';
  keytable[0x118] = 'n';
  keytable[0x11D] = '.';
  keytable[0x111] = KEY_LEFT_CTRL;
  keytable[0x10C] = KEY_LEFT_ARROW;
  keytable[0x109] = 'c';
  keytable[0x105] = ',';
  keytable[0x124] = '.';
  keytable[0x0A4] = '/';
  keytable[0x0FD] = '*';
  keytable[0x0CD] = KEY_BACKSPACE;
  keytable[0x0C1] = KEY_ESC;
  keytable[0x0BC] = '3';
  keytable[0x0B9] = 'm';
  keytable[0x0B5] = '\n';
  keytable[0x0B0] = 'z';
  keytable[0x0C8] = '3';
  keytable[0x0C4] = '9';
  keytable[0x0AD] = KEY_RIGHT_ARROW;
  keytable[0x0DC] = 0x045;
  keytable[0x0D9] = '6';
  keytable[0x0D5] = KEY_F11;
  keytable[0x0D0] = '1';
  keytable[0x0E9] = '5';
  keytable[0x0E5] = '-';
  keytable[0x0FD] = '*';
  keytable[0x0F8] = '8';
  keytable[0x0F4] = KEY_F12;
  keytable[0x0F1] = '2';
  keytable[0x07C] = KEY_ESC;
  keytable[0x064] = ';';
  keytable[0x0A8] = 'v';
  keytable[0x09D] = '2';
  keytable[0x098] = 'b';
  keytable[0x094] = 0x027;
  keytable[0X091] = KEY_LEFT_SHIFT;
  keytable[0x089] = 'x';
  keytable[0x085] = 'k';
  keytable[0x079] = 'u';
  keytable[0x070] = 'a';
  keytable[0x06D] = '7';
  keytable[0x068] = 't';
  keytable[0x05D] = '6';
  keytable[0x058] = 'g';
  keytable[0x054] = '[';
  keytable[0x051] = KEY_CAPS_LOCK;
  keytable[0x049] = 'e';
  keytable[0x045] = 'o';
  keytable[0x043] = '-';
  keytable[0x038] = KEY_F19;
  keytable[0x034] = KEY_RIGHT_CTRL;
  keytable[0x031] = KEY_F15;
  keytable[0x029] = KEY_F17;
  keytable[0x028] = KEY_F16;
  keytable[0x025] = KEY_F21;
  keytable[0x020] = KEY_F13;
  keytable[0x01C] = '0';
  keytable[0x019] = KEY_F18;
  keytable[0x015] = KEY_F22;
  keytable[0x010] = KEY_F14;
  keytable[0x00D] = KEY_DOWN_ARROW;
  keytable[0x004] = KEY_F20;
  pinMode(LED_PIN1, OUTPUT);//blue
  pinMode(LED_PIN2, OUTPUT);//white
  pinMode(LED_PIN3, OUTPUT);//green
  pinMode(LED_PIN4, OUTPUT);//yellow
  pinMode(LED_PIN5, OUTPUT);//red
  pinMode(CLK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT); 
  digitalWrite(CLK_PIN, HIGH);
  digitalWrite(DATA_PIN, HIGH);
  Keyboard.begin();
}

//
//display
//

static void displayNumber(int frame) {
  displayBit(frame, LED_PIN1, 1);
  displayBit(frame, LED_PIN2, 2);
  displayBit(frame, LED_PIN3, 4);
  displayBit(frame, LED_PIN4, 8);
  displayBit(frame, LED_PIN5, 16);
}

static void displayBit(int frame, int pin, int mask) {
  if (frame & mask) {
    digitalWrite(pin, HIGH);
  } else {
    digitalWrite(pin, LOW);
  }
}

//
//READ
//

int clk_state = CLK_UNREAD;

static bool readBit(int* frame) {
  if (digitalRead(CLK_PIN) == CLK_READ_STATE) {
      if (clk_state == CLK_UNREAD) {
        clk_state = CLK_READ;
        *frame = (*frame << 1) | digitalRead(DATA_PIN);
        return true;
      } 
  } else {
    clk_state = CLK_UNREAD;
  }
  return false;
}





static bool isSpecialKey(int usbKey) {
  int specialkeys[7] = {KEY_CAPS_LOCK, KEY_LEFT_SHIFT, KEY_RIGHT_SHIFT, KEY_LEFT_CTRL, KEY_RIGHT_CTRL, KEY_LEFT_ALT, KEY_RIGHT_ALT};
    for (int x = 0; x < 7; x++) {
      if (usbKey == specialkeys[x]) {
        return true;
      }
    }
    return false;
}

static int makeScanCode(int frame) {
  return (frame >> 1);
}

//
//WRITE
//

static void sendKeypress(int scancode) {
      int usbKey = keytable[scancode];
      if (isSpecialKey(usbKey)) {
        if (keyrelease == true) {
           Keyboard.release(usbKey);
        } else {
           Keyboard.press(usbKey);
        }
      } else {
        Keyboard.press(usbKey);
        delay(1);
        Keyboard.release(usbKey);   
     }
}

//
//MAIN
//

#define CHECK_BIT1 frame & 1
#define CHECK_BIT2 1 << 10

void loop() {
  if (readBit(&frame)) {
    counter++;
    if (counter == FRAME_SIZE) {
        if (frame == RELEASE_CODE) {
            keyrelease = true;
        } else if (CHECK_BIT1 && ~frame & CHECK_BIT2) {    
            int scancode = makeScanCode(frame);
            //displayNumber(scancode); 
            sendKeypress(scancode);
            keyrelease = false;
        } else {
            //displayNumber(~0);
            delay(1);    
        }
        counter = 0;
        frame = 0;
    } 
  }
}
