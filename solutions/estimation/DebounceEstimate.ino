/*

*/

const int buttonPin = 2;
const int ledPin = 13;

int buttonState = 0;
int lastButtonState = 0;
int buttonPressCount = 0;

// Required for the Toggle mode
int ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // Check for state change and count button presses
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPressCount++;
      Serial.println(buttonPressCount);
    }

    if (buttonState == HIGH) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);

      lastButtonState = buttonState;
    }
}

