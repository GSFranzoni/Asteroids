#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED

#include <windows.h>
#include <GL/glut.h>
#include <vector>
#include "Shot.h"
#include "Coordinate.h"
#include "Utilities.h"
#include "Physic.h"
#include "Timer.h"
#include "Sound.h"

using namespace std;

class Ship
{
private:
    Timer* time_shots;
    Coordinate coordinates_object[4];
    Coordinate coordinates_boost[4];
    vector<Shot*> shots;
    Physic* physic;
    float angle, tx, ty;
    int life, score;
    Sound* fire_sound, *boost_sound;
public:
    Ship(int, int);
    ~Ship();
    Coordinate hitbox[4];
    float getVelocity();
    void setVelocity(float);
    float getTx();
    void setTx(float);
    float getTy();
    void setTy(float);
    float getAngle();
    void setAngle(float);
    void draw(bool);
    void fire();
    void boost();
    void move();
    void rotate(float);
    void hyperspace();
    void shot_out();
    int getLife();
    int getScore();
    void setLife(int);
    void setScore(int);
    vector<Shot*> &getShots();
    bool collision(Coordinate[4], float, float);
};

#endif
