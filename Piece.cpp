#include "Piece.h"

namespace Gaming
{

    Piece::Piece(const Game &g, const Position &p):__game(g)
    {
        __id=__idGen++;
        __finished=false;
        __turned= false;
        __position=p;
    }

    std::ostream &Gaming::operator<<(std::ostream &os, const Piece &piece)
    {
        piece.print(os);
    }
}