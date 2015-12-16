#include "Strategic.h"
#include "AggressiveAgentStrategy.h"

namespace Gaming
{
    Strategic::STRATEGIC_ID = 'T';

    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s):Agent(g,p,energy)
    {
        __strategy=s;
    }

    Strategic::~Strategic()
    {
        delete __strategy;
    }

    void Strategic::print(std::ostream &os) const
    {
        os<<STRATEGIC_ID<<__id;
    }

    ActionType Strategic::takeTurn(const Surroundings &s) const
    {
        AggressiveAgentStrategy*aggro = dynamic_cast<AggressiveAgentStrategy*>(__strategy);
        if(aggro)
            aggro->setEnergy(__energy);
        return __strategy->operator()(s);
    }
}