#include "buttons.cpp"
#include "graphics.cpp"
#include "blocks.cpp"
#include "screen.cpp"
// #include "TetrisTheme.cpp" // Too much for an Atmega168 5v@16MHz

// [GeoPap] The new display manager
screen display;
graphics::titleScreen title_screen;

// pins for buttons
#define KEY_LEFT_pin    11
#define KEY_RIGHT_pin   12
#define KEY_DOWN_pin    10
#define KEY_ROTATE_pin  A0

const byte button_pins[4] = {
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
	display.clear();

	randomSeed(analogRead(A1));

}


void loop() {

	display.draw(
		0, title_screen.x,
		0, title_screen.y,
		title_screen.graph(),
		true
	);


	while (true){}
	
}

