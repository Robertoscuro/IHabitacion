#include "WiFi.h"
#include "DHT.h"
#include "LiquidCrystal.h"
#include "ThingsBoard.h"

// LiquidCrystal lcd(19,18,17,16,14,12);
#define TOKEN               " "
#define THINGSBOARD_SERVER  " "

WiFiClient espClient;
// Initialize ThingsBoard instance
ThingsBoard tb(espClient);
// the Wifi radio's status
int status = WL_IDLE_STATUS;


const char* ssid = " "; //introduce the credentials
const char* password =  " ";
int lightPin = 23; 
int temperaturePin = 22; 
int detectionPin = 21; 
int temp;
int hum;
int tiempoDesconexion;
DHT dht(temperaturePin, DHT11);
void setup() {
  tiempoDesconexion=0;
  pinMode(lightPin, INPUT);
  pinMode(temperaturePin, INPUT);
  pinMode(detectionPin, INPUT);
  dht.begin();
  Serial.begin(115200);
  
 conectarWifi();
  
  delay(1000);
  Serial.println("Iniciando sistema");
 // lcd.begin(16, 2);
  //  lcd.clear();
  //  lcd.print("Interfacing LCD");

  //  lcd.setCursor(0,1); 
   // lcd.print ("with ESP32");
 delay(60000);
}
 
void loop() {
  if(tiempoDesconexion==(3600000/2))
  {
   tiempoDesconexion=0;
   conectarWifi(); 
  }
   if (!tb.connected()) {
    if(tiempoDesconexion<5){
  Serial.print("Conectando al: ");
    Serial.print(THINGSBOARD_SERVER);
    Serial.print(" con token ");
    Serial.println(TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
      Serial.println("Failed to connect");
      }}
   }
      
  if(digitalRead(lightPin)){
    Serial.println("Sin luz");
    tb.sendTelemetryInt("Luz", 0);
  }else{
    Serial.println("Con luz");
    tb.sendTelemetryInt("Luz", 1);
  }
  
  hum= dht.readHumidity();
  temp= dht.readTemperature();
  Serial.print("Humedad: ");
   Serial.println(hum);
   tb.sendTelemetryFloat("Humedad", hum);
  Serial.print("Temperatura: ");
  
   Serial.println(temp);
  // Serial.println(digitalRead(detectionPin));
   tb.sendTelemetryFloat("Temperatura", temp);
    if(digitalRead(detectionPin)==HIGH){
    Serial.println("Movimiento");
     tb.sendTelemetryInt("Movimiento", digitalRead(detectionPin));
  }else{
    Serial.println("Sin movimiento");
    tb.sendTelemetryInt("Movimiento", digitalRead(detectionPin));
  }
  delay(2000);
  if(WiFi.status() != WL_CONNECTED){
    tiempoDesconexion++;
  }else{
    tiempoDesconexion==0;
  }
}
void conectarWifi(){
  int contador;
  WiFi.begin(ssid, password);
 contador=0;
  while (WiFi.status() != WL_CONNECTED && contador<120) {
    delay(500);
    Serial.println("Conectando al Wifi");
    contador++;
  }
  if(contador==120){
    Serial.println("Fallo al conectar");
  }
  else{
    Serial.println("Connectado a la red wifi");
    
  }
  }
