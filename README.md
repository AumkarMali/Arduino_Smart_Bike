
[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)
[![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://opensource.org/licenses/)
[![AGPL License](https://img.shields.io/badge/license-AGPL-blue.svg)](http://www.gnu.org/licenses/agpl-3.0)


# Arduino smart bike

Regular bicycles may be mechanically sound, they are still vehicles and should carry some safety features to them and keep track of data during a ride. By programming an Arduino Uno board and attaching it onto a bicycle with some other hardware components, I was able to measure speed, distance travelled, and indicate whether it is dangerous to travel with certain speeds.

## Program Explanation


#### LCD Display Initialize

To display data to the user during their ride, a liquid crystal display (LCD) is used. The parameters passed to the LCD object class is (0x27, 16, 2), the first value in this tuple is the I2C address of the LCD. And the other integers define the number of columns and rows, respectively. In the setup() function, the lcd is initialized and its backlight is turned on. 

#### LCD Display Printing

The `lcd.setCursor()` function positions the cursor at a specific character location on the screen, while the `lcd.print()` function outputs data starting from the cursor's current position.

#### Calculating RPM, speed, distance

To measure the RPM of the bicycle wheels, an infrared (IR) sensor and an encoded disk with four encoders attached to the rear wheel of the bicycle was used. The program counts the number of steps, where each step corresponds to a part of the encoder detected by the IR sensor using the `digitalRead()` function. This counting occurs over a one-second interval, implemented with the following code: `start_time = millis(); end_time = start_time + 1000;`. By dividing the number of steps by the number of encoders, the revolutions per second can calculated and subsequently converted to RPM (multiplied by 60). These values can then be used to determine speed and distance based on the circumference of bicycle's rear wheel.

#### Lighting of LED's
Red, yellow, and green pins illuminate at designated RPM intervals to indicate whether the speeds are too high or too low for the rider. This is done with `digitalWrite(pin#, HIGH/LOW)`.


## Mechanical Components

https://ibb.co/X4hXB1d

## Hardware Components

## Authors

- [@AumkarMali](https://www.github.com/AumkarMali)


## Deployment

Download arduino IDE from https://docs.arduino.cc/software/ide-v1/tutorials/Windows

Upload code to arduino board.
## Links

➊ Github: https://github.com/AumkarMali/

➋ Youtube: https://www.youtube.com/channel/UC7rhCKur9bF01lV0pNJNkvA
## Demo

https://www.youtube.com/watch?v=K2MKV6ptq0o


## Documentation

[Documentation](https://docs.arduino.cc)


![Logo](https://www.vectorlogo.zone/logos/arduino/arduino-ar21.png)

