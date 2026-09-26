#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#define GLUT_KEY_SPACE 32
#define GLUT_KEY_ESC 27
#define GLUT_KEY_ENTER 13

#include "Ship.h"

static bool KEY_END, KEY_LEFT = false, KEY_RIGHT = false, KEY_UP = false, KEY_SPACE = false, KEY_A = false, KEY_D = false, KEY_ESC = false, KEY_ENTER = false;

static void att_keyboard_func(Ship* ship, bool &playing)
{
    if(KEY_ENTER && !playing){
        playing = true;
        return;
    }
    if(!playing)
        return;
    if(KEY_ESC)
        exit(0);
    if(KEY_END)
    {
        ship->hyperspace();
        KEY_END = false;
    }
    if(KEY_SPACE)
    {
        ship->fire();
    }
    if(KEY_UP)
    {
        ship->boost();
        return;
    }
    if(KEY_LEFT)
    {
        ship->rotate(4);
    }
    else if(KEY_RIGHT)
    {
        ship->rotate(-4);
    }
    else if(KEY_D)
    {
        ship->rotate(-4);
        ship->fire();
    }
    else if(KEY_A)
    {
        ship->rotate(4);
        ship->fire();
    }
}

static void normal_key_down(unsigned char key, int x, int y)
{
    switch(tolower(key))
    {
    case GLUT_KEY_ENTER:
        KEY_ENTER = true;
        break;
    case GLUT_KEY_SPACE:
        KEY_SPACE = true;
        break;
    case 'a':
        KEY_A = true;
        break;
    case 'd':
        KEY_D = true;
        break;
    }
}

static void normal_key_up(unsigned char key, int x, int y)
{
    switch(tolower(key))
    {
    case GLUT_KEY_SPACE:
        KEY_SPACE = false;
        break;
    case 'a':
        KEY_A = false;
        break;
    case 'd':
        KEY_D = false;
        break;
    }
}

static void special_key_down(int key, int x, int y)
{
    switch(tolower(key))
    {
    case GLUT_KEY_LEFT:
        KEY_LEFT = true;
        break;
    case GLUT_KEY_RIGHT:
        KEY_RIGHT = true;
        break;
    case GLUT_KEY_UP:
        KEY_UP = true;
        break;
    case GLUT_KEY_END:
        KEY_END = true;
        break;
    }
}

static void special_key_up(int key, int x, int y)
{
    switch(tolower(key))
    {
    case GLUT_KEY_LEFT:
        KEY_LEFT = false;
        break;
    case GLUT_KEY_RIGHT:
        KEY_RIGHT = false;
        break;
    case GLUT_KEY_UP:
        KEY_UP = false;
        break;
    case GLUT_KEY_END:
        KEY_END = false;
        break;
    }
}

#endif
