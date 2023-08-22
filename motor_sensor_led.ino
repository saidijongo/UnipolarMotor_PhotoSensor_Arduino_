const int numLEDs = 2; // 
int ledPins[] = {7, 8};
const int rightSensorPin = 3; 
const int leftSensorPin = 4;  // left photomicrosensor

boolean ledsOn = false; //state of LEDs
boolean isCCW = false;  //
unsigned long lastTime = 0; 

void setup() {
 
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  pinMode(rightSensorPin, INPUT_PULLUP);
  pinMode(leftSensorPin, INPUT_PULLUP);
  
  //initial motor direction
  digitalWrite(leftSensorPin, HIGH);
  
  pinMode(5, OUTPUT); // CW+
  pinMode(6, OUTPUT); // CCW+
}

void loop() {
  unsigned long currentTime = millis();
  

  // Checking if the left sensor is interrupted
  if (digitalRead(leftSensorPin) == LOW) {
    if (isCCW) {
      isCCW = false;
    } else {
      isCCW = true;
    }
    
    //short delay to debounce the sensor
    delay(100);
  }

  // Checking if the right sensor is interrupted
  if (digitalRead(rightSensorPin) == LOW) {
    // Toggle LEDs
    ledsOn = !ledsOn;
    if (ledsOn) {
      if (isCCW) {
        turnOnAllLEDs();
      } else {
        blinkLEDsOneByOne();
      }
    } else {
      turnOffLEDs();
    }
    
    if (isCCW) {
      digitalWrite(5, LOW); 
      digitalWrite(6, HIGH); 
    } else {
      digitalWrite(5, HIGH); 
      digitalWrite(6, LOW); 
    }

    lastTime = currentTime; 
  }
  
  // Turning off LEDs after a certain time
  if (ledsOn && currentTime - lastTime > 500) {
    turnOffLEDs();
  }
}

void blinkLEDsOneByOne() {
  for (int i = 0; i < numLEDs; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(200);
    digitalWrite(ledPins[i], LOW);
  }
}

void turnOnAllLEDs() {
  for (int i = 0; i < numLEDs; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}

void turnOffLEDs() {
  for (int i = 0; i < numLEDs; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}
