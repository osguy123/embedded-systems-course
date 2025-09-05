#include <stdint.h>
#include "TM4C123.h"                    // Device header
#include "TM4C123GH6PM.h"

 
int main(){
   SYSCTL->RCGCGPIO = 0X20U; /* enable clock for GPIOF*/
   GPIOF->DIR = 0X0EU; // set pins 1,2, and 3 as outputs
   GPIOF->DEN = 0X0EU;

   while (1) {
       GPIOF->DATA = 0X02U;
       
       int volatile counter = 0;
       while (counter < 1000000) { // delay loop
           ++counter;
       }
       
       GPIOF->DATA = 0X00U;
       
       counter = 0;
       while (counter < 1000000) { // delay loop
           ++counter;
       }
   }

    return 0;
}