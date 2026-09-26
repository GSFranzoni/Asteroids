#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include <string>
#include <sstream>

#define M_PI 3.14159265358979323846

using namespace std;

static float radians_to_degrees(float angle)
{
    return angle/180*M_PI;
}

static string int_to_string(int a)
{
    stringstream ss;
    string b;
    ss << a;
    ss >> b;
    return b;
}

static int string_to_int(string a)
{
    stringstream ss;
    int b;
    ss << a;
    ss >> b;
    return b;
}

#endif
