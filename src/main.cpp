#include <Arduino.h>
#include <SPI.h>
#include "reader/Reader.h"

#define RST_PIN D0      
#define SS_PIN D8       

Reader reader(SS_PIN, RST_PIN);

void setup() {
	Serial.begin(9600);
	while (!Serial);
	SPI.begin();
	reader.init();
	delay(4);
}

void loop() {
	String tagRead = reader.read();
	if(tagRead != "") {
		Serial.println(tagRead);
	}
	delay(2000);
}
