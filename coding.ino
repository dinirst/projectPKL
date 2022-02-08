#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> 

LiquidCrystal_I2C lcd(0x27,16,2);
WidgetLCD lcd_blynk(V1);
WidgetTerminal terminal(V0);

const int SoilSensor = A0;
int pumpPin = D5;

char auth[] = "DeawhLk4NLGVnoOwoJ_WAXANpY2Mp93n";
char ssid[] = "tebu";
char pass[] = "@irigasi";

void setup() {
  // initialize digital pin A5 as an output.
  Serial.begin(9600);
  pinMode(pumpPin, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  lcd.init();
  lcd.backlight();
  lcd_blynk.clear();
  lcd.clear();
  }

void loop(){
  lcd.clear();
  int kelembabanTanah;
  int hasilPembacaan = analogRead(SoilSensor);
  kelembabanTanah = map(hasilPembacaan,900,295,0,100); 
    if (kelembabanTanah<60){
      lcd.setCursor(0,0);
      lcd.print("Kelembaban: ");
      lcd.print(kelembabanTanah);
      lcd.print("%");
      lcd.setCursor(0,1);
      lcd.print("Mulai Siram");
      
      lcd_blynk.print(0,0, "Kelembapan: ");
      lcd_blynk.print(12,0, kelembabanTanah);
      lcd_blynk.print(15,0, "%");
      lcd_blynk.print(0,1, "Mulai siram");
      Blynk.notify("Tanaman kering, penyiraman dilakukan!");

      digitalWrite(pumpPin, HIGH); 
      delay(10000);
      Blynk.virtualWrite(D5, HIGH); 
      delay (1000); 
      if(kelembabanTanah==100){
        digitalWrite(pumpPin, LOW);
        Blynk.virtualWrite(D5, LOW);
        delay(1000);
      }     
    } else {
      lcd.setCursor(0,0);
      lcd.print("Kelembaban: ");
      lcd.print(kelembabanTanah);
      lcd.print("%");
      lcd.setCursor(0,1);
      lcd.print("Henti Siram");
      
      lcd_blynk.print(0,0, "Kelembaban: ");
      lcd_blynk.print(12,0, kelembabanTanah);
      lcd_blynk.print(15,0, "%");
      lcd_blynk.print(0,1, "Henti siram");
      Blynk.notify("Tanaman lembab, penyiraman dihentikan!");
      
      digitalWrite(pumpPin, LOW);
      Blynk.virtualWrite(D5, LOW);
      delay(1000);
    }}
