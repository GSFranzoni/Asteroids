#include "Shot.h"
#include "Coordinate.h"
#include "Physic.h"
#include <algorithm>
#include <iostream>
#include <SFML/Audio.hpp>

using namespace std;

Shot::Shot(Coordinate c, float a)
{
    this->coordinate = c;
    this->angle = a;
}

Shot:: ~Shot()
{

}

Coordinate Shot::getCoordinate()
{
    return this->coordinate;
}

bool Shot::collision(Coordinate hitbox[4], float tx_hit, float ty_hit)
{
    float min_x = min(min(min(hitbox[0].x, hitbox[1].x), hitbox[2].x), hitbox[3].x)+tx_hit;
    float max_x = max(max(max(hitbox[0].x, hitbox[1].x), hitbox[2].x), hitbox[3].x)+tx_hit;
    float min_y = min(min(min(hitbox[0].y, hitbox[1].y), hitbox[2].y), hitbox[3].y)+ty_hit;
    float max_y = max(max(max(hitbox[0].y, hitbox[1].y), hitbox[2].y), hitbox[3].y)+ty_hit;
    if(this->coordinate.x+this->tx>=min_x && this->coordinate.x+this->tx<=max_x && this->coordinate.y+this->ty>=min_y && this->coordinate.y+this->ty<=max_y)
    {
        return true;
    }
    return false;
}

void Shot::setCoordinate(Coordinate c)
{
    this->coordinate = c;
}

float Shot::getTx()
{
    return this->tx;
}

float Shot::getTy()
{
    return this->ty;
}

void Shot::draw()
{
    glPushMatrix();
        glColor3f(1, 1, 1);
        glPointSize(2);
        glTranslatef(tx, ty, 0);
        glBegin(GL_POINTS);
            glVertex2f(this->coordinate.x, this->coordinate.y);
        glEnd();
    glPopMatrix();
}

void Shot::move()
{
    Physic::getConstantVelocity(this->tx, this->ty, this->angle, 0.75);
}

