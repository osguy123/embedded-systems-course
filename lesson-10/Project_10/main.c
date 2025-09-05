#include <stdint.h>
// #include "TM4C123.h"                    // Device header
#include "TM4C123GH6PM.h"
#include "delay.h"

#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)
#define GPIOF_AHB_BITS ((unsigned long volatile *) GPIOF_AHB)
    
//unsigned fact(unsigned n);

int *swap(int *x, int *y);
int *swap(int *x, int *y) {
    static int tmp[2];
    tmp[0] = *x;
    tmp[1] = *y;
    *x = tmp[1];
    *y = tmp[0];
    return tmp;
}

  int main() {
//     unsigned volatile x;
//     
//     x = fact(0U);
//     x = 2U + 3U*fact(1U);
//     (void)fact(9U); // this is out of the range of the defined fact fxn array. This then clobbers the return address, creating a runtime error
     
      
    unsigned int flashes = 0;
    
    SYSCTL->RCGCGPIO |= (1U << 5); /* enable clock for GPIOF*/
    SYSCTL->GPIOHBCTL |= (1U << 5); /* enable AHB for GPIOF */
    GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);  // set pins 1,2, and 3 as outputs
    GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);

    GPIOF_AHB_BITS[LED_BLUE] = LED_BLUE;
    int x = 1000000;
    int y = 1000000/2;

    while (flashes <= 30) {
        //GPIOF->DATA |= LED_RED;
        int *p = swap(&x, &y);

        GPIOF_AHB_BITS[LED_RED] = LED_RED;
        delay(p[0]);
       
        GPIOF_AHB_BITS[LED_RED] = 0;
       delay(p[1]);
       ++flashes;
   }
          GPIOF_AHB->DATA = 0x00;

//    return 0;
}
 
//unsigned fact(unsigned n) {
//// 0! = 1
//// n! = n(n-1)! for n > 0  
//    unsigned foo[6];
//    foo[n] = n;
//    
//    if (n == 0U) {
//        return 1U;
//    } else {
//        return foo[n] * fact(n - 1U);
//    }
//}
