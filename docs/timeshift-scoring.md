# Timeshift Scoring

## How it works

The score is a number from 0-100 representing how likely someone is to respond right now. It combines multiple factors into one final number.

## Factors

**Wakefulness** - are they likely awake? Based on their country's average sleep patterns, adjusted for age and weekend. Uses a continuous curve across 24 hours with no hard sleep/awake boundary. Configurable via `ito/sleep_curve.json`.

**Age** - two effects. Shifts the sleep window (younger people sleep later, older earlier) via `ito/age_brackets.json`. Also caps the max score for older age groups via `ito/age_caps.json`.

**Weekend** - bedtime and waketime shift later on weekends. Friday nights also shift bedtime. Configurable via `ito/weekend.json`.

**Work hours** - if set, reduces the score during work hours (busy, less likely to respond to personal messages).

**User override** - manual active hours per person. Trumps automatic calculations.

## Data flow

```
JSON configs ──→ Rust (loads data, resolves timezone/age) ──→ C++ (all math) ──→ score
```

Rust handles I/O and data lookup. C++ handles all scoring logic. C provides shared time utilities.

## File structure

```
habaki/src-tauri/
├── common/
│   └── timeutil.c/h          shared C utilities
├── blades/timeshift/
│   ├── wakefulness.cpp/h      sleep cycle scoring
│   ├── availability.cpp/h     work hours modifier
│   ├── overrides.cpp/h        user manual overrides
│   └── tsuka.cpp/h            orchestrator (combines everything)
└── src/main.rs               FFI bridge + data loading

ito/
├── countries.json             country sleep data
├── age_brackets.json          age-based sleep offsets
├── age_caps.json              age-based score caps
├── sleep_curve.json           curve shape parameters
└── weekend.json               weekend shift values
```

## Configuration

All scoring parameters live in JSON files under `ito/`. Change them without recompiling - Rust loads them at startup.
