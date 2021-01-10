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

    public:
        void init() {
            screen::init();
            screen::clear();
        }

        using screen::clear;
        using screen::drawTitleScreen;
        using screen::drawPerimiter;

        // void clearScreen() {
        //     screen::clear();
        // }

        void drawPiece(byte line, byte column, graphics::blocks & piece) {
            /**
             * Draws a piece on the screen.
             * 
            */

            piece.init(line, column);
            screen::drawPlayArea(piece.A.line, piece.A.column);
            screen::drawPlayArea(piece.B.line, piece.B.column);
            screen::drawPlayArea(piece.C.line, piece.C.column);
            screen::drawPlayArea(piece.D.line, piece.D.column);

        }

        void drawPieceNupdate(byte line, byte column, graphics::blocks & piece) {
            /**
             * Draws a piece on the screen and updates only the part of
             * the screen that is affected.
             * 
            */

            piece.init(line, column);
            screen::drawPlayArea(piece.A.line, piece.A.column);
            screen::updatePlayArea(piece.A.line);
            screen::drawPlayArea(piece.B.line, piece.B.column);
            screen::updatePlayArea(piece.B.line);
            screen::drawPlayArea(piece.C.line, piece.C.column);
            screen::updatePlayArea(piece.C.line);
            screen::drawPlayArea(piece.D.line, piece.D.column);
            screen::updatePlayArea(piece.D.line);

        }

        void deletePiece(byte line, byte column, graphics::blocks & piece) {
            /**
             * Deletes a piece on the screen and updates only the part of
             * the screen that is affected.
             * 
            */

            piece.init(line, column);
            screen::drawPlayArea(piece.A.line, piece.A.column, false);
            screen::drawPlayArea(piece.B.line, piece.B.column, false);
            screen::drawPlayArea(piece.C.line, piece.C.column, false);
            screen::drawPlayArea(piece.D.line, piece.D.column, false);
        }

        void deletePieceNupdate(byte line, byte column, graphics::blocks & piece) {
            /**
             * Deletes a piece on the screen and updates only the part of
             * the screen that is affected.
             * 
            */

            piece.init(line, column);
            screen::drawPlayArea(piece.A.line, piece.A.column, false);
            screen::updatePlayArea(piece.A.line);
            screen::drawPlayArea(piece.B.line, piece.B.column, false);
            screen::updatePlayArea(piece.B.line);
            screen::drawPlayArea(piece.C.line, piece.C.column, false);
            screen::updatePlayArea(piece.C.line);
            screen::drawPlayArea(piece.D.line, piece.D.column, false);
            screen::updatePlayArea(piece.D.line);
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
                graphics::block temp = *piece.blks[i];
                if (temp.line != lowest_point) {
                    continue;
                }
                if (screen::play_screen[temp.line + 1][temp.column]) {
                    return false;
                }
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
                graphics::block temp = *piece.blks[i];
                if (temp.line != lowest_point) {
                    continue;
                }
                if (screen::play_screen[temp.line + 1][temp.column]) {
                    return false;
                }
            }

            deletePieceNupdate(piece.A.line, piece.A.column, piece);
            drawPieceNupdate(piece.A.line + 1, piece.A.column, piece);
            return true;
        }
};

#endif