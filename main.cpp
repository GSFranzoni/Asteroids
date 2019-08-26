#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <string>
#include <time.h>
#include <fstream>
#include <SFML/Audio.hpp>

#include "Coordinate.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Boss.h"
#include "Keyboard.h"

using namespace std;

GLsizei width=0, height=0, win=0;
int fps, initial_time = time(NULL), current_time, level = 0;
bool playing = false, game_over = false;

Ship* ship;
Boss* boss;
vector<Asteroid*> asteroids;
Sound* hit_sound = new Sound("explosion.wav");
Sound* game_over_sound = new Sound("gameover.wav");
Sound* levelup_sound = new Sound("levelup.wav");

void drawText(const char *text, int length, int x, int y, void* font)
{
    glMatrixMode(GL_PROJECTION);
    double matrix[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);
    for(int i=0; i<length; i++)
    {
        glutBitmapCharacter(font, (int)text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}

void getAsteroid()
{
    int tx, ty;
    if(rand()%10%2==0)
    {
        ty = rand()%55-rand()%55;
        if(rand()%10%2==0)
        {
            tx = 55;
        }
        else
        {
            tx = -55;
        }
    }
    else
    {
        tx = rand()%55-rand()%55;
        if(rand()%10%2==0)
        {
            ty = 55;
        }
        else
        {
            ty = -55;
        }
    }
    asteroids.push_back(new Asteroid(3, tx, ty));
}

void restart()
{
    srand(time(NULL));
    ship = new Ship(ship->getLife(), ship->getScore());
    if(ship->getLife()<1){
        game_over_sound->play();
        game_over = true;
    }
    boss = new Boss();
    asteroids.clear();
    for(int i=0; i<3+level; i++)
    {
        getAsteroid();
    }
}

void update()
{
    att_keyboard_func(ship, playing);
    if(playing && !game_over)
    {
        boss->fire();
        if(asteroids.empty())
        {
            level++;
            ship->setLife(ship->getLife()+1);
            levelup_sound->play();
            restart();
        }
        for(auto it_asteroids = asteroids.begin(); it_asteroids != asteroids.end(); ++it_asteroids)
        {
            if(ship->collision((*it_asteroids)->hitbox, (*it_asteroids)->getTx(), (*it_asteroids)->getTy()))
            {
                ship->setLife(ship->getLife()-1);
                hit_sound->play();
                restart();
                return;
            }
        }
        if(ship->collision(boss->hitbox, boss->getTx(), boss->getTy()))
        {
            ship->setLife(ship->getLife()-1);
            hit_sound->play();
            restart();
            return;
        }
        for(auto it_shots_boss = boss->getShots().begin(); it_shots_boss != boss->getShots().end(); ++it_shots_boss)
        {
            if((*it_shots_boss)->collision(ship->hitbox, ship->getTx(), ship->getTy()))
            {
                ship->setLife(ship->getLife()-1);
                hit_sound->play();
                restart();
                return;
            }
        }
        for(auto it_shots = ship->getShots().begin(); it_shots != ship->getShots().end();)
        {
            bool collision = false;
            for(auto it_asteroids = asteroids.begin(); it_asteroids != asteroids.end(); ++it_asteroids)
            {
                if((*it_shots)->collision((*it_asteroids)->hitbox, (*it_asteroids)->getTx(), (*it_asteroids)->getTy()))
                {
                    float tx = (*it_asteroids)->getTx(), ty = (*it_asteroids)->getTy(), size = (*it_asteroids)->getSize();
                    it_asteroids = asteroids.erase(it_asteroids);
                    it_shots = ship->getShots().erase(it_shots);
                    collision = true;
                    if(size>1)
                    {
                        asteroids.push_back(new Asteroid(size-1, tx, ty));
                        asteroids.push_back(new Asteroid(size-1, tx, ty));
                    }
                    switch((int)size)
                    {
                    case 1:
                        ship->setScore(ship->getScore()+100);
                        break;
                    case 2:
                        ship->setScore(ship->getScore()+50);
                        break;
                    case 3:
                        ship->setScore(ship->getScore()+20);
                        break;
                    }
                    break;
                }
                else if((*it_shots)->collision(boss->hitbox, boss->getTx(), boss->getTy()))
                {
                    ship->setScore(ship->getScore()+150);
                    collision=true;
                    it_shots = ship->getShots().erase(it_shots);
                    boss = new Boss();
                }
            }
            if(!collision)
            {
                ++it_shots;
            }
            else
            {
                hit_sound->play();
            }
        }
        boss->move();
        ship->move();
        boss->shot_out();
        ship->shot_out();
        for(int i=0; i<(int)ship->getShots().size(); i++)
        {
            ship->getShots()[i]->move();
        }
        for(int i=0; i<(int)boss->getShots().size(); i++)
        {
            boss->getShots()[i]->move();
        }
    }
    for(int i=0; i<(int)asteroids.size(); i++)
    {
        asteroids[i]->move();
    }
}

void show_fps()
{
    fps++;
    current_time = time(NULL);
    if(current_time-initial_time>0)
    {
        string str_fps = int_to_string((int)(fps/(current_time-initial_time))) + " FPS";
        drawText(str_fps.data(), str_fps.size(), 675, 575, GLUT_BITMAP_9_BY_15);
    }
}

void show_score()
{
    string str_score = int_to_string(ship->getScore());
    drawText(str_score.data(), str_score.size(), 380, 570, GLUT_BITMAP_9_BY_15);
}

void show_life()
{
    glPushMatrix();
    glScalef(0.6, 0.6, 0);
    glTranslatef(-80, 77, 0);
    for(int i=0; i<ship->getLife(); i++)
    {
        glTranslatef(5, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex2f( 0, 2);
        glVertex2f( 2,-2);
        glVertex2f( 0,-1);
        glVertex2f(-2,-2);
        glEnd();
    }
    glPopMatrix();
}

void show_start_screen(){
    string txt = "Press enter to play!";
    drawText(txt.data(), txt.size(), 280, 250, GLUT_BITMAP_TIMES_ROMAN_24);
}

void show_game_over_screen(){
    string txt;
    fstream file;
    file.open("highscore.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    file >> txt;
    file.close();
    if(ship->getScore()>string_to_int(txt)){
        file.open("highscore.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
        file << ship->getScore();
        file.close();
    }
    file >> txt;
    string game_over = "GAME OVER!";
    string your_score = "Your score = " + int_to_string(ship->getScore());
    string highscore = "High score = " + txt;
    drawText(game_over.data(), game_over.size(), 290, 340, GLUT_BITMAP_TIMES_ROMAN_24);
    drawText(your_score.data(), your_score.size(), 277, 300, GLUT_BITMAP_TIMES_ROMAN_24);
    drawText(highscore.data(), highscore.size(), 280, 270, GLUT_BITMAP_TIMES_ROMAN_24);
    file.close();
}

void draw_game_area()
{
    glBegin(GL_LINE_LOOP);
    glVertex2f( 50, 50);
    glVertex2f( 50,-50);
    glVertex2f(-50,-50);
    glVertex2f(-50, 50);
    glEnd();
}

void draw(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    if(game_over){
        show_game_over_screen();
    }
    else{
        if(!playing){
            show_start_screen();
        }
        show_score();
        show_fps();
        show_life();
        draw_game_area();
        ship->draw(KEY_UP);
        boss->draw();
        for(int i=0; i<(int)ship->getShots().size(); i++)
        {
            ship->getShots()[i]->draw();
        }
        for(int i=0; i<(int)boss->getShots().size(); i++)
        {
            boss->getShots()[i]->draw();
        }
        for(int i=0; i<(int)asteroids.size(); i++)
        {
            asteroids[i]->draw();
        }
    }
    glViewport(0, 0, width, height);
    gluOrtho2D(-55, 55, -55, 55);
    glutSwapBuffers();
}

void run(int t)
{
    update();
    glutPostRedisplay();
    glutTimerFunc(12, run, 1);
}

void resize(GLsizei w, GLsizei h)
{
    if(h == 0)
        h = 1;
    width = w;
    height = h;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(width<=height)
    {
        gluOrtho2D (-50.0f, 50.0f, -50.0f*height/width, 50.0f*height/width);
        win = 50.0f;
    }
    else
    {
        gluOrtho2D (-50.0f*width/height, 50.0f*width/height, -50.0f, 50.0f);
        win = 50.0f*width/height;
    }
}

void init(void)
{
    ship = new Ship(3, 0);
    boss = new Boss();
    asteroids.clear();
    for(int i=0; i<3; i++)
    {
        getAsteroid();
    }
    glClearColor(0.0f, 0.0f, 0.0f, 1);
}

int main(void)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-600)/2, (glutGet(GLUT_SCREEN_HEIGHT)-600)/2);
    glutInitWindowSize(600,600);
    glutCreateWindow("Asteroids");
    glutDisplayFunc(draw);
    glutReshapeFunc(resize);
    glutSpecialFunc(special_key_down);
    glutKeyboardFunc(normal_key_down);
    glutSpecialUpFunc(special_key_up);
    glutKeyboardUpFunc(normal_key_up);
    glutTimerFunc(12, run, 1);
    init();
    glutMainLoop();
    return 0;
}
