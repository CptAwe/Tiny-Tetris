/**
 * Handles the low level talking to the screen
 * 
 * 
*/

#ifndef GRAPHICSCPP
#define GRAPHICSCPP

#include <Arduino.h>
#include <Printable.h>

class graphics {
    public:
        class block : public Printable {
            // Each pixel of a tetris block
            public:
                byte line;
                byte column;
                void init(byte _line, byte _column) {
                    line=_line;
                    column=_column;
                }
                
                virtual size_t printTo(Print& p) const {
                    size_t r = 0;
                    r += p.print("{");
                    r += p.print(line);
                    r += p.print(", ");
                    r += p.print(column);
                    r += p.print("}");
                    return r;
                }
        };

        class blocks : public graphics::block/**, public Printable*/ {
            public:
                graphics::block A;
                graphics::block B;
                graphics::block C;
                graphics::block D;
                graphics::block *blks[4] = {&A, &B, &C, &D};
                double pivot[2] = {0, 0};

                using graphics::block::init;
                virtual void init(byte line = 0, byte column = 0);
                
                // size_t printTo(Print& p) const {
                //     size_t r = 0;
                //     for (byte i=0; i<=3; i++) {
                //         r += p.print(*blks[i]);
                //         if (i != 3) {
                //             r += p.print(", ");
                //         }
                //     }
                //     return r;
                // }

                graphics::block lowest() {
                    // returns the lowest block, thus the block with the highest line.
                    byte max_line = A.line;
                    graphics::block lowest = A;
                    for (byte i=1; i<=3; i++) {
                        graphics::block temp = *blks[i];
                        if (temp.line > max_line) {
                            lowest = temp;
                            max_line = temp.line;
                        }
                    }
                    return lowest;
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
                     * b = |   |  to according to the pivot:  b' = |        | = |    |
                     *     | y |                                   | y - yp |   | y" |
                     * 
                     * So the vector of each rotated block is:
                     *      | x |   |  cosθ sinθ |   |  x*cosθ + y*sinθ |   | x' |
                     * br = |   | * |            | = |                  | = |    |
                     *      | y |   | -sinθ cosθ |   | -x*cosθ + y*sinθ |   | y' |
                     * 
                     * And after each has been moved back to the appropriate location:
                     * 
                     *      | x' + xp |         |  x*cosθ + y*sinθ + xp |
                     * br = |         | => br = |                       | =>
                     *      | y' + yp |         | -x*cosθ + y*sinθ + yp |
                     * 
                     *      |  (x-xp)*cosθ + (y-yp)*sinθ + xp |
                     * br = |                                 |
                     *      | -(x-xp)*cosθ + (y-yp)*sinθ + yp |
                    */


                }
        };

        class I : public graphics::blocks {
            public:
                using graphics::blocks::init;
                // using graphics::blocks::pivot;
                // using graphics::blocks::blks;
                // using graphics::blocks::printTo;
                void init(byte line = 0, byte column = 0) {
                    A.init(line  , column);
                    B.init(line+1, column);
                    C.init(line+2, column);
                    D.init(line+3, column);
                    // The pivot is in the middle. It is in between two blocks
                    pivot[0] = 0;
                    pivot[1] = 0;
                }
                void turnRight() {
                    // A is the pivot. it stays unchanged throughout.
                    B.init(B.column, B.line);
                    C.init(C.column, C.line);
                    D.init(D.column, D.line);
                }
        };
        

        class L  : public graphics::blocks {
            private:
                byte turn_flag = 0;
            public:
                using graphics::blocks::printTo;
                void init(byte line = 0, byte column = 0) {
                    A.init(line  , column);
                    B.init(line+1, column);
                    C.init(line+2, column);
                    D.init(line+2, column+1);
                }
                bool turnRight() {
                    // B is the pivot. it stays unchanged throughout.
                    switch (turn_flag) {
                        case 0:// top to right
                            A.init(A.line+1, A.column+1);
                            C.init(C.line-1, C.column-1);
                            D.init(D.line,   D.column-2);
                            turn_flag++;
                            return true;
                            break;
                        case 1:// right to bottom
                            A.init(A.line+1, A.column+1);
                            C.init(C.line-1, C.column+1);
                            D.init(D.line-2, D.column);
                            turn_flag++;
                            return true;
                            break;
                        case 2:// bottom to left
                            A.init(A.line-1, A.column-1);
                            C.init(C.line+1, C.column+1);
                            D.init(D.line, D.column-2);
                            turn_flag++;
                            return true;
                            break;
                        case 3:// left to top
                            A.init(A.line-1, A.column+1);
                            C.init(C.line+1, C.column-1);
                            D.init(D.line-2, D.column);
                            turn_flag = 0;
                            return true;
                            break;
                    }
                    return false;
                }
        };

        
        

};

#endif