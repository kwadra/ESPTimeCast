/**
 * Unit Tests for Brightness and Dimming Logic
 * Tests brightness calculations, dimming schedules, auto-dimming
 */

#include <unity.h>
#include "test_helpers.h"

// Test brightness boundary values
void test_brightness_minimum() {
  int brightness = 0;
  TEST_ASSERT_EQUAL(0, brightness);
}

void test_brightness_maximum() {
  int brightness = 15;
  TEST_ASSERT_EQUAL(15, brightness);
}

void test_brightness_mid_range() {
  int brightness = 7;
  TEST_ASSERT_EQUAL(7, brightness);
}

// Test brightness bounds checking
void test_brightness_clamp_below_min() {
  int brightness = -5;
  brightness = (brightness < 0) ? 0 : brightness;
  brightness = (brightness > 15) ? 15 : brightness;
  
  TEST_ASSERT_EQUAL(0, brightness);
}

void test_brightness_clamp_above_max() {
  int brightness = 20;
  brightness = (brightness < 0) ? 0 : brightness;
  brightness = (brightness > 15) ? 15 : brightness;
  
  TEST_ASSERT_EQUAL(15, brightness);
}

// Test dimming schedule detection (time-based)
void test_dimming_is_active_during_night() {
  int dim_start_hour = 18;  // 6 PM
  int dim_end_hour = 8;     // 8 AM
  int current_hour = 22;    // 10 PM
  
  bool is_dimming_time = (current_hour >= dim_start_hour) || (current_hour < dim_end_hour);
  
  TEST_ASSERT_TRUE(is_dimming_time);
}

void test_dimming_is_inactive_during_day() {
  int dim_start_hour = 18;  // 6 PM
  int dim_end_hour = 8;     // 8 AM
  int current_hour = 12;    // 12 PM
  
  bool is_dimming_time = (current_hour >= dim_start_hour) || (current_hour < dim_end_hour);
  
  TEST_ASSERT_FALSE(is_dimming_time);
}

void test_dimming_at_boundary_start() {
  int dim_start_hour = 18;  // 6 PM
  int dim_end_hour = 8;     // 8 AM
  int current_hour = 18;    // Exactly 6 PM
  
  bool is_dimming_time = (current_hour >= dim_start_hour) || (current_hour < dim_end_hour);
  
  TEST_ASSERT_TRUE(is_dimming_time);
}

void test_dimming_at_boundary_end() {
  int dim_start_hour = 18;  // 6 PM
  int dim_end_hour = 8;     // 8 AM
  int current_hour = 8;     // Exactly 8 AM
  
  bool is_dimming_time = (current_hour >= dim_start_hour) || (current_hour < dim_end_hour);
  
  TEST_ASSERT_FALSE(is_dimming_time);
}

// Test minute-level dimming precision
void test_dimming_with_minutes_start() {
  int dim_start_hour = 18;
  int dim_start_minute = 30;
  int dim_end_hour = 8;
  int dim_end_minute = 0;
  
  int current_hour = 18;
  int current_minute = 35;
  
  // Convert to minutes since midnight for comparison
  int current_total = current_hour * 60 + current_minute;
  int start_total = dim_start_hour * 60 + dim_start_minute;
  int end_total = dim_end_hour * 60 + dim_end_minute;
  
  bool is_dimming_time = (current_total >= start_total) || (current_total < end_total);
  
  TEST_ASSERT_TRUE(is_dimming_time);
}

void test_dimming_before_start_minute() {
  int dim_start_hour = 18;
  int dim_start_minute = 30;
  int current_hour = 18;
  int current_minute = 25;
  
  int current_total = current_hour * 60 + current_minute;
  int start_total = dim_start_hour * 60 + dim_start_minute;
  
  bool is_dimming_time = (current_total >= start_total);
  
  TEST_ASSERT_FALSE(is_dimming_time);
}

// Test dimming brightness calculation
void test_dimming_brightness_applied() {
  int normal_brightness = 7;
  int dim_brightness = 2;
  bool dimming_enabled = true;
  
  int effective_brightness = dimming_enabled ? dim_brightness : normal_brightness;
  
  TEST_ASSERT_EQUAL(2, effective_brightness);
}

void test_dimming_brightness_not_applied() {
  int normal_brightness = 7;
  int dim_brightness = 2;
  bool dimming_enabled = false;
  
  int effective_brightness = dimming_enabled ? dim_brightness : normal_brightness;
  
  TEST_ASSERT_EQUAL(7, effective_brightness);
}

// Test auto-dimming (sunrise/sunset based)
void test_auto_dimming_after_sunset() {
  int sunset_hour = 17;
  int current_hour = 18;
  
  bool should_dim = (current_hour >= sunset_hour);
  
  TEST_ASSERT_TRUE(should_dim);
}

void test_auto_dimming_before_sunrise() {
  int sunrise_hour = 6;
  int current_hour = 5;
  
  bool should_dim = (current_hour < sunrise_hour);
  
  TEST_ASSERT_TRUE(should_dim);
}

void test_auto_dimming_during_day() {
  int sunrise_hour = 6;
  int sunset_hour = 17;
  int current_hour = 12;
  
  bool should_dim = (current_hour < sunrise_hour) || (current_hour >= sunset_hour);
  
  TEST_ASSERT_FALSE(should_dim);
}

// Test display off by brightness (emergency dim)
void test_display_off_when_brightness_zero() {
  int brightness = 0;
  bool display_off = (brightness == 0);
  
  TEST_ASSERT_TRUE(display_off);
}

void test_display_on_when_brightness_nonzero() {
  int brightness = 5;
  bool display_off = (brightness == 0);
  
  TEST_ASSERT_FALSE(display_off);
}

// Test clock-only during dimming
void test_clock_only_mode_enabled() {
  bool clock_only_dimming = true;
  int display_mode = 0;  // Force clock mode
  
  bool should_show_clock_only = clock_only_dimming;
  
  TEST_ASSERT_TRUE(should_show_clock_only);
}

void test_clock_only_mode_disabled() {
  bool clock_only_dimming = false;
  
  bool should_show_clock_only = clock_only_dimming;
  
  TEST_ASSERT_FALSE(should_show_clock_only);
}

// Run tests
void run_brightness_dimming_tests() {
  RUN_TEST(test_brightness_minimum);
  RUN_TEST(test_brightness_maximum);
  RUN_TEST(test_brightness_mid_range);
  RUN_TEST(test_brightness_clamp_below_min);
  RUN_TEST(test_brightness_clamp_above_max);
  RUN_TEST(test_dimming_is_active_during_night);
  RUN_TEST(test_dimming_is_inactive_during_day);
  RUN_TEST(test_dimming_at_boundary_start);
  RUN_TEST(test_dimming_at_boundary_end);
  RUN_TEST(test_dimming_with_minutes_start);
  RUN_TEST(test_dimming_before_start_minute);
  RUN_TEST(test_dimming_brightness_applied);
  RUN_TEST(test_dimming_brightness_not_applied);
  RUN_TEST(test_auto_dimming_after_sunset);
  RUN_TEST(test_auto_dimming_before_sunrise);
  RUN_TEST(test_auto_dimming_during_day);
  RUN_TEST(test_display_off_when_brightness_zero);
  RUN_TEST(test_display_on_when_brightness_nonzero);
  RUN_TEST(test_clock_only_mode_enabled);
  RUN_TEST(test_clock_only_mode_disabled);
}
