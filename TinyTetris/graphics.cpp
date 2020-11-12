/**
 * This handles the graphics. I could put each one to a separate library on its own.
 * Then I could handle the widths and heights of each graphic better.
 * Would it be better? Propably yes.
 * Is it worth it just to save a little time and make the code more intuitive? No. This is the manly way!
 * 
 * For each graphic:
 *  * The max height is 128 lines
 *  * The max width is 8 columns, with each column containing 1 byte.
 *  * Each bit is one pixel.
 *  * Each graphic is shown as is. No mirroring is necessary. Any modifications are done by screen.cpp
 * 
 * 
 */

#ifndef GRAPHICSCPP
#define GRAPHICSCPP

#include <Arduino.h>


class graphics {
    public:
        class titleScreen {
            public:
                byte x = 20; 
                byte y = 8;
                byte* graph() {
                    static const byte welcomeScreen[160] = {// [20][8]
                        0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,
                        0B11000001,0B00000101,0B11010111,0B01111111,0B11111111,0B11111111,0B11111111,0B11111111,
                        0B11110111,0B11011100,0B11010111,0B01111111,0B11111111,0B11111111,0B11111111,0B11111111,
                        0B11110111,0B11011101,0B01011000,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,
                        0B11110111,0B11011101,0B10011101,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,
                        0B11110111,0B00000101,0B11011101,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,
                        0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,
                        0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,
                        0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,
                        0B11100000,0B00000100,0B00000100,0B00000000,0B10000001,0B10000000,0B00010000,0B00001111,
                        0B11100000,0B00000100,0B00000100,0B00000000,0B10000000,0B10000000,0B00010000,0B00001111,
                        0B11100110,0B01100100,0B11111100,0B11001100,0B10011100,0B11111001,0B11110001,0B11111111,
                        0B11111110,0B01111100,0B11111111,0B11001111,0B10000000,0B11111001,0B11110001,0B11111111,
                        0B11111110,0B01111100,0B00011111,0B11001111,0B10000001,0B11111001,0B11111000,0B01111111,
                        0B11111110,0B01111100,0B00011111,0B11001111,0B10000111,0B11111001,0B11111100,0B00011111,
                        0B11111110,0B01111100,0B11111111,0B11001111,0B10000011,0B11111001,0B11111111,0B10001111,
                        0B11111110,0B01111100,0B11111111,0B11001111,0B10010001,0B11111001,0B11111111,0B10001111,
                        0B11111110,0B01111100,0B00000111,0B11001111,0B10011000,0B10000000,0B00010000,0B00001111,
                        0B11111110,0B01111100,0B00000111,0B11001111,0B10011100,0B10000000,0B00010000,0B00001111,
                        0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111,0B11111111
                    };
                    return welcomeScreen;
                }
        };

        class blocks {
            class I {
                public:
                    byte x;
                    byte y;
                    byte* graph() {
                        static const byte _I[20];
                    }
            };
        };
        

};



#endif