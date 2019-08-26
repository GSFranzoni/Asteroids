#include "Asteroid.h"
#include "time.h"
#include "Utilities.h"
#include "Physic.h"
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

/**
Construtor do asteroid.
Como parâmetros, recebe o tamanho, sua translação em x e sua translação em y.
Seta as coordenadas do desenho e hitbox do asteroid.
Diminui o tamanho do asteroid de acordo com o parâmetro size.
Gera um ângulo para a movimentação do asteroid.
**/
Asteroid::Asteroid(float size, float tx, float ty)
{
    this->coordinates[0] = Coordinate(-1.881420729, 0.663809618);
    this->coordinates[1] = Coordinate(-1.2204023831, 1.7287836197);
    this->coordinates[2] = Coordinate(0.6157596888, 1.4717209296);
    this->coordinates[3] = Coordinate(1.6440104491, 0.7005328594);
    this->coordinates[4] = Coordinate(1.6807336905, -1.2457989368);
    this->coordinates[5] = Coordinate(0, -2);
    this->coordinates[6] = Coordinate(-0.7430002444, -1.0254594882);
    this->coordinates[7] = Coordinate(-1.7345277632, -0.9520130053);
    this->hitbox[0] = Coordinate(-2, 2);
    this->hitbox[1] = Coordinate( 2, 2);
    this->hitbox[2] = Coordinate( 2,-2);
    this->hitbox[3] = Coordinate(-2,-2);
    for(int i=0; i<8; i++)
    {
        this->coordinates[i].x*=size;
        this->coordinates[i].y*=size;
    }
    for(int i=0; i<4; i++)
    {
        this->hitbox[i].x*=size;
        this->hitbox[i].y*=size;
    }
    this->tx = tx;
    this->ty = ty;
    this->size = size;
    this->angle = rand()%360;
}

Asteroid::~Asteroid()
{

}

/**
Desenha o asteroid de acordo com as coordenadas do mesmo.
**/
void Asteroid::draw()
{
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(tx, ty, 0);
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 1, 1);
    for(int i=0; i<8; i++)
    {
        glVertex2f(this->coordinates[i].x, this->coordinates[i].y);
    }
    glEnd();
    glPopMatrix();
}

/**
Atualiza as coordenadas do asteroid de acordo com a velocidade através do método estático 'getConstantVelocity' da
classe Physic.
E testa os limites do mapa.
**/
void Asteroid::move()
{
    Physic::getConstantVelocity(this->tx, this->ty, this->angle, 0.25/size);
    if(this->tx>52)
    {
        this->tx = -52;
    }
    if(this->tx<-52)
    {
        this->tx = 52;
    }
    if(this->ty>52)
    {
        this->ty = -52;
    }
    if(this->ty<-52)
    {
        this->ty = 52;
    }
}

float Asteroid::getSize()
{
    return this->size;
}

float Asteroid::getTx()
{
    return this->tx;
}

void Asteroid::setTx(float tx)
{
    this->tx=tx;
}

float Asteroid::getTy()
{
    return this->ty;
}

void Asteroid::setTy(float ty)
{
    this->ty=ty;
}
