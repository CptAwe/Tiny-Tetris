#include "buttons.cpp"
#include "title.cpp"
#include "blocks.cpp"
#include "screen.cpp"
// #include "TetrisTheme.cpp" // Too much for an Atmega168 5v@16MHz

// [GeoPap] The new display manager
screen display;

// pins for buttons
#define KEY_LEFT_pin    11
#define KEY_RIGHT_pin   12
#define KEY_DOWN_pin    10
#define KEY_ROTATE_pin  A0

const int button_pins[] = {
	KEY_LEFT_pin, KEY_RIGHT_pin, KEY_DOWN_pin, KEY_ROTATE_pin
};
buttons Dpad(button_pins);

#define KEY_LEFT    2
#define KEY_RIGHT   4
#define KEY_DOWN    8
#define KEY_ROTATE  16

// misc pins
// #define PIEZO_PIN   3
// #define LED_PIN     13
// #define KEYPAD_PIN  A0

void setup() {
	Serial.begin(9600);

	// pinMode(PIEZO_PIN, OUTPUT);
	// pinMode(LED_PIN, OUTPUT);
	display.init();
	randomSeed(analogRead(A1)); /// To do: create a decent random number generator.

}


void loop() {
	// for (int i=0; i<=10; i++){
	// 	Serial.println(blocks::random_piece()[0], BIN);
	// }

	Serial.println(title::welcomeScreen[0][0], BIN);
	byte row = 13;
	byte col = 2;
	byte arr[13][2] = {
		{0B01111110, 0B01111110},
		{0B01100110, 0B01100110},
		{0B01100110, 0B01100110},
		{0B01100110, 0B01100110},
		{0B01100000, 0B01100110},
		{0B01100000, 0B01100110},
		{0B01100000, 0B01100110},
		{0B01100110, 0B01100110},
		{0B01100110, 0B01100110},
		{0B01100110, 0B01100110},
		{0B01100110, 0B01100110},
		{0B01100110, 0B01100110},
		{0B01100110, 0B01111110},
	};

	// display.entire_display_on();
	// display.show_gddram_contents();

	display.clear();
	display.draw(0, col, 0, row, arr);
	// display.inverse();

	while (true){}
	
}

