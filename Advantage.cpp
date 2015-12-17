#include "Advantage.h"
namespace Gaming
{
    const char Advantage::ADVANTAGE_ID = 'D';
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

    void Advantage::print(std::ostream &os) const
    {
        os<<ADVANTAGE_ID<<__id;
    }

    double Advantage::consume()
    {
        finish();
        return __capacity*ADVANTAGE_MULT_FACTOR;
    }
}