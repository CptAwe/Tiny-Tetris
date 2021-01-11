#include "buttons.cpp"
#include "graphics.cpp"
#include "gameplay.cpp"
// #include "TetrisTheme.cpp" // Too much for an Atmega168 5v@16MHz

gameplay game;

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


graphics::I I_block;
graphics::L L_block;

void setup() {
	Serial.begin(9600);

	randomSeed(analogRead(A1));

	game.init();
	game.drawTitleScreen();

	delay(2000);

	game.clear();

	game.drawPerimiter();

}


void loop() {
	I_block.init(0, 2);
	L_block.init(10, 0);

	Serial.println("Everythin ready");

	game.drawPieceNupdate(I_block);
	Serial.println(game.drawPieceNupdate(L_block));

	
	delay(2000);

	while (game.turnPieceNupdate(I_block)) {
		delay(1000);
		// game.turnPieceNupdate(I_block);
		// delay(1000);
	}
	
	

	// display.inverse();

	Serial.println("Done");
	while (true){
		// Serial.println(Dpad.states());
	}
	
}

