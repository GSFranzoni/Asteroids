#include <sys/time.h>

#include "Timer.h"

Timer::Timer(long long min_diff_time)
{
    this->min_diff_time = min_diff_time;
    this->setCurrent_time();
    this->last_time = this->getCurrent_time()-min_diff_time;
}

Timer::~Timer()
{

}

bool Timer::valid_diff_time()
{
    if(this->getCurrent_time()-this->last_time>=this->min_diff_time)
    {
        setCurrent_time();
        this->last_time = this->getCurrent_time();
        return true;
    }
    setCurrent_time();
    return false;
}

long long Timer::getCurrent_time()
{
    return this->current_time;
}

long long Timer::getLast_time()
{
    return this->last_time;
}

long long Timer::getMin_diff_time()
{
    return this->min_diff_time;
}

void Timer::setCurrent_time()
{
    struct timeval te;
    gettimeofday(&te, NULL);
    this->current_time = te.tv_sec*1000LL + te.tv_usec/1000;
}

void Timer::setMin_diff_time(long long x)
{
    this->min_diff_time = x;
}
