#include "wakefulness.h"
#include "timeutil.h"

int awake_score(int current_minutes, int bedtime, int waketime, const SleepCurveConfig* c)
{
    int since_wake = minutes_between(waketime, current_minutes);
    int since_bed = minutes_between(bedtime, current_minutes);
    int active_window = minutes_between(waketime, bedtime);
    int sleep_window = 1440 - active_window;

    bool awake;
    if (waketime < bedtime)
        awake = (current_minutes >= waketime && current_minutes < bedtime);
    else
        awake = (current_minutes >= waketime || current_minutes < bedtime);

    if (!awake)
    {
        int pct = safe_div(since_bed * 100, sleep_window);

        if (pct < 8)
            return c->falling_asleep_high - safe_div((c->falling_asleep_high - c->falling_asleep_low) * pct, 8);

        if (pct < c->deep_sleep_midpoint_pct)
            return c->falling_asleep_low - safe_div((c->falling_asleep_low - c->deep_sleep_floor) * (pct - 8), c->deep_sleep_midpoint_pct - 8);

        if (pct > 85)
            return c->pre_wake_low + safe_div((c->pre_wake_high - c->pre_wake_low) * (pct - 85), 15);

        if (pct > c->deep_sleep_midpoint_pct)
            return c->deep_sleep_floor + safe_div((c->pre_wake_low - c->deep_sleep_floor) * (pct - c->deep_sleep_midpoint_pct), 85 - c->deep_sleep_midpoint_pct);

        return c->deep_sleep_floor;
    }

    int pct = safe_div(since_wake * 100, active_window);

    if (pct < c->wake_ramp_pct)
        return c->wake_ramp_low + safe_div((c->wake_ramp_high - c->wake_ramp_low) * pct, c->wake_ramp_pct);

    if (pct < c->morning_ramp_pct)
        return c->wake_ramp_high + safe_div((c->peak_score - c->wake_ramp_high) * (pct - c->wake_ramp_pct), c->morning_ramp_pct - c->wake_ramp_pct);

    if (pct > c->dip_start_pct && pct < c->dip_end_pct)
    {
        int dist = pct - c->dip_center_pct;
        if (dist < 0)
            dist = -dist;
        int half = (c->dip_end_pct - c->dip_start_pct) / 2;
        return c->dip_low + safe_div((c->peak_score - c->dip_low) * dist, half);
    }

    if (pct > c->wind_down_pct)
    {
        if (pct > c->pre_sleep_pct)
            return c->pre_sleep_low + safe_div((c->wind_down_low - c->pre_sleep_low) * (100 - pct), 100 - c->pre_sleep_pct);
        return c->peak_score - safe_div((c->peak_score - c->wind_down_low) * (pct - c->wind_down_pct), c->pre_sleep_pct - c->wind_down_pct);
    }

    return c->peak_score;
}

int shift_for_age(int base_minutes, int offset)
{
    return wrap_minutes(base_minutes + offset);
}

int shift_for_weekend(int base_minutes, int day_of_week, bool is_bedtime, const WeekendConfig* w)
{
    if (day_of_week == 0 || day_of_week == 6)
        return wrap_minutes(base_minutes + (is_bedtime ? w->bedtime_shift : w->waketime_shift));

    if (day_of_week == 5 && is_bedtime)
        return wrap_minutes(base_minutes + w->friday_bedtime_shift);

    return base_minutes;
}
