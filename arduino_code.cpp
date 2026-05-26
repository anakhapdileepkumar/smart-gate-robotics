#include <Servo.h>

Servo gateServo;

const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 7;

long duration;
int distance;

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  gateServo.attach(6);

  // Gate initially closed
  gateServo.write(90);

  Serial.begin(9600);
}

void loop() {

  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  // Read echo time
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // Vehicle detected
  if(distance < 20) {

    Serial.println("Vehicle Detected - Opening Gate");

    // LED blinks while opening
    blinkLED();

    // Open gate
    gateServo.write(0);

    // Keep gate open for 5 seconds
    delay(5000);

    // Check continuously if vehicle is still there
    while(distance < 20) {

      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);

      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);

      digitalWrite(trigPin, LOW);

      duration = pulseIn(echoPin, HIGH);

      distance = duration * 0.034 / 2;

      Serial.print("Waiting... Distance: ");
      Serial.println(distance);

      delay(500);
    }

    Serial.println("Path Clear - Closing Gate");

    // LED blinks while closing
    blinkLED();

    // Close gate
    gateServo.write(90);
  }

  delay(500);
}

// LED blinking function
void blinkLED() {

  for(int i = 0; i < 6; i++) {

    digitalWrite(ledPin, HIGH);
    delay(300);

    digitalWrite(ledPin, LOW);
    delay(200);
  }
}
