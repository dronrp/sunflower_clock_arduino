#include <Servo.h>

#include <Wire.h>
#include <virtuabotixRTC.h>  
#include <LiquidCrystal_I2C.h> 
 
virtuabotixRTC myRTC(2, 3, 4);
LiquidCrystal_I2C lcd(0x27, 16, 2);

//LCD está conectado a A4 y A5

int sensorPin = A0;
int servoPin  = 8;

int sensorValue = 0;
int servoDegree = 90;
int tolerance = 40;


String minutes = "";
String day = "";
String month = "";

Servo myservo;

void setup() {
  pinMode(sensorPin, INPUT);
  myservo.attach(servoPin);
  myservo.write(servoDegree);
  Serial.begin(9600);
  myRTC.setDS1302Time(0, 36, 18, 7, 3, 1, 2021);
  
  lcd.begin();  
  lcd.home(); 
}

void loop() {
  sensorValue = analogRead(sensorPin);
  if (sensorValue < (512-tolerance) )
  {
    if (servoDegree < 180) servoDegree++;
  }

  if ( sensorValue > (512+tolerance) )
  {
    if (servoDegree > 0) servoDegree--;
  }

  myservo.write(servoDegree); 

  

  myRTC.updateTime();
  
  lcd.setCursor(3,0);
  day = myRTC.dayofmonth;
  
  if (day.length() == 1){
    day = "0"+ day;
  } 
  
  lcd.print(day);

  month = myRTC.month;
  if (month.length() == 1){
    month = "0"+ month;
  } 
  
  lcd.setCursor(5,0);
  lcd.print("/");
  lcd.setCursor(6,0);
  lcd.print(month);
  lcd.setCursor(8,0);
  lcd.print("/");
  lcd.setCursor(9,0);
  lcd.print(myRTC.year);

  lcd.setCursor(6,1);
  lcd.print(myRTC.hours);
  lcd.setCursor(8,1);
  lcd.print(":");
  lcd.setCursor(9,1);
  minutes = myRTC.minutes;
  if (minutes.length() == 1){
    minutes = "0"+ minutes;
  }
  lcd.print(minutes);
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.println(myRTC.seconds);
  
  delay(100);
 
}
