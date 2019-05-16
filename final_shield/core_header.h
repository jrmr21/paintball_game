#ifndef CORE_HEADER
#define CORE_HEADER

#include <Arduino.h>

// ***********    BUTTON  *****************
void    key_loop(int8_t *bt1, int8_t *bt2, int8_t *bt3);


// ***********    LCD   ********************
#include <Wire.h> 
#include "LiquidCrystal_I2C.h"

#define clear_line    "                "
#define clear_arrow   "  "
#define posX_arrow    14
#define arrow         "<="

//#define   lcd_ADRESS 0x3F
#define   lcd_ADRESS 0x27

#ifndef LCD                // PROTECT DOUBLE INCLUSION BABY
  #define LCD
  static LiquidCrystal_I2C lcd(lcd_ADRESS, 16, 2);  // set the LCD address for a 16 chars and 2 line display
#else
  extern LiquidCrystal_I2C lcd(lcd_ADRESS, 16, 2);
#endif

void  init_lcd(void);

/*
 *                    We USE  
  lcd.set_Cursor(col, line);
  lcd.printstr(char* a);
  lcd.clear();
 * 
 */

// **********   ALL   *********************
#define   B   2   // min 150 to max 255 to ONE pin
#define   G   3
#define   R   4

#define btn1  5
#define btn2  6
#define btn3  9

#define MIN_item  1
#define MAX_item  6

void    init_pin(void);
void    update_mouse(int8_t select);


//************  FRAME   *********************
void  frame1(int8_t *frame);
void  frame2(int8_t *frame);
void  frame3(int8_t *frame);


//***********  Item   ************************
void  opt_demo(void);
void  demo_sender(void);
void  demo_receirve(void);
void  adress(void);
void  led(void);



// ***********    RADIO   ********************
#include <nRF24L01.h>
#include <RF24.h>
//  const byte address[6] = "00001";      EXAMPLE

void  radio_init_sender(const byte address[6]);
void  radio_init_receirve(const byte address[6]);
void  radio_receirve(char *text);
void  radio_send(const char *text);

#endif
