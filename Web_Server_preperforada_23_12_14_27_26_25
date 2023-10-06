// Abre el monitor serial, verifica los baudios, copia la ip y pegala en un un navegador (de preferencia Chrome)
// Colocas el nombre de tu red y contraseña
#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
#include <Servo.h>

const char* ssid = "NOMBRERED";
const char* password = "PASSWORD";

// Create an instance of the AsyncWebServer
AsyncWebServer server(80);

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

int servo1Pos = 90; // Initial position for servo 1
int servo2Pos = 90; // Initial position for servo 2
int servo3Pos = 90; // Initial position for servo 3
int servo4Pos = 90; // Initial position for servo 4
int servo5Pos = 90; // Initial position for servo 5
int servo6Pos = 90; // Initial position for servo 6

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  // Initialize servo motors
  servo1.attach(23);
  servo2.attach(12);
  servo3.attach(14);
  servo4.attach(27);
  servo5.attach(26);
  servo6.attach(25);
  
  // Print ESP32 IP address
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html><body>";
    html += "<h1>Servo Control</h1>";
    html += "<p>Servo 1: <input type='range' min='0' max='180' value='90' id='servo1Slider'></p>";
    html += "<p>Servo 2: <input type='range' min='0' max='180' value='90' id='servo2Slider'></p>";
    html += "<p>Servo 3: <input type='range' min='0' max='180' value='90' id='servo3Slider'></p>";
    html += "<p>Servo 4: <input type='range' min='0' max='180' value='90' id='servo4Slider'></p>";
    html += "<p>Servo 5: <input type='range' min='0' max='180' value='90' id='servo5Slider'></p>";
    html += "<p>Servo 6: <input type='range' min='0' max='180' value='90' id='servo6Slider'></p>";
    html += "<button onclick='updateServos()'>Apply</button>";
    html += "<script>";
    html += "function updateServos() {";
    html += "var servo1Value = document.getElementById('servo1Slider').value;";
    html += "var servo2Value = document.getElementById('servo2Slider').value;";
    html += "var servo3Value = document.getElementById('servo3Slider').value;";
    html += "var servo4Value = document.getElementById('servo4Slider').value;";
    html += "var servo5Value = document.getElementById('servo5Slider').value;";
    html += "var servo6Value = document.getElementById('servo6Slider').value;";
    html += "var xhr = new XMLHttpRequest();";
    html += "xhr.open('GET', '/setServos?s1=' + servo1Value + '&s2=' + servo2Value + '&s3=' + servo3Value + '&s4=' + servo4Value + '&s5=' + servo5Value + '&s6=' + servo6Value, true);";
    html += "xhr.send();";
    html += "}";
    html += "</script>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  server.on("/setServos", HTTP_GET, [](AsyncWebServerRequest *request){
    int s1 = request->arg("s1").toInt();
    int s2 = request->arg("s2").toInt();
    int s3 = request->arg("s3").toInt();
    int s4 = request->arg("s4").toInt();
    int s5 = request->arg("s5").toInt();
    int s6 = request->arg("s6").toInt();
    servo1.write(s1);
    servo2.write(s2);
    servo3.write(s3);
    servo4.write(s4);
    servo5.write(s5);
    servo6.write(s6);
    request->send(200, "text/plain", "Servos updated");
  });

  server.begin();
}


void loop() {

}
