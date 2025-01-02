// ESP 32 Motor Control

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPpmDNS.h>

// define a pins
int Pin1 = 13;
int Pin2 = 12;
int Pin3 = 14;
int Pin4 = 27;

int pole1[] = {0, 0, 0, 0,  0, 1, 1, 1,  0}; // pole 1 8 steps 
int pole2[] = {0, 0, 0, 1,  1, 1, 0, 0,  0}; // pole 2 8 steps
int pole3[] = {1, 1, 1, 0,  0, 0, 0, 0,  0}; // pole 3 8 steps
int pole4[] = {0, 1, 1, 0,  0, 0, 0, 1,  0}; // pole 4 8 steps 

int poleStep = 0;
int dirStatus = 3;

String buttonTitle1[] = {"Right", "Left"};
String buttonTitle2[] = {"Right", "Left"};
String argId[] = {"Right", "Left"};

const char *ssid = "ESP32-Motor-Control";
const char *password  = "123456789";

WebServer server(80);

void handleRoot(){
    String HTML = "
    <html>
    <head>
        <title>ESP32 Motor Control</title>
        <style>
            .button {
                background-color: #4CAF50;
                border: none;
                color: white;
                padding: 15px 32px;
                text-align: center;
                text-decoration: none;
                display: inline-block;
                font-size: 16px;
                margin: 4px 2px;
                cursor: pointer;
            }
        </style>
    </head>
    <body>
        <h1>ESP32 Motor Control</h1>
        <form action='/motorControl' method='get'>
            <button class='button' name='Right' value='1'>Right</button>
            <button class='button' name='Left' value='1'>Left</button>
        </form>
    </body>
    </html>";
    server.send(200, "text/html", HTML);
}

void handleNotFound(){
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++){
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}

void setup(void){
    pinMode(Pin1, OUTPUT);
    pinMode(Pin2, OUTPUT);
    pinMode(Pin3, OUTPUT);
    pinMode(Pin4, OUTPUT);

    Serial.begin(115200);

    Wifi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.println("Waiting to connect...");
    }

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.println("");
    Serial.println("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: http://");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("esp32")){
        Serial.println("MDNS responder started");
    }

    server.on("/", handleRoot);
    server.on("/motorControl", HTTP_GET, motorControl);
    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("HTTP server started");
}

void loop(void){
    server.handleClient();
    if (dirStatus == 1){
        poleStep++;
        deiverStepper(poleStep);
    } else if (dirStatus == 2){
        poleStep--;
        deiverStepper(poleStep);
    } else if (dirStatus == 3){
        deiverStepper(8);
    }

    if (poleStep > 7){
        poleStep = 0;
    } if (poleStep < 0){
        poleStep = 7;
    }

    delay(100);
    handleRoot();
}

void deiverStepper(int step){
    digitalWrite(Pin1, pole1[step]);
    digitalWrite(Pin2, pole2[step]);
    digitalWrite(Pin3, pole3[step]);
    digitalWrite(Pin4, pole4[step]);
}
