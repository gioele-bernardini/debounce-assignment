const int buttonPin = 2;
const int ledPin = 13;

int buttonState = 0;
int lastButtonState = 0;
int buttonPressCount = 0;

// Required for the Toggle mode
int ledState = LOW;

// Variables for debounce detection
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; // Initial debounce delay
bool debounceDetected = false;
int debounceCount = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // Check for state change
  if (buttonState != lastButtonState) {
    unsigned long currentTime = millis();
    
    // Detect debounce
    if ((currentTime - lastDebounceTime) < debounceDelay && !debounceDetected) {
      debounceCount++;
      debounceDetected = true;
      Serial.print("Debounce Detected: ");
      Serial.println(debounceCount);
    }
    
    if ((currentTime - lastDebounceTime) >= debounceDelay) {
      debounceDetected = false;
    }
    
    lastDebounceTime = currentTime;
    
    if (buttonState == HIGH) {
      buttonPressCount++;
      Serial.print("Button Press Count: ");
      Serial.println(buttonPressCount);

      ledState = !ledState;
      digitalWrite(ledPin, ledState);
    }

    lastButtonState = buttonState;
  }
}

