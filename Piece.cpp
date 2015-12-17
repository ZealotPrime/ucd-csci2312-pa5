#include "Piece.h"

namespace Gaming
{
    unsigned int Piece::__idGen=0;
    Piece::Piece(const Game &g, const Position &p):__game(g)
    {
        __id=newId();
        __finished=false;
        __turned= false;
        __position=p;
    }

    std::ostream &operator<<(std::ostream &os, const Piece &piece)
    {
        piece.print(os);
        return os;
    }

    unsigned int Piece::newId()
    {
        return __idGen++;
    }
}