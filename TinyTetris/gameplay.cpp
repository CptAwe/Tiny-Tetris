/**
 * 
 * This handles the stuff that happens on the screen at a higher level.
 * 
*/

#ifndef GAMEPLAYCPP
#define GAMEPLAYCPP

#include <Arduino.h>
#include "graphics.cpp"
#include "screen.cpp"

class gameplay : public screen {
    private:

        using screen::play_screen;

        void drawPiece(graphics::blocks & piece) {
            /**
             * Draws a piece on the screen.
             * 
            */
            for (byte i=0; i<=3; i++) {
                screen::drawPlayArea(piece.blks[i]->line, piece.blks[i]->column);
            }
        }

        void deletePiece(graphics::blocks & piece) {
            /**
             * Deletes a piece on the screen and updates only the part of
             * the screen that is affected.
             * 
            */
            for (byte i=0; i<=3; i++) {
                screen::drawPlayArea(piece.blks[i]->line, piece.blks[i]->column, false);
            }
        }

        bool movePieceDown(graphics::blocks & piece) {
            /**
             * Deletes the piece on the previous position and moves it one position down
             * 
             * It returns 'true' if the move was successful and 'false' if a collision was detected.
             * 
            */

            // find the lowest line of the piece
            byte lowest_point = piece.lowest().line;
            if (lowest_point == screen::PLAY_LINES-1) {// it has reached the bottom
                return false;
            }

            /**
             * Detect colision with another piece
             * 
             * Check only the pieces that are on a unique column
             * if they have a piece under them.
            */
            for (byte i=0; i<=3; i++) {
                graphics::block temp = piece.blks[i]->clone();
                if (temp.line != lowest_point) {
                    continue;
                }
                if (screen::play_screen[temp.line + 1][temp.column]) {
                    return false;
                }
            }

            deletePiece(piece);
            piece.moveDown();
            drawPiece(piece);
            return true;
        }

    public:
        using screen::clear;
        using screen::drawTitleScreen;
        using screen::drawPerimiter;

        void init() {
            screen::init();
            screen::clear();
        }


        bool itFits(graphics::blocks & piece) {
            /**
             * Checks if the piece actually fits.
             * It checks if the coordinates of each block are
             * already occupied in the screen::play_screen
             * 
            */
            for (byte i=0; i<=3; i++) {
                // Is it on the screen? (too high coordinates)
                if (piece.blks[i]->line >= PLAY_LINES || piece.blks[i]->column >= PLAY_COLUMNS) {
                    return false;
                }
                // Is it on the screen? (too low coordinates)
                if (piece.blks[i]->line < 0 || piece.blks[i]->column < 0) {
                    return false;
                }
                // It is on the screen, but does it fit?
                if (screen::play_screen[piece.blks[i]->line][piece.blks[i]->line]) {
                    return false;
                }
            }
            return true;
        }

        bool drawPieceNupdate(graphics::blocks & piece) {
            /**
             * Draws a piece on the screen and updates only the part of
             * the screen that is affected.
             * 
            */
            if (itFits(piece)){
                for (byte i=0; i<=3; i++) {
                    screen::drawPlayArea(piece.blks[i]->line, piece.blks[i]->column);
                    screen::updatePlayArea(piece.blks[i]->line);
                }
                return true;
            }
            return false;
        }

        bool deletePieceNupdate(graphics::blocks & piece) {
            /**
             * Deletes a piece on the screen and updates only the part of
             * the screen that is affected.
             * 
            */
            if (itFits(piece)){
                for (byte i=0; i<=3; i++) {
                    screen::drawPlayArea(piece.blks[i]->line, piece.blks[i]->column, false);
                    screen::updatePlayArea(piece.blks[i]->line);
                }
                return true;
            }
            return false;
        }

        int movePieceDownNupdate(graphics::blocks & piece) {
            /**
             * Moves the piece (if it can) one line down and updates the part of the
             * screen that is affected.
             * 
            */

            // find the lowest line of the piece
            byte lowest_point = piece.lowest().line;
            if (lowest_point == screen::PLAY_LINES-1) {// it has reached the bottom
                return false;
            }

            /**
             * Detect colision with another piece
             * 
             * Check only the pieces that are on a unique column
             * if they have a piece under them.
            */
            for (byte i=0; i<=3; i++) {
                graphics::block *temp = piece.blks[i];
                if (temp->line != lowest_point) {
                    continue;
                }
                if (screen::play_screen[temp->line + 1][temp->column]) {
                    return false;
                }
            }

            deletePieceNupdate(piece);
            piece.moveDown();
            drawPieceNupdate(piece);
            return true;
        }

        bool turnPieceNupdate(graphics::blocks & piece) {
            /**
             * Checks if the piece can be turned 90 degrees to the right. If it can't, it
             * tries to turn it 90 degrees more. It checks 3 times in total. If all fail
             * it doesn't turn it.
             * 
            */

            graphics::block A;
            A.init(6,6);
            Serial.println(A);
            graphics::block B;
            B = A.clone();
            B.init(0, 0);
            Serial.println(A);
            Serial.println(B);
            
            // Serial.println("Original: ");
            // for (byte i=0; i<=3; i++) {
            //     Serial.println(*piece.blks[i]);
            // }

            // graphics::blocks *temp = piece.clone();
            // Serial.println("Copied: ");
            // for (byte i=0; i<=3; i++) {
            //     Serial.println(temp->B);
            // }

            // temp->turnRight();
            // Serial.println("Rotate Copy: ");
            // for (byte i=0; i<=3; i++) {
            //     Serial.println(temp->blks[i]->line);
            // }
            // Serial.println("Original: ");
            // for (byte i=0; i<=3; i++) {
            //     Serial.println(*piece.blks[i]);
            // }

            // piece = *temp->clone();
            // Serial.println("Original After Overwrite: ");
            // for (byte i=0; i<=3; i++) {
            //     Serial.println(*piece.blks[i]);
            // }

            return false;
            // for (byte times=0; times<=2; times++) {
            //     temp.turnRight();
            //     if (itFits(temp)) {
            //         Serial.print("Tries: ");
            //         Serial.println(times);
            //         break;
            //     } else {
            //         return false;
            //     }
            // }

            // Serial.print("Original: ");
            // Serial.println(*piece.blks[1]);
            // deletePieceNupdate(piece);
            
            // piece = temp;
            
            // drawPieceNupdate(piece);
            // Serial.print("Rotated: ");
            // Serial.println(*piece.blks[1]);
            
            // return true;
        }
};

#endif