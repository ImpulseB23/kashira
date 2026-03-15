#include "availability.h"

int age_responsiveness(int score, int age)
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

int work_busy_factor(int current_minutes, int work_start, int work_end)
{
    if (work_start == -1 || work_end == -1)
        return 100;

    if (current_minutes >= work_start && current_minutes < work_end)
        return 40;

    return 100;
}
