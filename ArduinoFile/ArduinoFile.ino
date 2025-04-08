#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16,2);

const int MQ2_PIN = A0 ;
float Smoke_level ;
const int MQ7_PIN = A1;
float CO_level; 
int buzzer = 6;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(MQ2_PIN,INPUT);
  pinMode(MQ7_PIN, INPUT);
  pinMode(buzzer,OUTPUT);
  
  lcd.begin(16,2);
  lcd.backlight();
  
  myservo.attach(9); 
  myservo.write(0);
  delay(2000);

}

void loop() {
  // put your main code here, to run repeatedly:
  int Co_Value = analogRead(MQ7_PIN);
  CO_level = (Co_Value / 1023.0) * 1000;
  int Smoke_Value= analogRead(MQ2_PIN);
  Smoke_level = (Smoke_Value / 1023.0) * 1000;
  Serial.print("CO : ");
  Serial.print(CO_level);
  Serial.println("ppm");
  
  Serial.print("Smoke : ");
  Serial.print(Smoke_level);
  Serial.println("ppm");

  lcd.setCursor(0,0);
  lcd.print("CO: ");
  lcd.print(CO_level);
  lcd.print(" ppm");
  lcd.setCursor(0,1);
  lcd.print("Smoke:");
  lcd.print(Smoke_level);
  lcd.print(" ppm");
    
  if((CO_level < 500 ) || (Smoke_level < 200 ))
  {
      myservo.write(0);
}
  if((CO_level >= 500 ) || (Smoke_level >= 200 ))
  {
    myservo.write(180);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("AIR POLUTTED");
    lcd.setCursor(0,1);
    lcd.print("WINDOW OPEN");
    digitalWrite(buzzer,HIGH);
    delay(2000);
    digitalWrite(buzzer,LOW);
}
  delay(500);
  
} 
