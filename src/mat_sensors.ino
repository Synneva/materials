#include "HX711.h"
#include <LS7366.h>
#include <SPI.h>


// 2x hx711 chips - 4 objects? (one per channel?)
    // 1A = lateral strain
    // 1B = extension
    // 2A = axial strain
    // 2B = loadcell
        // chip 1 on pin 2, chip 2 on pin 3
// lvdt analog in on A0
// ls7366 - encoder on SPI (pins 10-13)

const int SCALE1_DOUT_PIN = 2;
const int SCALE2_DOUT_PIN = 3;
const int SCALE_SCK_PIN = 4;
const int ENCODER_SELECT_PIN = 10;
const int LVDT_PIN = A0;


HX711 scale1, scale2;
LS7366 encoder(ENCODER_SELECT_PIN);

void setup() {
    Serial.begin(9600);
    lvdt_setup();
    encoder_setup();


}

void loop() {


}

void lvdt_setup(){
    analogReference(EXTERNAL);
    long sensorValue = 0;
}

void lvdt_read(){
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);
    delay(1000);
}

void encoder_setup() {
  Serial.begin(9600);
  encoder.write_mode_register_0(FILTER_1 | DISABLE_INDX | FREE_RUN | QUADRX4);
  encoder.write_mode_register_1(NO_FLAGS | EN_CNTR | BYTE_4 );
  encoder.clear_counter();
  encoder.clear_status_register();
  encoder.write_data_register(4);
}

void encoder_read() {
  unsigned long count = encoder.read_counter();
  Serial.print("Count: ");
  Serial.print(count, DEC);
  Serial.print(" Status: ");
  print_binary(encoder.read_status_register());
  Serial.print("\n");
  delay(1000);
}

//Function to print out one byte in a readable, left-padded binary format

void print_binary(byte val)
{
byte i=0;
for (i=0;i<8;i++)
    {
        if (val & (0x01 << (7-i)))
        {
             Serial.print("1");
        }
        else
        {
             Serial.print("0");
        }
        if (i==3) Serial.print("_");
    }
}