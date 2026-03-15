# Naming System

Kashira's internals are named after parts of a Japanese katana. Each part maps to a layer of the application.

## The Katana

```
┌─────────┐  ┌──────────┐  ┌─────────┐  ┌─────────────────┐
│ Kashira │──│  Tsuka   │──│ Habaki  │──│     Blade       │
│ (cap)   │  │ (grip)   │  │(collar) │  │                 │
└─────────┘  └──────────┘  └─────────┘  └─────────────────┘
      │            │             │              │
   The app    Orchestrator   FFI bridge    Feature modules
```

## Parts

**Kashira (頭)** - The app itself. The pommel cap that holds everything together. Without it, the handle unravels.

**Tsuka (柄)** - The core orchestrator. The grip that connects your hand to the blade. In code, this is the layer that combines all inputs and produces the final result. Each blade has its own tsuka (`tsuka.cpp`).

**Habaki (鎺)** - The FFI bridge between Rust and C++. The small metal collar that locks the blade into the handle. Tiny but critical - it's what keeps the languages connected. Lives in `habaki/src-tauri/src/main.rs`.

**Blade (刃)** - Feature modules. Each blade is a self-contained tool - timeshift, shush, wherespace. Users install the blades they want. Code lives in `habaki/src-tauri/blades/`.

**Menuki (目貫)** - The UI layer. Ornamental grip pieces that you see and feel. Everything in `habaki/menuki/` - Svelte components, styles, the visual interface.

**Ito (糸)** - Configuration and data. The cord wrapping that holds the tsuka together. All the JSON files in `ito/` that tune the scoring, define countries, set thresholds. Pull on one thread and the behavior changes.

**Saya (鞘)** - Storage and persistence. The scabbard where the blade rests. User data, saved contacts, preferences. Not yet implemented.

**Tsuba (鍔)** - The guard. Security layer, input validation, permissions. Protects the system from bad data. Not yet implemented.

## Why?

Every part of a katana exists for a reason. Nothing is decorative without being functional. Same principle applies to the codebase - every layer has a clear purpose, and the naming makes that purpose immediately obvious once you know the system.

Also it's just cool.
