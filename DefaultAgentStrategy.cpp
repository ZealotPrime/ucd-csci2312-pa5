#include "DefaultAgentStrategy.h"
namespace Gaming
{
    ActionType DefaultAgentStrategy::operator()(const Surroundings &surroundings) const
    {
        ActionType move = surroundings.getMove(ADVANTAGE);
        if (move != STAY)
            return move;
        move = surroundings.getMove(FOOD);
        if (move != STAY)
            return move;
        move = surroundings.getMove(EMPTY);
        if (move != STAY)
            return move;
        move = surroundings.getMove(SIMPLE);
        return move;
    }
}