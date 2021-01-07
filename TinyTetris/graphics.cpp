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
        class block {
            // Each pixel of a tetris block
            public:
                byte line;
                byte column;
                void set(byte _line, byte _column) {
                    line=_line;
                    column=_column;
                }
        };
        class blocks : public graphics::block{
            public:
                graphics::block A;
                graphics::block B;
                graphics::block C;
                graphics::block D;
        };

        class I : public graphics::blocks {
            private:
                graphics::blocks _I;
            public:
                void init(byte line = 0, byte column = 0) {
                    _I.A.set(line  , column);
                    _I.B.set(line+1, column);
                    _I.A.set(line+2, column);
                    _I.A.set(line+3, column);
                }
                void turnRight() {
                    // A is the pivot. it stays unchanged throughout.
                    _I.B.set(_I.B.column, _I.B.line);
                    _I.C.set(_I.C.column, _I.C.line);
                    _I.D.set(_I.D.column, _I.D.line);
                }
        };

        class L  : public graphics::blocks {
            private:
                graphics::blocks _L;
                byte turn_flag = 0;
            public:
                void init(byte line = 0, byte column = 0) {
                    _L.A.set(line  , column);
                    _L.B.set(line+1, column);
                    _L.A.set(line+2, column);
                    _L.A.set(line+2, column+1);
                }
                void turnRight() {
                    // B is the pivot. it stays unchanged throughout.
                    switch (turn_flag) {
                        case 0:// top to right
                            _L.A.set(_L.A.line+1, _L.A.column+1);
                            _L.C.set(_L.C.line-1, _L.C.column-1);
                            _L.D.set(_L.D.line,   _L.D.column-2);
                            turn_flag++;
                            break;
                        case 1:// right to bottom
                            _L.A.set(_L.A.line+1, _L.A.column+1);
                            _L.C.set(_L.C.line-1, _L.C.column+1);
                            _L.D.set(_L.D.line-2, _L.D.column);
                            turn_flag++;
                            break;
                        case 2:// bottom to left
                            _L.A.set(_L.A.line-1, _L.A.column-1);
                            _L.C.set(_L.C.line+1, _L.C.column+1);
                            _L.D.set(_L.D.line, _L.D.column-2);
                            turn_flag++;
                            break;
                        case 3:// left to top
                            _L.A.set(_L.A.line-1, _L.A.column+1);
                            _L.C.set(_L.C.line+1, _L.C.column-1);
                            _L.D.set(_L.D.line-2, _L.D.column);
                            turn_flag = 0;
                            break;
                    }
                }
        };
        

};

#endif