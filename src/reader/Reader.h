#ifndef Reader_h
#define Reader_h

#include "Arduino.h"
#include <SPI.h>
#include "MFRC522.h"

class Reader {
    public:
        Reader(int chipSelectPin, int resetPowerDownPin);
        void init();
        String read();
    private:
        MFRC522 mfrc522;
        String transformByteToString(byte *buffer, byte bufferSize);
};  

#endif