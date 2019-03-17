#include "GPIO.h"
#include "M4MemMap.h"
/**
 * simple code to demosntrate how to use the driver.
 * LED always ON ,but Blinks when Pushing SW2
 */
void main(void)
{
   GPIO_Init();
   GPIO_SetInterruptEvent(1, EVENT_FALL_EDGE, MASK_ENABLED);
   EN_INT(30);
   while(1)
   {
       GPIO_Write(0, 0xff);
   }
}

void PortF_CallBack(void)
{
    int i ,j ;
    for(i=0;i<20;i++)
    {
     GPIO_Write(0, 0xff);
     for (j=0;j<50000;j++){}
     GPIO_Write(0, 0x00);
     for (j=0;j<50000;j++){}
    }
}
