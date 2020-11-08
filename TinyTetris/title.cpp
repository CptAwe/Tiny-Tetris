/**
 * "Tiny Tetris" upside-down text binarized from http://www.dcode.fr/binary-image
 * 
 */

#ifndef TITLECPP
#define TITLECPP

#include <Arduino.h>


class title {
    public:

        static const byte welcomeScreen[16][5] PROGMEM = {
            B01110011, B10100010, B00100011, B11100010, B00000000,
            B10001001, B00100010, B00100000, B00100010, B00000000,
            B10000001, B00100010, B00100000, B00100010, B00000000,
            B01110001, B00011110, B00100001, B11100010, B00000000,
            B00001001, B00100010, B00100000, B00100010, B00000000,
            B10001001, B00100010, B00100000, B00100010, B00000000,
            B01110011, B10011110, B11111011, B11101111, B10000000,
            B00000000, B00000000, B00000000, B00000000, B00000000,
            B00000000, B00000000, B00000000, B00000000, B00000000,
            B00000000, B10001000, B10111000, B10000000, B00000000,
            B00000000, B10001100, B10010000, B10000000, B00000000,
            B00000000, B10001100, B10010000, B10000000, B00000000,
            B00000001, B01001010, B10010000, B10000000, B00000000,
            B00000010, B00101001, B10010000, B10000000, B00000000,
            B00000010, B00101001, B10010000, B10000000, B00000000,
            B00000010, B00101000, B10111011, B11100000, B00000000
        };

        // Tetris Illustration upside-down image binarized from http://www.dcode.fr/binary-image
        static const byte tetrisLogo[40][8] PROGMEM =  {
            B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
            B11101101, B10111111, B11111111, B11111111, B11111111, B01111111, B11111001, B11100111,
            B11101101, B00110100, B11111111, B11111111, B11111110, B01110011, B11110001, B11100111,
            B10111000, B01010101, B11111111, B11111111, B11111000, B01110011, B11100001, B11100111,
            B10011110, B10110011, B10110011, B11100011, B11100100, B00100011, B11100011, B11110011,
            B10001111, B00010011, B00110001, B11110001, B11110100, B00100011, B11100011, B11110011,
            B10001111, B00000111, B01110001, B11110000, B11110010, B00110011, B11100011, B11110001,
            B10001111, B00000110, B01100001, B11111000, B11111010, B00000001, B11000001, B11100001,
            B10000110, B00001110, B11100000, B11111000, B01111001, B00000001, B11000000, B11000001,
            B10000110, B00001100, B11100000, B11111100, B01111001, B00000001, B11000000, B00000001,
            B10000110, B00001100, B11110000, B11111100, B01111001, B00000000, B10000000, B00000001,
            B10000110, B00001100, B11110000, B01111100, B01111001, B00000000, B10000000, B00000001,
            B10000110, B00000110, B11110000, B01111100, B01111001, B00000000, B10000000, B00000001,
            B10000110, B00000111, B01111000, B01111000, B01110010, B00000000, B10000000, B00000001,
            B10001101, B00000011, B00111000, B01111000, B01110010, B00000000, B00000000, B00000001,
            B10011001, B10000011, B10111000, B01111000, B11110100, B00000000, B00000000, B00000001,
            B10011001, B10000001, B10011100, B01110001, B11101100, B00000000, B00000000, B00000001,
            B10001001, B00000000, B11111100, B01110001, B11011000, B00000000, B00000000, B00000001,
            B10001011, B00000000, B01111100, B01100011, B10110000, B00000000, B00000000, B00000001,
            B10000110, B00000000, B00110100, B11100111, B01100000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00011110, B11100110, B01000000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00001110, B11001100, B10000000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00000110, B11011011, B00000000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00000111, B11010010, B00000000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00000011, B10100100, B00000000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00000001, B11111000, B00000000, B00000000, B00110000, B00000001,
            B10000000, B00000000, B00000000, B11110000, B00000000, B00000000, B00110000, B00000001,
            B10000000, B00000000, B00000000, B11010000, B00000000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00000000, B01110000, B00000000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B10000000, B01100000, B00000000, B00000000, B00000000, B00000001,
            B10000011, B00000000, B00000000, B01100000, B00000000, B00000000, B00000000, B00000001,
            B10000011, B00000000, B00000000, B01100000, B00000000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00000000, B01100000, B00000000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00000000, B01100000, B00000000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00000000, B11110000, B00000000, B00000000, B00000000, B00010001,
            B10000000, B00000000, B00000000, B11001000, B00000000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00000001, B10001000, B00000000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00000001, B10001000, B00000000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00000000, B10010000, B00000000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00000000, B11110000, B00001000, B00000000, B00000000, B00000001
        };

