const int buttonPin = 2;

int buttonState = 0;
int lastButtonState = 0;
int validPressCount = 0;
int debounceDetected = 0;

// Variables for binary search
unsigned long debounceDelayMin = 1;
unsigned long debounceDelayMax = 50; // Set this to a reasonable upper bound
unsigned long debounceDelay = (debounceDelayMin + debounceDelayMax) / 2;
unsigned long lastDebounceTime = 0;
unsigned long lastPressTime = 0;
const int requiredValidPresses = 10;

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  unsigned long currentTime = millis();

  // Check for state change
  if (buttonState != lastButtonState) {
    if ((currentTime - lastDebounceTime) < debounceDelay) {
      debounceDetected++;
      validPressCount = 0; // Reset the count if a debounce is detected

      // Update debounceDelayMax
      debounceDelayMin = debounceDelay + 1;
      debounceDelay = (debounceDelayMin + debounceDelayMax) / 2;
    } else {
      lastDebounceTime = currentTime;

      if (buttonState == HIGH) {
        if (debounceDetected == 0) {
          validPressCount++;
          Serial.print("Valid Press Count: ");
          Serial.println(validPressCount);

          if (validPressCount >= requiredValidPresses) {
            // Update debounceDelayMax
            debounceDelayMax = debounceDelay;
            debounceDelay = (debounceDelayMin + debounceDelayMax) / 2;
            validPressCount = 0; // Reset the count after updating the delay
          }
        } else {
          debounceDetected = 0;
        }

        lastPressTime = currentTime;
      }
    }

    Serial.print("Current debounceDelay: ");
    Serial.println(debounceDelay);

    lastButtonState = buttonState;
  }
}