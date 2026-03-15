#include "timeshift.h"
#include "wakefulness.h"
#include "availability.h"
#include "overrides.h"

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
)
{
    int now = current_hour * 60 + current_minute;

    if (has_override(override_active_start, override_active_end))
        return apply_override(now, override_active_start, override_active_end, curve);

    int bed = shift_for_age(bedtime_minutes, age);
    int wake = shift_for_age(waketime_minutes, age);

    bed = shift_for_weekend(bed, day_of_week, true);
    wake = shift_for_weekend(wake, day_of_week, false);

    int score = awake_score(now, bed, wake, curve);
    score = age_responsiveness(score, age);

    int busy = work_busy_factor(now, work_start, work_end);
    score = (score * busy) / 100;

    return score;
}
