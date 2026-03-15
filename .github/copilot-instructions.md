# review instructions

## project
kashira is a modular desktop app. rust/tauri core, svelte frontend, c++ for blade logic. blades are feature modules.

## what to look for
- memory issues in c/c++ (leaks, overflows, use-after-free)
- FFI boundary bugs between rust and c++
- hardcoded secrets or credentials
- unused code and dead imports
- breaking changes to public interfaces
- missing error handling at system boundaries

## language boundaries
- flag any business logic, calculations, or data processing in typescript/svelte. all logic belongs in c++, rust, c, or go
- svelte is UI only: rendering and calling tauri commands
- c++ handles blade logic, rust handles security-sensitive ops and FFI

## architecture notes
- `habaki/menuki/` svelte frontend
- `habaki/src-tauri/src/` rust backend
- `habaki/src-tauri/blades/` c++ blade logic
- `ito/` json config data
- `tests/` c++ tests (catch2)
- times are internally minutes past midnight (0-1439)
- rust calls c++ via extern "C" FFI
