#ifndef SHOT_H_INCLUDED
#define SHOT_H_INCLUDED

#include <windows.h>
#include <GL/glut.h>

#include "Coordinate.h"
#include "Utilities.h"
#include "Sound.h"

class Physic;

class Shot
{
private:
    Coordinate coordinate;
    float angle, tx, ty;
public:
    Shot(Coordinate, float);
    ~Shot();
    float getTx();
    float getTy();
    void draw();
    void setCoordinate(Coordinate);
    Coordinate getCoordinate();
    void move();
    bool collision(Coordinate[4], float, float);
};

#endif
