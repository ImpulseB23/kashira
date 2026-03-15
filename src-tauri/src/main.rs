use serde::Deserialize;
use std::sync::LazyLock;

#[repr(C)]
#[derive(Deserialize)]
struct SleepCurveConfig {
    falling_asleep_minutes: i32,
    falling_asleep_high: i32,
    falling_asleep_low: i32,
    deep_sleep_floor: i32,
    pre_wake_ramp_minutes: i32,
    pre_wake_low: i32,
    pre_wake_high: i32,
    wake_ramp_pct: i32,
    wake_ramp_low: i32,
    wake_ramp_high: i32,
    morning_ramp_pct: i32,
    morning_ramp_high: i32,
    wind_down_pct: i32,
    wind_down_high: i32,
    wind_down_low: i32,
    pre_sleep_pct: i32,
    pre_sleep_low: i32,
    peak_score: i32,
    dip_start_pct: i32,
    dip_end_pct: i32,
    dip_center_pct: i32,
    dip_low: i32,
}

unsafe extern "C" {
    fn get_activity_score(
        current_hour: i32,
        current_minute: i32,
        day_of_week: i32,
        bedtime_minutes: i32,
        waketime_minutes: i32,
        age: i32,
        work_start: i32,
        work_end: i32,
        override_active_start: i32,
        override_active_end: i32,
        curve: *const SleepCurveConfig,
    ) -> i32;
}

#[derive(Deserialize)]
struct Country {
    code: String,
    name: String,
    timezones: Vec<String>,
    bedtime: String,
    waketime: String,
}

static COUNTRIES: LazyLock<Vec<Country>> = LazyLock::new(|| {
    let data = include_str!("../../data/countries.json");
    serde_json::from_str(data).expect("bad countries.json")
});

static CURVE: LazyLock<SleepCurveConfig> = LazyLock::new(|| {
    let data = include_str!("../../data/sleep_curve.json");
    serde_json::from_str(data).expect("bad sleep_curve.json")
});

fn parse_time(t: &str) -> i32 {
    let parts: Vec<&str> = t.split(':').collect();
    let h: i32 = parts[0].parse().unwrap_or(0);
    let m: i32 = parts[1].parse().unwrap_or(0);
    h * 60 + m
}

#[tauri::command]
fn score_for_person(
    country_code: String,
    age: i32,
    work_start: i32,
    work_end: i32,
    override_start: i32,
    override_end: i32,
) -> i32 {
    let country = COUNTRIES.iter().find(|c| c.code == country_code);
    let Some(country) = country else { return -1 };

    let bed = parse_time(&country.bedtime);
    let wake = parse_time(&country.waketime);

    let now = chrono::Local::now();

    unsafe {
        get_activity_score(
            now.format("%H").to_string().parse().unwrap_or(0),
            now.format("%M").to_string().parse().unwrap_or(0),
            now.format("%w").to_string().parse().unwrap_or(0),
            bed,
            wake,
            age,
            work_start,
            work_end,
            override_start,
            override_end,
            &*CURVE,
        )
    }
}

#[tauri::command]
fn list_countries() -> Vec<(String, String)> {
    COUNTRIES.iter().map(|c| (c.code.clone(), c.name.clone())).collect()
}

fn main() {
    tauri::Builder::default()
        .invoke_handler(tauri::generate_handler![score_for_person, list_countries])
        .run(tauri::generate_context!())
        .expect("failed to run app");
}
