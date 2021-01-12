/**
 * Classes that describe the tetris pieces
 * 
 * 
 * 
 * 
 * Very informative read about cloning objects:
 *    https://agiledeveloper.com/articles/cloning072002.htm
*/

#ifndef GRAPHICSCPP
#define GRAPHICSCPP

#include <Arduino.h>
#include <Printable.h>

class graphics {
    public:
        class block {
            // Each pixel of a tetris block
            protected:
                block(const graphics::block & another) {
                    column = another.column;
                    line = another.line;
                }
            
            public:
            
                byte line;
                byte column;
                block(){}

                void init(byte _line, byte _column) {
                    line=_line;
                    column=_column;
                }

                graphics::block clone() const{
                    return graphics::block(*this);
                }
                
                void print() {
                    // Prints to Serial
                    Serial.print("{");
                    Serial.print(line);
                    Serial.print(", ");
                    Serial.print(column);
                    Serial.println("}");
                }
        };

        class blocks : public graphics::block {
            protected:
                blocks(const graphics::blocks & another) {
                    this->A = another.A.clone();
                    this->B = another.B.clone();
                    this->C = another.C.clone();
                    this->D = another.D.clone();

                    this->blks[0] = &this->A;
                    this->blks[1] = &this->B;
                    this->blks[2] = &this->C;
                    this->blks[3] = &this->D;

                    this->pivot[0] = another.pivot[0];
                    this->pivot[1] = another.pivot[1];
                }
            public:
                graphics::block A;
                graphics::block B;
                graphics::block C;
                graphics::block D;
                graphics::block *blks[4] = {&A, &B, &C, &D};
                double pivot[2];

                blocks(){}

                graphics::blocks clone() const {
                    /**
                     * Creates returns a copy of the blocks
                     * 
                    */
                   return graphics::blocks(*this);
                }

                graphics::block *lowest() {
                    /**
                     * Returns the lowest block, thus the block with the highest line.
                    */
                    byte max_line = A.line;
                    graphics::block * lowest;
                    for (byte i=1; i<=3; i++) {
                        if (this->blks[i]->line > max_line) {
                            lowest = this->blks[i];
                            max_line = this->blks[i]->line;
                        }
                    }
                    return lowest;
                }

                void moveDown() {
                    /**
                     * Moves the piece one line down,
                     * including the pivot.
                     * 
                    */
                    for (byte i=0; i<=3; i++) {
                        blks[i]->line++;
                    }
                    pivot[0]++;
                }

                void turnRight() {
                    /**
                     * Rotates the pieces around each pivot
                     * The rotation is done according to the rotation matrix:
                     *     |  cosθ sinθ |         (clockwise)
                     * R = |            |         (θ is in radians)
                     *     | -sinθ cosθ |
                     * 
                     * which is multiplied by the matrix of each block vector:
                     *     | x |  after each has been moved        | x - xp |   | x" |
                     * b = |   |  to put the pivot as the  :  b' = |        | = |    |
                     *     | y |  origin                           | y - yp |   | y" |
                     * 
                     * So the vector of each rotated block is:
                     *      | x" |   |  cosθ sinθ |   |  x"*cosθ + y"*sinθ |   | x' |
                     * br = |    | * |            | = |                    | = |    |
                     *      | y" |   | -sinθ cosθ |   | -x"*sinθ + y"*cosθ |   | y' |
                     * 
                     * And after each has been moved back to the appropriate location:
                     * 
                     *      | x' + xp |         |  x*cosθ + y*sinθ + xp |
                     * br = |         | => br = |                       | =>
                     *      | y' + yp |         | -x*sinθ + y*cosθ + yp |
                     * 
                     *      |  (x-xp)*cosθ + (y-yp)*sinθ + xp |
                     * br = |                                 |
                     *      | -(x-xp)*sinθ + (y-yp)*cosθ + yp |
                     * 
                     * For 90 degrees:
                     *      |  y - yp + xp |
                     * br = |              |
                     *      | -x + xp + yp |
                    */
                    for (byte i=0; i<=3; i++) {
                        byte previous_line = this->blks[i]->line;
                        byte previous_col = this->blks[i]->column;
                        this->blks[i]->line   = (previous_col - this->pivot[1]) + this->pivot[0];
                        this->blks[i]->column = (-previous_line + this->pivot[0]) + this->pivot[1];
                    }
                }

                void print() {
                    // Prints to Serial
                    for (byte i=0; i<=3; i++) {
                        blks[i]->print();
                    }
                
                }
                // graphics::blocks virtuallyTurnRight(byte times = 1) {
                //     /**
                //      * It turns the turned piece without actually turning it.
                //      * "times" dictates how many times to apply the turning.
                //      * 
                //     */
                //     graphics::blocks turned;
                //     for (byte i=0; i <= times; i++) {
                //         turned.turnRight();
                //     }
                //     return turned;
                // }

        };

        class I : public graphics::blocks {
            public:
                using graphics::blocks::init;
                using graphics::blocks::turnRight;
                
                void init(byte line = 0, byte column = 0) {
                    A.init(line  , column);
                    B.init(line+1, column);
                    C.init(line+2, column);
                    D.init(line+3, column);
                    /**
                     *  The pivot is in between two blocks
                     *  _______   _______   _______   _______
                     * |  A    | |       | |    D  | |       |
                     * |  B.   | |D C.B A| |   .C  | |A B.C D|
                     * |  C    | |       | |    B  | |       |
                     * |  D    | |       | |    A  | |       |
                     *  ‾‾‾‾‾‾‾   ‾‾‾‾‾‾‾   ‾‾‾‾‾‾‾   ‾‾‾‾‾‾‾
                     * it is always on { A.line + 1.5 , A.column + 1.5}
                    */
                    pivot[0] = line + 1.5;
                    pivot[1] = column + 1.5;
                }
        };
        

        class L  : public graphics::blocks {
            public:
                // using graphics::blocks::printTo;
                void init(byte line = 0, byte column = 0) {
                    A.init(line  , column);
                    B.init(line+1, column);
                    C.init(line+2, column);
                    D.init(line+2, column+1);
                    /**
                     *  The pivot is block B
                     *  _______   _______   _______   _______
                     * |  A    | |       | |D C    | |    D  |
                     * |  B    | |C B A  | |  B    | |A B C  |
                     * |  C D  | |D      | |  A    | |       |
                     * |       | |       | |       | |       |
                     *  ‾‾‾‾‾‾‾   ‾‾‾‾‾‾‾   ‾‾‾‾‾‾‾   ‾‾‾‾‾‾‾
                    */
                    pivot[0] = B.line;
                    pivot[1] = B.column;
                }
        };

        
        

};

#endif