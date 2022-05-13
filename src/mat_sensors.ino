#include "HX711.h"
#include <LS7366.h>
#include <SPI.h>


// 2x hx711 chips - 4 objects? (one per channel?)
    // 1A = lateral strain
    // 1B = extensometer
    // 2A = axial strain
    // 2B = loadcell
        // chip 1 on pin 2, chip 2 on pin 3
// lvdt analog in on A0
// ls7366 - encoder on SPI (pins 10-13)     20MHz (for now)

const int SCALE1_DOUT_PIN = 2;
const int SCALE2_DOUT_PIN = 3;
const int SCALE_SCK_PIN = 4;
const int ENCODER_SELECT_PIN = 10;
const int LVDT_PIN = A0;


HX711 scale1A, scale1B, scale2A, scale2B;
LS7366 encoder(ENCODER_SELECT_PIN);

long lvdt_value = 0;
unsigned long encoder_count = 0;
long scale1_reading = 0;
long scale2_reading = 0;

void setup() {
    Serial.begin(9600);
    lvdt_setup();
    //encoder_setup();
    //scale_setup();

}

void loop() {
    lvdt_read();
    //encoder_read();
    //scale_read('A');
    //scale_read('B');
}

void scale_setup() {
    scale1A.begin(SCALE1_DOUT_PIN, SCALE_SCK_PIN, 64);
    scale1B.begin(SCALE1_DOUT_PIN, SCALE_SCK_PIN, 32);
    scale2A.begin(SCALE2_DOUT_PIN, SCALE_SCK_PIN, 64);
    scale2B.begin(SCALE2_DOUT_PIN, SCALE_SCK_PIN, 32);
}


// not tested yet
void scale_read(char channel) { // channel A for strain, B for extensiometer + load
    switch(channel) {
        case 'A':
        case 'a':
            if(scale1A.is_ready()){
                scale1_reading = scale1A.read();
                Serial.print("Lateral strain: ");
                Serial.print(scale1_reading);
                Serial.print("\n");
            }
            else
                Serial.println("Scale 1 not found");

            if(scale2A.is_ready()){
                scale2_reading = scale2A.read();
                Serial.print("Axial strain: ");
                Serial.print(scale2_reading);
                Serial.print("\n");
            }
            else
                Serial.println("Scale 2 not found");

            break;

        case 'B':
        case 'b':
            if(scale1B.is_ready()){
                scale1_reading = scale1B.read();
                Serial.print("Extension: ");
                Serial.print(scale1_reading);
                Serial.print("\n");
            }
            else
                Serial.println("Scale 1 not found");

            if(scale2B.is_ready()){
                scale2_reading = scale2B.read();
                Serial.print("Load: ");
                Serial.print(scale2_reading);
                Serial.print("\n");
            }
            else
                Serial.println("Scale 2 not found");

            break;

        default:
            Serial.println("Select channel A or B");
    }
}

void lvdt_setup(){
    analogReference(EXTERNAL);
}

void lvdt_read(){
    lvdt_value = analogRead(LVDT_PIN);
    Serial.print("LVDT value: ");
    Serial.print(lvdt_value);
    Serial.print("\n");
    delay(500);
}

void encoder_setup() {
  encoder.write_mode_register_0(FILTER_1 | DISABLE_INDX | FREE_RUN | QUADRX4);
  encoder.write_mode_register_1(NO_FLAGS | EN_CNTR | BYTE_4 );
  encoder.clear_counter();
  encoder.clear_status_register();
  encoder.write_data_register(4);
}

void encoder_read() {
  encoder_count = encoder.read_counter();
  Serial.print("Encoder count: ");
  Serial.print(encoder_count, DEC);
  //Serial.print(" Status: ");
  //print_binary(encoder.read_status_register());
  Serial.print("\n");
  delay(200);
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