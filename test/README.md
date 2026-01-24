# ESPTimeCast Unit Tests

## Overview
Comprehensive unit tests for the ESPTimeCast project using the **Unity** testing framework.

## Test Organization

### Test Suites
- `test_time_functions.cpp` - Time parsing, formatting, timezone handling
- `test_display_logic.cpp` - Display mode transitions, countdown calculations
- `test_config_management.cpp` - Configuration loading/saving, JSON parsing
- `test_weather_parsing.cpp` - OpenWeather API response parsing
- `test_brightness_dimming.cpp` - Brightness calculations, dimming schedules
- `test_countdown_logic.cpp` - Countdown calculations and state management
- `test_utilities.cpp` - String utilities, format functions

## Running Tests

### Prerequisites
```bash
pip install platformio
cd /Users/quadra/git/ESPTimeCast
```

### Run All Tests
```bash
pio test -e native
```

### Run Specific Test Suite
```bash
pio test -e native -f test_time_functions
```

### Run with Verbose Output
```bash
pio test -e native -v
```

## Test Conventions

1. **Test Naming**: `test_<feature>_<scenario>_<expected_result>`
   - Example: `test_countdown_with_past_time_should_show_expired`

2. **Assertions**: Use TEST_ASSERT_* macros from Unity
   - `TEST_ASSERT_EQUAL(expected, actual)`
   - `TEST_ASSERT_TRUE(condition)`
   - `TEST_ASSERT_FALSE(condition)`
   - `TEST_ASSERT_EQUAL_STRING(expected, actual)`

3. **Setup/Teardown**: Use `setUp()` and `tearDown()` for test initialization

## Coverage Goals
- Core logic: >80% coverage
- Display transitions
- Time calculations
- Configuration management
- Weather parsing
- Dimming algorithms

## CI/CD Integration
These tests can be run in GitHub Actions or other CI systems using:
```yaml
- name: Run Unit Tests
  run: pio test -e native
```
