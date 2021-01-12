#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

const char* ssid = "admin";
const char* password = "12345678";

ESP8266WebServer server(80);

const byte AIN1 = D0; //GPI04
const byte AIN2 = D1; //GPI0
const byte AIN3 = D2; // GPI02
const byte AIN4 = D3; // GPIO14

const byte BIN1 = D4; // GPI05
const byte BIN2 = D5; //GPI12
const byte BIN3 =  D6; //GPIO13
const byte BIN4 =  D7; //GPIO15

const byte servoPin =  D8; //GPIO3   //

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

void carForward() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(AIN3, HIGH);
  digitalWrite(AIN4, LOW);
  delay(10);
  Serial.println("carForward");
}
void carBackward() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(AIN3, LOW);
  digitalWrite(AIN4, HIGH);
  delay(10);
  Serial.println("carBackward");
}
void carLeft() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(AIN3, HIGH);
  digitalWrite(AIN4, LOW);
  delay(10);
  Serial.println("carLeft");
}
void carRight() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(AIN3, LOW);
  digitalWrite(AIN4, HIGH);
  delay(10);
  Serial.println("carRight");
}
void carStop() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(AIN3, LOW);
  digitalWrite(AIN4, LOW);
  delay(10);
  Serial.println("carStop");
}
void servoTrigger() {
  myservo.write(150);
  Serial.println("servoTriggered");
  delay(1000);
  myservo.write(30);
  delay(1000);
}
void pumpON() {
  Serial.println("Pump ON");
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void pumpOFF() {
  Serial.println("Pump OFF");
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}

void drillForward() {
  Serial.println("Drill ON");
  digitalWrite(BIN3, HIGH);
  digitalWrite(BIN4, LOW);
  delay(3000);
  digitalWrite(BIN3, LOW);
  digitalWrite(BIN4, LOW);
}

void drillBackward() {
  Serial.println("Drill ON");
  digitalWrite(BIN3, LOW);
  digitalWrite(BIN4, HIGH);
  delay(3000);
  digitalWrite(BIN3, LOW);
  digitalWrite(BIN4, LOW);
}

void drillOFF() {
  Serial.println("Drill OFF");
  digitalWrite(BIN3, LOW);
  digitalWrite(BIN4, LOW);
}

void handleCar() {
  String message = "";
  int BtnValue = 0;
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "a")
    {
      String s = server.arg(i);
      BtnValue = s.toInt();
    }
    Serial.println(server.argName(i) + ": " + server.arg(i) + "\n");
  }

  switch (BtnValue) {
    case 1: //ON1
      pumpON();
      break;

    case 2: //carForward
      carForward();
      break;

    case  3://OFF1
      pumpOFF();
      break;

    case  4://carLeft
      carLeft();
      break;

    case 5: //carStop
      carStop();
      break;

    case  6://carRight
      carRight();
      break;

    case 7://s_ON
      servoTrigger();
      break;

    case 8://
      carBackward();
      break;

    case 9://fDrill
      drillForward();
      break;

    case 10://bDrill
      drillBackward();
      break;

    default:
      break;
  }

  message += "<html> <head> <title>Robot Car</title><head>";
  message += "<body><h3>Agriculture Robot</h1>";
  message += "<table> ";
  message += "<tr>";
  message += "<td><p><a href=\"/car?a=1\"><button style=\"width:100;height:100;font-size:25px;\" class=\"button\">ON1</button></a></p> ";
  message += "<td><p><a href=\"/car?a=2\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">^</button></a></p> ";
  message += "<td><p><a href=\"/car?a=3\"><button style=\"width:100;height:100;font-size:25px;\" class=\"button\">OFF1</button></a></p> ";
  message += "<tr>";
  message += "<td><p><a href=\"/car?a=4\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\"> < </button></a></p> ";
  message += "<td><p><a href=\"/car?a=5\"><button style=\"width:100;height:100;font-size:40px;\" class=\"button\">Stop</button></a></p> ";
  message += "<td><p><a href=\"/car?a=6\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\"> > </button></a></p> ";
  message += "<tr>";
  message += "<td><p><a href=\"/car?a=7\"><button style=\"width:100;height:100;font-size:25px;\" class=\"button\">s_ON</button></a></p> ";
  message += "<td><p><a href=\"/car?a=8\"><button style=\"width:100;height:100;font-size:100px;\" class=\"button\">v</button></a></p> ";
  message += "<td><p><a href=\"/car?a=9\"><button style=\"width:100;height:100;font-size:25px;\" class=\"button\">fDrill</button></a></p> ";
  message += "<td><p><a href=\"/car?a=10\"><button style=\"width:100;height:100;font-size:25px;\" class=\"button\">bDrill</button></a></p> ";
  message += "</table> ";
  message += "</body></html>";
  server.send(200, "text/html", message);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}


void setup() {

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(AIN3, OUTPUT);
  pinMode(AIN4, OUTPUT);

  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(AIN3, LOW);
  digitalWrite(AIN4, LOW);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(BIN3, OUTPUT);
  pinMode(BIN4, OUTPUT);

  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  digitalWrite(BIN3, LOW);
  digitalWrite(BIN4, LOW);

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(servoPin, OUTPUT);
  myservo.attach(servoPin);
  myservo.write(30);

  server.on("/", handleRoot);
  server.on("/car", handleCar);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
