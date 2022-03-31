#include <SPI.h>
#include <Arduino.h>
#define CLR 0x00
#define RD 0x40
#define WR 0x80
#define LOAD 0xC0
#define MDR0 0x08
#define MDR1 0x10
#define DTR 0x18
#define CNTR 0x20
#define OTR 0x28
#define STR 0x30
// filter factor 1
// async index
// no index
// free-running
// 4x quadrature
#define MDR0_CONF 0x03
// no flag
// enabled
// 32 bits
#define MDR1_CONF 0x00
/* void setup() {
  Serial.begin(9600);
  SPI.begin();
  pinMode(10, OUTPUT);
  
  
  digitalWrite(10, LOW);
  SPI.transfer(WR | MDR0);
  SPI.transfer(MDR0_CONF);
  digitalWrite(10, HIGH);
  
  digitalWrite(10, LOW);
  SPI.transfer(WR | MDR1);
  SPI.transfer(MDR1_CONF);
  digitalWrite(10, HIGH);
  
  digitalWrite(10, LOW);
  SPI.transfer(CLR | CNTR);
  digitalWrite(10, HIGH);
}
long count = 0;
void loop() {
  digitalWrite(10, LOW);
  byte b = SPI.transfer((byte) RD | CNTR);
  count = SPI.transfer(0x00);
  count <<= 8;
  count |= SPI.transfer(0x00);
  count <<= 8;
  count |= SPI.transfer(0x00);
  count <<= 8;
  count |= SPI.transfer(0x00);
  digitalWrite(10, HIGH);
  Serial.print(count);
  Serial.println();
  delay(100);
} */
