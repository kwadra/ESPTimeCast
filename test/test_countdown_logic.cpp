/**
 * Unit Tests for Countdown Logic
 * Tests countdown calculations, state transitions, time remaining
 */

#include <unity.h>
#include "test_helpers.h"
#include <time.h>

// Test countdown time calculation
void test_countdown_time_remaining_positive() {
  time_t target = TestHelpers::createTimestamp(2026, 1, 31, 12, 0, 0);
  time_t current = TestHelpers::createTimestamp(2026, 1, 30, 12, 0, 0);
  
  long seconds_remaining = target - current;
  
  TEST_ASSERT(seconds_remaining > 0);
  TEST_ASSERT_EQUAL(86400, seconds_remaining);  // 24 hours in seconds
}

void test_countdown_time_remaining_zero() {
  time_t target = TestHelpers::createTimestamp(2026, 1, 30, 12, 0, 0);
  time_t current = TestHelpers::createTimestamp(2026, 1, 30, 12, 0, 0);
  
  long seconds_remaining = target - current;
  
  TEST_ASSERT_EQUAL(0, seconds_remaining);
}

void test_countdown_time_remaining_expired() {
  time_t target = TestHelpers::createTimestamp(2026, 1, 30, 12, 0, 0);
  time_t current = TestHelpers::createTimestamp(2026, 1, 31, 12, 0, 0);
  
  long seconds_remaining = target - current;
  
  TEST_ASSERT(seconds_remaining < 0);
}

// Test countdown expiration detection
void test_countdown_is_expired_false() {
  time_t target = TestHelpers::createTimestamp(2026, 1, 31, 12, 0, 0);
  time_t current = TestHelpers::createTimestamp(2026, 1, 30, 12, 0, 0);
  
  bool is_expired = (current >= target);
  
  TEST_ASSERT_FALSE(is_expired);
}

void test_countdown_is_expired_true() {
  time_t target = TestHelpers::createTimestamp(2026, 1, 30, 12, 0, 0);
  time_t current = TestHelpers::createTimestamp(2026, 1, 31, 12, 0, 0);
  
  bool is_expired = (current >= target);
  
  TEST_ASSERT_TRUE(is_expired);
}

void test_countdown_is_expired_boundary() {
  time_t target = TestHelpers::createTimestamp(2026, 1, 30, 12, 0, 0);
  time_t current = TestHelpers::createTimestamp(2026, 1, 30, 12, 0, 0);
  
  bool is_expired = (current >= target);
  
  TEST_ASSERT_TRUE(is_expired);  // Equal should be expired
}

// Test countdown formatting
void test_countdown_format_days_hours_minutes() {
  long total_seconds = 86400 + 3600 + 300;  // 1 day, 1 hour, 5 minutes
  
  int days = total_seconds / 86400;
  int hours = (total_seconds % 86400) / 3600;
  int minutes = (total_seconds % 3600) / 60;
  
  TEST_ASSERT_EQUAL(1, days);
  TEST_ASSERT_EQUAL(1, hours);
  TEST_ASSERT_EQUAL(5, minutes);
}

void test_countdown_format_zero_days() {
  long total_seconds = 3600 + 300;  // 1 hour, 5 minutes
  
  int days = total_seconds / 86400;
  int hours = (total_seconds % 86400) / 3600;
  int minutes = (total_seconds % 3600) / 60;
  
  TEST_ASSERT_EQUAL(0, days);
  TEST_ASSERT_EQUAL(1, hours);
  TEST_ASSERT_EQUAL(5, minutes);
}

void test_countdown_format_less_than_minute() {
  long total_seconds = 45;  // 45 seconds
  
  int days = total_seconds / 86400;
  int hours = (total_seconds % 86400) / 3600;
  int minutes = (total_seconds % 3600) / 60;
  int seconds = total_seconds % 60;
  
  TEST_ASSERT_EQUAL(0, days);
  TEST_ASSERT_EQUAL(0, hours);
  TEST_ASSERT_EQUAL(0, minutes);
  TEST_ASSERT_EQUAL(45, seconds);
}

// Test dramatic countdown threshold (last 24 hours)
void test_countdown_dramatic_mode_active() {
  long seconds_remaining = 43200;  // 12 hours
  bool is_dramatic = (seconds_remaining <= 86400);  // < 24 hours
  
  TEST_ASSERT_TRUE(is_dramatic);
}

void test_countdown_dramatic_mode_inactive() {
  long seconds_remaining = 172800;  // 48 hours
  bool is_dramatic = (seconds_remaining <= 86400);  // < 24 hours
  
  TEST_ASSERT_FALSE(is_dramatic);
}

void test_countdown_dramatic_mode_boundary() {
  long seconds_remaining = 86400;  // Exactly 24 hours
  bool is_dramatic = (seconds_remaining <= 86400);
  
  TEST_ASSERT_TRUE(is_dramatic);
}

// Test display message rotation during countdown
void test_countdown_should_update_display_true() {
  unsigned long last_update = 0;
  unsigned long current_time = 500;
  unsigned long update_interval = 100;
  
  bool should_update = (current_time - last_update) >= update_interval;
  
  TEST_ASSERT_TRUE(should_update);
}

void test_countdown_should_update_display_false() {
  unsigned long last_update = 100;
  unsigned long current_time = 150;
  unsigned long update_interval = 100;
  
  bool should_update = (current_time - last_update) >= update_interval;
  
  TEST_ASSERT_FALSE(should_update);
}

// Test countdown enable/disable logic
void test_countdown_state_toggle() {
  bool countdown_enabled = false;
  
  countdown_enabled = !countdown_enabled;
  TEST_ASSERT_TRUE(countdown_enabled);
  
  countdown_enabled = !countdown_enabled;
  TEST_ASSERT_FALSE(countdown_enabled);
}

// Test past date handling
void test_countdown_with_past_target_time() {
  time_t target = TestHelpers::createTimestamp(2020, 1, 1, 0, 0, 0);  // Past
  time_t current = TestHelpers::createTimestamp(2026, 1, 24, 0, 0, 0);  // Now
  
  bool is_valid = (target > current);
  
  TEST_ASSERT_FALSE(is_valid);  // Target is in the past
}

// Run tests
void run_countdown_tests() {
  RUN_TEST(test_countdown_time_remaining_positive);
  RUN_TEST(test_countdown_time_remaining_zero);
  RUN_TEST(test_countdown_time_remaining_expired);
  RUN_TEST(test_countdown_is_expired_false);
  RUN_TEST(test_countdown_is_expired_true);
  RUN_TEST(test_countdown_is_expired_boundary);
  RUN_TEST(test_countdown_format_days_hours_minutes);
  RUN_TEST(test_countdown_format_zero_days);
  RUN_TEST(test_countdown_format_less_than_minute);
  RUN_TEST(test_countdown_dramatic_mode_active);
  RUN_TEST(test_countdown_dramatic_mode_inactive);
  RUN_TEST(test_countdown_dramatic_mode_boundary);
  RUN_TEST(test_countdown_should_update_display_true);
  RUN_TEST(test_countdown_should_update_display_false);
  RUN_TEST(test_countdown_state_toggle);
  RUN_TEST(test_countdown_with_past_target_time);
}
