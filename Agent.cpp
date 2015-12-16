#include "Agent.h"
namespace Gaming
{
    Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy):Piece(g,p)
    {
        __energy=energy;
    }

    void Agent::age()
    {
        __energy-=AGENT_FATIGUE_RATE;
    }

    Piece &Agent::operator*(Piece &other)
    {
        return other.interact(this);
    }

    Piece &Agent::interact(Agent *other)
    {
        if(this->__energy==other->__energy)
        {
            finish();
            other->finish();
            return *this;
        }
        if(this->__energy>other->__energy)
        {
            other->finish();
            __energy-=other->__energy;
            return *this;
        }
        finish();
        other->__energy-=__energy;
        return *other;
    }

    Piece &Agent::interact(Resource *resource)
    {
        __energy+=resource->consume();
        return *this;
    }
}