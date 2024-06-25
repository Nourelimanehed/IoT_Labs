#include <ADS1X15.h>

ADS1115 ADS(0x48);

void setup() {
  Serial.begin(9600);
  ADS.begin();
  ADS.setGain(0);
  ADS.setMode(1);
  ADS.setDataRate(7);
  ADS.readADC(0);
}

void loop() {
  int16_t tension_A0 = ADS.readADC(0);
  // Mapping the value
  byte val0 = map(tension_A0, 0, 32767, 0, 255);

  Serial.print("Light value: ");
  Serial.println(val0);

  delay(100);
}
