fn main() {
    cc::Build::new()
        .file("common/timeutil.c")
        .compile("common");

    cc::Build::new()
        .cpp(true)
        .include("common")
        .file("blades/timeshift/wakefulness.cpp")
        .file("blades/timeshift/availability.cpp")
        .file("blades/timeshift/overrides.cpp")
        .file("blades/timeshift/tsuka.cpp")
        .compile("timeshift");

    tauri_build::build()
}
