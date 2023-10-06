
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi.h>
#include "ESPAsyncWebSrv.h"

// Replace with your network credentials
const char* ssid = "NOMBRERED";
const char* password = "PASSWORD";

// PCA9685 I2C address
#define PCA9685_ADDR 0x40

// Servo settings
#define SERVO_MIN_ANGLE 0
#define SERVO_MAX_ANGLE 180
#define SERVO_MIN_PULSE_WIDTH 125  // Adjust as needed
#define SERVO_MAX_PULSE_WIDTH 575 // Adjust as needed

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PCA9685_ADDR);

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  // Initialize PCA9685
  pwm.begin();
  pwm.setPWMFreq(60);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print ESP32 IP address
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Set up web server routes
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "<html><body><h1>Servo Control</h1>"
                                    "<p>Servo 1: <input type=\"range\" min=\"0\" max=\"180\" value=\"90\" id=\"servo1\"></p>"
                                    "<p>Servo 2: <input type=\"range\" min=\"0\" max=\"180\" value=\"90\" id=\"servo2\"></p>"
                                    "<p>Servo 3: <input type=\"range\" min=\"0\" max=\"180\" value=\"90\" id=\"servo3\"></p>"
                                    "<p>Servo 4: <input type=\"range\" min=\"0\" max=\"180\" value=\"90\" id=\"servo4\"></p>"
                                    "<p>Servo 5: <input type=\"range\" min=\"0\" max=\"180\" value=\"90\" id=\"servo5\"></p>"
                                    "<p>Servo 6: <input type=\"range\" min=\"0\" max=\"180\" value=\"90\" id=\"servo6\"></p>"
                                    "<button onclick=\"sendValues()\">Set Values</button>"
                                    "<script>function sendValues() {"
                                    "var servo1 = document.getElementById('servo1').value;"
                                    "var servo2 = document.getElementById('servo2').value;"
                                    "var servo3 = document.getElementById('servo3').value;"
                                    "var servo4 = document.getElementById('servo4').value;"
                                    "var servo5 = document.getElementById('servo5').value;"
                                    "var servo6 = document.getElementById('servo6').value;"
                                    "var url = '/set?servo1=' + servo1 + '&servo2=' + servo2 + '&servo3=' + servo3 + '&servo4=' + servo4 + '&servo5=' + servo5 + '&servo6=' + servo6;"
                                    "var xhr = new XMLHttpRequest();"
                                    "xhr.open('GET', url, true);"
                                    "xhr.send();"
                                    "}</script></body></html>");
  });

  server.on("/set", HTTP_GET, [](AsyncWebServerRequest *request){
    int servo1Value = request->getParam("servo1")->value().toInt();
    int servo2Value = request->getParam("servo2")->value().toInt();
    int servo3Value = request->getParam("servo3")->value().toInt();
    int servo4Value = request->getParam("servo4")->value().toInt();
    int servo5Value = request->getParam("servo5")->value().toInt();
    int servo6Value = request->getParam("servo6")->value().toInt();

    setServoAngle(0, servo1Value);
    setServoAngle(1, servo2Value);
    setServoAngle(2, servo3Value);
    setServoAngle(3, servo4Value);
    setServoAngle(4, servo5Value);
    setServoAngle(5, servo6Value);

    request->send(200, "text/plain", "Servo values set");
  });

  server.begin();
}

void setServoAngle(uint8_t servoIndex, int angle) {
  if (angle < SERVO_MIN_ANGLE) {
    angle = SERVO_MIN_ANGLE;
  } else if (angle > SERVO_MAX_ANGLE) {
    angle = SERVO_MAX_ANGLE;
  }

  int pulseWidth = map(angle, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE, SERVO_MIN_PULSE_WIDTH, SERVO_MAX_PULSE_WIDTH);
  pwm.setPWM(servoIndex, 0, pulseWidth);
}

void loop() {
  
}
