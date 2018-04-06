#ifndef MAX6958Breakout_h
#define MAX6958Breakout_h
#include <Arduino.h>

class MAX6958Breakout{
public:
  MAX6958Breakout(void);
  
  void init(void);                    //Join I2C bus as master and get MAX6958 ready (woken up, all LEDs off, half intensity)
  byte setBrightness(byte);       //Set global brightness 0 to 63
  byte setChannel(uint8_t, bool); //Set an individual channel on/off with LEDAddr 0-35, or all on/off with LEDAddr = 255
  void clear(void);               //Clear out all LED channels
  void decodeOff(void);           //Turn off Hex Decode mode
  void wake(void);                //Come out of shutdown
  void setRegVal(uint8_t, uint8_t);	//Adding this for debugging. Directly send byte to register address.
  static const unsigned char* _portAddress;
  static const unsigned char* _pinToPort;
  static const unsigned char* _pinToBit;
  static const unsigned char _portAddressData[5];            //LEDAddr -> _pinToPort -> Specific Register on MAX6958
  static const unsigned char _pinToPortData[36];         //LEDAddr -> _pinToPort -> Specific Register on MAX6958
  static const unsigned char _pinToBitData[36];          //LEDAddr -> _pinToBit -> Specific bit in Register on MAX6958
  uint8_t _memCache[5];              //Local copy of MAX6958 LED registers so we don't have to read it to clear a bit  
  
private:
  

};

#endif