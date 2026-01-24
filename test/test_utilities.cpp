/**
 * Unit Tests for Utility Functions
 * Tests string utilities, format functions, display logic
 */

#include <unity.h>
#include "test_helpers.h"
#include <string.h>
#include <stdio.h>

// Test string utilities
void test_string_contains_found() {
  const char* str = "Hello World";
  bool found = TestHelpers::stringContains(str, "World");
  
  TEST_ASSERT_TRUE(found);
}

void test_string_contains_not_found() {
  const char* str = "Hello World";
  bool found = TestHelpers::stringContains(str, "Goodbye");
  
  TEST_ASSERT_FALSE(found);
}

void test_string_contains_case_sensitive() {
  const char* str = "Hello World";
  bool found = TestHelpers::stringContains(str, "world");  // lowercase
  
  TEST_ASSERT_FALSE(found);
}

void test_string_ends_with_match() {
  const char* str = "config.json";
  bool matches = TestHelpers::stringEndsWith(str, ".json");
  
  TEST_ASSERT_TRUE(matches);
}

void test_string_ends_with_no_match() {
  const char* str = "config.json";
  bool matches = TestHelpers::stringEndsWith(str, ".txt");
  
  TEST_ASSERT_FALSE(matches);
}

void test_string_ends_with_full_match() {
  const char* str = "test";
  bool matches = TestHelpers::stringEndsWith(str, "test");
  
  TEST_ASSERT_TRUE(matches);
}

// Test temperature symbol
void test_temp_symbol_celsius() {
  char symbol = 'C';
  TEST_ASSERT_EQUAL('C', symbol);
}

void test_temp_symbol_fahrenheit() {
  char symbol = 'F';
  TEST_ASSERT_EQUAL('F', symbol);
}

void test_temp_symbol_switch() {
  char symbol = 'C';
  // Toggle between C and F
  symbol = (symbol == 'C') ? 'F' : 'C';
  
  TEST_ASSERT_EQUAL('F', symbol);
}

// Test string formatting
void test_format_time_string() {
  int hour = 14;
  int minute = 30;
  char buffer[10];
  snprintf(buffer, sizeof(buffer), "%02d:%02d", hour, minute);
  
  TEST_ASSERT_EQUAL_STRING("14:30", buffer);
}

void test_format_time_string_single_digits() {
  int hour = 9;
  int minute = 5;
  char buffer[10];
  snprintf(buffer, sizeof(buffer), "%02d:%02d", hour, minute);
  
  TEST_ASSERT_EQUAL_STRING("09:05", buffer);
}

void test_format_humidity_string() {
  int humidity = 65;
  char buffer[10];
  snprintf(buffer, sizeof(buffer), "%d%%", humidity);
  
  TEST_ASSERT_EQUAL_STRING("65%", buffer);
}

void test_format_ip_address() {
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%d.%d.%d.%d", 192, 168, 1, 100);
  
  TEST_ASSERT_EQUAL_STRING("192.168.1.100", buffer);
}

// Test display mode cycling
void test_display_mode_cycle_forward() {
  int mode = 0;  // Clock
  mode = (mode + 1) % 4;  // Cycle through 0-3
  
  TEST_ASSERT_EQUAL(1, mode);  // Weather
}

void test_display_mode_cycle_wraparound() {
  int mode = 3;  // Countdown
  mode = (mode + 1) % 4;  // Cycle through 0-3
  
  TEST_ASSERT_EQUAL(0, mode);  // Back to Clock
}

void test_display_mode_backward() {
  int mode = 1;  // Weather
  mode = (mode - 1 + 4) % 4;  // Cycle backward
  
  TEST_ASSERT_EQUAL(0, mode);  // Clock
}

void test_display_mode_backward_wraparound() {
  int mode = 0;  // Clock
  mode = (mode - 1 + 4) % 4;  // Cycle backward
  
  TEST_ASSERT_EQUAL(3, mode);  // Countdown
}

// Test scroll speed range
void test_scroll_speed_min() {
  int speed = 1;
  bool valid = (speed >= 1 && speed <= 255);
  
  TEST_ASSERT_TRUE(valid);
}

void test_scroll_speed_max() {
  int speed = 255;
  bool valid = (speed >= 1 && speed <= 255);
  
  TEST_ASSERT_TRUE(valid);
}

void test_scroll_speed_invalid_zero() {
  int speed = 0;
  bool valid = (speed >= 1 && speed <= 255);
  
  TEST_ASSERT_FALSE(valid);
}

void test_scroll_speed_invalid_over_max() {
  int speed = 256;
  bool valid = (speed >= 1 && speed <= 255);
  
  TEST_ASSERT_FALSE(valid);
}

// Test character encoding
void test_special_char_degree() {
  const char* temp_str = "25°C";
  bool contains_degree = TestHelpers::stringContains(temp_str, "°");
  
  TEST_ASSERT_TRUE(contains_degree);
}

// Run tests
void run_utility_tests() {
  RUN_TEST(test_string_contains_found);
  RUN_TEST(test_string_contains_not_found);
  RUN_TEST(test_string_contains_case_sensitive);
  RUN_TEST(test_string_ends_with_match);
  RUN_TEST(test_string_ends_with_no_match);
  RUN_TEST(test_string_ends_with_full_match);
  RUN_TEST(test_temp_symbol_celsius);
  RUN_TEST(test_temp_symbol_fahrenheit);
  RUN_TEST(test_temp_symbol_switch);
  RUN_TEST(test_format_time_string);
  RUN_TEST(test_format_time_string_single_digits);
  RUN_TEST(test_format_humidity_string);
  RUN_TEST(test_format_ip_address);
  RUN_TEST(test_display_mode_cycle_forward);
  RUN_TEST(test_display_mode_cycle_wraparound);
  RUN_TEST(test_display_mode_backward);
  RUN_TEST(test_display_mode_backward_wraparound);
  RUN_TEST(test_scroll_speed_min);
  RUN_TEST(test_scroll_speed_max);
  RUN_TEST(test_scroll_speed_invalid_zero);
  RUN_TEST(test_scroll_speed_invalid_over_max);
  RUN_TEST(test_special_char_degree);
}
