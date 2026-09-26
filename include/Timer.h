#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

class Timer
{
private:
    long long current_time, last_time, min_diff_time;
public:
    Timer(long long);
    ~Timer();
    long long getCurrent_time();
    long long getLast_time();
    long long getMin_diff_time();
    void setCurrent_time();
    void setMin_diff_time(long long);
    bool valid_diff_time();
};

#endif
