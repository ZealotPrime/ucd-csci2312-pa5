#include "Gaming.h"

namespace Gaming
{

    ActionType Surroundings::getMove(PieceType objective)const
    {
        std::vector<int> targets;
        bool special=false;
        int count=1;
        if(objective==RESOURCE||objective==AGENT)
        {
            special=true;
            count=2;
        }
        for(int y=0;y<count;++y)
        {
            if(special)
                objective=(PieceType) (((int)objective)+1) ;
            for(int x=0;x<9;++x)
            {
                if(array[x]==objective)
                {
                    targets.push_back(x);
                }
            }
        }
        if(!targets.empty())
        {
            Position destination=PositionRandomizer()(targets);
            return static_cast<ActionType>(destination.x+destination.y*3);
        }
        return STAY;
    }

}