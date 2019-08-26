#include "Physic.h"
#include <ctime>
#include <iostream>
#include <math.h>
#include "Utilities.h"

using namespace std;

/**
Construtor da classe Physic.
Recebe como par�metros a velocidade m�xima e acelera��o do objeto e o atrito do ambiente.
**/
Physic::Physic(float mv, float f, float a)
{
    this->velocity_x = 0;
    this->velocity_y = 0;
    this->acceleration = a;
    this->friction = f;
    this->max_velocity = mv;
}

Physic::~Physic()
{

}

/**
Fun��o usada para acelerar um objeto de acordo com sua acelera��o e �ngulo.
**/
void Physic::accelerate(float angle){
    this->velocity_x-=(sin(radians_to_degrees(angle)))*this->acceleration;
    this->velocity_y+=(cos(radians_to_degrees(angle)))*this->acceleration;
}

float Physic::getAcceleration(){
    return this->acceleration;
}

/**
Fun��o usada para movimentar objetos que possuem velocidade constante.
**/
void Physic::getConstantVelocity(float& tx, float& ty, float angle, float velocity){
    angle = radians_to_degrees(angle);
    tx-=sin(angle)*velocity;
    ty+=cos(angle)*velocity;
}

/**
Fun��o usada para movimentar um objeto de acordo com sua velocidade e o atrito do ambiente.
**/
void Physic::getVelocity(float& tx, float& ty){
    tx+=this->velocity_x;
    ty+=this->velocity_y;
    this->velocity_x*=this->friction;
    this->velocity_y*=this->friction;
}
