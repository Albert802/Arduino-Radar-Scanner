#include <Servo.h>

// Pin definitions
const int TRIG_PIN = 9;
const int ECHO_PIN = 10;
const int SERVO_PIN = 11;

// Servo configuration
Servo radarServo;
const int SERVO_START = 0;
const int SERVO_END = 180;
const int STEP_DELAY = 15; // ms between steps

// Radar data
float distances[181]; // Array to store distances for each angle
int currentAngle = 0;
bool sweepForward = true;

void setup() {
  Serial.begin(9600);
  
  // Initialize ultrasonic pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Initialize servo
  radarServo.attach(SERVO_PIN);
  radarServo.write(SERVO_START);
  
  delay(1000); // Allow servo to stabilize
  Serial.println("RADAR_START");
}

void loop() {
  // Sweep the servo
  if (sweepForward) {
    currentAngle++;
    if (currentAngle >= SERVO_END) {
      currentAngle = SERVO_END;
      sweepForward = false;
    }
  } else {
    currentAngle--;
    if (currentAngle <= SERVO_START) {
      currentAngle = SERVO_START;
      sweepForward = true;
    }
  }
  
  // Move servo to current angle
  radarServo.write(currentAngle);
  delay(STEP_DELAY);
  
  // Read distance at this angle
  float distance = measureDistance();
  distances[currentAngle] = distance;
  
  // Send data to serial
  sendRadarData(currentAngle, distance);
}

float measureDistance() {
  // Clear trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Send 10us pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read echo time
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // Timeout after 30ms
  
  if (duration == 0) {
    return 999.0; // No obstacle detected
  }
  
  // Calculate distance in cm (speed of sound = 343 m/s)
  float distance = duration * 0.034 / 2;
  
  // Limit maximum distance
  if (distance > 400) distance = 400;
  
  return distance;
}

void sendRadarData(int angle, float distance) {
  Serial.print(angle);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(",");
  
  // Determine object presence and status
  if (distance < 20) {
    Serial.println("CRITICAL");
  } else if (distance < 50) {
    Serial.println("WARNING");
  } else if (distance < 200) {
    Serial.println("SAFE");
  } else {
    Serial.println("CLEAR");
  }
}
