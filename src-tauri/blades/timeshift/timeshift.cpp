#include "timeshift.h"
#include "curves.h"
#include "overrides.h"

int get_activity_score(
    int current_hour,
    int current_minute,
    int bedtime_minutes,
    int waketime_minutes,
    int age,
    int override_active_start,
    int override_active_end
) {
    int now = current_hour * 60 + current_minute;

    if (has_override(override_active_start, override_active_end))
        return apply_override(now, override_active_start, override_active_end);

    int bed = apply_age_offset(bedtime_minutes, age);
    int wake = apply_age_offset(waketime_minutes, age);

    return activity_at(now, bed, wake);
}
