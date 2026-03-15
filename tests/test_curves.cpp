#include <catch2/catch_test_macros.hpp>
#include "wakefulness.h"
#include "availability.h"

SleepCurveConfig cfg = {
    45, 25, 12, 8, 45, 90, 10, 25,
    15, 28, 70, 30, 88,
    90, 85, 40, 97, 25,
    88, 48, 58, 53, 76
};

TEST_CASE("deep sleep returns low score") {
    REQUIRE(awake_score(180, 1410, 440, &cfg) < 15);
}

TEST_CASE("peak hours return high score") {
    REQUIRE(awake_score(780, 1410, 440, &cfg) > 80);
}

TEST_CASE("just woke up is mid range") {
    int score = awake_score(470, 1410, 440, &cfg);
    REQUIRE(score > 25);
    REQUIRE(score < 75);
}

TEST_CASE("winding down before bed") {
    int score = awake_score(1350, 1410, 440, &cfg);
    REQUIRE(score > 20);
    REQUIRE(score < 70);
}

TEST_CASE("midnight wrap works") {
    REQUIRE(awake_score(0, 60, 540, &cfg) > 20);
    REQUIRE(awake_score(180, 60, 540, &cfg) < 15);
    REQUIRE(awake_score(720, 60, 540, &cfg) > 70);
}

TEST_CASE("afternoon dip exists") {
    int dip = awake_score(960, 1410, 440, &cfg);
    REQUIRE(dip < cfg.peak_score);
}

TEST_CASE("age offset shifts bedtime later") {
    int shifted = shift_for_age(1410, 50);
    REQUIRE(shifted < 60);
}

TEST_CASE("age offset shifts bedtime earlier") {
    int shifted = shift_for_age(1410, -60);
    REQUIRE(shifted < 1410);
}

TEST_CASE("age offset wraps around midnight") {
    int shifted = shift_for_age(1420, 50);
    REQUIRE(shifted < 60);
}

TEST_CASE("work busy factor during work") {
    REQUIRE(work_busy_factor(600, 540, 1020) == 40);
    REQUIRE(work_busy_factor(480, 540, 1020) == 100);
}
