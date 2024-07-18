/*
  File: DebounceEstimate.ino
  
  Description:
  This implementation detects a state change in the button, and starts a debounce timer. During the debounce period, further state changes are ignored. The LED state toggles instantly when the button is pressed, and debounces are counted and displayed via serial communication. Button presses are also counted and displayed.

  Key Points:
  - Debounce timer is initiated upon detecting a change in button state.
  - Further state changes are ignored during the debounce period, ensuring stable button reads.
  - The LED state toggles immediately on button press, providing instant feedback.
  - Counts both debounces and button presses, displaying them via serial communication.

  Pros:
  - Immediate feedback on LED state change upon button press.
  - Tracks and displays debounce events and button press counts, aiding in debugging and analysis.

  Cons:
  - May register brief bounces as state changes if debounce period is too short.
  - Ignores all changes during debounce period, possibly missing rapid legitimate presses.
  - Might not detect false triggers caused by quick fluctuations shorter than the debounce period.

  Additional Notes:
  This solution is suited for systems requiring immediate feedback upon button press, with added functionality of counting debounces and button presses for better insight and debugging. This solution may require improvements. 

  Usage for Estimating Debounce Delay:
  - Upload the program to your microcontroller and open the serial monitor at 9600 baud rate.
  - Press the button several times and observe the "Debounces" and "Button presses" counts in the serial monitor.
  - If you notice a high number of debounces, increase the debounceDelay value.
  - If the button presses are not registered reliably, decrease the debounceDelay value.
  - Repeat the process of adjusting debounceDelay and pressing the button until the debounce count is minimal and the button press count is accurate.
*/

#define buttonPin 2
#define ledPin 13

int buttonState = LOW;             // the current reading from the input pin
int lastReading = LOW;             // the previous reading from the input pin
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50;   // the debounce time; increase if the output flickers
int ledState = LOW;                // the current state of the LED
int buttonPressCount = 0;          // count of button presses
int debounceCount = 0;             // count of debounces

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(buttonPin);

  // Check for changes in reading to identify a potential debounce
  if (reading != lastReading) {
    // Update the debounce timer
    if ((millis() - lastDebounceTime) < debounceDelay) {
      debounceCount++;  // Increment debounce count
      Serial.print("Debounces: ");
      Serial.println(debounceCount);  // Print debounce count
    }
    lastDebounceTime = millis();  // Reset debounce timer on state change
  }

  // Check if debounce time has passed
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the debounce period has passed, update buttonState if necessary
    if (reading != buttonState) {
      buttonState = reading;  // Update button state

      // Handle the button press
      if (buttonState == HIGH) {
        ledState = !ledState;
        digitalWrite(ledPin, ledState);

        buttonPressCount++; // Increment the press count
        Serial.print("Button presses: ");
        Serial.println(buttonPressCount);
      }
    }
  }

  // Save the current reading for the next iteration
  lastReading = reading;
}

