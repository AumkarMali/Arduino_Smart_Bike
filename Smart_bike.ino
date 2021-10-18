#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);


int sensor = 8;
unsigned long start_time = 0;
unsigned long end_time = 0;
int steps=0;
float steps_old=0;
float temp=0;
float rps=0;
float rpm=0;
float velocity=0;
float dist_count = 0;
float distance = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(sensor,INPUT_PULLUP);
  lcd.init();                     
  lcd.backlight();

  pinMode(10, OUTPUT); //red
  pinMode(11, OUTPUT); //yellow
  pinMode(12, OUTPUT); //green
  
}
 
void loop()
{

 int Run_LED_func;

  lcd.setCursor(0,0);
  lcd.print("speed=" + String(velocity) + "kph");
  lcd.setCursor(0,5);

  if (distance < 1000) {
    lcd.print(String(round(distance)) + "m's " + round(rpm) + "rpm");
  }

  else {
    lcd.print(String(distance/1000) + "km's " + round(rpm) + "rpm");
  }

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("speed=" + String(velocity) + "kph");
  lcd.setCursor(0,5);


 if (distance < 1000) {
    lcd.print(String(round(distance)) + "m's " + round(rpm) + "rpm");
  }


  else {
    lcd.print(String(distance/1000) + "km's " + round(rpm) + "rpm");
  }

  rpm = 0;
  velocity = 0;
    
 start_time=millis();
 end_time=start_time+1000;
 while(millis()<end_time)
 {
   if(digitalRead(sensor))
   {
    steps=steps+1; 
    dist_count = dist_count+1;
    while(digitalRead(sensor));
   }
 }
    temp=steps-steps_old;
    steps_old=steps;
    rps=(temp/4);
    rpm = rps * 60;
    velocity = 0.1885 * rpm * 0.66;
    distance = (dist_count/4) * 2.07;

    if (temp == 0) {
      velocity = 0;
      rpm = 0;
    }

    temp = 0;
    steps = 0;
    steps_old = 0;

    
    Run_LED_func = LED_RPM_reader(rpm);
  
}

int LED_RPM_reader(int rpm){


  if (rpm > 15 && rpm < 60) {
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
  }

  else if (rpm > 60 && rpm < 150) {
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
  }

  else if (rpm > 150) {
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
  }

  else {
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
  }

 
  return rpm;

}
