/*
  File: BouncePlotter.ino
*/

#define MODE_TOOGLE 1
#define MODE_HOLD 2
#define MODE_BLINK 3

// Modify this value to change the LED behavior
#define CURRENT_MODE MODE_TOOGLE

const int buttonPin = 2;
const int ledPin = 13;

int buttonPressCount = 0; // Counter for button presses
int buttonState = 0;      // Current button state
int lastButtonState = 0;  // Last button state

int ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600); // Initialize serial communication at 9600 bps

  Serial.print(buttonState); // Print initial state
}

void loop() {
  int reading = digitalRead(buttonPin);

  // Update the button state if it has changed
  if (reading != lastButtonState) {
    buttonState = reading;
    
    // Send the button state to the Serial Monitor for the plotter
    Serial.print(buttonState);

    // Handle button press
    handleLED(CURRENT_MODE, buttonState);
  }

  lastButtonState = reading;
}

// Handle LED modes
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

