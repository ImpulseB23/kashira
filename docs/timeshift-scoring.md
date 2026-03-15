# timeshift scoring

## how it works

the score is a number from 0-100 that tells you how likely someone is to be awake right now. it's not a guess — it layers real data on top of each other to get a pretty accurate read.

## layers

from most to least important:

**user override** — if someone manually sets active hours for a person (night shift worker, weird schedule, etc), that wins over everything. -1 means no override.

**learned patterns** — not implemented yet, but the plan is to eventually learn from when people actually respond and adjust automatically. the interface is ready for it.

**age** — younger people stay up later, older people wake up earlier. data in `data/age_brackets.json`. offsets are in minutes, 35-44 age group is the baseline (0 offset).

**country** — different cultures have wildly different sleep habits. spain doesn't go to bed until midnight, south africa is out by 10:30pm. data in `data/countries.json`.

**timezone** — the obvious one. all scoring happens in the person's local time.

## the curve

it's not just "asleep or awake". the score ramps up and down throughout the day:

- deep sleep (middle of the night): 5-10
- falling asleep (around bedtime): 30 dropping to 10
- waking up: 10 ramping to 60
- morning: 60 ramping to 90
- peak hours (mid-morning to evening): 85-95
- afternoon dip (~2-3pm): drops to ~75
- winding down (few hours before bed): 85 dropping to 30

## architecture

```
src-tauri/blades/timeshift/
  timeshift.h/.cpp   — FFI api + combines everything
  curves.h/.cpp      — the actual curve math
  overrides.h/.cpp   — user override handling
```

rust loads the json data, resolves timezones, and passes plain ints to c++. c++ just does math — no IO, no allocations.

## FFI

times are minutes past midnight (23:30 = 1410).

```cpp
extern "C" {
    int get_activity_score(
        int current_hour,
        int current_minute,
        int bedtime_minutes,
        int waketime_minutes,
        int age,
        int override_active_start,
        int override_active_end
    );
}
```

## data flow

json files → rust (parses, resolves timezone, applies age offset) → c++ (pure math) → score back to frontend
