/*
 * Master Arduino Program written by Maksim Stojkovic 2018
 * Team Sitz submission for Project Arduino Competition - Thales
 */

#include <Wire.h> // Loads the library for Wire, which is used for I2C communication
#include <LiquidCrystal.h> // Loads the library for LiquidCrystal, which is used to display carriage information on external LCD screens

// Initialises the pinouts for the LCD screen and creates an new LiquidCrystal Instance
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Initialises constants used for I2C communication, such as the range of addresses to check, and the delay between checks
const int DATA_SIZE = 2;
const int FIRST = 1;
const int LAST = 2;
const int DELAY = 100;

// Creates an empty array which will be populated with the information retrieved from slaves
int data[DATA_SIZE];

// Starts the Serial output for debugging purposes, as well as start-up operations for the LCD and I2C comm.
void setup() {
  Serial.begin(9600);
  Serial.println("MASTER DEVICE ENABLED");
  Serial.println("****************");

  lcd.begin(16, 2);

  Wire.begin();
}

void loop() {
  // Search through the range of addresses defined, requesting information from the slave Arduinos
  // and assigning it to the data array
  for (int address = FIRST; address <= LAST; address++) {
    Wire.requestFrom(address, DATA_SIZE);
    if (Wire.available() == DATA_SIZE) {
      for (int i = 0; i < DATA_SIZE; i++) {
        data[i] = Wire.read();
      }

      // Used to ensure that the row selected on the LCD is set correctly
      int row = data[0] - 1;

      // Prints the data retrieved to the LCD, and the Serial for debugging
      lcd.setCursor(0, row);
      lcd.print("Carriage ");
      lcd.print(data[0]);
      lcd.print(": ");
      lcd.print(data[1]);
      lcd.print("  ");
      
      Serial.print("Carriage ");
      Serial.print(data[0]);
      Serial.print(": ");
      Serial.println(data[1]);
    }
    
  }
  delay(DELAY);
}
