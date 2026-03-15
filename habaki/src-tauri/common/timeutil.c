#include "timeutil.h"

int wrap_minutes(int minutes)
{
    if (minutes < 0)
        minutes += 1440;
    if (minutes >= 1440)
        minutes -= 1440;
    return minutes;
}

int minutes_between(int from, int to)
{
    int diff = to - from;
    if (diff < 0)
        diff += 1440;
    return diff;
}

int safe_div(int num, int den)
{
    if (den == 0)
        return 0;
    return num / den;
}
