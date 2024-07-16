/*
  File: DebounceStableReadings.ino
  
  Description:
  This implementation debounces the button by counting stable readings.
  When a button state change is detected, the new state must be consistent for a defined number of consecutive readings to be considered valid. 
  If the button state remains stable for the required number of readings, the button state is updated, and the LED is toggled accordingly.

  Key Points:
  - Counts stable readings before considering a state change valid.
  - Updates the button state only if stable for a specified threshold.
  - Provides immediate feedback by turning the LED on or off based on the button press.
  
  Pros:
  - Effective debounce without using timers or delays.
  - Simple implementation with minimal additional logic.
  
  Cons:
  - May introduce a slight delay due to the need for stable readings.

  Additional Notes:
  I conceived this idea while trying to find a non-well-known hardware solution.
  One such hardware solution involves using a capacitor and a transistor for debouncing. 
  Here's how it should have worked:
  - When the button is pressed, it starts charging a capacitor through a resistor.
  - The capacitor smooths out any rapid changes in voltage due to button bounces.
  - Once the capacitor voltage reaches a certain threshold, it turns on a transistor.
  - The transistor then allows current to flow, providing a clean and stable signal to the microcontroller.
*/

const int buttonPin = 2; // Button pin
const int ledPin = 13;   // LED pin

int buttonState = 0;          // Current button state
int lastButtonState = 0;      // Previous button state
int stableCount = 0;          // Count of stable readings
const int stabilityThreshold = 5; // Number of stable readings required
int buttonPressCount = 0;     // Button press counter

int ledState = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600); // Initialize serial communication at 9600 bps
}

void loop() {
  int reading = digitalRead(buttonPin); // Read the current button state

  if (reading == lastButtonState) {
    stableCount++; // Increment stable reading count
  } else {
    stableCount = 0; // Reset stable reading count
  }

  // Update button state if stable for required number of readings
  if (stableCount >= stabilityThreshold) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        ledState = !ledState;
        digitalWrite(ledPin, ledState);

        buttonPressCount++; // Increment the press count
        Serial.println(buttonPressCount);
      }
    }
    // Must be set to 0 to avoid variable overflow if change won't change for a while
    // Might be handled in ways for more sophisticated LED behaviors
    stableCount = 0; // Reset stable reading count after state change
  }

  lastButtonState = reading; // Update the previous button state
}

