/* The OLED screen is set into Page Addressing Mode. This means that there are
 * 128 columns and 8*(8 pages).
 * 
 * very informative read:
 * https://iotexpert.com/debugging-ssd1306-display-problems/
*/

#ifndef SCREENCPP
#define SCREENCPP

#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>

class screen{

    private:
		static const byte SCREEN_WIDTH = 128;
		static const byte SCREEN_HEIGHT = 64;

		static const byte PLAY_WIDTH = 118;
		static const byte PLAY_HEIGHT = 58;

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

		byte OLEDRead(){
			// Not supported for SSD1306.
			return 0;
		}

		byte pow2(byte exponent) {
			// 2^x
            if (exponent <= 0) {
                return 1;
            }
            byte sum = 2;
            for (byte i=1; i<exponent; i++) {
                sum = sum*2;
            }
            return sum;
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

		byte inverse_data(byte data) {
			return ~data;
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

		void draw(
			byte column_start, byte column_end, byte page_start, byte page_end,
			byte data[], bool read_from_progmem, bool invert = false) {
			// draws on the screen by vertical addressing
			// The data array has to be mirrored

			OLEDCommand(OLED_SET_ADDRESSING);
			OLEDCommand(OLED_VERTICAL_ADDRESSING);

			OLEDCommand(OLED_SET_COLUMN);
			OLEDCommand(column_start);
			OLEDCommand(column_start + column_end-1);

			OLEDCommand(OLED_SET_PAGE);
			OLEDCommand(page_start);
			OLEDCommand(page_end-1);
			
			// set them to zero before referring to the array
			column_start = 0;
			page_start = 0;

			for (byte col=column_start; col<=column_end-1; col++){
				byte mirror_page = page_end-1;// The image has to be mirrored horizontally
				for (byte page=page_start; page<=page_end-1; page++){
					
					byte data_2b_sent = 0;
					int position = mirror_page + col*(page_end-page_start);// It can't be a byte. The number is too big

					if (read_from_progmem) {
						data_2b_sent = pgm_read_byte(&data[position]);
					}else{
						data_2b_sent = data[position];
					}

					if (invert){
						data_2b_sent = ~data_2b_sent;
					}
					// OLEDData(data[col][mirror_page]);
					
					OLEDData(data_2b_sent);
					// delay(100);
					mirror_page--;
				}
			}
		}

		void draw(byte column_start, byte column_end, byte page_start, byte page_end, byte data) {
			// draws on the screen by vertical addressing
			// The data array has to be mirrored
			// This is a simpler version of the above function. It sends the same data to 
			// a part of the screen.

			OLEDCommand(OLED_SET_ADDRESSING);
			OLEDCommand(OLED_VERTICAL_ADDRESSING);

			OLEDCommand(OLED_SET_COLUMN);
			OLEDCommand(column_start);
			OLEDCommand(column_start + column_end-1);

			OLEDCommand(OLED_SET_PAGE);
			OLEDCommand(page_start);
			OLEDCommand(page_end-1);
			
			int data_end = column_end*page_end;
			for (int i=0; i<=data_end; i++){
				OLEDData(data);
			}
		}

		void draw(byte x /*column*/, byte y /*page*/, bool color) {
			// Draws a specific pixel of the screen.
			// It converts from columns and pages to coordinates.

			// TODO: This sets all other pixels of the page to 0.
			// To avoid this the rest of the pixels have to be known.
			// Can I read their values from the screen or I have to keep track of them?
			
			byte page = y/8;
			byte bit = y - page*8;
			byte data;
			if (bit != 0) {
				data = pow2(bit - 1);
			} else {
				data = 1;
			}

			draw(
				x, x,
				page, page,
				data*color
			);
		}
	

};

#endif