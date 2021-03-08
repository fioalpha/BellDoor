#include <Arduino.h>
#include <SPI.h>
#include "reader/Reader.h"
#include "secrets/secrets.h"

#include <ESP8266WiFi.h> // Importa a Biblioteca ESP8266WiFi
#include <PubSubClient.h> // Importa a Biblioteca PubSubClient

#define LOCK  D4
#define BELL_BUTTON D3

WiFiClient wifiClient;
PubSubClient MQTT(wifiClient);
Reader reader(D8, D0);
String readTagStatus = "";
unsigned int bellButtonStatus = LOW;

void mqttCallback(char* topic, byte* paylod, unsigned int length) {

}

void setupPins() {
	pinMode(D4, OUTPUT);
	pinMode(D3, INPUT_PULLUP);
}

void initMqttClient() {
	MQTT.setServer(MQTT_BROKER, MQTT_PORT);
	MQTT.setCallback(mqttCallback);
}

void mqttConnect() {
	if (MQTT.connected()) return;

	Serial.println("Starting mqtt client");
	Serial.println("Trying connect the mqtt client");

	while (!MQTT.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS))
		Serial.print('.');
	
	Serial.println("MQTT client connected");
}

void wifiConnect() {
	if (WiFi.isConnected()) return ;
	WiFi.begin(SSID_WIFI, PASS_WIFI);
	Serial.println("Trying connectthe wifi");
	while (!WiFi.isConnected()){
		Serial.print(".");
		delay(100);
	}

	Serial.println();
	Serial.println("Connected on the wifi");
	Serial.print(SSID_WIFI);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}

void connectService() {
	wifiConnect();
	mqttConnect();
}

void setup() {
	Serial.begin(9600);
	while (!Serial);
	SPI.begin();
	reader.init();
	delay(4);
	initMqttClient();
}

void sendClickBellButton() {}

void sendTagRead(String tag) {}

void loop() {
	connectService();
	MQTT.loop();

	bellButtonStatus =  digitalRead(BELL_BUTTON);
	if (bellButtonStatus == HIGH) {
		sendClickBellButton();
		return; 
	}

	readTagStatus = reader.read();
	if(!readTagStatus.equals("")) {
		Serial.println(readTagStatus);	
		sendTagRead(readTagStatus);
	}

	
}
