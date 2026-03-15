#include "overrides.h"

bool has_override(int override_start, int override_end)
{
    return override_start != -1 && override_end != -1;
}

int apply_override(int current_minutes, int override_start, int override_end, const SleepCurveConfig* curve)
{
    return awake_score(current_minutes, override_end, override_start, curve);
}
