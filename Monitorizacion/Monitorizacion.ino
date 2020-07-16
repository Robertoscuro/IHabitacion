#include "WiFi.h"
#include "DHT.h"
 
const char* ssid = "ONOA2F9"; //introduce the credentials
const char* password =  "hCNYeM3RbGK2";
int lightPin = 23; 
int temperaturePin = 22; 
int detectionPin = 1; 
int temp;
int hum;
DHT dht(temperaturePin, DHT11);
void setup() {
  pinMode(lightPin, INPUT);
  pinMode(temperaturePin, INPUT);
  pinMode(detectionPin, INPUT);
  dht.begin();
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
}
 
void loop() {
  if(digitalRead(lightPin)){
    Serial.println("Sin luz");
  }else{
    Serial.println("Con luz");
  }
  
  hum= dht.readHumidity();
  temp= dht.readTemperature();
  Serial.print("Humedad: ");
   Serial.println(hum);
  Serial.print("Temperatura: ");
   Serial.println(temp);
    if(digitalRead(detectionPin)==HIGH){
    Serial.println("Movimiento");
  }else{
    Serial.println("Sin movimiento");
  }
  delay(1000);

  }
