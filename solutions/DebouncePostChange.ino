/*
  File: DebouncePostChange.ino
  
  Description:
  This implementation starts a debounce timer immediately after detecting a state change in the button.
  The LED state changes instantly when the button is pressed or released, and further state changes
  are ignored for the duration of the debounce period. This ensures that mechanical bouncing of the 
  button does not cause multiple transitions to be registered.

  Key Points:
  - The debounce timer is initiated immediately after detecting a change in button state.
  - Further changes are ignored for the debounce period, ensuring a stable button read.
  - The LED state is toggled immediately based on the button press, providing instant feedback.
  
  Pros:
  - Immediate feedback on the LED state change upon button press or release.
  - Requires one less variable and a simpler logic compared to the pre-stable change approach.

  Cons:
  - May still register brief bounces as state changes if the debounce period is too short.
  - Ignores all changes during the debounce period, which may miss legitimate rapid presses.
  - Might not detect false triggers caused by quick fluctuations that are shorter than the debounce period.
  
  Additional Notes:
  I advised this solution with systems in mind where the delay between input and action needs to be minimal.
  In scenarios where user input must be read and responded to immediately, this approach ensures prompt feedback.
*/

const int buttonPin = 2;
const int ledPin = 13;
// The debounce time in milliseconds to prevent immediate state changes
const unsigned long debounceDelay = 50;

int buttonPressCount = 0; // Counter for button presses
int buttonState = 0;      // Current debounced button state
unsigned long lastDebounceTime = 0; // Last time the button state changed

int ledState = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600); // Initialize serial communication at 9600 bps
}

void loop() {
  int reading = digitalRead(buttonPin);

  // Check if the debounce period has not passed
  if ((millis() - lastDebounceTime) < debounceDelay) {
    return; // Skip the rest of the loop during debounce period
  }

  // Check if the button state has changed
  if (reading != buttonState) {
    // Immediate state change
    buttonState = reading;  
    if (buttonState == HIGH) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);

      buttonPressCount++; // Increment the press count
      Serial.println(buttonPressCount);
    }

    // Start debounce timer to ignore further changes for the debounce period
    lastDebounceTime = millis();
  }
}

