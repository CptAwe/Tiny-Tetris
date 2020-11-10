/* The OLED screen is set into Page Addressing Mode. This means that there are
 * 128 columns and 7*(8 pages).
 * 
 * very informative read:
 * https://iotexpert.com/debugging-ssd1306-display-problems/
*/

#ifndef SCREENCPP
#define SCREENCPP

#include <Arduino.h>
#include <Wire.h>

class screen{
    private:
		static const byte SCREEN_WIDTH = 128;
		static const byte SCREEN_HEIGHT = 64;
		// OLED commands
		static const byte OLED_ADDRESS = 0x3C;// you may need to change this, this is the OLED I2C address.  
		static const byte OLED_COMMAND = 0x80;// declare that a command is to be sent
		static const byte OLED_DATA = 0x40;// declare that data is to be sent
		static const byte OLED_FULL_ON = 0xA5;// Disregards GDDRAM and forces the display to be ON
		static const byte OLED_SHOW_GDDRAM = 0xA4;// The diplay shows what GDDRAM has
		static const byte OLED_DISPLAY_OFF = 0xAE;// Power off display
		static const byte OLED_DISPLAY_ON = 0xAF;// Power on display
		static const byte OLED_NORMAL_DISPLAY = 0xA6;// not inverse - 1 means ON
		static const byte OLED_INVERSE_DISPLAY = 0xA7;// inverse - 1 means OFF
		static const byte OLED_SET_BRIGHTNESS = 0x81;// contrast control (does it actually do something?)
		static const byte OLED_SET_ADDRESSING = 0x20;// set memory addressing mode
		static const byte OLED_HORIZONTAL_ADDRESSING = 0x00;// horizontal addressing mode
		static const byte OLED_VERTICAL_ADDRESSING = 0x01;// vertical addressing mode
		static const byte OLED_PAGE_ADDRESSING = 0x02;// page addressing mode
		static const byte OLED_SET_COLUMN = 0x21;// at what column to start at (vertical addressing)
		static const byte OLED_SET_PAGE = 0x22;// at what page to start (vertical addressing)

		void OLEDCommand(byte command) {
			// send commands to the display
			Wire.beginTransmission(OLED_ADDRESS);
			Wire.write(OLED_COMMAND);
			Wire.write(command);
			Wire.endTransmission();
		}

		void OLEDData(byte data) {
			// send data to the display
			Wire.beginTransmission(OLED_ADDRESS);
			Wire.write(OLED_DATA);
			Wire.write(data);
			Wire.endTransmission();
		}

	public:
		void init(){
			// Initialise the display
			OLEDCommand(OLED_DISPLAY_OFF);
			delay(20);
			OLEDCommand(OLED_DISPLAY_ON);
			delay(20);
			OLEDCommand(OLED_NORMAL_DISPLAY);
			delay(20);
			OLEDCommand(0x8D);// what command is that? (enable oscilator frequency?)
			delay(20);
			OLEDCommand(0x14);// what command is that? (enable charge pumb regulator?)
			delay(20);
			OLEDCommand(OLED_NORMAL_DISPLAY);
		}

		void entire_display_on() {
			// Don't forget to set the display to show the GDDRAM contents afterwards
			OLEDCommand(OLED_FULL_ON);
		}

		void show_gddram_contents() {
			OLEDCommand(OLED_SHOW_GDDRAM);
		}

		void inverse() {
			OLEDCommand(OLED_INVERSE_DISPLAY);
		}

		void clear() {
			// clears the display.
			// Isn't there a better way?
			OLEDCommand(OLED_SET_ADDRESSING);
			OLEDCommand(OLED_VERTICAL_ADDRESSING);

			OLEDCommand(OLED_SET_COLUMN);
			OLEDCommand(0);
			OLEDCommand(SCREEN_WIDTH-1);

			OLEDCommand(OLED_SET_PAGE);
			OLEDCommand(0);
			OLEDCommand(SCREEN_HEIGHT-1);

			for (int col=0; col<=SCREEN_WIDTH-1; col++){
				for (int page=0; page<=SCREEN_HEIGHT-1; page++){
					OLEDData(0);
				}
			}
		}

		void draw(byte page_start, byte page_end, byte column_start, byte column_end, byte data[13][2]) {
			// draws on the screen by vertical addressing
			// The data array has to be mirrored

			OLEDCommand(OLED_SET_ADDRESSING);
			OLEDCommand(OLED_VERTICAL_ADDRESSING);

			OLEDCommand(OLED_SET_COLUMN);
			OLEDCommand(column_start);
			OLEDCommand(column_end-1);

			OLEDCommand(OLED_SET_PAGE);
			OLEDCommand(page_start);
			OLEDCommand(page_end-1);
			
			for (byte col=column_start; col<=column_end-1; col++){
				byte mirror_page = page_end-1;
				for (byte page=page_start; page<=page_end-1; page++){
					OLEDData(data[col][mirror_page]);
					// delay(100);
					mirror_page--;
				}
			}
		}		

};

#endif