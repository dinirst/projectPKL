#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLBPruhWj0"
#define BLYNK_DEVICE_NAME "Irigasi Tebu"

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16,2);

const int pinDigital = A0;
int sensor_pin = A0;
int output_value;
String response;
//char auth[] = "St2wGt1R3Gx3eKv14WRYxbzRCJPHZSdZ";

int motorPin = A3;
int watertime = 5;
int waittime = 60;

//char ssid[] = "ssid wifi";
//char pass[] = "pass wifi";

#define EspSerial Serial1
#define ESP8266_BAUD 38400
ESP8266 wifi(&EspSerial);

void setup(){
  lcd.init();
  lcd.backlight();
  Serial.begin (9600);
  pinMode(pinDigital, INPUT);
  pinMode(motorPin, OUTPUT);

  //EspSerial.begin(ESP8266_BAUD);
  //delay(10);
  //Blynk.begin(auth, ssid, pass);
}

void loop() {
  int dataAnalog = analogRead (pinDigital);
  output_value= analogRead(sensor_pin);
  int output_value2 = map(output_value,1023,0,0,100);

  //Blynk.run();
  
  lcd.setCursor(0,0);
  lcd.print("KLBPN TANAH :");
  lcd.print(output_value2);
  lcd.println("% ");
  
  if (dataAnalog <=512) {
      lcd.setCursor(0,1);
      //Blynk.notify("Tanah basah. Penyiraman dihentikan")
      lcd.println("TANAH BASAH ");
      digitalWrite(motorPin, LOW);}
      //delay(waittime*1000);
  else {
      lcd.setCursor(0,1);
      //Blynk.notify("Tanah kering. Penyiraman dilakukan");
      lcd.println("TANAH KERING ");
      digitalWrite(motorPin, HIGH); // turn on the motor
      delay(watertime*500);}
}
