/*
  Project: Button Debounce Optimizer
  Description: This program implements a debounce system for a button, automatically adjusting the debounce
               time to minimize erroneous readings. The program uses two variables to track the current and
               previous state of the button, as well as a timer for debounce.

  Functionality:
    - When a change in the button state is detected, it checks if it is a bounce or an actual action.
    - If a bounce is detected, the program increments the debounce time.
    - If no bounces are detected for a certain number of iterations, the program decrements the debounce time.
    - The debounce time is automatically adjusted until an optimal value is found.

  Motivation:
    - Automatically optimize the debounce time for a button, avoiding the need for manual adjustments.

  Prototype Note:
    - This code is a prototype and an embryonic version. Due to time constraints for my thesis,
      it has only been sketched out and may require further improvements and refinements.

  Author: Gioele Bernardini
  Date: 16/07/2024
*/

#define buttonPin 2
#define ledPin 13
#define TWEAK_ACCURACY 100

int buttonState = LOW;             // the current reading from the input pin
int lastReading = LOW;             // the previous reading from the input pin
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled

unsigned long minDebounceDelay = 1;
unsigned long maxDebounceDelay = 1000;
// the debounce time; increase if the output flickers
unsigned long debounceDelay = (minDebounceDelay + maxDebounceDelay) / 2;

int ledState = LOW;                // the current state of the LED
int buttonPressCount = 0;          // count of button presses
int debounceCount = 0;             // count of debounces
int noDebounceCount = 0;           // count of iterations without debounces

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  int reading = digitalRead(buttonPin);

  // Check for changes in reading to identify a potential debounce
  if (reading != lastReading) {
    // Update the debounce timer
    if ((millis() - lastDebounceTime) < debounceDelay) {
      debounceCount++;  // Increment debounce count
      incrementDelay();

      Serial.print("Debounces: ");
      Serial.println(debounceCount);  // Print debounce count
      noDebounceCount = 0;  // Reset no debounce count
    } else {
      noDebounceCount++;  // Increment no debounce count
      if (noDebounceCount > 10) {
        decrementDelayTime();
        noDebounceCount = 0;
      }
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

  if (checkDelay()) {
    Serial.println("Range found:");
    Serial.print("Min debounce delay: ");
    Serial.println(minDebounceDelay);
    Serial.print("Max debounce delay: ");
    Serial.println(maxDebounceDelay);
    while(1);
  }
}

void incrementDelay() {
  minDebounceDelay = debounceDelay;
  debounceDelay = (minDebounceDelay + maxDebounceDelay) / 2;
  if (debounceDelay > maxDebounceDelay) {
    debounceDelay = maxDebounceDelay;
  }
  if (debounceDelay < minDebounceDelay) {
    debounceDelay = minDebounceDelay;
  }
  Serial.print("Increment delay: ");
  Serial.println(debounceDelay);
}

void decrementDelayTime() {
  maxDebounceDelay = debounceDelay;
  debounceDelay = (minDebounceDelay + maxDebounceDelay) / 2;
  if (debounceDelay > maxDebounceDelay) {
    debounceDelay = maxDebounceDelay;
  }
  if (debounceDelay < minDebounceDelay) {
    debounceDelay = minDebounceDelay;
  }
  Serial.print("Decrement delay: ");
  Serial.println(debounceDelay);
}

int checkDelay() {
  if ((maxDebounceDelay - minDebounceDelay) <= TWEAK_ACCURACY)
    return 1;
  else
    return 0;
}

