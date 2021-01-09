/**
 * 
 * 
 * 
*/

#ifndef GRAPHICSCPP
#define GRAPHICSCPP

#include <Arduino.h>

class graphics {
    public:
        class block : public Printable{
            // Each pixel of a tetris block
            public:
                byte line;
                byte column;
                void init(byte _line, byte _column) {
                    line=_line;
                    column=_column;
                }
                size_t printTo(Print& p) const {
                    size_t r = 0;
                    r += p.print("{");
                    r += p.print(line);
                    r += p.print(", ");
                    r += p.print(column);
                    r += p.print("}");
                    return r;
                }
        };

        class blocks : public graphics::block {
            public:
                graphics::block A;
                graphics::block B;
                graphics::block C;
                graphics::block D;
                graphics::block *blks[4] = {&A, &B, &C, &D};

                using graphics::block::init;
                virtual void init(byte line = 0, byte column = 0) {
                };

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
        };

        class I : public graphics::blocks {
            public:
                using graphics::blocks::init;
                using graphics::blocks::blks;
                void init(byte line = 0, byte column = 0) {
                    A.init(line  , column);
                    B.init(line+1, column);
                    C.init(line+2, column);
                    D.init(line+3, column);
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