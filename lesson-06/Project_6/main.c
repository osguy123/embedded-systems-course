#include <stdint.h>
#include "TM4C123.h"                    // Device header
#include "TM4C123GH6PM.h"

#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)
 
int main(){
    unsigned int flashes = 0;
    
   SYSCTL->RCGCGPIO |= (1U << 5); /* enable clock for GPIOF*/
   GPIOF->DIR |= (LED_RED | LED_BLUE | LED_GREEN);  // set pins 1,2, and 3 as outputs
   GPIOF->DEN |= (LED_RED | LED_BLUE | LED_GREEN);

   GPIOF->DATA = LED_BLUE;
   while (flashes <= 30) {
       GPIOF->DATA |= LED_RED;
       
       int volatile counter = 0;
       while (counter < 1000000) { // delay loop
           ++counter;
       }
       
       GPIOF->DATA &= ~LED_RED;
       
       counter = 0;
       while (counter < 1000000) { // delay loop
           ++counter;
       }
       ++flashes;
   }
          GPIOF->DATA = 0x00;

    return 0;
}