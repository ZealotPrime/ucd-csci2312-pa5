#include "Food.h"

namespace Gaming
{
    Food::FOOD_ID = 'F';

    void Food::print(std::ostream &os) const
    {
        os<<FOOD_ID<<__id;
    }
}