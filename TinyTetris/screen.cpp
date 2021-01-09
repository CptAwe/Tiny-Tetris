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
#include "graphics.cpp"

class screen{

    private:
		static const byte SCREEN_WIDTH = 128;
		static const byte SCREEN_HEIGHT = 64;

		static const byte PLAY_WIDTH = 118;// actual pixels
		static const byte PLAY_HEIGHT = 58;// actual pixels

		static const byte PLAY_COLUMNS = 10;// squares
		static const byte PLAY_LINES = 20;// squares

		bool play_screen[PLAY_LINES][PLAY_COLUMNS];

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

		byte empty_row[4*8] = {// Default row with no blocks filled
			0B01000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000010,
			0B01000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000010,
			0B01000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000010,
			0B01000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000010
		};
		byte empty_row_size = sizeof(empty_row)/sizeof(byte);

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

			// fill play_screen array with zeroes
			// TODO: This can be squished even more. Each square doesn't need to be one byte.
			for (int i=0; i<PLAY_LINES; i++){
				for (int j=0; j<PLAY_COLUMNS; j++){
					play_screen[i][j] = false;
				}
			}
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
			byte data[], bool read_from_progmem = false, bool invert = false) {
			// draws on the screen by vertical addressing
			// The data array has to be mirrored

			OLEDCommand(OLED_SET_ADDRESSING);
			OLEDCommand(OLED_VERTICAL_ADDRESSING);

			OLEDCommand(OLED_SET_COLUMN);
			OLEDCommand(column_start);
			OLEDCommand(column_end-1);

			OLEDCommand(OLED_SET_PAGE);
			OLEDCommand(page_start);
			OLEDCommand(page_end - 1);
			
			// set them to zero before referring to the array
			column_end = column_end - column_start;
			column_start = 0;
			page_end = page_end - page_start;
			page_start = 0;

			for (byte col=column_start; col<=column_end-1; col++){
				byte mirror_page = page_end-1;// The image has to be mirrored horizontally
				for (byte page=page_start; page<=page_end-1; page++){
					
					byte data_2b_sent = 0;
					int position = mirror_page + col*page_end;// It can't be a byte. The number is too big

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
			OLEDCommand(column_end - 1);

			OLEDCommand(OLED_SET_PAGE);
			OLEDCommand(page_start);
			OLEDCommand(page_end - 1);
			
			int data_end = (column_end - column_start)*(page_end - page_start);
			for (int i=0; i<data_end; i++){
				OLEDData(data);
			}
		}

		void draw(byte x /*column*/, byte y /*page*/, bool color) {
			// Draws a specific pixel of the screen.
			// It converts from columns and pages to coordinates.
			// This sets all other pixels of the page to 0.

			// TODO: Needs a little more testing
			
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

		void drawPerimiter() {
			/** The perimiter is a square (column, page, byte):
			 * 
			 *                              0B11111111
			 *          A(5, 7, 0B01111111)    ----    B(5, 0, 0B11111110)
			 *                  |                           |
			 *   0B01000000     |                           |  0B00000010
			 *                  |                           |
			 *         C(126, 7, 0B01111111)   ----    D(126 , 0, 0B11111110)
			 *                              0B11111111
			*/

			draw(5, 6, 1, 7, 255);// top line
			draw(5, 127, 0, 1, 0B00000010);// right line
			draw(126, 127, 1, 7, 255);// bottom line
			draw(5, 127, 7, 8, 0B01000000);// left line

			draw(5, 6, 0, 1, 0B11111110);// top right point
			draw(126, 127, 0, 1, 0B11111110);// bottom right point
			draw(126, 127, 7, 8, 0B01111111);// bottom left point
			draw(5, 6, 7, 8, 0B01111111);// top left point
		}

		void drawPlayArea(byte x /*line*/, byte y /*column*/, bool color = true){
			// Fills appropriate box on the play area coordinates
			// The x,y values refer to the number of columns and lines a tetris game has.

			// The 0,0 coordinates are the top left corner, to be consistent with the vertical addressing
			play_screen[x][y] = color;
		}

		void updatePlayArea() {
			/** Updates the whole play area on the screen
			 * 
			 * Check each column first and then each line.
			 * Some columns affect more than one page.
			 * Thus the adjacent columns have to also be checked.
			 *
			 * The checking occurs in 4 groups.
			 * Group 1: Column 0
			 * Group 2: Columns 1, 2, 3, 4
			 * Group 3: Columns 5, 6, 7, 8
			 * Group 4: Columns 9
			 * 
			 * Each tetris line coresponds to a line on the screen.
			 *  Tetris Line | Display line 
			 *       19     |   121-124     | x1 - y1
			 *       18     |   115-118     | x2 - x1-3
			 *       17     |   109-112     | x3 - x2-3
			 *       ...    |     ...       |
			 *  ------------|---------------|
			 *                 x-3 - x
			 * 
			 * NOTE: This function can be replaced by the updatePlayArea(byte line).
			*/
			byte actual_line_end = 124;// The line of the display
			for (byte line = PLAY_LINES-1; line < 255; line--) {// from bottom to top
				byte current_row[empty_row_size];
				byte actual_line_start = actual_line_end - 3;

				memcpy(current_row, empty_row, empty_row_size*sizeof(byte));

				// Group 1: Column 0
				if (play_screen[line][0]){
					for (byte i=0; i<=28; i+=8){
						current_row[i] += 0B00011110;
					}
				}

				// Group 2: Columns 1, 2, 3, 4
				if (play_screen[line][1]) {
					for (byte i=1; i<=25; i+=8){
						current_row[i] += 0B01111000;
					}
				}
				if (play_screen[line][2]) {
					for (byte i=2; i<=26; i+=8){
						current_row[i-1] += 0B00000001;
						current_row[i]   += 0B11100000;
					}
				}
				if (play_screen[line][3]) {
					for (byte i=2; i<=26; i+=8){
						current_row[i]   += 0B00000111;
						current_row[i+1] += 0B10000000;
					}
				}
				if (play_screen[line][4]) {
					for (byte i=3; i<=27; i+=8){
						current_row[i] += 0B00011110;
					}
				}

				//Group 3: Columns 5, 6, 7, 8
				if (play_screen[line][5]) {
					for (byte i=4; i<=28; i+=8){
						current_row[i] += 0B01111000;
					}
				}
				if (play_screen[line][6]) {
					for (byte i=4; i<=28; i+=8){
						current_row[i]   += 0B00000001;
						current_row[i+1] += 0B11100000;
					}
				}
				if (play_screen[line][7]) {
					for (byte i=5; i<=29; i+=8){
						current_row[i]   += 0B00000111;
						current_row[i+1] += 0B10000000;
					}
				}
				if (play_screen[line][8]) {
					for (byte i=6; i<=30; i+=8){
						current_row[i] += 0B00011110;
					}
				}

				// Group 4: Column 9
				if (play_screen[line][PLAY_COLUMNS-1]){
					for (byte i=7; i<=31; i+=8){
						current_row[i] += 0B01111000;
					}
				}

				draw(actual_line_start, actual_line_end+1,
					0, 8,
					current_row
				);

				actual_line_end -= 6;// (-3) + (-3) from the start of the for loop
			}
		}

		void updatePlayArea(byte line) {
			/** Updates a specific tetris line
			 * 
			 * "line" refers to the tetris lines, not the display's.
			 * 0 is the top line, 19 the bottom.
			 * 
			*/
			byte actual_line_end = 124 - ((PLAY_LINES-1) - line)*6;// The line of the display
			byte current_row[empty_row_size];
			byte actual_line_start = actual_line_end - 3;

			memcpy(current_row, empty_row, empty_row_size*sizeof(byte));

			// Group 1: Column 0
			if (play_screen[line][0]){
				for (byte i=0; i<=28; i+=8){
					current_row[i] += 0B00011110;
				}
			}

			// Group 2: Columns 1, 2, 3, 4
			if (play_screen[line][1]) {
				for (byte i=1; i<=25; i+=8){
					current_row[i] += 0B01111000;
				}
			}
			if (play_screen[line][2]) {
				for (byte i=2; i<=26; i+=8){
					current_row[i-1] += 0B00000001;
					current_row[i]   += 0B11100000;
				}
			}
			if (play_screen[line][3]) {
				for (byte i=2; i<=26; i+=8){
					current_row[i]   += 0B00000111;
					current_row[i+1] += 0B10000000;
				}
			}
			if (play_screen[line][4]) {
				for (byte i=3; i<=27; i+=8){
					current_row[i] += 0B00011110;
				}
			}

			//Group 3: Columns 5, 6, 7, 8
			if (play_screen[line][5]) {
				for (byte i=4; i<=28; i+=8){
					current_row[i] += 0B01111000;
				}
			}
			if (play_screen[line][6]) {
				for (byte i=4; i<=28; i+=8){
					current_row[i]   += 0B00000001;
					current_row[i+1] += 0B11100000;
				}
			}
			if (play_screen[line][7]) {
				for (byte i=5; i<=29; i+=8){
					current_row[i]   += 0B00000111;
					current_row[i+1] += 0B10000000;
				}
			}
			if (play_screen[line][8]) {
				for (byte i=6; i<=30; i+=8){
					current_row[i] += 0B00011110;
				}
			}

			// Group 4: Column 9
			if (play_screen[line][PLAY_COLUMNS-1]){
				for (byte i=7; i<=31; i+=8){
					current_row[i] += 0B01111000;
				}
			}

			draw(actual_line_start, actual_line_end+1,
				0, 8,
				current_row
			);
			
		}

		void drawPiece(byte line, byte column, graphics::blocks & piece) {
			/**
			 * Draws a piece on the screen.
			 * 
			*/

			piece.init(line, column);
			drawPlayArea(piece.A.line, piece.A.column);
			drawPlayArea(piece.B.line, piece.B.column);
			drawPlayArea(piece.C.line, piece.C.column);
			drawPlayArea(piece.D.line, piece.D.column);

		}

		void drawPieceNupdate(byte line, byte column, graphics::blocks & piece) {
			/**
			 * Draws a piece on the screen and updates only the part of
			 * the screen that is affected.
			 * 
			*/

			piece.init(line, column);
			drawPlayArea(piece.A.line, piece.A.column);
			updatePlayArea(piece.A.line);
			drawPlayArea(piece.B.line, piece.B.column);
			updatePlayArea(piece.B.line);
			drawPlayArea(piece.C.line, piece.C.column);
			updatePlayArea(piece.C.line);
			drawPlayArea(piece.D.line, piece.D.column);
			updatePlayArea(piece.D.line);

		}

		void deletePiece(byte line, byte column, graphics::blocks & piece) {
			/**
			 * Deletes a piece on the screen and updates only the part of
			 * the screen that is affected.
			 * 
			*/

			piece.init(line, column);
			drawPlayArea(piece.A.line, piece.A.column, false);
			drawPlayArea(piece.B.line, piece.B.column, false);
			drawPlayArea(piece.C.line, piece.C.column, false);
			drawPlayArea(piece.D.line, piece.D.column, false);
		}

		void deletePieceNupdate(byte line, byte column, graphics::blocks & piece) {
			/**
			 * Deletes a piece on the screen and updates only the part of
			 * the screen that is affected.
			 * 
			*/

			piece.init(line, column);
			drawPlayArea(piece.A.line, piece.A.column, false);
			updatePlayArea(piece.A.line);
			drawPlayArea(piece.B.line, piece.B.column, false);
			updatePlayArea(piece.B.line);
			drawPlayArea(piece.C.line, piece.C.column, false);
			updatePlayArea(piece.C.line);
			drawPlayArea(piece.D.line, piece.D.column, false);
			updatePlayArea(piece.D.line);
		}

		bool movePieceDown(graphics::blocks & piece) {
			/**
			 * Deletes the piece on the previous position and moves it one position down
			 * 
			 * "line" and "column" refer to the destination.
			 * It returns 'true' if the move was successful and 'false' if a collision was detected.
			 * 
			*/

			// find the lowest line of the piece
			byte lowest_point = piece.lowest().line;
			if (lowest_point == PLAY_LINES-1) {// it has reached the bottom
				return false;
			}

			if (play_screen[lowest_point+1][piece.lowest().column]) {// it has collided with another piece
				return false;
			}

			deletePiece(piece.A.line, piece.A.column, piece);
			drawPiece(piece.A.line + 1, piece.A.column, piece);
			return true;
		}

		int movePieceDownNupdate(graphics::blocks & piece) {
			/**
			 * Same as above but with built in update.
			 * 
			*/

			// find the lowest line of the piece
			byte lowest_point = piece.lowest().line;
			return lowest_point;
			if (lowest_point == PLAY_LINES-1) {// it has reached the bottom
				return 0;
			}

			/**
			 * Detect colision with another piece
			 * 
			 * Check only the pieces that are on a unique column
			 * if they have a piece under them.
			*/
			for (byte i=0; i<=3; i++) {
				if (piece.blks[i].line != lowest_point) {
					continue;
				}
				if (play_screen[piece.blks[i].line + 1][piece.blks[i].column]) {
					return 1;
				}
			}

			deletePieceNupdate(piece.A.line, piece.A.column, piece);
			drawPieceNupdate(piece.A.line + 1, piece.A.column, piece);
			return 2;
		}


};

#endif