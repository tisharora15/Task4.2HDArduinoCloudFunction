#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>

char ssid[] = "IBN-B";
char pass[] = "CUPunjab";

char server[] = "hdproject-3fe83-default-rtdb.firebaseio.com";

int redPin = 2;
int greenPin = 3;
int bluePin = 4;

WiFiSSLClient wifi;
HttpClient client = HttpClient(wifi, server, 443);

void toggleLED(String color, bool state) {
  if (color == "red") {
    if (state == true) {
      digitalWrite(redPin, HIGH);
    } else {
      digitalWrite(redPin, LOW);
    }
  } 
  else if (color == "green") {
    if (state == true) {
      digitalWrite(greenPin, HIGH);
    } else {
      digitalWrite(greenPin, LOW);
    }
  } 
  else if (color == "blue") {
    if (state == true) {
      digitalWrite(bluePin, HIGH);
    } else {
      digitalWrite(bluePin, LOW);
    }
  }
}

bool getFirebaseState(String color) {
  String path = "/color/" + color + ".json";  
  client.get(path);

  int status = client.responseStatusCode();
  String response = client.responseBody();
  response.trim();

  

  if (status == 200) {
    return (response == "true");  
  } else {
    return false;
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.println("Connecting to WiFi");
    delay(2000);
  }
  Serial.println("WiFi Connected!");
}

void loop() {
  toggleLED("red", getFirebaseState("red"));
  toggleLED("green", getFirebaseState("green"));
  toggleLED("blue", getFirebaseState("blue"));

  delay(500); 
}
