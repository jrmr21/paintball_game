#ifndef CORE_HEADER
#define CORE_HEADER

#include <Arduino.h>
#include <stdarg.h>

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

typedef struct    trame_s
{
  unsigned char   adress;
  unsigned char   adress_to;

  unsigned char   size_trame;
  unsigned char   number_command;

  //unsigned char   **data = NULL; 
  unsigned char     data[10][4];
  
}                 trame_t;

void    init_pin(void);
void    update_mouse(int8_t select);


//************  FRAME   *********************
void  frame1(int8_t *frame);
void  frame2(int8_t *frame);
void  frame3(int8_t *frame);


//***********  Item   ************************
void  opt_demo(void);
void  demo_sender(void);
void  demo_receive(void);
void  adress(void);
void  led(void);
void  adress(void);
void  game_mode(void);



// ***********    RADIO   ********************
#include <nRF24L01.h>
#include <RF24.h>
//  const byte address[6] = "00001";      EXAMPLE

void  radio_init_sender(const byte address[6]);
void  radio_init_receive(const byte address[6]);
void  radio_receive(trame_t* trame);
void  radio_send(trame_t *t);


// ***********    GAME_ONE   ********************
void  game_master(void);
void  game_slave(void);


// ***********    TOOLS   ********************
#define   END_COMMAND       '\0'
#define   ERROR_DATA        "ED \0"
#define   CONFLIT_ADRESS    "CA \0"
#define   DOUBLE_COMMAND    '#'  
#define   MASTER_ADRESS     255

#define   TIME_START        "TS \0"       // master command
#define   TIME_STOP         "TE \0"
#define   TIME_GET          "TG \0"

#define   TIME             'T'                  // slave command
#define   SCORE            'S' 


int             create_trame(trame_t *t, unsigned char network[4], ...);
unsigned char*  compress_char(unsigned int a);
unsigned int    decompress_char(unsigned char a[2]);
int             trame_to_str(trame_t *t, unsigned char str[50]);
void            debug_trame(trame_t *t);
void            print_str(unsigned char* str);


#endif
