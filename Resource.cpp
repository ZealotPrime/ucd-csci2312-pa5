#include "Resource.h"
#include "Agent.h"

namespace Gaming
{
    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Game &g, const Position &p, double capacity):Piece(g,p)
    {
        __capacity=capacity;
    }

    double Resource::consume()
    {
        finish();
        return getCapacity();
    }

    void Resource::age()
    {
        __capacity-=RESOURCE_SPOIL_FACTOR;
    }

    Piece &Resource::operator*(Piece &other)
    {
        return other.interact(this);
    }


    Piece &Resource::interact(Agent *agent)
    {
        agent->addEnergy(consume());
        return *agent;
    }
}