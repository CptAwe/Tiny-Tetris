#include "buttons.cpp"
#include "graphics.cpp"
#include "staticGraphics.cpp"
#include "screen.cpp"
// #include "TetrisTheme.cpp" // Too much for an Atmega168 5v@16MHz

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

	display.drawPerimiter();

}


void loop() {
	graphics::I I_block;
	I_block.init();
	// graphics::L L_block;
	// L_block.init();

	Serial.println("made perimeter");

	// Serial.println(L_block.turnRight());
	// display.drawPieceNupdate(0, 5, L_block);

	display.drawPiece(10, 0, I_block);
	display.updatePlayArea();
	// display.drawPieceNupdate(10, 0, L_block);

	for (byte i=0; i<=3; i++) {
		Serial.print("--");
		Serial.println(*I_block.blks[i]);
	}

	Serial.println(display.movePieceDownNupdate(I_block));
	// while (display.movePieceDownNupdate(I_block)) {
	// 	delay(1000);
	// }

	Serial.println("done_filling");
	

	// display.inverse();

	Serial.println("done");
	while (true){
		// Serial.println(Dpad.states());
	}
	
}

