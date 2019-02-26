#include "GPIO.h"
/**
 * main.c
 * simple code to demosntrate how to use thr driver.
 * control the state of the LED using the 2 Pushbuttons
 */
int main(void)
{  uint8_t x;
   uint8_t y;
   GPIO_Init();
   while(1){

     GPIO_Read(1, &x);   
     GPIO_Read(2, &y);
     if(x==0){
        GPIO_Write(0, 0xE);
        }
     if(y==0){
        GPIO_Write(0, 0x0);
        }
  }

}
