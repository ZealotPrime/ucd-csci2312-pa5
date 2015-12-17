#include "Food.h"

namespace Gaming
{
    const char Food::FOOD_ID = 'F';

    void Food::print(std::ostream &os) const
    {
        os<<FOOD_ID<<__id;
    }

    double Food::consume()
    {
        finish();
        return __capacity;
    }
}