# Test Reference & Examples

## Test Structure Template

Every test file follows this structure:

```cpp
/**
 * Unit Tests for [Feature Name]
 * Tests [what is being tested]
 */

#include <unity.h>
#include "test_helpers.h"

void setUp(void) {
  // Run before each test
  TestHelpers::resetMockState();
}

void tearDown(void) {
  // Run after each test
}

// Test group 1: Feature aspect
void test_feature_scenario_expected_result() {
  // Arrange
  int input = 5;
  
  // Act
  int result = function_under_test(input);
  
  // Assert
  TEST_ASSERT_EQUAL(10, result);
}

// More tests...

void run_my_tests() {
  RUN_TEST(test_feature_scenario_expected_result);
  // Add all tests here
}
```

## Common Test Patterns

### Testing a Calculation
```cpp
void test_countdown_time_remaining() {
  time_t target = 1000;      // Arrange
  time_t current = 600;
  
  long remaining = target - current;  // Act
  
  TEST_ASSERT_EQUAL(400, remaining);  // Assert
}
```

### Testing a Condition
```cpp
void test_dimming_is_active_at_night() {
  int hour = 22;             // Arrange
  int start = 18;
  int end = 8;
  
  bool active = (hour >= start) || (hour < end);  // Act
  
  TEST_ASSERT_TRUE(active);   // Assert
}
```

### Testing Boundary Values
```cpp
void test_brightness_boundary_min() {
  int brightness = 0;        // Arrange - minimum
  
  bool valid = (brightness >= 0 && brightness <= 15);  // Act
  
  TEST_ASSERT_TRUE(valid);    // Assert
}

void test_brightness_boundary_max() {
  int brightness = 15;       // Arrange - maximum
  
  bool valid = (brightness >= 0 && brightness <= 15);
  
  TEST_ASSERT_TRUE(valid);
}

void test_brightness_below_min() {
  int brightness = -1;       // Arrange - below minimum
  
  bool valid = (brightness >= 0 && brightness <= 15);
  
  TEST_ASSERT_FALSE(valid);   // Should be invalid
}
```

### Testing String Operations
```cpp
void test_string_contains() {
  const char* str = "Hello World";  // Arrange
  
  bool found = TestHelpers::stringContains(str, "World");  // Act
  
  TEST_ASSERT_TRUE(found);   // Assert
}

void test_string_equals() {
  char buffer[20];           // Arrange
  snprintf(buffer, sizeof(buffer), "%02d:%02d", 14, 30);
  
  // Assert
  TEST_ASSERT_EQUAL_STRING("14:30", buffer);
}
```

### Testing State Transitions
```cpp
void test_countdown_enable_toggle() {
  bool enabled = false;      // Arrange - initial state
  
  enabled = !enabled;        // Act - toggle
  
  TEST_ASSERT_TRUE(enabled); // Assert - new state
}

void test_display_mode_cycle() {
  int mode = 0;              // Arrange
  
  mode = (mode + 1) % 4;     // Act - cycle forward
  
  TEST_ASSERT_EQUAL(1, mode); // Assert
}
```

## Mock Usage

### Using Mock Time
```cpp
void setUp(void) {
  // Set mock time to Jan 1, 2026 midnight
  time_t test_time = TestHelpers::createTimestamp(2026, 1, 1, 0, 0, 0);
  MockFunctions::setCurrentTime(test_time);
}
```

### Using Mock WiFi State
```cpp
void test_with_wifi_connected() {
  MockFunctions::setWiFiConnected(true);
  
  // Test code assumes WiFi is connected
}

void test_with_wifi_disconnected() {
  MockFunctions::setWiFiConnected(false);
  
  // Test code assumes WiFi is disconnected
}
```

### Using Mock Filesystem
```cpp
void test_with_littlefs_available() {
  MockFunctions::setLittleFSAvailable(true);
  
  // Test code assumes filesystem is available
}
```

## Running Specific Tests

### Run All Time Function Tests
```bash
pio test -e native --filter test_time_functions
```

