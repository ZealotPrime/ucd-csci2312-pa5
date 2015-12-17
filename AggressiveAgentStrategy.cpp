#include "AggressiveAgentStrategy.h"
#include "Game.h"

namespace Gaming
{
    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

    AggressiveAgentStrategy::AggressiveAgentStrategy()
    {
        __agentEnergy=Game::STARTING_AGENT_ENERGY;
    }

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy)
    {
        __agentEnergy=agentEnergy;
    }

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &surroundings) const
    {
        if(__agentEnergy>DEFAULT_AGGRESSION_THRESHOLD)
        {
            ActionType move = surroundings.getMove(AGENT);
            if(move!=STAY)
                return move;
        }
        ActionType move = surroundings.getMove(ADVANTAGE);
        if(move!=STAY)
            return move;
        move = surroundings.getMove(FOOD);
        if(move!=STAY)
            return move;
        move=surroundings.getMove(EMPTY);
        return move;
    }
}