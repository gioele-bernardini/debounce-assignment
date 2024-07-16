/*
  Project: LED Control with Button
  Description: This project demonstrates various configurations for controlling an LED using a button. 
               Note that debounce handling is not implemented in this example. 

  Configurations:
    1. MODE_TOGGLE - The LED toggles its state with each button press.
    2. MODE_HOLD - The LED remains on while the button is pressed and off when released.
    3. MODE_BLINK - The LED blinks briefly with each button press.

  Usage:
    - Modify the CURRENT_MODE constant to switch between different LED behaviors.
    - This example uses MODE_TOGGLE as the default configuration.

    - Ensure proper hardware connections before running the code.
    - Be aware of the *pulldown* resistor for the button connection.

  Hardware:
    - Button connected to pin 2.
    - LED connected to pin 13.

  Author: [Gioele Bernardini]
  Date: [14/07/2024]
*/

#define MODE_TOOGLE 1
#define MODE_HOLD 2
#define MODE_BLINK 3

// Modify this value to change the LED behavior
#define CURRENT_MODE MODE_TOOGLE

const int buttonPin = 2;
const int ledPin = 13;

int buttonState = 0;
int lastButtonState = 0;
int buttonPressCount = 0;

// Required for the Toggle mode
int ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // Check for state change and count button presses
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPressCount++;
      Serial.println(buttonPressCount);
    }

    handleLED(CURRENT_MODE, buttonState);
    lastButtonState = buttonState;
  }
}

// Note: Both parameters are global variables and are directly accessible.
// This approach is used to promote good coding practices and enhance adaptability.
void handleLED(int mode, int buttonState) {
  switch (mode) {
    case MODE_TOOGLE:
      toggleLED(buttonState);
      break;
    case MODE_HOLD:
      holdLED(buttonState);
      break;
    case MODE_BLINK:
      blinkLED(buttonState);
      break;

    default:
      break;
  }
}

// Toggles the LED state on button press
void toggleLED(int buttonState) {
  if (buttonState == HIGH) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}

// Keeps the LED on while the button is pressed
void holdLED(int buttonState) {
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

// Blinks the LED briefly when the button is pressed
void blinkLED(int buttonState) {
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
  }
}

