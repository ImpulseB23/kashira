#include "adjustments.h"

int wrap_minutes(int minutes)
{
    if (minutes < 0)
        minutes += 1440;
    if (minutes >= 1440)
        minutes -= 1440;
    return minutes;
}

int apply_age_offset(int base_minutes, int age)
{
    int offset = 0;
    if (age < 18)
        offset = 30;
    else if (age < 25)
        offset = 50;
    else if (age < 35)
        offset = 20;
    else if (age < 45)
        offset = 0;
    else if (age < 55)
        offset = -15;
    else if (age < 65)
        offset = -30;
    else
        offset = -60;

    return wrap_minutes(base_minutes + offset);
}

int apply_weekend_offset(int base_minutes, int day_of_week)
{
    if (day_of_week == 0 || day_of_week == 6)
        return wrap_minutes(base_minutes + 60);
    return base_minutes;
}

int apply_age_cap(int score, int age)
{
    int cap = 90;
    if (age >= 60)
        cap = 75;
    else if (age >= 45)
        cap = 82;
    else if (age >= 25)
        cap = 88;

    if (score > cap)
        return cap;
    return score;
}
