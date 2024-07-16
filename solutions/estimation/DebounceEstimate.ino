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

