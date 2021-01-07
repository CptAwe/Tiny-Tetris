#include "buttons.cpp"
#include "graphics.cpp"
#include "staticGraphics.cpp"
#include "screen.cpp"
// #include "TetrisTheme.cpp" // Too much for an Atmega168 5v@16MHz

// [GeoPap] The new display manager
screen display;
staticGraphics::titleScreen title_screen;

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

	display.draw(
		0, title_screen.x,
		0, title_screen.y,
		title_screen.graph(),
		true
	);

	delay(2000);

	display.clear();

}


void loop() {
	// graphics::TetrisBlocks::I I_block;
	

	// display.draw(
	// 	0,
	// 	0,
	// 	1
	// );

	display.drawPerimiter();
	Serial.println("made perimeter");

	// for (byte i=0; i<20; i++) {
	// 	for (byte j=0; j<10; i++) {
	// 		display.drawPlayArea(i,j);
	// 	}
	// }

	// for (byte i=0; i<=19; i++){
	// 	display.drawPlayArea(i, 0);
	// 	display.drawPlayArea(i, 1);
	// 	display.drawPlayArea(i, 2);
	// 	display.drawPlayArea(i, 3);
	// 	display.drawPlayArea(i, 4);
	// 	display.drawPlayArea(i, 5);
	// 	display.drawPlayArea(i, 6);
	// 	display.drawPlayArea(i, 7);
	// 	display.drawPlayArea(i, 8);
	// 	display.drawPlayArea(i, 9);
	// 	display.updatePlayArea(i);
	// }


	// display.drawPlayArea(19, 9);
	// display.drawPiece(0, 0, I_block);

	Serial.println("done_filling");
	

	// display.inverse();

	Serial.println("done");
	while (true){
		// Serial.println(Dpad.states());
	}
	
}

