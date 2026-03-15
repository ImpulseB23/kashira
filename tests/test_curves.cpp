#include <catch2/catch_test_macros.hpp>
#include "curves.h"
#include "adjustments.h"

TEST_CASE("deep sleep returns low score") {
    int bed = 1410;   // 23:30
    int wake = 440;   // 07:20
    REQUIRE(activity_at(180, bed, wake) < 15);  // 3am
}

TEST_CASE("peak hours return high score") {
    int bed = 1410;
    int wake = 440;
    REQUIRE(activity_at(780, bed, wake) > 80);  // 1pm
}

TEST_CASE("just woke up is mid range") {
    int bed = 1410;
    int wake = 440;
    int score = activity_at(470, bed, wake);     // 7:50, 30 min after wake
    REQUIRE(score > 25);
    REQUIRE(score < 75);
}

TEST_CASE("winding down before bed") {
    int bed = 1410;
    int wake = 440;
    int score = activity_at(1350, bed, wake);    // 22:30, 1hr before bed
    REQUIRE(score > 20);
    REQUIRE(score < 70);
}

TEST_CASE("midnight wrap works") {
    int bed = 60;     // 01:00 (late sleeper)
    int wake = 540;   // 09:00
    REQUIRE(activity_at(0, bed, wake) > 20);     // midnight, still up
    REQUIRE(activity_at(180, bed, wake) < 15);   // 3am, asleep
    REQUIRE(activity_at(720, bed, wake) > 80);   // noon, peak
}

TEST_CASE("afternoon dip") {
    int bed = 1410;   // 23:30
    int wake = 440;   // 07:20
    int peak = activity_at(660, bed, wake);       // 11am
    int dip = activity_at(920, bed, wake);         // ~8hrs after wake
    REQUIRE(dip < peak);
    REQUIRE(dip >= 75);
    REQUIRE(dip <= 80);
}

TEST_CASE("age offset shifts bedtime later for young") {
    int base = 1410;  // 23:30
    int shifted = apply_age_offset(base, 20);
    REQUIRE(shifted < 60);
}

TEST_CASE("age offset shifts bedtime earlier for old") {
    int base = 1410;
    int shifted = apply_age_offset(base, 70);
    REQUIRE(shifted < base);
}

TEST_CASE("age offset wraps around midnight") {
    int base = 1420;  // 23:40
    int shifted = apply_age_offset(base, 20);
    REQUIRE(shifted < 60);
}
