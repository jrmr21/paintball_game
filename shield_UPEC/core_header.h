#ifndef CORE_HEADER
#define CORE_HEADER

#include <Arduino.h>

// ***********    BUTTON  *****************
void    key_loop(int8_t *bt1, int8_t *bt2, int8_t *bt3);


// ***********    LCD   ********************
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define   lcd_ADRESS 0x3F

#ifndef LCD       // PROTECT DOUBLE INCLUSION BABY
  #define LCD
  static LiquidCrystal_I2C lcd(lcd_ADRESS, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#else
  extern LiquidCrystal_I2C lcd(lcd_ADRESS, 16, 2);
#endif


void    init_lcd(void);

/*
 *                    EXAMPLE CODE   
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Hello, world!");
 * 
 */


// **********   ALL   *********************
#define   B   2   // min 150 to max 255 to ONE pin
#define   G   3
#define   R   4

#define btn1  5
#define btn2  6
#define btn3  9

void    init_pin(void);

#endif
