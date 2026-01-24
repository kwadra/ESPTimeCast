#pragma once
/**
 * Test Helpers and Mocks for ESPTimeCast
 * Provides mock implementations and utility functions for testing
 */

#include <string.h>
#include <time.h>

// Mock time functions
extern time_t g_current_time;

// Mock WiFi state
extern bool g_wifi_connected;
extern const char* g_wifi_ssid;

// Mock LittleFS state
extern bool g_littlefs_available;

// Utility functions for tests
namespace TestHelpers {
  // Time utilities
  time_t createTimestamp(int year, int month, int day, int hour, int minute, int second);
  
  // String utilities
  bool stringContains(const char* str, const char* substring);
  bool stringEndsWith(const char* str, const char* suffix);
  
  // JSON utilities
  bool isValidJSON(const char* json_str);
  
  // State reset
  void resetMockState();
}

// Mock implementations
namespace MockFunctions {
  void setCurrentTime(time_t t);
  void setWiFiConnected(bool connected);
  void setWiFiSSID(const char* ssid);
  void setLittleFSAvailable(bool available);
}
