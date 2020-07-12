/*
 * Slave One Arduino Program written by Maksim Stojkovic 2018
 * Team Sitz submission for Project Arduino Competition - Thales
 */

#include <Wire.h> // Loads the library for Wire, which is used for I2C communication
#include <LiquidCrystal.h> // Loads the library for LiquidCrystal, which is used to display carriage information on external LCD screens

// Initialises constants used for I2C communication, such as the range of addresses to check, and the delay between checks
const int ADDRESS = 1;
const int DATA_SIZE = 2;
const int DELAY = 250;
const int MAX_SEATS = 5;

// Initialises the pinouts for the LCD screen and creates an new LiquidCrystal Instance
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Creates an empty array which will be populated with information from the current carriage
byte data[DATA_SIZE];

// Starts the Serial output for debugging purposes,
// as well as start-up operations for the LCD and I2C comm. and pin modes
void setup() {
  Serial.begin(9600);
  Serial.println("SLAVE ONE ENABLED");
  Serial.println("****************");

  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Seats Available:");

  Wire.begin(ADDRESS);
  Wire.onRequest(sendData);

  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
}

void loop() {
  // Reads the value of 5 pins to determine whether seats are occupied
  int b1 = 1 - digitalRead(6);
  int b2 = 1 - digitalRead(7);
  int b3 = 1 - digitalRead(8);
  int b4 = 1 - digitalRead(9);
  int b5 = 1 - digitalRead(10);

  int sum = MAX_SEATS - (b1 + b2 + b3 + b4 + b5);

  // Assigns the total number of seats to the second element in the data array
  data[0] = ADDRESS;
  data[1] = sum;

  // Prints the number of seats available on an external LCD screen
  lcd.setCursor(0, 1);
  lcd.print(sum);
  lcd.print("   "); // Erases any residual characters on the LCD without needed to use clear()

  delay(DELAY);
}

void sendData() {
  // When data is requested from this slave, the data array is sent
  Wire.write(data, DATA_SIZE);

  // The number of seats available is printed to the Serial for debugging
  Serial.print("Seats Available: ");
  Serial.println(data[1]);
}

