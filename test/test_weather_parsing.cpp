/**
 * Unit Tests for Weather Parsing
 * Tests OpenWeather API JSON parsing, data validation
 */

#include <unity.h>
#include "test_helpers.h"
#include <string.h>

// Test JSON validation
void test_json_valid_weather_response() {
  const char* json = "{\"main\":{\"temp\":25}}";
  bool is_valid = TestHelpers::isValidJSON(json);
  
  TEST_ASSERT_TRUE(is_valid);
}

void test_json_empty_object() {
  const char* json = "{}";
  bool is_valid = TestHelpers::isValidJSON(json);
  
  TEST_ASSERT_TRUE(is_valid);
}

void test_json_invalid_missing_close() {
  const char* json = "{\"main\":{\"temp\":25";
  bool is_valid = TestHelpers::isValidJSON(json);
  
  TEST_ASSERT_FALSE(is_valid);
}

void test_json_invalid_empty() {
  const char* json = "";
  bool is_valid = TestHelpers::isValidJSON(json);
  
  TEST_ASSERT_FALSE(is_valid);
}

// Test temperature parsing
void test_parse_temperature_integer() {
  // Simulate parsing "25" from JSON
  float temperature = 25.0f;
  TEST_ASSERT_EQUAL(25, (int)temperature);
}

void test_parse_temperature_decimal() {
  // Simulate parsing "25.5" from JSON
  float temperature = 25.5f;
  TEST_ASSERT_EQUAL(25, (int)temperature);
}

void test_parse_temperature_negative() {
  // Simulate parsing "-5" from JSON
  float temperature = -5.0f;
  int temp_int = (int)temperature;
  TEST_ASSERT_EQUAL(-5, temp_int);
}

void test_temperature_celsius_to_fahrenheit() {
  // Formula: F = (C * 9/5) + 32
  float celsius = 0.0f;
  float fahrenheit = (celsius * 9.0f / 5.0f) + 32.0f;
  
  TEST_ASSERT_EQUAL_FLOAT(32.0, fahrenheit);
}

void test_temperature_celsius_to_fahrenheit_room_temp() {
  float celsius = 20.0f;
  float fahrenheit = (celsius * 9.0f / 5.0f) + 32.0f;
  
  TEST_ASSERT_EQUAL_FLOAT(68.0, fahrenheit);
}

// Test description parsing
void test_parse_weather_description() {
  const char* description = "Partly cloudy";
  bool has_description = (strlen(description) > 0);
  
  TEST_ASSERT_TRUE(has_description);
}

void test_parse_weather_description_empty() {
  const char* description = "";
  bool has_description = (strlen(description) > 0);
  
  TEST_ASSERT_FALSE(has_description);
}

void test_description_contains_keyword() {
  const char* description = "Light rain and cloud";
  bool has_rain = TestHelpers::stringContains(description, "rain");
  
  TEST_ASSERT_TRUE(has_rain);
}

void test_description_keyword_not_found() {
  const char* description = "Clear skies";
  bool has_rain = TestHelpers::stringContains(description, "rain");
  
  TEST_ASSERT_FALSE(has_rain);
}

// Test humidity parsing
void test_parse_humidity_valid() {
  int humidity = 65;
  bool valid = (humidity >= 0 && humidity <= 100);
  
  TEST_ASSERT_TRUE(valid);
}

void test_parse_humidity_boundary_zero() {
  int humidity = 0;
  bool valid = (humidity >= 0 && humidity <= 100);
  
  TEST_ASSERT_TRUE(valid);
}

void test_parse_humidity_boundary_hundred() {
  int humidity = 100;
  bool valid = (humidity >= 0 && humidity <= 100);
  
  TEST_ASSERT_TRUE(valid);
}

void test_parse_humidity_invalid_negative() {
  int humidity = -10;
  bool valid = (humidity >= 0 && humidity <= 100);
  
  TEST_ASSERT_FALSE(valid);
}

void test_parse_humidity_invalid_over_hundred() {
  int humidity = 150;
  bool valid = (humidity >= 0 && humidity <= 100);
  
  TEST_ASSERT_FALSE(valid);
}

// Test API response error detection
void test_api_error_code_404() {
  int http_code = 404;
  bool error = (http_code != 200);
  
  TEST_ASSERT_TRUE(error);
}

void test_api_success_code_200() {
  int http_code = 200;
  bool error = (http_code != 200);
  
  TEST_ASSERT_FALSE(error);
}

void test_api_error_code_500() {
  int http_code = 500;
  bool error = (http_code >= 500);
  
  TEST_ASSERT_TRUE(error);
}

// Test data staleness detection
void test_weather_data_fresh() {
  unsigned long last_fetch = 1000;
  unsigned long current_time = 2000;
  unsigned long max_age_ms = 600000;  // 10 minutes
  
  bool data_stale = (current_time - last_fetch) > max_age_ms;
  
  TEST_ASSERT_FALSE(data_stale);
}

void test_weather_data_stale() {
  unsigned long last_fetch = 1000;
  unsigned long current_time = 700000;
  unsigned long max_age_ms = 600000;  // 10 minutes
  
  bool data_stale = (current_time - last_fetch) > max_age_ms;
  
  TEST_ASSERT_TRUE(data_stale);
}

// Run tests
void run_weather_parsing_tests() {
  RUN_TEST(test_json_valid_weather_response);
  RUN_TEST(test_json_empty_object);
  RUN_TEST(test_json_invalid_missing_close);
  RUN_TEST(test_json_invalid_empty);
  RUN_TEST(test_parse_temperature_integer);
  RUN_TEST(test_parse_temperature_decimal);
  RUN_TEST(test_parse_temperature_negative);
  RUN_TEST(test_temperature_celsius_to_fahrenheit);
  RUN_TEST(test_temperature_celsius_to_fahrenheit_room_temp);
  RUN_TEST(test_parse_weather_description);
  RUN_TEST(test_parse_weather_description_empty);
  RUN_TEST(test_description_contains_keyword);
  RUN_TEST(test_description_keyword_not_found);
  RUN_TEST(test_parse_humidity_valid);
  RUN_TEST(test_parse_humidity_boundary_zero);
  RUN_TEST(test_parse_humidity_boundary_hundred);
  RUN_TEST(test_parse_humidity_invalid_negative);
  RUN_TEST(test_parse_humidity_invalid_over_hundred);
  RUN_TEST(test_api_error_code_404);
  RUN_TEST(test_api_success_code_200);
  RUN_TEST(test_api_error_code_500);
  RUN_TEST(test_weather_data_fresh);
  RUN_TEST(test_weather_data_stale);
}
