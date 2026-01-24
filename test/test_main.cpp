/**
 * Main Test Runner
 * Runs all test suites for ESPTimeCast
 */

#include <unity.h>
#include <stdio.h>

// Forward declarations for test suites
void run_time_function_tests();
void run_countdown_tests();
void run_brightness_dimming_tests();
void run_weather_parsing_tests();
void run_utility_tests();

int main(int argc, char* argv[]) {
  UNITY_BEGIN();
  
  printf("\n========================================\n");
  printf("ESPTimeCast Unit Test Suite\n");
  printf("========================================\n\n");
  
  // Run all test suites
  printf("Running Time Function Tests...\n");
  run_time_function_tests();
  
  printf("\nRunning Countdown Logic Tests...\n");
  run_countdown_tests();
  
  printf("\nRunning Brightness & Dimming Tests...\n");
  run_brightness_dimming_tests();
  
  printf("\nRunning Weather Parsing Tests...\n");
  run_weather_parsing_tests();
  
  printf("\nRunning Utility Tests...\n");
  run_utility_tests();
  
  printf("\n========================================\n");
  int result = UNITY_END();
  printf("Test Suite Complete\n");
  printf("========================================\n\n");
  
  return result;
}
