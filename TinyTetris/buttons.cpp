/* 
 * 
 * 
 * 
 */

#ifndef BUTTONSCPP
#define BUTTONSCPP

#include <Arduino.h>

class buttons {
    // There are 4 buttons
    private:
        byte num_of_buttons = 4;
        int* pins_;

        /**
         * Calculates the power of 2
         */
        int pow2(int exponent) {
            if (exponent == 0) {
                return 1;
            }
            int sum = 2;
            for (int i=1; i<exponent; i++) {
                sum = sum*2;
            }
            return sum;
        }

    public:
        buttons(int pins[]) {
            
            pins_ = new int[num_of_buttons];

            memcpy(pins_, pins, num_of_buttons*sizeof(int));

            for (int i=0; i<=num_of_buttons-1; i++){
                pinMode(pins_[i], INPUT);
            }
        }

        int states() {
            int states = 0;
            for (int i=0; i<=num_of_buttons-1; i++){
                
                // Each button is a unique power of 2
                // | 2^0 | 2^1 | 2^2 | 2^3 | 2^4 |
                
                states += digitalRead(pins_[i]) * pow2(i);
            }
            return states;
        }
};





#endif