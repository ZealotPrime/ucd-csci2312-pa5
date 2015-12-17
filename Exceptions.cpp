#include <ostream>
#include "Exceptions.h"
namespace Gaming
{


    std::ostream &operator<<(std::ostream &os, const GamingException &ex)
    {
        ex.__print_args(os);
        return os;
    }

    DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height)
    {
        __exp_width=expWidth;
        __exp_height=expHeight;
        __width=width;
        __height=height;
    }

    void InsufficientDimensionsEx::__print_args(std::ostream &os) const
    {
        os<<"Insufficent dimension exception!"<<std::endl;
        os<<"Minimum width "<<__exp_width<<" called width "<<__width<<std::endl;
        os<<"Minimum height "<<__exp_height<<" called height "<<__height<<std::endl;
    }

    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width, unsigned height):DimensionEx(minWidth,minHeight,width,height)
    {
        __print_args(std::cout);
    }

    OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height):DimensionEx(maxWidth,maxHeight,width,height)
    {
        __print_args(std::cout);
    }

    void OutOfBoundsEx::__print_args(std::ostream &os) const
    {
        os<<"Out of bounds exception!"<<std::endl;
        os<<"Maximum width "<<__exp_width<<" called width "<<__width<<std::endl;
        os<<"Maximum height "<<__exp_height<<" called height "<<__height<<std::endl;
    }
}