### Run Tests Matching Pattern
```bash
# All tests with "countdown" in name
pio test -e native --filter "*countdown*"

# All dimming-related tests
pio test -e native --filter "*dimming*"
```

### Run with Output Capture
```bash
pio test -e native 2>&1 | tee test_results.txt
```

## Assertion Reference

| Assertion | Example | Use For |
|-----------|---------|---------|
| `TEST_ASSERT_EQUAL` | `TEST_ASSERT_EQUAL(5, result)` | Integer/numeric equality |
| `TEST_ASSERT_EQUAL_INT` | `TEST_ASSERT_EQUAL_INT(5, x)` | Explicit int comparison |
| `TEST_ASSERT_EQUAL_STRING` | `TEST_ASSERT_EQUAL_STRING("5", str)` | String comparison |
| `TEST_ASSERT_EQUAL_FLOAT` | `TEST_ASSERT_EQUAL_FLOAT(5.0, f)` | Float comparison |
| `TEST_ASSERT_TRUE` | `TEST_ASSERT_TRUE(condition)` | Boolean true |
| `TEST_ASSERT_FALSE` | `TEST_ASSERT_FALSE(condition)` | Boolean false |
| `TEST_ASSERT` | `TEST_ASSERT(x > 0)` | Generic condition |
| `TEST_ASSERT_NOT_NULL` | `TEST_ASSERT_NOT_NULL(ptr)` | Pointer not null |
| `TEST_ASSERT_NULL` | `TEST_ASSERT_NULL(ptr)` | Pointer is null |

## Example: Complete Test Suite

```cpp
/**
 * Unit Tests for Custom Feature
 */

#include <unity.h>
#include "test_helpers.h"

void setUp(void) {
  TestHelpers::resetMockState();
}

void tearDown(void) {
}

// Test 1: Basic functionality
void test_feature_basic_operation() {
  int input = 10;
  int result = my_function(input);
  TEST_ASSERT_EQUAL(20, result);
}

// Test 2: Edge case
void test_feature_with_zero_input() {
  int input = 0;
  int result = my_function(input);
  TEST_ASSERT_EQUAL(0, result);
}

// Test 3: Error condition
void test_feature_with_negative_input() {
  int input = -5;
  int result = my_function(input);
  TEST_ASSERT_EQUAL(-10, result);
}

// Run function
void run_custom_feature_tests() {
  RUN_TEST(test_feature_basic_operation);
  RUN_TEST(test_feature_with_zero_input);
  RUN_TEST(test_feature_with_negative_input);
}
```

Then in `test_main.cpp`, add:
```cpp
extern void run_custom_feature_tests();

// In main():
printf("\nRunning Custom Feature Tests...\n");
run_custom_feature_tests();
```

## Tips for Effective Testing

1. **Test One Thing**: Each test should verify one behavior
2. **Use Clear Names**: Name should describe what and why
3. **Arrange-Act-Assert**: Structure with comments
4. **Test Boundaries**: Include min, max, and edge cases
5. **Test Errors**: Verify error conditions are handled
6. **Reset State**: Always reset mocks in setUp()
7. **Avoid Dependencies**: Tests should be independent
8. **Use Helpers**: Leverage TestHelpers for common operations
9. **Comment Why**: Explain the business logic being tested
10. **Keep Simple**: Write simple, readable test code

## Debugging Failed Tests

### See Detailed Output
```bash
pio test -e native -vv
```

### Run Single Test File
```bash
pio test -e native --filter test_time_functions -vv
```

### Check for Compilation Issues
```bash
pio test -e native --target clean
pio test -e native
```

### Common Issues

| Issue | Solution |
|-------|----------|
| "Test not found" | Make sure test runs in `run_*` function |
| Compilation error | Check includes and spelling |
| Assertion fails | Add debug output before assertion |
| Tests skip | Verify `RUN_TEST()` calls in runner |

---

For more information, see the documentation files in the test/ directory.
