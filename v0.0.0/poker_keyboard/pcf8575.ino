#include "pcf8575.h"

void pcf8575_begin(){
    pcf8575_writeAll(word(B11111111,B11111111));
}

void pcf8575_writeAll(uint16_t data) {
  Wire.beginTransmission(pcf_address);
  Wire.write(lowByte(data));
  Wire.write(highByte(data));
  Wire.endTransmission();
}

void pcf8575_readAll() {
    Wire.requestFrom(pcf_address, 16);    // Request 8 bytes from slave device number two
    // Slave may send less than requested
	byte b1 = Wire.read();
	byte b2 = Wire.read();

    if (DBG_KEYBOARD){
        Serial.println("..");
        Serial.println(b1);
	    Serial.println(b2);
    }
    
}
