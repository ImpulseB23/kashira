#include <cstdio>
#include <cstring>
#include <ctime>
#include "../src-tauri/blades/timeshift/curves.h"

struct Country {
    const char* code;
    const char* name;
    int bedtime;
    int waketime;
};

Country countries[] = {
    {"US", "United States", 1387, 440},
    {"GB", "United Kingdom", 1407, 453},
    {"CA", "Canada", 1400, 453},
    {"AU", "Australia", 1372, 433},
    {"NZ", "New Zealand", 1372, 431},
    {"JP", "Japan", 27, 429},
    {"KR", "South Korea", 5, 458},
    {"CN", "China", 32, 462},
    {"IN", "India", 12, 456},
    {"DE", "Germany", 1411, 445},
    {"FR", "France", 1428, 471},
    {"ES", "Spain", 1439, 485},
    {"IT", "Italy", 1430, 472},
    {"PT", "Portugal", 1, 502},
    {"NL", "Netherlands", 1414, 467},
    {"BE", "Belgium", 1417, 460},
    {"SE", "Sweden", 1405, 441},
    {"NO", "Norway", 1429, 463},
    {"DK", "Denmark", 1402, 439},
    {"FI", "Finland", 1412, 464},
    {"IE", "Ireland", 1419, 470},
    {"CH", "Switzerland", 1409, 433},
    {"AT", "Austria", 1404, 440},
    {"PL", "Poland", 1425, 445},
    {"CZ", "Czechia", 1409, 435},
    {"SK", "Slovakia", 1400, 438},
    {"HU", "Hungary", 1439, 442},
    {"RO", "Romania", 5, 481},
    {"GR", "Greece", 0, 505},
    {"RU", "Russia", 33, 486},
    {"TR", "Turkey", 0, 482},
    {"IL", "Israel", 1430, 474},
    {"AE", "UAE", 1437, 463},
    {"SA", "Saudi Arabia", 15, 507},
    {"TH", "Thailand", 1436, 444},
    {"SG", "Singapore", 12, 458},
    {"MY", "Malaysia", 5, 461},
    {"PH", "Philippines", 1430, 448},
    {"ID", "Indonesia", 1410, 415},
    {"TW", "Taiwan", 37, 476},
    {"HK", "Hong Kong", 11, 477},
    {"BR", "Brazil", 1425, 451},
    {"MX", "Mexico", 1416, 429},
    {"CO", "Colombia", 1421, 391},
    {"ZA", "South Africa", 1357, 384},
    {"EG", "Egypt", 0, 450},
    {"NG", "Nigeria", 1410, 390},
    {"KE", "Kenya", 1395, 390},
    {"UA", "Ukraine", 0, 471},
    {"PK", "Pakistan", 0, 435},
    {"AR", "Argentina", 0, 450},
};

int country_count = sizeof(countries) / sizeof(countries[0]);

int main() {
    char code[8];
    int age;

    printf("country code (e.g. US, DE, JP): ");
    scanf("%s", code);

    for (int i = 0; code[i]; i++)
        if (code[i] >= 'a' && code[i] <= 'z') code[i] -= 32;

    Country* match = nullptr;
    for (int i = 0; i < country_count; i++) {
        if (strcmp(countries[i].code, code) == 0) {
            match = &countries[i];
            break;
        }
    }

    if (!match) {
        printf("country not found\n");
        return 1;
    }

    printf("age: ");
    scanf("%d", &age);

    int bed = apply_age_offset(match->bedtime, age);
    int wake = apply_age_offset(match->waketime, age);

    time_t now = time(nullptr);
    struct tm* local = localtime(&now);
    int current = local->tm_hour * 60 + local->tm_min;

    int score = activity_at(current, bed, wake);

    printf("\n%s, age %d, %s\n", match->name, age, match->code);
    printf("adjusted bedtime:  %02d:%02d\n", bed / 60, bed % 60);
    printf("adjusted waketime: %02d:%02d\n", wake / 60, wake % 60);
    printf("current time:      %02d:%02d\n", local->tm_hour, local->tm_min);
    printf("activity score:    %d/100\n\n", score);

    for (int i = 0; i < score / 2; i++) printf("#");
    printf("\n");

    return 0;
}
