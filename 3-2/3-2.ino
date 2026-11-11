
const int ledPin = 3;
const int buttonPin = 2;

int mode = 0;

int buttonState = HIGH;
int lastButtonReading = HIGH;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

unsigned long previousMillis = 0;

int blinkInterval = 1000;
int ledState = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  digitalWrite(ledPin, HIGH);
}

void loop() {

  int reading = digitalRead(buttonPin);

  // 按鈕防彈跳
  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay) {

    if (reading != buttonState) {
      buttonState = reading;

      // 按下按鈕
      if (buttonState == LOW) {

        mode++;

        // 第四次回到恆亮
        if (mode > 3) {
          mode = 0;
        }

        previousMillis = millis();
        ledState = HIGH;

        // 設定閃爍速度
        if (mode == 1) {
          blinkInterval = 1000;
        }
        else if (mode == 2) {
          blinkInterval = 600;
        }
        else if (mode == 3) {
          blinkInterval = 350;
        }

        digitalWrite(ledPin, HIGH);
      }
    }
  }

  lastButtonReading = reading;

  // 控制 LED
  if (mode == 0) {

    // 恆亮
    digitalWrite(ledPin, HIGH);

  } else {

    // 閃爍
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= blinkInterval) {

      previousMillis = currentMillis;

      ledState = !ledState;

      digitalWrite(ledPin, ledState);
    }
  }
}
