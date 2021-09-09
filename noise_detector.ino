#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C LCD를 사용하기 위한 준비

const int soundSensor = A0;
const int rLed = 9;
const int gLed = 10;
const int buzzer = 7; // 센서와 모튤의 핀번호 설정

float sensorValue; // 소리 센서가 입력한 아날로그 형태 값 저장하는 변수
float dB; // 소리 센서가 입력한 아날로그 형태 값을 데시벨로 변환한 후 그 데시벨 값  저장하는 변수

void setup()
{
  Serial.begin(9600); // 시리얼 통신 시작

  pinMode(rLed, OUTPUT); 
  pinMode(gLed, OUTPUT);
  pinMode(buzzer, OUTPUT); // LED와 부저 출력모드
  
  lcd.begin(); // I2C LCD 사용 시작
  lcd.backlight(); // 백라이트 켜기
  
}

void loop()
{
  sensorValue = analogRead(soundSensor); // 소리 센서가 인식한 소리의 크기 입력
  
  dB = (sensorValue + 83.2073) /11.003; // 소리 센서가 입력한 아날로그 형태 값을 데시벨 값으로 변환시켜주는 함수()
  
  Serial.println(dB); // 시리얼 모니터에 데시벨 값 출력
  
  lcd.setCursor(0, 0);
  lcd.print(dB);
  lcd.print("dB"); // I2C LCD화면에 데시벨 값 출력((데시벨 값)dB형태로 출력)
  
  delay(50); // 50ms(0.05초)만큼 딜레이

  if (dB >= 65) {
    digitalWrite(rLed, HIGH);
    digitalWrite(gLed, LOW); // 일 때 LED 작동
    
    digitalWrite(buzzer, HIGH); // 일 때 부저 작동
  }
 
  else {
    digitalWrite(gLed, HIGH); 
    digitalWrite(rLed, LOW); // 일 때 LED 작동
 
    digitalWrite(buzzer, LOW); // 일 때 부저 작동

  }
}
