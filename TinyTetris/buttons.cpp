/* 
 * 
 * 
 * 
 */

#ifndef BUTTONSCPP
#define BUTTONSCPP

#include <Arduino.h>

#define NUM_OF_BUTTONS 4

class buttons {
    // There are 4 buttons
    private:
        byte num_of_buttons = NUM_OF_BUTTONS;
        byte* pins_;

        /**
         * Calculates the power of 2
         */
        int pow2(byte exponent) {
            if (exponent == 0) {
                return 1;
            }
            byte sum = 2;
            for (byte i=1; i<exponent; i++) {
                sum = sum*2;
            }
            return sum;
        }

    public:
        buttons(const byte pins[NUM_OF_BUTTONS]) {
            
            pins_ = new byte[num_of_buttons];

            memcpy(pins_, pins, num_of_buttons*sizeof(int));

            for (int i=0; i<=num_of_buttons-1; i++){
                pinMode(pins_[i], INPUT);
            }
        }

        byte states() {
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