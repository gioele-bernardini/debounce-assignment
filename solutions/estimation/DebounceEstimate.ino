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
const unsigned long debounceCheckInterval = 500; // 0.5 seconds

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  unsigned long currentTime = millis();

  // Check for state change
  if (buttonState != lastButtonState) {
    // Transition detected
    if ((currentTime - lastDebounceTime) < debounceCheckInterval) {
      if ((currentTime - lastDebounceTime) > debounceDelay) {
        // Increase debounce delay
        debounceDelayMin = debounceDelay + 1;
        debounceDelay = (debounceDelayMin + debounceDelayMax) / 2;
        debounceDetected++;
        Serial.print("Debounce detected: ");
        Serial.println(debounceDetected);
        Serial.print("Increasing debounce delay to: ");
        Serial.println(debounceDelay);
      }
    } else {
      // Valid press detected
      validPressCount++;
      Serial.print("Valid Press Count: ");
      Serial.println(validPressCount);

      if (validPressCount >= requiredValidPresses) {
        // Update debounceDelayMax
        debounceDelayMax = debounceDelay;
        debounceDelay = (debounceDelayMin + debounceDelayMax) / 2;
        validPressCount = 0; // Reset the count after updating the delay
        Serial.print("Increasing valid presses debounce delay to: ");
        Serial.println(debounceDelay);
      }

      debounceDetected = 0;
    }

    lastDebounceTime = currentTime;
    lastButtonState = buttonState;
  }

  Serial.print("Current debounceDelay: ");
  Serial.println(debounceDelay);
}

