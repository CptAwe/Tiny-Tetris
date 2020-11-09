/* 
 * 
 */

#ifndef BLOCKSCPP
#define BLOCKSCPP

#include <Arduino.h>

class blocks{
	public:

		// the tetris blocks
		static const byte I[2] PROGMEM = { 0B01000100, 0B01000100 };
		static const byte J[2] PROGMEM = { 0B11000000, 0B01000100 };
		static const byte L[2] PROGMEM = { 0B01100000, 0B01000100 };
		static const byte O[2] PROGMEM = { 0B01100000, 0B00000110 };
		static const byte S[2] PROGMEM = { 0B11000000, 0B00000110 };
		static const byte T[2] PROGMEM = { 0B01000000, 0B00001110 };
		static const byte Z[2] PROGMEM = { 0B01100000, 0B00001100 };
		
		static byte * random_piece() {
			// For some reason doing this with a switch() causes an "undefined reference" >:/
			byte ran = random(7);
			if (ran == 0) {
				return I;
			} else if (ran == 1) {
				return J;
			}else if (ran == 2) {
				return L;
			}else if (ran == 3) {
				return O;
			}else if (ran == 4) {
				return S;
			}else if (ran == 5) {
				return T;
			}else if (ran == 6) {
				return Z;
			}else{
				return I;
			}
		}

};

#endif