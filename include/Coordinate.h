#ifndef COORDINATE_H_INCLUDED
#define COORDINATE_H_INCLUDED

struct Coordinate
{
    float x, y;
    Coordinate(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
    Coordinate(){}
};

#endif
