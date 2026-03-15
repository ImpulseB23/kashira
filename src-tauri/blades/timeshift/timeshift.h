#ifndef TIMESHIFT_H
#define TIMESHIFT_H

extern "C" {
    int get_activity_score(
        int current_hour,
        int current_minute,
        int day_of_week,
        int bedtime_minutes,
        int waketime_minutes,
        int age,
        int override_active_start,
        int override_active_end
    );
}

#endif
