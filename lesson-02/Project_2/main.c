#include <stdint.h>
#include "TM4C123.h"                    // Device header

int main(){
    int counter = 0;
    while (counter < 21) {
        ++counter;
        if ((counter & 1) != 0) {  //the condition compares the last significant bits with each other and gives 1 or 0 if true or false
            /* do something when the counter is odd */
        }
        else {
            /* do something when the counter is even */
        }
    }
    
    return 0;
}