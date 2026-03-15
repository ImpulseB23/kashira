#ifndef WAKEFULNESS_H
#define WAKEFULNESS_H

struct SleepCurveConfig
{
    int falling_asleep_minutes;
    int falling_asleep_high;
    int falling_asleep_low;
    int deep_sleep_floor;
    int deep_sleep_midpoint_pct;
    int pre_wake_ramp_minutes;
    int pre_wake_low;
    int pre_wake_high;
    int wake_ramp_pct;
    int wake_ramp_low;
    int wake_ramp_high;
    int morning_ramp_pct;
    int morning_ramp_high;
    int wind_down_pct;
    int wind_down_high;
    int wind_down_low;
    int pre_sleep_pct;
    int pre_sleep_low;
    int peak_score;
    int dip_start_pct;
    int dip_end_pct;
    int dip_center_pct;
    int dip_low;
};

int awake_score(int current_minutes, int bedtime, int waketime, const SleepCurveConfig* cfg);
int shift_for_age(int base_minutes, int offset);
struct WeekendConfig
{
    int bedtime_shift;
    int waketime_shift;
    int friday_bedtime_shift;
};

int shift_for_weekend(int base_minutes, int day_of_week, bool is_bedtime, const WeekendConfig* wcfg);

#endif
