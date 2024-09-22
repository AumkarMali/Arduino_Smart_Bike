#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Initialize the LCD display with I2C address 0x27, 16 columns, and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define the pin for the sensor
int sensor = 8;

// Variables for timing and calculations
unsigned long start_time = 0;
unsigned long end_time = 0;
int steps = 0;
float steps_old = 0;
float temp = 0;
float rps = 0;
float rpm = 0;
float velocity = 0;
float dist_count = 0;
float distance = 0;

void setup() 
{
  Serial.begin(9600); // Start serial communication at 9600 bps
  pinMode(sensor, INPUT_PULLUP); // Set sensor pin as input with pull-up resistor
  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight

  // Set up LED pins
  pinMode(10, OUTPUT); // Red LED
  pinMode(11, OUTPUT); // Yellow LED
  pinMode(12, OUTPUT); // Green LED
}
 
void loop()
{
  int Run_LED_func; // Variable to hold LED control function result

  // Display speed and distance information on the LCD
  lcd.setCursor(0, 0);
  lcd.print("speed=" + String(velocity) + "kph");
  lcd.setCursor(0, 5);

  // Display distance and RPM
  if (distance < 1000) {
    lcd.print(String(round(distance)) + "m's " + round(rpm) + "rpm");
  } else {
    lcd.print(String(distance / 1000) + "km's " + round(rpm) + "rpm");
  }

  // Clear the display for fresh information
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("speed=" + String(velocity) + "kph");
  lcd.setCursor(0, 5);

  // Update display with distance and RPM again
  if (distance < 1000) {
    lcd.print(String(round(distance)) + "m's " + round(rpm) + "rpm");
  } else {
    lcd.print(String(distance / 1000) + "km's " + round(rpm) + "rpm");
  }

  // Reset RPM and velocity for the new calculation period
  rpm = 0;
  velocity = 0;

  // Set the timing for measuring RPM and velocity
  start_time = millis();
  end_time = start_time + 1000; // Measure for 1 second

  // Measure RPM based on sensor readings
  while (millis() < end_time) {
    if (digitalRead(sensor)) {
      steps = steps + 1; 
      dist_count = dist_count + 1; // Increment distance count
      while (digitalRead(sensor)); // Wait for the sensor to go low
    }
  }

  // Calculate the RPM and velocity
  temp = steps - steps_old; // Calculate the number of steps in this period
  steps_old = steps; // Update steps_old for the next calculation
  rps = (temp / 4); // Calculate revolutions per second
  rpm = rps * 60; // Convert to revolutions per minute
  velocity = 0.1885 * rpm * 0.66; // Calculate velocity in kph
  distance = (dist_count / 4) * 2.07; // Calculate distance

  // Handle cases where no steps were detected
  if (temp == 0) {
    velocity = 0;
    rpm = 0;
  }

  // Reset temporary variables
  temp = 0;
  steps = 0;
  steps_old = 0;

  // Update LED indicators based on RPM
  Run_LED_func = LED_RPM_reader(rpm);
}

// Function to control LEDs based on RPM values
int LED_RPM_reader(int rpm) {
  if (rpm > 15 && rpm < 60) {
    digitalWrite(10, HIGH); // Red LED on
    digitalWrite(11, LOW);  // Yellow LED off
    digitalWrite(12, LOW);  // Green LED off
  } else if (rpm > 60 && rpm < 150) {
    digitalWrite(10, HIGH); // Red LED on
    digitalWrite(11, HIGH); // Yellow LED on
    digitalWrite(12, LOW);  // Green LED off
  } else if (rpm > 150) {
    digitalWrite(10, HIGH); // Red LED on
    digitalWrite(11, HIGH); // Yellow LED on
    digitalWrite(12, HIGH); // Green LED on
  } else {
    digitalWrite(10, LOW);  // All LEDs off
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
  }

  return rpm; // Return the RPM value
}
