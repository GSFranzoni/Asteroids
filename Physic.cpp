#include "Physic.h"
#include <ctime>
#include <iostream>
#include <math.h>
#include "Utilities.h"

using namespace std;

/**
Construtor da classe Physic.
Recebe como parâmetros a velocidade máxima e aceleração do objeto e o atrito do ambiente.
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
Função usada para acelerar um objeto de acordo com sua aceleração e ângulo.
**/
void Physic::accelerate(float angle){
    this->velocity_x-=(sin(radians_to_degrees(angle)))*this->acceleration;
    this->velocity_y+=(cos(radians_to_degrees(angle)))*this->acceleration;
}

float Physic::getAcceleration(){
    return this->acceleration;
}

/**
Função usada para movimentar objetos que possuem velocidade constante.
**/
void Physic::getConstantVelocity(float& tx, float& ty, float angle, float velocity){
    angle = radians_to_degrees(angle);
    tx-=sin(angle)*velocity;
    ty+=cos(angle)*velocity;
}

/**
Função usada para movimentar um objeto de acordo com sua velocidade e o atrito do ambiente.
**/
void Physic::getVelocity(float& tx, float& ty){
    tx+=this->velocity_x;
    ty+=this->velocity_y;
    this->velocity_x*=this->friction;
    this->velocity_y*=this->friction;
}
