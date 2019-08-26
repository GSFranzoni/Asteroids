#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include <windows.h>
#include <GL/glut.h>
#include "Coordinate.h"
#include "Physic.h"

class Asteroid
{
private:
    Coordinate coordinates[8];
    float angle, tx, ty, size;
public:
    Asteroid(float, float, float);
    ~Asteroid();
    Coordinate hitbox[4];
    float getSize();
    float getTx();
    void setTx(float);
    float getTy();
    void setTy(float);
    void draw();
    void move();
};

#endif
