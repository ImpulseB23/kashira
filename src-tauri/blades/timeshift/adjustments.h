#ifndef ADJUSTMENTS_H
#define ADJUSTMENTS_H

int apply_age_offset(int base_minutes, int age);
int apply_weekend_offset(int base_minutes, int day_of_week);
int apply_age_cap(int score, int age);

#endif
