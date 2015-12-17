#include "Simple.h"

namespace Gaming
{
    const char Simple::SIMPLE_ID = 'S';


    void Simple::print(std::ostream &os) const
    {
        os<<SIMPLE_ID<<__id;
    }

    ActionType Simple::takeTurn(const Surroundings &surroundings) const
    {
        ActionType move=surroundings.getMove(RESOURCE);
        if(move!=STAY)
            return move;
        move=surroundings.getMove(EMPTY);
        return move;
    }
}