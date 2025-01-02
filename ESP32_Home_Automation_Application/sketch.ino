#define BLYNK_TEMPLATE_ID "TMPLJ9Z6Q6Z"
#define BLYNK_DEVICE_NAME "ESP32_Home_Automation_Application"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// define a led pins
const int ledPins[4] = {5, 4, 16, 17};

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

BLYNK_WRITE(V0){
    int value = param.asInt();
    Serial.print(value);
    if (value == 1){
        digitalWrite(ledPins[0], HIGH);
        Serial.println("LED 1 is ON");
    }else{
        digitalWrite(ledPins[0], LOW);
        Serial.println("LED 1 is OFF");
    }
}

BLYNK_WRITE(V1){
    int value = param.asInt();
    Serial.print(value);
    if (value == 1){
        digitalWrite(ledPins[1], HIGH);
        Serial.println("LED 2 is ON");
    }else{
        digitalWrite(ledPins[1], LOW);
        Serial.println("LED 2 is OFF");
    }
}

BLYNK_WRITE(V2){
    int value = param.asInt();
    Serial.print(value);
    if (value == 1){
        digitalWrite(ledPins[2], HIGH);
        Serial.println("LED 3 is ON");
    }else{
        digitalWrite(ledPins[2], LOW);
        Serial.println("LED 3 is OFF");
    }
}

BLYNK_WRITE(V3){
    int value = param.asInt();
    Serial.print(value);
    if (value == 1){
        digitalWrite(ledPins[3], HIGH);
        Serial.println("LED 4 is ON");
    }else{
        digitalWrite(ledPins[3], LOW);
        Serial.println("LED 4 is OFF");
    }
}

void setup(){
    Serial.begin(115200);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED){
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to the WiFi network");
    Blynk.begin(auth, ssid, pass);

    // Set the led pins as output
    for (int i = 0; i < 4; i++){
        pinMode(ledPins[i], OUTPUT);
    }
}

void loop(){
    Blynk.run();
}