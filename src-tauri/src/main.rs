unsafe extern "C" {
    fn get_activity_score(
        current_hour: i32,
        current_minute: i32,
        bedtime_minutes: i32,
        waketime_minutes: i32,
        age: i32,
        override_active_start: i32,
        override_active_end: i32,
    ) -> i32;
}

#[tauri::command]
fn activity_score(
    current_hour: i32,
    current_minute: i32,
    bedtime: i32,
    waketime: i32,
    age: i32,
    override_start: i32,
    override_end: i32,
) -> i32 {
    unsafe {
        get_activity_score(
            current_hour,
            current_minute,
            bedtime,
            waketime,
            age,
            override_start,
            override_end,
        )
    }
}

fn main() {
    tauri::Builder::default()
        .invoke_handler(tauri::generate_handler![activity_score])
        .run(tauri::generate_context!())
        .expect("failed to run app");
}
