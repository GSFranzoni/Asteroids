#include "Ship.h"
#include "Shot.h"
#include "Physic.h"
#include <math.h>
#include <windows.h>
#include <iostream>

using namespace std;

Ship::Ship(int life, int score)
{
    this->time_shots = new Timer(80);
    this->coordinates_object[0] = Coordinate( 0, 2);
    this->coordinates_object[1] = Coordinate( 2,-2);
    this->coordinates_object[2] = Coordinate( 0,-1);
    this->coordinates_object[3] = Coordinate(-2,-2);
    this->coordinates_boost[0] = Coordinate( 0, -1.0);
    this->coordinates_boost[1] = Coordinate( 1,-1.5);
    this->coordinates_boost[2] = Coordinate( 0,-3.0);
    this->coordinates_boost[3] = Coordinate(-1,-1.5);
    this->hitbox[0] = Coordinate(-1.5, 1.5);
    this->hitbox[1] = Coordinate( 1.5, 1.5);
    this->hitbox[2] = Coordinate( 1.5,-1.5);
    this->hitbox[3] = Coordinate(-1.5,-1.5);
    this->angle = 0;
    this->tx = 0;
    this->ty = 0;
    this->life = life;
    this->score = score;
    this->physic = new Physic(1, 0.99, 0.010);
    this->fire_sound = new Sound("fire.wav");
    this->boost_sound = new Sound("thrust.wav");
}

Ship::~Ship()
{
    delete time_shots;
    delete physic;
    shots.clear();
}

bool Ship::collision(Coordinate hitbox_enemies[4], float tx_asteroid, float ty_asteroid)
{
    try
    {
        float min_x = min(min(min(hitbox_enemies[0].x, hitbox_enemies[1].x), hitbox_enemies[2].x), hitbox_enemies[3].x)+tx_asteroid;
        float max_x = max(max(max(hitbox_enemies[0].x, hitbox_enemies[1].x), hitbox_enemies[2].x), hitbox_enemies[3].x)+tx_asteroid;
        float min_y = min(min(min(hitbox_enemies[0].y, hitbox_enemies[1].y), hitbox_enemies[2].y), hitbox_enemies[3].y)+ty_asteroid;
        float max_y = max(max(max(hitbox_enemies[0].y, hitbox_enemies[1].y), hitbox_enemies[2].y), hitbox_enemies[3].y)+ty_asteroid;
        for(int i=0; i<4; i++)
        {
            if(coordinates_object[i].x+this->tx>=min_x && coordinates_object[i].x+this->tx<=max_x && coordinates_object[i].y+this->ty>=min_y && coordinates_object[i].y+this->ty<=max_y)
            {
                return true;
            }
        }
        min_x = min(min(min(this->hitbox[0].x, this->hitbox[1].x), this->hitbox[2].x), this->hitbox[3].x)+this->tx;
        max_x = max(max(max(this->hitbox[0].x, this->hitbox[1].x), this->hitbox[2].x), this->hitbox[3].x)+this->tx;
        min_y = min(min(min(this->hitbox[0].y, this->hitbox[1].y), this->hitbox[2].y), this->hitbox[3].y)+this->ty;
        max_y = max(max(max(this->hitbox[0].y, this->hitbox[1].y), this->hitbox[2].y), this->hitbox[3].y)+this->ty;
        for(int i=0; i<4; i++)
        {
            if(hitbox_enemies[i].x+tx_asteroid>=min_x && hitbox_enemies[i].x+tx_asteroid<=max_x && hitbox_enemies[i].y+ty_asteroid>=min_y && hitbox_enemies[i].y+ty_asteroid<=max_y)
            {
                return true;
            }
        }
    }
    catch(exception e)
    {
        return true;
    }
    return false;
}

void Ship::shot_out()
{
    vector<Shot*> shots_in;
    for(int i=0; i<(int)this->getShots().size(); i++)
    {
        if(this->getShots()[i]->getTx()+this->getShots()[i]->getCoordinate().x>=-50 && this->getShots()[i]->getTx()+this->getShots()[i]->getCoordinate().x<=50)
        {
            if(this->getShots()[i]->getTy()+this->getShots()[i]->getCoordinate().y>=-50 && this->getShots()[i]->getTy()+this->getShots()[i]->getCoordinate().y<=50)
            {
                shots_in.push_back(this->getShots()[i]);
            }
        }
    }
    this->shots = shots_in;
}

void Ship::move()
{
    this->physic->getVelocity(this->tx, this->ty);
    if(this->tx>50 || this->tx<-50)
    {
        this->tx = -this->tx;
    }
    else if(this->ty>50 || this->ty<-50)
    {
        this->ty = -this->ty;
    }
}

void Ship::rotate(float a)
{
    this->angle+=a;
    if(this->angle>360)
    {
        this->angle=0;
    }
    if(this->angle<0)
    {
        this->angle=360;
    }
}

void Ship::fire()
{
    if(this->shots.size()<6 && this->time_shots->valid_diff_time())
    {
        this->fire_sound->play();
        this->shots.push_back(new Shot(Coordinate(tx-sin(radians_to_degrees(this->angle)), ty+cos(radians_to_degrees(this->angle))), this->angle));
    }
}

vector<Shot*>&Ship::getShots()
{
    return this->shots;
}

void Ship::draw(bool KEY_UP)
{
    this->time_shots->setCurrent_time();
    glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(tx, ty, 0);
        glRotatef(this->getAngle(), 0, 0, 1);
        if(KEY_UP)
        {
            glBegin(GL_POLYGON);
            for(int i=0; i<4; i++)
            {
                if(i==2)
                {
                    glColor3f(1, 0, 0);
                }
                else
                {
                    glColor3f(1, 1, 0);
                }
                glVertex2f(this->coordinates_boost[i].x, this->coordinates_boost[i].y);
            }
            glEnd();
        }
        glBegin(GL_LINE_LOOP);
            glColor3f(1, 1, 1);
            for(int i=0; i<4; i++)
            {
                glVertex2f(this->coordinates_object[i].x, this->coordinates_object[i].y);
            }
        glEnd();
    glPopMatrix();
}

void Ship::boost()
{
    this->boost_sound->play();
    this->physic->accelerate(this->angle);
}

void Ship::hyperspace()
{
    this->tx = rand()%50-rand()%50;
    this->ty = rand()%50-rand()%50;
}

float Ship::getAngle()
{
    return this->angle;
}

void Ship::setAngle(float a)
{
    this->angle=a;
}

float Ship::getTx()
{
    return this->tx;
}

int Ship::getLife()
{
    return this->life;
}

void Ship::setLife(int l)
{
    this->life = l;
}

int Ship::getScore()
{
    return this->score;
}

void Ship::setScore(int s)
{
    this->score = s;
}

void Ship::setTx(float tx)
{
    this->tx=tx;
}

float Ship::getTy()
{
    return this->ty;
}

void Ship::setTy(float ty)
{
    this->ty=ty;
}
