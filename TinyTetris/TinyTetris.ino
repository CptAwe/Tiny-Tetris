#include "buttons.cpp"
#include "graphics.cpp"
#include "blocks.cpp"
#include "screen.cpp"
// #include "TetrisTheme.cpp" // Too much for an Atmega168 5v@16MHz

// [GeoPap] The new display manager
screen display;
graphics::titleScreen title_screen;
graphics::blocks::I I_block;
graphics::blocks::J J_block;
graphics::blocks::L L_block;

// pins for buttons
#define KEY_LEFT_pin    6
#define KEY_RIGHT_pin   7
#define KEY_DOWN_pin    8
#define KEY_ROTATE_pin  9

const byte button_pins[4] = {
	KEY_LEFT_pin, KEY_RIGHT_pin, KEY_DOWN_pin, KEY_ROTATE_pin
};
buttons Dpad(button_pins);

#define KEY_LEFT    8
#define KEY_RIGHT   1
#define KEY_DOWN    4
#define KEY_ROTATE  2

// misc pins
// #define PIEZO_PIN   3
// #define LED_PIN     13
// #define KEYPAD_PIN  A0

void setup() {
	Serial.begin(9600);

	// pinMode(PIEZO_PIN, OUTPUT);
	// pinMode(LED_PIN, OUTPUT);
	display.init();
	display.clear();

	randomSeed(analogRead(A1));

}


void loop() {

	display.draw(
		0,
		0,
		1
	);
	

	// display.inverse();


	while (true){
		// Serial.println(Dpad.states());
	}
	
}

