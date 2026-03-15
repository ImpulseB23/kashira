#include "wakefulness.h"

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

int lerp(int a, int b, int num, int den)
{
    return a + ((b - a) * num) / den;
}

int awake_score(int current_minutes, int bedtime, int waketime, const SleepCurveConfig* c)
{
    int time_awake = minutes_between(waketime, current_minutes);
    int time_til_sleep = minutes_between(current_minutes, bedtime);
    int active_window = minutes_between(waketime, bedtime);

    bool awake;
    if (waketime < bedtime)
        awake = (current_minutes >= waketime && current_minutes < bedtime);
    else
        awake = (current_minutes >= waketime || current_minutes < bedtime);

    if (!awake)
    {
        int time_since_bed = minutes_between(bedtime, current_minutes);
        int time_til_wake = minutes_between(current_minutes, waketime);
        int sleep_window = time_since_bed + time_til_wake;

        if (time_since_bed < c->falling_asleep_minutes)
            return lerp(c->falling_asleep_high, c->falling_asleep_low,
                        time_since_bed, c->falling_asleep_minutes);

        if (time_til_wake < c->pre_wake_ramp_minutes)
            return lerp(c->pre_wake_high, c->pre_wake_low,
                        c->pre_wake_ramp_minutes - time_til_wake, c->pre_wake_ramp_minutes);

        int pct_through = (time_since_bed * 100) / sleep_window;
        if (pct_through < 50)
            return c->deep_sleep_floor + (50 - pct_through) / 8;
        else
            return c->deep_sleep_floor + (pct_through - 50) / 6;
    }

    int pct = (time_awake * 100) / active_window;

    if (pct < c->wake_ramp_pct)
        return lerp(c->wake_ramp_low, c->wake_ramp_high, pct, c->wake_ramp_pct);

    if (pct < c->morning_ramp_pct)
        return lerp(c->wake_ramp_high, c->morning_ramp_high,
                    pct - c->wake_ramp_pct, c->morning_ramp_pct - c->wake_ramp_pct);

    if (pct > c->pre_sleep_pct)
        return lerp(c->wind_down_low, c->pre_sleep_low,
                    100 - pct, 100 - c->pre_sleep_pct);

    if (pct > c->wind_down_pct)
        return lerp(c->peak_score, c->wind_down_low,
                    pct - c->wind_down_pct, c->pre_sleep_pct - c->wind_down_pct);

    if (pct > c->dip_start_pct && pct < c->dip_end_pct)
    {
        int dist = pct - c->dip_center_pct;
        if (dist < 0)
            dist = -dist;
        int half = (c->dip_end_pct - c->dip_start_pct) / 2;
        return lerp(c->dip_low, c->peak_score, dist, half);
    }

    return c->peak_score;
}

int shift_for_age(int base_minutes, int age)
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

int shift_for_weekend(int base_minutes, int day_of_week, bool is_bedtime)
{
    if (day_of_week == 0 || day_of_week == 6)
        return wrap_minutes(base_minutes + (is_bedtime ? 40 : 75));

    if (day_of_week == 5 && is_bedtime)
        return wrap_minutes(base_minutes + 40);

    return base_minutes;
}
