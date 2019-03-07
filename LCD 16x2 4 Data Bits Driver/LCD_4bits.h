#include <stdint.h>
#include "LCD_4bits_Cfg.h"

# ifndef LCD_4bits_h
# define LCD_4bits_h
typedef struct
{
uint8_t Lcd_Data_GPIO_GroupId;   // Data pins index in GPIO ConfigParam Structure in "gpio_cfg.c"

uint8_t Lcd_Enable_GPIO_GroupId; // Enable pin index in GPIO ConfigParam Structure in "gpio_cfg.c"

uint8_t Lcd_RW_GPIO_GroupId;     // R/W pin index in GPIO ConfigParam Structure in "gpio_cfg.c"

uint8_t Lcd_RS_GPIO_GroupId;     // RS pin index in GPIO ConfigParam Structure in "gpio_cfg.c"

}LCD_CfgType;

extern const LCD_CfgType LCD_ConfigParam [LCD_GROUPS_NUMBER];
typedef enum {LCD_OK =0, LCD_NOK} LCD_CheckType;

void delayMs(int n) ;
LCD_CheckType enableTrigger(uint8_t GroupId);
LCD_CheckType LCD_Init(void);
LCD_CheckType LCD_sendCommand(uint8_t GroupId ,uint8_t cmd);
LCD_CheckType LCD_displayChar (uint8_t GroupId ,unsigned char data);
LCD_CheckType LCD_clrScreen(uint8_t GroupId );
LCD_CheckType LCD_dispString(uint8_t GroupId ,char * ptr);

#endif
