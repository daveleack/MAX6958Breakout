#include "MAX6958Breakout.h"
#include <Wire.h>
#define OUTOFRANGE 5
#define MAX6958Address 0x38

uint8_t _memCache[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
static const unsigned char MAX6958Breakout::_portAddressData[5] = {0x20,0x21,0x22,0x23,0x24};
static const unsigned char MAX6958Breakout::_pinToPortData[36] = {0, 0, 0, 0, 0, 0, 0, 4, 1, 1, 1 ,1 ,1 ,1 ,1 ,4 ,2, 2, 2, 2, 2, 2, 2, 4, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4};
static const unsigned char MAX6958Breakout::_pinToBitData[36] =  {6, 5, 4, 3, 2, 1, 0, 0, 6, 5, 4, 3, 2, 1, 0, 1, 6, 5, 4, 3, 2, 1, 0, 2, 6, 5, 4, 3, 2, 1, 0, 3, 4, 6, 5, 7};
static const unsigned char* MAX6958Breakout::_portAddress;
static const unsigned char* MAX6958Breakout::_pinToPort;
static const unsigned char* MAX6958Breakout::_pinToBit;
MAX6958Breakout::MAX6958Breakout()
{
	_portAddress = _portAddressData;
	_pinToPort = _pinToPortData;
	_pinToBit = _pinToBitData;
}  
void MAX6958Breakout::init(void)
{
Wire.begin();
wake();
decodeOff();
setBrightness(32);
clear();
}  
void MAX6958Breakout::clear(void)
{
byte returnCode = 0;
Wire.beginTransmission(MAX6958Address);
Wire.write(0x20);                       //Starting LED register
Wire.write(0);                          //Sequentially write over all five with zeros
Wire.write(0);
Wire.write(0);
Wire.write(0);
Wire.write(0);
returnCode = Wire.endTransmission();
}
void MAX6958Breakout::decodeOff(void)
{
byte returnCode = 0;
Wire.beginTransmission(MAX6958Address);
Wire.write(0x01);                       //Select Decode register
Wire.write(0x00);                       //Write 0 to it
returnCode = Wire.endTransmission();
}
void MAX6958Breakout::wake(void)
{
byte returnCode = 0;
Wire.beginTransmission(MAX6958Address);
Wire.write(0x04);                       //Select config register
Wire.write(0x01);                       //Write 1 to it (0th bit is 0 for shutdown, 1 for wake)
returnCode = Wire.endTransmission();
}
byte MAX6958Breakout::setBrightness(byte bri)
{
byte returnCode = 0;
if(bri > 63)
{
  bri = 63;
}
Wire.beginTransmission(MAX6958Address);
Wire.write(0x02);                       //Select Global Intensity register
Wire.write(bri);                        //Write bri to it
returnCode = Wire.endTransmission();
return returnCode;
}
byte MAX6958Breakout::setChannel(uint8_t LEDAddr, bool on) //Set port at address to on or off (LEDAddr = 255 for ALL)
{
	byte returnCode = 0;
	
	if(LEDAddr == 255)
	{
	  Wire.beginTransmission(MAX6958Address);
	  Wire.write(0x20);
	  for(byte i = 0; i < 5; i ++)
	  {
		_memCache[i] = (on)? 0xFF:0x00;                                 //Clear or fill local copy of LED registers
		Wire.write(_memCache[i]);                                        //Write local to remote
	  }
	  returnCode = Wire.endTransmission();
	}
	else
	{
	  if((LEDAddr <= 36) & (LEDAddr > 0))
	  {
		Wire.beginTransmission(MAX6958Address);
		Wire.write(_portAddress[_pinToPort[LEDAddr - 1]]);
		if(on)
		{
		  uint8_t tmp = _memCache[_pinToPort[LEDAddr - 1]];
		  tmp |= (1 << _pinToBit[LEDAddr - 1]);    //Set bit in local copy of LED registers
		  Wire.write(tmp);                   //Write local to remote
		  _memCache[_pinToPort[LEDAddr - 1]] = tmp;
		}
		else
		{
		  uint8_t tmp = _memCache[_pinToPort[LEDAddr - 1]];
		  tmp &= ~(1 << _pinToBit[LEDAddr - 1]); //Set bit in local copy of LED registers
		  Wire.write(tmp);                   //Write local to remote
		  _memCache[_pinToPort[LEDAddr - 1]] = tmp;
		}
		returnCode = Wire.endTransmission();
	  }
	  else
	  {
		returnCode = OUTOFRANGE;
	  }
	}
	return returnCode;
}

void MAX6958Breakout::setRegVal(uint8_t reg, uint8_t val)
{
	Wire.beginTransmission(MAX6958Address);
	Wire.write(reg);
	Wire.write(val);
	Wire.endTransmission();
	
}