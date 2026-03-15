use serde::{Deserialize, Serialize};
use std::sync::LazyLock;

#[repr(C)]
#[derive(Deserialize)]
struct SleepCurveConfig {
    falling_asleep_minutes: i32,
    falling_asleep_high: i32,
    falling_asleep_low: i32,
    deep_sleep_floor: i32,
    deep_sleep_midpoint_pct: i32,
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

#[repr(C)]
#[derive(Deserialize)]
struct WeekendConfig {
    bedtime_shift: i32,
    waketime_shift: i32,
    friday_bedtime_shift: i32,
}

unsafe extern "C" {
    fn get_activity_score(
        current_hour: i32,
        current_minute: i32,
        day_of_week: i32,
        bedtime_minutes: i32,
        waketime_minutes: i32,
        age: i32,
        age_cap: i32,
        bed_offset: i32,
        wake_offset: i32,
        work_start: i32,
        work_end: i32,
        override_active_start: i32,
        override_active_end: i32,
        curve: *const SleepCurveConfig,
        weekend: *const WeekendConfig,
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

#[derive(Deserialize)]
struct AgeBracket {
    min: i32,
    max: i32,
    bedtime_offset: i32,
    waketime_offset: i32,
}

#[derive(Deserialize)]
struct AgeCap {
    min_age: i32,
    max_age: i32,
    cap: i32,
}

#[derive(Serialize)]
struct CountryInfo {
    code: String,
    name: String,
    timezones: Vec<String>,
}

static COUNTRIES: LazyLock<Vec<Country>> = LazyLock::new(|| {
    serde_json::from_str(include_str!("../../../ito/countries.json")).expect("bad countries.json")
});

static AGE_BRACKETS: LazyLock<Vec<AgeBracket>> = LazyLock::new(|| {
    serde_json::from_str(include_str!("../../../ito/age_brackets.json")).expect("bad age_brackets.json")
});

static AGE_CAPS: LazyLock<Vec<AgeCap>> = LazyLock::new(|| {
    serde_json::from_str(include_str!("../../../ito/age_caps.json")).expect("bad age_caps.json")
});

static CURVE: LazyLock<SleepCurveConfig> = LazyLock::new(|| {
    serde_json::from_str(include_str!("../../../ito/sleep_curve.json")).expect("bad sleep_curve.json")
});

static WEEKEND: LazyLock<WeekendConfig> = LazyLock::new(|| {
    serde_json::from_str(include_str!("../../../ito/weekend.json")).expect("bad weekend.json")
});

fn parse_time(t: &str) -> i32 {
    let parts: Vec<&str> = t.split(':').collect();
    let h: i32 = parts[0].parse().unwrap_or(0);
    let m: i32 = parts[1].parse().unwrap_or(0);
    h * 60 + m
}

fn age_offsets(age: i32) -> (i32, i32) {
    AGE_BRACKETS
        .iter()
        .find(|b| age >= b.min && age <= b.max)
        .map(|b| (b.bedtime_offset, b.waketime_offset))
        .unwrap_or((0, 0))
}

fn age_cap(age: i32) -> i32 {
    AGE_CAPS
        .iter()
        .find(|c| age >= c.min_age && age <= c.max_age)
        .map(|c| c.cap)
        .unwrap_or(90)
}

#[tauri::command]
fn score_for_person(
    country_code: String,
    timezone: String,
    age: i32,
    work_start: i32,
    work_end: i32,
    override_start: i32,
    override_end: i32,
) -> i32 {
    let country = COUNTRIES.iter().find(|c| c.code == country_code);
    let Some(country) = country else { return -1 };

    let (bed_off, wake_off) = age_offsets(age);
    let bed = parse_time(&country.bedtime);
    let wake = parse_time(&country.waketime);
    let cap = age_cap(age);

    let tz: chrono_tz::Tz = match timezone.parse() {
        Ok(t) => t,
        Err(_) => return -1,
    };
    let now = chrono::Utc::now().with_timezone(&tz);
    use chrono::{Timelike, Datelike};

    unsafe {
        get_activity_score(
            now.hour() as i32,
            now.minute() as i32,
            now.weekday().num_days_from_sunday() as i32,
            bed,
            wake,
            age,
            cap,
            bed_off,
            wake_off,
            work_start,
            work_end,
            override_start,
            override_end,
            &*CURVE,
            &*WEEKEND,
        )
    }
}

#[tauri::command]
fn list_countries() -> Vec<CountryInfo> {
    COUNTRIES.iter().map(|c| CountryInfo {
        code: c.code.clone(),
        name: c.name.clone(),
        timezones: c.timezones.clone(),
    }).collect()
}

fn main() {
    tauri::Builder::default()
        .invoke_handler(tauri::generate_handler![score_for_person, list_countries])
        .run(tauri::generate_context!())
        .expect("failed to run app");
}
