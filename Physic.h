#ifndef PHYSIC_H_INCLUDED
#define PHYSIC_H_INCLUDED

#include <ctime>

class Physic
{
private:
    float friction, velocity_x, velocity_y, max_velocity, acceleration;
public:
    Physic(float, float, float);
    ~Physic();
    void getVelocity(float&, float&);
    static void getConstantVelocity(float&, float&, float, float);
    float getAcceleration();
    void accelerate(float);
};

#endif
