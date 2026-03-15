fn main() {
    cc::Build::new()
        .cpp(true)
        .file("blades/timeshift/wakefulness.cpp")
        .file("blades/timeshift/availability.cpp")
        .file("blades/timeshift/overrides.cpp")
        .file("blades/timeshift/timeshift.cpp")
        .compile("timeshift");

    tauri_build::build()
}
