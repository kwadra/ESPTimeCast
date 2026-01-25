# Quick Start Guide for Running Tests

## Setup

### 1. Install PlatformIO CLI (if not already installed)
```bash
pip install platformio
```

### 2. Navigate to project
```bash
cd $HOME/git/ESPTimeCast
```

## Running Tests

### Run All Tests
```bash
pio test -e native
```

### Run Specific Test Suite
```bash
# Time functions only
pio test -e native --filter test_time_functions

# Countdown logic only
pio test -e native --filter test_countdown_logic

# Brightness/dimming only
pio test -e native --filter test_brightness_dimming

# Weather parsing only
pio test -e native --filter test_weather_parsing

# Utilities only
pio test -e native --filter test_utilities
```

### Verbose Output
```bash
pio test -e native -vv
```

### Run and Keep Output
```bash
pio test -e native 2>&1 | tee test_output.log
```

## Test Files Overview

| File | Tests | Coverage |
|------|-------|----------|
| `test_time_functions.cpp` | 14 | Timezones, formatting, NTP |
| `test_countdown_logic.cpp` | 16 | Countdown math, state, thresholds |
| `test_brightness_dimming.cpp` | 20 | Brightness calc, dimming schedules |
| `test_weather_parsing.cpp` | 23 | JSON parsing, temperature, humidity |
| `test_utilities.cpp` | 22 | String utilities, formatting, modes |
| **Total** | **95** | Core business logic |

## Adding New Tests

### 1. Add test function to appropriate file
```cpp
void test_my_new_feature() {
  // Setup
  int value = 42;
  
  // Execute
  int result = my_function(value);
  
  // Assert
  TEST_ASSERT_EQUAL(42, result);
}
```

### 2. Add to run function at bottom of file
```cpp
void run_my_test_suite() {
  RUN_TEST(test_my_new_feature);
}
```

### 3. Add to test_main.cpp
```cpp
void run_my_test_suite();  // Add declaration

// In main():
printf("\nRunning My Test Suite...\n");
run_my_test_suite();
```

## Common Assertions

| Assertion | Usage |
|-----------|-------|
| `TEST_ASSERT_EQUAL(expected, actual)` | Integer/value equality |
| `TEST_ASSERT_EQUAL_STRING(expected, actual)` | String equality |
| `TEST_ASSERT_EQUAL_FLOAT(expected, actual)` | Float equality |
| `TEST_ASSERT_TRUE(condition)` | Boolean true |
| `TEST_ASSERT_FALSE(condition)` | Boolean false |
| `TEST_ASSERT_NULL(pointer)` | Pointer is NULL |
| `TEST_ASSERT_NOT_NULL(pointer)` | Pointer is not NULL |
| `TEST_ASSERT(condition)` | Generic condition |

## CI/CD Integration

### GitHub Actions Example
```yaml
name: Unit Tests
on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - uses: actions/setup-python@v2
      - run: pip install platformio
      - run: cd ESPTimeCast && pio test -e native
```

## Troubleshooting

### Tests not found
```bash
# Clean build
pio test -e native --target clean
pio test -e native
```

### Compilation errors
```bash
# Check for issues
pio test -e native -vv
```

### All tests fail
```bash
# Verify test environment exists
pio platform list
# Should include: native
```

## Test Report

After running tests, you'll see a summary:
```
========================================
ESPTimeCast Unit Test Suite
========================================

Running Time Function Tests...
...

========================================
Test Suite Complete
========================================
```

Total test count: **95 tests**
- Time Functions: 14
- Countdown Logic: 16  
- Brightness/Dimming: 20
- Weather Parsing: 23
- Utilities: 22
