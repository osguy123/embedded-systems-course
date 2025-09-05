#include <stdint.h>
// #include "TM4C123.h"                    // Device header
#include "TM4C123GH6PM.h"
#include "delay.h"

#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)
#define GPIOF_AHB_BITS ((unsigned long volatile *) GPIOF_AHB)

uint8_t u8a, u8b;
uint16_t u16c, u16d;
uint32_t u32e, u32f;

int8_t s8;
int16_t s16;
int32_t s32;


int main() {
    
    u8a = sizeof(u8a);
    u16c = sizeof(uint16_t);
    u32e = sizeof(uint32_t);

    u8a = 0xa1u;
    u16c = 0xc1c2u;
    u32e = 0xe1e2e3e4u; // Most modern silicon vendors are little-endian || This means that this is stored e4 e3 e2 e1 instead of e1 e2 e3 e4
    
    u8b = u8a; // This used LDRB and STRB to store one byte
    u16d = u16c; // This uses LDRH and STRH to store half-words
    u32f = u32e; // This uses LDR and STR to store 4 byte values (this one we're familiar with already)
    
    u16c = 40000U;
    u16d = 30000U;
    u32e = (uint32_t) u16c + u16d; // Without the type-cast, this works. However, not everywhere. u16c and u16d get implicitly cast to the default int size (32 for tiva C)
    
    u16c = 100u;
    s32 = 10 - (int32_t) u16c; // Once again works here but not on a 16 bit default int. This is because everything is typecast to unsigned int since mismatching types (10 is a signed int)
    // Type-cast to the type of the result to increase limit past 32,767 (the largest signed integer you can have with 16 bits)
    
    
    if ((int32_t) u32e > -1) { // Since -1 is promoted to unsigned int (mismatching types), you are comparing to 0xFFFFFFFF which is larger than everything so the loop always skips "if"
    } else {
        u8a = 0u;
    } 
    
    u8a = 0xffu;
    if ((uint8_t) ~u8a == 0x00u) { // Here, u8a is promoted as an int so the 1's complement is now 0x00FFFFFF != 0x00. (cast back to 1 byte)
        u8b = 1u;
    }
       
    unsigned int flashes = 0;
    
    SYSCTL->RCGCGPIO |= (1U << 5); /* enable clock for GPIOF*/
    SYSCTL->GPIOHBCTL |= (1U << 5); /* enable AHB for GPIOF */
    GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);  // set pins 1,2, and 3 as outputs
    GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);

    GPIOF_AHB_BITS[LED_BLUE] = LED_BLUE;
    
    while (flashes <= 30) {
        //GPIOF->DATA |= LED_RED;
        GPIOF_AHB_BITS[LED_RED] = LED_RED;
        delay(500000);
       
        GPIOF_AHB_BITS[LED_RED] = 0;
       delay(500000);
       ++flashes;
   }
          GPIOF_AHB->DATA = 0x00;

//    return 0;
}
 
