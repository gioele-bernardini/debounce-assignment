/*
  File: DebouncePreChange.ino
  
  Description:
  The first solution I advised.
  When a new button state is detected, a debounce timer is started. The new state must remain stable
  for the duration of the timer to be considered valid. If the state remains unchanged past the debounce
  period, buttonState is updated. If buttonState transitions from LOW to HIGH, it is considered a button
  press, and the press count is incremented. This approach ensures that only stable state changes are
  registered, effectively debouncing the button input.

  Key Points:
  - The debounce timer is initiated after detecting a change in button state.
  - The new state must remain unchanged for the debounce period to update the button state.
  - The LED state is toggled immediately based on the button press, providing instant feedback.

  Pros:
  - Ensures that only stable state changes are registered, providing reliable input.
  - Reduces the chance of false triggers due to mechanical bouncing, compared to the other timer approach

  Cons:
  - Slight delay in updating the LED state due to the debounce period.
  - Requires additional logic to compare the current reading with the last reading.

  This solution helps mitigate the effects of button bounce by requiring the state to remain
  stable for a set period, ensuring reliable and predictable behavior of the LED in response
  to button presses.
*/

const int buttonPin = 2;
const int ledPin = 13;
// The debounce time in milliseconds to ensure stable button reading
const unsigned long debounceDelay = 50;

int buttonPressCount = 0; // Counter for button presses
int buttonState = 0;      // Current debounced button state
int lastReading = 0;      // Previous button reading
unsigned long lastDebounceTime = 0; // Last time the button state changed

int ledState = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600); // Initialize serial communication at 9600 bps
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastReading) {
    lastDebounceTime = millis();  // Reset debounce timer on state change
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the debounce period has passed, update buttonState if necessary
    if (reading != buttonState) {
      buttonState = reading;  // Update button state

      // Handle the button press
      if (buttonState == HIGH) {
        ledState = !ledState;
        digitalWrite(ledPin, ledState);

        buttonPressCount++; // Increment the press count
        Serial.println(buttonPressCount);
      }
    }
  }

  // Save the current reading for the next iteration
  lastReading = reading;
}

