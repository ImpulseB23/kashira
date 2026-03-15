# review instructions

## project
hilt is a modular desktop app. rust/tauri core, svelte frontend, c++ for blade logic. blades are feature modules.

## what to look for
- memory issues in c/c++ (leaks, overflows, use-after-free)
- FFI boundary bugs between rust and c++
- hardcoded secrets or credentials
- unused code and dead imports
- breaking changes to public interfaces
- missing error handling at system boundaries

## architecture notes
- `src/` svelte frontend
- `src-tauri/src/` rust backend
- `src-tauri/blades/` c++ blade logic
- `data/` static json data
- `tests/` c++ tests (catch2)
- times are internally minutes past midnight (0-1439)
- rust calls c++ via extern "C" FFI
