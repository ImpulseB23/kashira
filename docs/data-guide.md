# Data Contributions

You don't need to know how to code to contribute to Kashira. A lot of what makes the scoring accurate lives in JSON data files that anyone can edit.

## What you can help with

### Adding or fixing country data

`ito/countries.json` contains sleep data for every supported country. If your country is missing or the times feel wrong, you can fix it.

Each entry looks like this:

```json
{
  "code": "DE",
  "name": "Germany",
  "timezones": ["Europe/Berlin"],
  "bedtime": "23:31",
  "waketime": "07:25"
}
```

- `code` - two-letter country code (ISO 3166-1)
- `name` - country name in English
- `timezones` - list of IANA timezone identifiers (find yours at https://en.wikipedia.org/wiki/List_of_tz_database_time_zones)
- `bedtime` / `waketime` - average for the general adult population in 24h format

If your country has multiple timezones, list all of them. Users pick which one applies to them.

### Fixing age brackets

`ito/age_brackets.json` controls how much the sleep window shifts based on age. Offsets are in minutes - positive means later, negative means earlier.

```json
{ "min": 18, "max": 24, "bedtime_offset": 50, "waketime_offset": 55 }
```

This means 18-24 year olds go to bed ~50 minutes later and wake ~55 minutes later than the country average.

### Tuning the sleep curve

`ito/sleep_curve.json` controls the shape of the activity score throughout the day. This is more advanced - if you change a value, test it by running the app and checking if the scores feel realistic for different times.

### Reporting inaccurate scores

Even if you don't want to edit files, you can open an issue saying "I'm [age] in [country] and the score at [time] says [X] but I'm actually [awake/asleep/busy]." That helps us calibrate.

## How to submit

1. Fork the repo
2. Edit the JSON file
3. Open a pull request with a short description of what you changed and why
4. If you have a source for the data (study, article, survey), link it in the PR
