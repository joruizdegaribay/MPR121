/*
  Library to control the touch sensor MPR121
  More info at https://www.sparkfun.com/datasheets/Components/MPR121.pdf
*/

#include "Arduino.h"
#include "SensorTouch.h"
#include <Wire.h>

SensorTouch::SensorTouch(int address, uint8_t irqPin){

	_address = address;
	_irqPin = irqPin;
	pinMode(_irqPin, INPUT_PULLUP);
	Wire.begin();
}               

void SensorTouch::setup(){

	set_register(_address, ELE_CFG, 0x00); 

	// Section A - Controls filtering when data is > baseline.
	set_register(_address, MHD_R, 0x01);
	set_register(_address, NHD_R, 0x01);
	set_register(_address, NCL_R, 0x00);
	set_register(_address, FDL_R, 0x00);

	// Section B - Controls filtering when data is < baseline.
	set_register(_address, MHD_F, 0x01);
	set_register(_address, NHD_F, 0x01);
	set_register(_address, NCL_F, 0xFF);
	set_register(_address, FDL_F, 0x02);

	// Section C - Sets touch and release thresholds for each electrode
	set_register(_address, ELE0_T, TOU_THRESH);
	set_register(_address, ELE0_R, REL_THRESH);
 
	set_register(_address, ELE1_T, TOU_THRESH);
	set_register(_address, ELE1_R, REL_THRESH);

	set_register(_address, ELE2_T, TOU_THRESH);
	set_register(_address, ELE2_R, REL_THRESH);

	set_register(_address, ELE3_T, TOU_THRESH);
	set_register(_address, ELE3_R, REL_THRESH);

	set_register(_address, ELE4_T, TOU_THRESH);
	set_register(_address, ELE4_R, REL_THRESH);

	set_register(_address, ELE5_T, TOU_THRESH);
	set_register(_address, ELE5_R, REL_THRESH);

	set_register(_address, ELE6_T, TOU_THRESH);
	set_register(_address, ELE6_R, REL_THRESH);

	set_register(_address, ELE7_T, TOU_THRESH);
	set_register(_address, ELE7_R, REL_THRESH);

	set_register(_address, ELE8_T, TOU_THRESH);
	set_register(_address, ELE8_R, REL_THRESH);

	set_register(_address, ELE9_T, TOU_THRESH);
	set_register(_address, ELE9_R, REL_THRESH);

	set_register(_address, ELE10_T, TOU_THRESH);
	set_register(_address, ELE10_R, REL_THRESH);

	set_register(_address, ELE11_T, TOU_THRESH);
	set_register(_address, ELE11_R, REL_THRESH);

	// Section D
	// Set the Filter Configuration
	// Set ESI2
	set_register(_address, FIL_CFG, 0x04);

	// Section E
	// Electrode Configuration
	// Set ELE_CFG to 0x00 to return to standby mode
	set_register(_address, ELE_CFG, 0x0C);  // Enables all 12 Electrodes

	// Section F
	// Enable Auto Config and auto Reconfig
	/*set_register(_address, ATO_CFG0, 0x0B);
	set_register(_address, ATO_CFGU, 0xC9);  // USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   set_register(0x5A, ATO_CFGL, 0x82);  // LSL = 0.65*USL = 0x82 @3.3V
	set_register(_address, ATO_CFGT, 0xB5);*/  // Target = 0.9*USL = 0xB5 @3.3V
	set_register(_address, ELE_CFG, 0x0C);
 
} 

void SensorTouch::readTouchInputs(byte status[]){
  
	if(!checkInterrupt()){
		Wire.requestFrom(_address,2); //Wire.requestFrom(address,quantity in bytes)//Address from the datasheet
     
		byte LSB = Wire.read();
		byte MSB = Wire.read();
    
		for (int i = 0; i < 12; i++){
			int touched =  ((MSB << 8) | LSB);   
              
			if(touched & (1<<i))       
				status[i] = 1;
			else
				status[i] = 0; 
		}
	}
}

 boolean SensorTouch::checkInterrupt(void){
	return digitalRead(_irqPin);
}

 void SensorTouch::set_register(int address, unsigned char r, unsigned char v){
 
	Wire.beginTransmission(address);
	Wire.write(r);
	Wire.write(v);
	Wire.endTransmission();
}