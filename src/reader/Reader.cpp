#include "Arduino.h"
#include "Reader.h"


Reader::Reader(int chipSelectPin, int resetPowerDownPin) {
    MFRC522 mfrc522(chipSelectPin, resetPowerDownPin);
}

void Reader::init() {
    SPI.begin();
    mfrc522.PCD_Init();
    mfrc522.PCD_DumpVersionToSerial();
    Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

String Reader::read() {
    if (!mfrc522.PICC_IsNewCardPresent()) {
        return "";
    }
    if (!mfrc522.PICC_ReadCardSerial()) {
        return "";
    }
    return transformByteToString(mfrc522.uid.uidByte, mfrc522.uid.size);
}

String Reader::transformByteToString(byte *buffer, byte bufferSize) {
    String accumute = String();
    for (byte i = 0; i < bufferSize; i++) {
        accumute.concat(String(buffer[i], HEX));
    }
    return accumute;
}

 