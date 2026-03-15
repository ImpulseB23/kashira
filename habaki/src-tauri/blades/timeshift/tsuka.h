#ifndef TSUKA_H
#define TSUKA_H

#include "wakefulness.h"

extern "C" {
    int get_activity_score(
        int current_hour,
        int current_minute,
        int day_of_week,
        int bedtime_minutes,
        int waketime_minutes,
        int age,
        int age_cap,
        int bed_offset,
        int wake_offset,
        int work_start,
        int work_end,
        int override_active_start,
        int override_active_end,
        const SleepCurveConfig* curve,
        const WeekendConfig* weekend
    );
}

#endif
