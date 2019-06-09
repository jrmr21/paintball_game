#ifndef CORE_HEADER
#define CORE_HEADER

#include <Arduino.h>
#include <stdarg.h>

// ***********    BUTTON  *****************
void    key_loop(int8_t *bt1, int8_t *bt2, int8_t *bt3);
void    key_time_loop(int *bt1, int *bt2, int *bt3);


// ***********    LCD   ********************
#include <Wire.h> 
#include "LiquidCrystal_I2C.h"


#define clear_line    "                "
#define clear_arrow   "  "
#define posX_arrow    14
#define arrow         "<="

#define   lcd_ADRESS 0x3F
//#define   lcd_ADRESS 0x27

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
#define   B   4   // min 150 to max 255 to ONE pin
#define   G   3
#define   R   2

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


// ***********    FLAGS GAME   ********************
void  game_flag_slave(int game_time);
void  game_flag_master(const unsigned char players[10]);

void  game_flag(int game_time, int res[3]);


// ***********    GAME  ********************
void  game_master(void);
void  game_slave(void);

void  game_lobby(const unsigned char players[10]);
void  game_flag(int game_time, int res[3]);


// ***********    TOOLS   ********************
#define   END_COMMAND       '\0'
#define   ERROR_DATA        "ED \0"
#define   CONFLIT_ADRESS    "CA \0"
#define   DOUBLE_COMMAND    '#'  
#define   ADRESS_BRODCAST   255
#define   ADRESS_MASTER     254

#define   TIME_START        "TS \0"       // master command
#define   TIME_STOP         "TE \0"
#define   TIME_GET          "TG \0"

#define   GAME_FLAGS_SELECT "GF1\0"
#define   GAME_BOM_SELECT   "GB1\0"

#define   TEAM_RED          'R'
#define   TEAM_GREEN        'G'
#define   TEAM_BLUE         'B'

#define   JOIN_VALIDATION   "J1 \0"
#define   JOIN_REQUEST      "J0 \0" 

#define   TIME             'T'                  // slave command
#define   SCORE            'S'


void            create_command(unsigned char data, unsigned int a, unsigned char p[4]);
int             create_trame(trame_t *t, unsigned char network[4], ...);
void            compress_char(unsigned int a, unsigned char data[2]);
unsigned int    decompress_char(unsigned char a[2]);
int             trame_to_str(trame_t *t, unsigned char str[50]);
void            str_to_trame(trame_t *t, unsigned char* str);
void            debug_trame(trame_t *trame);
void            print_str(unsigned char* str);


#endif
