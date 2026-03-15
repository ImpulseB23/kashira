#include "curves.h"

int minutes_between(int from, int to)
{
    int diff = to - from;
    if (diff < 0)
        diff += 1440;
    return diff;
}

int activity_at(int current_minutes, int bedtime, int waketime)
{
    int time_awake = minutes_between(waketime, current_minutes);
    int time_til_sleep = minutes_between(current_minutes, bedtime);

    bool awake;
    if (waketime < bedtime)
    {
        awake = (current_minutes >= waketime && current_minutes < bedtime);
    }
    else
    {
        awake = (current_minutes >= waketime || current_minutes < bedtime);
    }

    if (!awake)
    {
        int time_since_bed = minutes_between(bedtime, current_minutes);
        int time_til_wake = minutes_between(current_minutes, waketime);

        if (time_since_bed < 30)
            return 20 - (time_since_bed * 15) / 30;

        if (time_til_wake < 45)
            return 10 + ((45 - time_til_wake) * 10) / 45;

        return 5;
    }

    if (time_awake < 60)
        return 30 + (time_awake * 40) / 60;

    if (time_awake < 180)
        return 70 + ((time_awake - 60) * 20) / 120;

    if (time_til_sleep < 60)
        return 20 + (time_til_sleep * 30) / 60;

    if (time_til_sleep < 180)
        return 50 + ((time_til_sleep - 60) * 35) / 120;

    if (time_awake > 420 && time_awake < 540)
    {
        int dist = time_awake - 480;
        if (dist < 0)
            dist = -dist;
        return 75 + (dist * 15) / 60;
    }

    return 90;
}
