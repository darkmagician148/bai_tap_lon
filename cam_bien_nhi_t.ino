#include <LabC.h>
#include <avr/interrupt.h>
#include <Wire.h>
#include <TimerOne.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
LiquidCrystal_I2C lcd(0x27,16,4);   
#define TIMER_US 5000 // thời gian trễ = 5 ms
const int DHTPIN = 2; //
const int DHTTYPE = DHT11;
int koi = 13;
int binh_thuong = 8;
int sot = 9;
int button = 3;
int led = 7;
boolean nhan = false;
boolean starts = true;
volatile byte s = HIGH;
float a;
DHT dht(DHTPIN, DHTTYPE);
byte degree[8] = {
 0B01110,
 0B01010,
 0B01110,
 0B00000,
 0B00000,
 0B00000,
 0B00000,
 0B00000
};
float t;
void Delay(){
   t = dht.readTemperature();
  };
void ngat(){
  s=!s;
  nhan = !nhan; 
  starts = false; 
 }
void setup() {
 pinMode(led,OUTPUT);
 pinMode(koi,OUTPUT);
 pinMode(binh_thuong, OUTPUT);
 digitalWrite(binh_thuong,HIGH);
 pinMode(sot,OUTPUT);
 digitalWrite(sot,HIGH);
 pinMode(button,INPUT);
 digitalWrite(led,HIGH);
 Serial.begin(9600);
 Timer1.initialize(TIMER_US); // khởi tạo timer 1 đến 1 giây
 Timer1.attachInterrupt(Delay); // khai báo ngắt timer 1  
 attachInterrupt(1,ngat,CHANGE);                 
 lcd.init(); // hàm khỏi tạo lcd
 lcd.backlight();// bật đèn nền lcd
 lcd.setCursor (0,0);
 lcd.print("Nhiet do: ");//
 lcd.setCursor(3,1);
 lcd.print("bai tap lon ");
 lcd.setCursor (1,3);
 lcd.print(" nhom 2 ");
 lcd.createChar(1, degree);
 dht.begin(); 
}
void loop() {  
  digitalWrite(led,s);
  if( starts == true){
    a=t;
  }
  else{
   if( nhan == true){
    t=a;
  }
  else
  {
      Delay();
    a=t;
  }}
   if (isnan(t)) { // Kiểm tra xem thử việc đọc giá trị có bị thất bại hay không. hàm isnan 
 }
 else {
 lcd.setCursor(10,0);
 lcd.print(round(t));
 lcd.print(" ");
 lcd.write(1);
 lcd.print("C");
  if( a>37.5) {
  digitalWrite(sot,LOW);  
  digitalWrite(binh_thuong,HIGH);}
 else {
  digitalWrite(binh_thuong,LOW);
  digitalWrite(sot,HIGH);
      }
      }
 }
