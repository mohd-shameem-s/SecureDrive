#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// Initialize the LCD library with the address of the I2C display
LiquidCrystal_I2C lcd(0x27, 16, 2);  // 0x27 is the default I2C address for a 16x2 display

// Define alcohol sensor pin
const int alcoholSensorPin = A0;

// Define keypad layout
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {6, 7, 8, 9}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {10, 11, 12, 13}; // connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Define L293D motor driver pins
const int motor1Pin1 = 8; // I1
const int motor1Pin2 = 9; // I2
const int motor2Pin1 = 10; // I3
const int motor2Pin2 = 11; // I4

// Define LED and buzzer pins
const int redLedPin = 3;
const int yellowLedPin = 4;
const int greenLedPin = 5;
const int buzzerPin = 2;

// Define correct pin number
const char correctPin[] = "5555"; // Pin number

char enteredPin[4] = ""; // Array to store entered PIN
bool alcoholDetected = false; // Flag to track alcohol detection
bool pinEntered = false; // Flag to track whether PIN has been entered correctly
unsigned long lastAlcoholCheck = 0; // Time of the last alcohol check

void setup() {
  // Initialize LCD display
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  SECURE DRIVE");
  
  // Display the initial message for a few seconds before starting the loop
  delay(2000);  // Display for 2 seconds
  
  // Initialize motor driver pins
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  
  // Initialize LED and buzzer pins
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Initialize keypad
  keypad.setDebounceTime(50);
  
  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Check alcohol sensor if 5 seconds have passed since the last check
  if (millis() - lastAlcoholCheck >= 5000) {
    int alcoholValue = analogRead(alcoholSensorPin);
    Serial.print("Alcohol Sensor Value: ");
    Serial.println(alcoholValue); // Continuously print sensor value
    
    // Adjust threshold based on actual sensor values
    alcoholDetected = (alcoholValue > 100); // Adjust threshold as needed
    lastAlcoholCheck = millis(); // Update the time of the last alcohol check

    if (alcoholDetected) {
      // Alcohol detected, vehicle off
      Serial.println("Alcohol Detected");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Alcohol Detected");
      alertAndShutdown();
    }
  }
  
  if (alcoholDetected) {
    // Alcohol detected, vehicle off
    return; // Exit loop to avoid further execution
  }
  
  if (!pinEntered) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Alcohol");
    digitalWrite(yellowLedPin, HIGH); // Yellow LED on
    Serial.println("No Alcohol Detected, Enter PIN");
  
    // Get PIN from keypad
    lcd.setCursor(0, 1);
    lcd.print("Enter PIN:");
    
    int index = 0;
    char key = keypad.getKey();
    
    while (index < 4 && key != '#') {
      key = keypad.getKey();
      
      if (key != NO_KEY) {
        if (key == '*' && index > 0) {
          // Backspace pressed, remove last entered digit
          enteredPin[--index] = '\0'; // Null terminate the string
          lcd.setCursor(10 + index, 1); // Move cursor back for LCD
          lcd.print(' '); // Clear the digit from display
          lcd.setCursor(10 + index, 1); // Move cursor back again
        } else if (isdigit(key)) {
          // Digit entered, add to the PIN
          enteredPin[index++] = key;
          lcd.print(key);
        }
        delay(200); // debounce delay
      }
    }
    
    // Check if correct PIN is entered
    if (strcmp(enteredPin, correctPin) == 0) {
      // Correct PIN entered, vehicle ready to run
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Access Granted!");
      lcd.setCursor(0, 1); 
      lcd.print("You can run Vehicle");
      digitalWrite(greenLedPin, HIGH); // Green LED on
      digitalWrite(yellowLedPin, LOW); // Turn off yellow LED
      delay(2000); // Delay to show message
      pinEntered = true; // Set flag that PIN has been entered correctly
      Serial.println("Correct PIN Entered, Vehicle Ready");
    } else {
      // Wrong PIN entered, alert and reset
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Wrong PIN");
      Serial.println("Wrong PIN Entered");
      alertAndReset();
    }
  } else {
    // PIN entered correctly, run the motor
    runMotor();
  }
}

void runMotor() {
  // Run motors forward
  Serial.println("Vehicle Running...");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Happy Journey..!");
  
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  
  // Display running message for 5 seconds
  delay(50000);
  
  // Stop motors
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  
  // Display stop message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Motors Stopped");
  Serial.println("Motors Stopped");
  
  // Turn off LEDs
  digitalWrite(redLedPin, LOW);
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  
  // Reset entered PIN
  resetPin();
  
  // Reset flags
  pinEntered = false;
  alcoholDetected = false;
}

void alertAndShutdown() {
  // Turn off yellow LED explicitly
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  
  // Blink red LED and sound buzzer to alert for 5 seconds
  Serial.println("Alert: Alcohol Detected, Vehicle Off");
  unsigned long startTime = millis(); // Get the current time
  while (millis() - startTime < 5000) { // Run for 5 seconds
    digitalWrite(redLedPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(200); // LED and buzzer on for 200ms
    digitalWrite(redLedPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(200); // LED and buzzer off for 200ms
  }
  
  // Shutdown vehicle
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vehicle Off");
  Serial.println("Vehicle Shutdown");
  
  digitalWrite(redLedPin, LOW);
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  
  // Reset entered PIN
  resetPin();
  
  // Wait for a moment before allowing restart
  delay(2000);
}

void alertAndReset() {
  // Turn off yellow LED explicitly
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  
  // Blink red LED and sound buzzer to alert for 5 seconds
  Serial.println("Alert: Wrong PIN Entered");
  unsigned long startTime = millis(); // Get the current time
  while (millis() - startTime < 5000) { // Run for 5 seconds
    digitalWrite(redLedPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(200); // LED and buzzer on for 200ms
    digitalWrite(redLedPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(200); // LED and buzzer off for 200ms
  }
  
  // Clear entered PIN
  resetPin();
  Serial.println("Resetting PIN");
}

void resetPin() {
  // Reset entered PIN
  for (int i = 0; i < 4; ++i) {
    enteredPin[i] = '\0';
  }
}