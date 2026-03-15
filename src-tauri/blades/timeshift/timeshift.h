#ifndef TIMESHIFT_H
#define TIMESHIFT_H

#include "wakefulness.h"

extern "C" {
    int get_activity_score(
        int current_hour,
        int current_minute,
        int day_of_week,
        int bedtime_minutes,
        int waketime_minutes,
        int age,
        int work_start,
        int work_end,
        int override_active_start,
        int override_active_end,
        const SleepCurveConfig* curve
    );
}

#endif
