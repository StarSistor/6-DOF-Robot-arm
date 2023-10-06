

#include <Servo.h> // codigo para mover seros de brazo 6 dof mediante monitor serial

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;


void setup() {
  Serial.begin(115200);

  servo1.attach(23);
  servo2.attach(12);
  servo3.attach(14);
  servo4.attach(27);
  servo5.attach(26);
  servo6.attach(25);

  Serial.println("Enter final servo positions (0 to 180) for each servo:");
}


void loop() {
  if (Serial.available() > 0) {
    int servoPos[6];
    
    for (int i = 0; i < 6; i++) {
      while (Serial.available() == 0);
      servoPos[i] = Serial.parseInt();
    }

    for (int i = 0; i < 6; i++) {
      if (servoPos[i] >= 0 && servoPos[i] <= 180) {
        moveServo(i + 1, servoPos[i]);
      } else {
        Serial.println("Invalid servo position. Please enter a value between 0 and 180.");
      }
    }

    Serial.println("Enter servo position (0 to 180) for each servo:");
  }
}

void moveServo(int servoNumber, int position) {
  switch (servoNumber) {
    case 1:
      servo1.write(position);
      break;
    case 2:
      servo2.write(position);
      break;
    case 3:
      servo3.write(position);
      break;
    case 4:
      servo4.write(position);
      break;
    case 5:
      servo5.write(position);
      break;
    case 6:
      servo6.write(position);
      break;
    default:
      break;
  }
}
