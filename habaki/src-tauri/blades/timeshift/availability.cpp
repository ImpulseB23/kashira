#include "availability.h"

int work_busy_factor(int current_minutes, int work_start, int work_end)
{
    if (work_start == -1 || work_end == -1)
        return 100;

    bool at_work;
    if (work_start < work_end)
        at_work = (current_minutes >= work_start && current_minutes < work_end);
    else
        at_work = (current_minutes >= work_start || current_minutes < work_end);

    return at_work ? 40 : 100;
}
