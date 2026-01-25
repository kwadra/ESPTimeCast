# Major Changes since fork
Development is targeted toward the esp32 since I don't have any ESP8266's to test with.
Added unit tests and automated dependency management / builds using PlatformIO tools.

## Getting Started
1. Ensure Astral UV is installed. See https://docs.astral.sh/uv/getting-started/installation/ for platform-specific install. 
1. Clone project from github - ```git clone https://github.com/kwadra/ESPTimeCast.git```
1. Run ```cd ESPTimeCast && uv sync ```
1. Run build/upload via ```pio run -e XXX``` where XXX is currently esp32_s3 or esp32_c3 (see pio run --list-targets for all options)

## Unsupported ESP variants
To add additional ESP variants just add a new section to platformio.ini with your board details.
Then, update the relavent section at the top of ESPTimeCast_ESP32.ino with the matching 
CONFIG_IDF_TARGET_ESP32xx DEFINE for your target along with the correct PIN definitions. 

## Change log

1. PR#1 - Add unit tests,  Add PlatformIO as build tool, UV as python manager, Github unit test runner

