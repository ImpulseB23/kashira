#ifndef TIMEUTIL_H
#define TIMEUTIL_H

#ifdef __cplusplus
extern "C" {
#endif

int wrap_minutes(int minutes);
int minutes_between(int from, int to);
int safe_div(int num, int den);

#ifdef __cplusplus
}
#endif

#endif
