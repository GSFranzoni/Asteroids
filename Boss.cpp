#include "Boss.h"
#include <iostream>

using namespace std;

/**
Construtor do Boss.
Seta as coordenadas do desenho e hitbox do Boss.
Gera um ângulo para a movimentação do Boss.
Gera uma translação em x e y randômicas de maneira que o Boss não se colida com a nave assim que for criado.
Seta um tempo de 200ms entre um tiro e outro dado pelo Boss.
**/
Boss::Boss()
{
    this->coordinates[0] = Coordinate(-0.5, 1.8);
    this->coordinates[1] = Coordinate(0.5, 1.8);
    this->coordinates[2] = Coordinate(1, 1);
    this->coordinates[3] = Coordinate(2, 0);
    this->coordinates[4] = Coordinate(1, -1);
    this->coordinates[5] = Coordinate(-1, -1);
    this->coordinates[6] = Coordinate(-2, 0);
    this->coordinates[7] = Coordinate(-1, 1);
    this->hitbox[0] = Coordinate(-2, 1.8);
    this->hitbox[1] = Coordinate(2, 1.8);
    this->hitbox[2] = Coordinate(2, -1);
    this->hitbox[3] = Coordinate(-2, -1);
    if(rand()%10%2==0)
    {
        this->ty = rand()%55-rand()%55;
        if(rand()%10%2==0)
        {
            this->tx = 55;
        }
        else
        {
            this->tx = -55;
        }
    }
    else
    {
        this->tx = rand()%55-rand()%55;
        if(rand()%10%2==0)
        {
            this->ty = 55;
        }
        else
        {
            this->ty = -55;
        }
    }
    this->angle = rand()%360;
}

Boss::~Boss()
{
    shots.clear();
}

/**
Desenha o asteroid de acordo com as coordenadas do mesmo.
**/
void Boss::draw()
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
        glBegin(GL_LINES);
        glVertex2f(this->coordinates[2].x, this->coordinates[2].y);
        glVertex2f(this->coordinates[7].x, this->coordinates[7].y);
        glVertex2f(this->coordinates[3].x, this->coordinates[3].y);
        glVertex2f(this->coordinates[6].x, this->coordinates[6].y);
        glEnd();
    glPopMatrix();
}

/**
Atualiza as coordenadas do asteroid de acordo com a velocidade através do método estático 'getConstantVelocity' da
classe Physic.
E testa os limites do mapa.
**/
void Boss::move()
{
    Physic::getConstantVelocity(this->tx, this->ty, this->angle, 0.15);
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

/**
Deleta os tiros que saíram da área de jogo.
**/
void Boss::shot_out()
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

/**
Se a diferença de tempo for válida, o Boss atira em um ângulo aleatório.
**/
void Boss::fire()
{
    if(this->shots.size()<1)
    {
        this->shots.push_back(new Shot(Coordinate(tx, ty), rand()%360));
    }
}

/**
Retorna os tiros do Boss.
**/
vector<Shot*>&Boss::getShots()
{
    return this->shots;
}

float Boss::getTx()
{
    return this->tx;
}

void Boss::setTx(float tx)
{
    this->tx=tx;
}

float Boss::getTy()
{
    return this->ty;
}

void Boss::setTy(float ty)
{
    this->ty=ty;
}

