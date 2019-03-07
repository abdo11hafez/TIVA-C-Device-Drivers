#include "GPIO.h"
#include "LCD_4bits.h"
#include <stdint.h>

#define HIGH_NIBBLE(hVar,var) hVar= (var & 0xf0)  // hVar will hold value of high nibble of var
#define LOW_NIBBLE(lVar,var)  lVar= (var<<4)      // lVar will hold the value of low nibble of var


/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++){
        for(j = 0; j < 3180; j++){
        } /* do nothing for 1 ms */
    }
}

LCD_CheckType enableTrigger(uint8_t GroupId)
{
    const LCD_CfgType * CfgPtr;
    if ( GroupId <LCD_GROUPS_NUMBER)
    {
        CfgPtr =  & LCD_ConfigParam[GroupId];

        GPIO_Write(CfgPtr->Lcd_Enable_GPIO_GroupId, 0);
        delayMs(1);
        GPIO_Write(CfgPtr->Lcd_Enable_GPIO_GroupId, 0xff);
        delayMs(6);

        return LCD_OK;
    }
    return LCD_NOK;
}

LCD_CheckType LCD_Init(void)
{
    uint8_t LoopIndex;
    const LCD_CfgType * CfgPtr;
    if (LCD_GROUPS_NUMBER >0 ) {
        for(LoopIndex = 0; (LoopIndex < LCD_GROUPS_NUMBER); LoopIndex ++)
        {
            CfgPtr = & LCD_ConfigParam[LoopIndex];
            GPIO_Write(CfgPtr->Lcd_Enable_GPIO_GroupId, 0xff); // activate LCD enable

            LCD_sendCommand (LoopIndex,0x33); // 4-bit mode
            LCD_sendCommand (LoopIndex,0x32);
            LCD_sendCommand (LoopIndex,0x28);
            LCD_sendCommand (LoopIndex,0x0c); // turn on lcd
        }
        return LCD_OK ;
    }
    else return LCD_NOK ;
}

LCD_CheckType LCD_sendCommand(uint8_t GroupId ,uint8_t cmd)
{
    uint8_t high_nibble , low_nibble ;
    HIGH_NIBBLE(high_nibble,cmd);
    LOW_NIBBLE(low_nibble,cmd);
    const LCD_CfgType * CfgPtr;
    if ( GroupId <LCD_GROUPS_NUMBER)
        {
        CfgPtr = & LCD_ConfigParam[GroupId];

        GPIO_Write(CfgPtr->Lcd_RS_GPIO_GroupId, 0) ;            // enable command mode
        GPIO_Write(CfgPtr->Lcd_RW_GPIO_GroupId, 0) ;            // activate lcd write

        GPIO_Write(CfgPtr->Lcd_Data_GPIO_GroupId, 0) ;
        GPIO_Write(CfgPtr->Lcd_Data_GPIO_GroupId, high_nibble);  // to send high nibble command
        enableTrigger(GroupId);                                  // triggre lcd enable

        GPIO_Write(CfgPtr->Lcd_Data_GPIO_GroupId, 0) ;
        GPIO_Write(CfgPtr->Lcd_Data_GPIO_GroupId, low_nibble);  // to send low nibble command
        enableTrigger(GroupId);

        return LCD_OK ;
        }
    else return LCD_NOK ;
}

LCD_CheckType LCD_displayChar (uint8_t GroupId ,uint8_t data)
{
    uint8_t high_nibble , low_nibble ;
    HIGH_NIBBLE(high_nibble,data);
    LOW_NIBBLE(low_nibble,data);
    const LCD_CfgType * CfgPtr;
    if ( GroupId <LCD_GROUPS_NUMBER)
    {
        CfgPtr = & LCD_ConfigParam[GroupId];

        GPIO_Write(CfgPtr->Lcd_RS_GPIO_GroupId, 0xff) ; //  enable data mode
        GPIO_Write(CfgPtr->Lcd_RW_GPIO_GroupId, 0)    ; //  activate lcd write

        GPIO_Write(CfgPtr->Lcd_Data_GPIO_GroupId, 0) ;
        GPIO_Write(CfgPtr->Lcd_Data_GPIO_GroupId, high_nibble) ;// to send high nibble data
        enableTrigger(GroupId);                   // triggre lcd enable

        GPIO_Write(CfgPtr->Lcd_Data_GPIO_GroupId, 0) ;
        GPIO_Write(CfgPtr->Lcd_Data_GPIO_GroupId, low_nibble) ;// to send low nibble data
        enableTrigger(GroupId);

            return LCD_OK;
        }
    else return LCD_NOK ;
}

LCD_CheckType LCD_clrScreen(uint8_t GroupId)
{
    if ( GroupId <LCD_GROUPS_NUMBER)
    {
        LCD_sendCommand(GroupId,0x01);
        return LCD_OK;
    }
    else return LCD_NOK ;
}

LCD_CheckType LCD_dispString(uint8_t GroupId ,char * ptr)
{
    if ( GroupId <LCD_GROUPS_NUMBER)
    {
        while(* ptr!= '\0')
        {
            LCD_displayChar(GroupId ,*ptr);
            ptr++;
        }
        return LCD_OK;
    }
    else return LCD_NOK;
}
