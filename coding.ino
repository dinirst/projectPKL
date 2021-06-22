#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16,2);

const int pinDigital = A0;
int sensor_pin = A0;
int output_value;
String response;

int motorPin = A3;
int watertime = 5;
int waittime = 60;

void setup(){
  lcd.init();
  lcd.backlight();
  Serial.begin (9600);
  pinMode(pinDigital, INPUT);
  pinMode(motorPin, OUTPUT);
}

void loop() {
  int dataAnalog = analogRead (pinDigital);
  output_value= analogRead(sensor_pin);
  int output_value2 = map(output_value,1023,0,0,100);
  lcd.setCursor(0,0);
  lcd.print("KLBPN TANAH :");
  lcd.print(output_value2);
  lcd.println("% ");
  if (dataAnalog <=512) {
      lcd.setCursor(0,1);
      lcd.println("TANAH BASAH ");
      digitalWrite(motorPin, LOW);}
      //delay(waittime*1000);
  else {
      lcd.setCursor(0,1);
      lcd.println("TANAH KERING ");
      digitalWrite(motorPin, HIGH); // turn on the motor
      delay(watertime*500);}
}
