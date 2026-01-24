/**
 * Test Helpers Implementation
 */

#include "test_helpers.h"
#include <string.h>
#include <time.h>
#include <unity.h>

// Global mock state
time_t g_current_time = 1609459200;  // 2021-01-01 00:00:00 UTC
bool g_wifi_connected = false;
const char* g_wifi_ssid = "";
bool g_littlefs_available = true;

// Unity setup/teardown - called once per test
void setUp(void) {
  TestHelpers::resetMockState();
}

void tearDown(void) {
}

namespace TestHelpers {
  time_t createTimestamp(int year, int month, int day, int hour, int minute, int second) {
    struct tm timeinfo = {};
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = hour;
    timeinfo.tm_min = minute;
    timeinfo.tm_sec = second;
    timeinfo.tm_isdst = 0;  // UTC
    return mktime(&timeinfo);
  }

  bool stringContains(const char* str, const char* substring) {
    if (!str || !substring) return false;
    return strstr(str, substring) != nullptr;
  }

  bool stringEndsWith(const char* str, const char* suffix) {
    if (!str || !suffix) return false;
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);
    if (suffix_len > str_len) return false;
    return strcmp(str + str_len - suffix_len, suffix) == 0;
  }

  bool isValidJSON(const char* json_str) {
    if (!json_str || strlen(json_str) < 2) return false;
    // Simple check: starts with { and ends with }
    return json_str[0] == '{' && json_str[strlen(json_str) - 1] == '}';
  }

  void resetMockState() {
    g_current_time = 1609459200;
    g_wifi_connected = false;
    g_wifi_ssid = "";
    g_littlefs_available = true;
  }
}

namespace MockFunctions {
  void setCurrentTime(time_t t) {
    g_current_time = t;
  }

  void setWiFiConnected(bool connected) {
    g_wifi_connected = connected;
  }

  void setWiFiSSID(const char* ssid) {
    g_wifi_ssid = ssid;
  }

  void setLittleFSAvailable(bool available) {
    g_littlefs_available = available;
  }
}
