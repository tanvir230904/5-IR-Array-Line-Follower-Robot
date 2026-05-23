#include <AFMotor.h>


// 1. PIN DEFINITIONS
#define S_FAR_L   A4  
#define S_INN_L   A3  
#define S_CENTER  A2  
#define S_INN_R   A1  
#define S_FAR_R   A0  


// 2. SETTINGS
const int threshold = 560;
const int baseSpeed = 250;


// Memory variable: 0 = Center, 1 = Left, 2 = Right
int lastSeen = 0;


AF_DCMotor motorFL(3); AF_DCMotor motorFR(4);
AF_DCMotor motorRL(2); AF_DCMotor motorRR(1);


void setup() {
  stopMotors();
  pinMode(S_FAR_L, INPUT); pinMode(S_INN_L, INPUT);
  pinMode(S_CENTER, INPUT); pinMode(S_INN_R, INPUT);
  pinMode(S_FAR_R, INPUT);
 
  motorFL.setSpeed(baseSpeed);
  motorFR.setSpeed(baseSpeed);
  motorRL.setSpeed(baseSpeed);
  motorRR.setSpeed(baseSpeed);
  delay(2000);
}


void loop() {
  int vFarL = analogRead(S_FAR_L);
  int vInL  = analogRead(S_INN_L);
  int vCent = analogRead(S_CENTER);
  int vInR  = analogRead(S_INN_R);
  int vFarR = analogRead(S_FAR_R);


  // --- LOGIC ---


  // 1. FORWARD (Center is on line)
  if (vCent < threshold) {
    moveForward();
    lastSeen = 0;
  }
  // 2. LEFT (Left sensors hit the line)
  else if (vInL < threshold || vFarL < threshold) {
    turnRight();
    lastSeen = 1;
  }
  // 3. RIGHT (Right sensors hit the line)
  else if (vInR < threshold || vFarR < threshold) {
    turnLeft();
    lastSeen = 2;
  }
  // 4. LINE LOST (Recovery Mode)
  else {
    if (lastSeen == 1) {
      // If we last saw the line on the left, spin left to find it
      spinRight();
    }
    else if (lastSeen == 2) {
      // If we last saw the line on the right, spin right to find it
      spinLeft();
    }
    else {
      stopMotors();
    }
  }
}


// --- MOVEMENT FUNCTIONS ---


void moveForward() {
  motorFL.run(FORWARD); motorFR.run(FORWARD);
  motorRL.run(FORWARD); motorRR.run(FORWARD); // Polarity Fix
}


void turnLeft() {
  motorFL.run(RELEASE); motorRL.run(RELEASE);
  motorFR.run(FORWARD); motorRR.run(FORWARD);
}


void turnRight() {
  motorFL.run(FORWARD); motorRL.run(FORWARD);
  motorFR.run(RELEASE); motorRR.run(RELEASE);
}


// Sharp "Tank Turns" for recovery
void spinLeft() {
  motorFL.run(BACKWARD); motorRL.run(BACKWARD);
  motorFR.run(FORWARD);  motorRR.run(FORWARD);
}


void spinRight() {
  motorFL.run(FORWARD);  motorRL.run(FORWARD);
  motorFR.run(BACKWARD); motorRR.run(BACKWARD); // RR Forward is BACKWARD port logic
}


void stopMotors() {
  motorFL.run(RELEASE); motorFR.run(RELEASE);
  motorRL.run(RELEASE); motorRR.run(RELEASE);
}
