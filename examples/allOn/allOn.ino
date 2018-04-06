#include <MAX6958Breakout.h>

MAX6958Breakout leds;
void setup() {
  //Available functions:
  //    init() - Must be called first. Sets up Wire library and brings chip out of sleep mode
  //    clear() - Clears out all data, turning all LEDs off
  //    setChannel(uint8_t LEDAddr, bool On)  - Sets the LED at address LEDAddr (1 - 36, or 255 for all) to value On (true/false). Values of LEDAddr at 0 or higher than 36 will be ignored and return code OUTOFRANGE (which is 0x05), will be sent back.
  //    setBrightness(uint8_t Bri) - Sets the global brightness of all LED channels to Bri (0 to 63, higher values will be clamped to 63)
  
  leds.init();
  byte returnCode = leds.setChannel(255, true); //Set all LED channels to ON
}

void loop() {
  
  
}
