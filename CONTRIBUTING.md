# contributing

thanks for wanting to help out. here's how to get going.

## setup

1. clone the repo
2. install [bun](https://bun.sh), [rust](https://rustup.rs), and a c++ compiler (g++ or clang)
3. run `bun install`
4. run `cargo tauri dev` to start the app

## project structure

- `src/` — frontend (svelte + typescript)
- `src-tauri/` — backend (rust, tauri)
- `src-tauri/blades/` — blade logic (c++)
- `data/` — static data files (country info, age brackets)
- `tests/` — c++ unit tests (catch2)
- `docs/` — documentation

## running tests

```
cd tests
cmake -B build -G "MinGW Makefiles"
cmake --build build
./build/tests.exe
```

## making changes

- fork the repo and make a branch
- keep PRs small and focused
- make sure tests pass before submitting
- if you're adding new c++ logic, add tests for it
- match the existing code style

## language rules

all logic lives outside the frontend. the frontend (svelte/typescript) is strictly for UI rendering and calling backend commands. no business logic, no calculations, no data processing in typescript.

- **c++** — blade logic, scoring algorithms, data processing
- **rust** — app shell, FFI bridge, file I/O, anything security-sensitive
- **c** — low-level utilities, OS-level operations, shared glue code
- **go** — network-related features (background daemons, connectivity)
- **typescript/svelte** — UI only. display data, handle user input, call tauri commands

## blades

each blade is a self-contained feature module. if you want to add a new blade, look at how `timeshift` is structured and follow the same pattern.

## reporting bugs

open an issue. include what happened, what you expected, and steps to reproduce. screenshots help.
