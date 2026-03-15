#include <catch2/catch_test_macros.hpp>
#include "wakefulness.h"
#include "availability.h"

SleepCurveConfig cfg = {
    45, 25, 12, 8, 90, 10, 25,
    12, 30, 70, 25, 90,
    85, 85, 45, 92, 25,
    90, 45, 60, 52, 75
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
    REQUIRE(awake_score(720, 60, 540, &cfg) > 75);
}

TEST_CASE("afternoon dip") {
    int peak = awake_score(660, 1410, 440, &cfg);
    int dip = awake_score(920, 1410, 440, &cfg);
    REQUIRE(dip < peak);
}

TEST_CASE("age offset shifts bedtime later for young") {
    int shifted = shift_for_age(1410, 20);
    REQUIRE(shifted < 60);
}

TEST_CASE("age offset shifts bedtime earlier for old") {
    int shifted = shift_for_age(1410, 70);
    REQUIRE(shifted < 1410);
}

TEST_CASE("age offset wraps around midnight") {
    int shifted = shift_for_age(1420, 20);
    REQUIRE(shifted < 60);
}

TEST_CASE("age responsiveness caps older people") {
    REQUIRE(age_responsiveness(90, 20) == 90);
    REQUIRE(age_responsiveness(90, 70) == 75);
}
