#include <Arduino.h>
#include <module/hc595.h>

HC595 ic(10, 13, 11, 2);
void setup()
{
  Serial.begin(9600);
  //-----test 2 ic 595-------
  // pinMode(10, 1);
  // pinMode(11, 1);
  // pinMode(13, 1);
  // digitalWrite(10, 0);
  // shiftOut(11, 13, MSBFIRST, 0b11111111);
  // shiftOut(11, 13, MSBFIRST, 0b11111111);
  // digitalWrite(10, 1);
  //-----end-------------

  ic.bat_chan(16);
}
void loop()
{
  for (int i = 1; i <= 16; i++)
  {
    Serial.println(i);
    ic.bat_chan(i);
    delay(300);
  }
  for (int i = 16; i > 0; i--)
  {
    Serial.println(i);
    ic.bat_chan(i);
    delay(300);
  }
}