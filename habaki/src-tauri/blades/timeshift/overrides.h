#ifndef OVERRIDES_H
#define OVERRIDES_H

#include "wakefulness.h"

int apply_override(int current_minutes, int override_start, int override_end, const SleepCurveConfig* curve);
bool has_override(int override_start, int override_end);

#endif
