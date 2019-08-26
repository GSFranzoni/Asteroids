#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED

#include <windows.h>
#include <GL/glut.h>

#include <vector>
#include "Coordinate.h"
#include "Physic.h"
#include "Boss.h"
#include "Shot.h"
#include "Timer.h"
#include "Sound.h"

using namespace std;

class Boss
{
private:
    Coordinate coordinates[8];
    vector<Shot*> shots;
    float angle, tx, ty, size;
    Sound* fire_sound;
public:
    Boss();
    ~Boss();
    Coordinate hitbox[4];
    float getSize();
    float getTx();
    void setTx(float);
    float getTy();
    void setTy(float);
    void draw();
    void move();
    void rotate(float);
    void fire();
    void shot_out();
    vector<Shot*> &getShots();
    bool collision(Coordinate[4], float, float);
};

#endif