        // Tetris Brick upside-down image binarized from http://www.dcode.fr/binary-image
        static const byte brickLogo[36][8] PROGMEM= {
            B10000000, B00000000, B00000000, B00000000, B00000000, B11111111, B11111100, B00000001,
            B10000000, B00000111, B11111100, B11111111, B11111110, B11111111, B11111100, B00000001,
            B10000011, B11111111, B11111110, B11111111, B11111111, B01111111, B11111110, B00000001,
            B10000011, B11111111, B11111110, B01111111, B11111111, B00111111, B11111111, B00000001,
            B10000011, B11111111, B11111111, B01111111, B11111111, B10111111, B11111111, B10000001,
            B10001001, B11111111, B11111111, B00111111, B11111111, B10011111, B11111111, B10000001,
            B10001101, B11111111, B11111111, B10111111, B11111111, B11001111, B11111111, B11000001,
            B10001101, B11111111, B11111111, B10011111, B11111111, B11101111, B11111111, B11100001,
            B10001100, B11111111, B11111111, B11011111, B11111111, B11100111, B11111111, B11110001,
            B10001110, B11111111, B11111111, B11001111, B11111111, B11110111, B11111111, B11110001,
            B10001110, B11111111, B11111111, B11101111, B11111111, B11111011, B11111111, B00000001,
            B10001110, B01111111, B11111111, B11101111, B11111111, B11100000, B00000000, B00010001,
            B10001111, B01111111, B11111111, B11100100, B00000000, B00000001, B11111111, B11110001,
            B10001111, B00111111, B10000000, B00000000, B00111111, B11111011, B11111111, B11110001,
            B10011111, B00000000, B00000111, B11110111, B11111111, B11110011, B11111111, B11100001,
            B10001111, B00111111, B11111111, B11100111, B11111111, B11110111, B11111111, B11000001,
            B10001111, B00111111, B11111111, B11101111, B11111111, B11100111, B11111111, B11000001,
            B10001111, B01111111, B11111111, B11101111, B11111111, B11101111, B11111111, B10000001,
            B10001111, B01111111, B11111111, B11001111, B11111111, B11001111, B11111111, B10000001,
            B10000111, B01111111, B11111111, B11011111, B11111111, B11011111, B11111111, B00000001,
            B10000110, B01111111, B11111111, B11011111, B11111111, B11011111, B11111111, B00000001,
            B10000110, B01111111, B11111111, B10011111, B11111111, B10111111, B11111110, B00000001,
            B10000010, B11111111, B11111111, B10111111, B11111111, B10111111, B11111000, B00000001,
            B10000010, B11111111, B11111111, B10111111, B11111111, B00110000, B00000000, B00000001,
            B10000010, B11111111, B11111111, B00111111, B11100000, B00000000, B00000000, B00000001,
            B10000000, B11111111, B11111111, B00000000, B00000110, B00000000, B00000000, B00000001,
            B10000000, B11111111, B11000000, B00000111, B11111110, B00000000, B00000000, B00000001,
            B10000000, B10000000, B00001110, B01111111, B11111100, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00111110, B11111111, B11111100, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00011110, B11111111, B11111100, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00011100, B11111111, B11111000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00011101, B11111111, B11111000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00001101, B11111111, B11110000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00001001, B11111111, B11110000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00000011, B11111111, B11100000, B00000000, B00000000, B00000001,
            B10000000, B00000000, B00000011, B11110000, B00000000, B00000000, B00000000, B00000001
        };
};



#endif