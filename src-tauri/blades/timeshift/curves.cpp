#include "curves.h"

int minutes_between(int from, int to) {
    int diff = to - from;
    if (diff < 0) diff += 1440;
    return diff;
}

int activity_at(int current_minutes, int bedtime, int waketime) {
    int time_awake = minutes_between(waketime, current_minutes);
    int time_til_sleep = minutes_between(current_minutes, bedtime);

    bool awake;
    if (waketime < bedtime) {
        awake = (current_minutes >= waketime && current_minutes < bedtime);
    } else {
        awake = (current_minutes >= waketime || current_minutes < bedtime);
    }

    if (!awake) return 5;

    if (time_awake < 60)
        return 30 + (time_awake * 40) / 60;

    if (time_awake < 180)
        return 70 + ((time_awake - 60) * 20) / 120;

    if (time_til_sleep < 60)
        return 20 + (time_til_sleep * 30) / 60;

    if (time_til_sleep < 180)
        return 50 + ((time_til_sleep - 60) * 35) / 120;

    return 90;
}

int apply_age_offset(int base_minutes, int age) {
    int offset = 0;
    if (age < 18) offset = 30;
    else if (age < 25) offset = 50;
    else if (age < 35) offset = 20;
    else if (age < 45) offset = 0;
    else if (age < 55) offset = -15;
    else if (age < 65) offset = -30;
    else offset = -60;

    int result = base_minutes + offset;
    if (result < 0) result += 1440;
    if (result >= 1440) result -= 1440;
    return result;
}
