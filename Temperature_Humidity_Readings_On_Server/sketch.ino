// Import required libraries
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

// Replace with your network credentials
const char *ssid = "ESP32-Access-Point";
const char *password = "123456789";

#define DHTPIN 27

// Uncomment the type of sensor in use:
#define DHTTYPE DHT11 // DHT 11
// #define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
// #define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readDHTTemperature(){
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    // float t = dht.readTemperature(true);
    // Check if any reads failed and exit early (to try again).
    if (isnan(t)){
        Serial.println("Failed to read from DHT sensor!");
        return "--";
    }
    else{
        Serial.println(t);
        return String(t);
    }
}

String readDHTHumidity(){
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    if (isnan(h)){
        Serial.println("Failed to read from DHT sensor!");
        return "--";
    }
    else{
        Serial.println(h);
        return String(h);
    }
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <h1>ESP Web Server</h1>
  <p>Temperature: %TEMPERATURE%</p>
  <p>Humidity: %HUMIDITY%</p>
</body>
</html>
)rawliteral";

// Replaces placeholder with DHT values
String processor(const String &var){
    // Serial.println(var);
    if (var == "TEMPERATURE"){
        return readDHTTemperature();
    }
    else if (var == "HUMIDITY"){
        return readDHTHumidity();
    }
    return String();
}

void setup(){
    // Serial port for debugging purposes
    Serial.begin(115200);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED){
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    // Print ESP Local IP Address
    Serial.println(WiFi.localIP());

    // Initialize DHT sensor
    dht.begin();

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){ 
        request->send(200, "text/plain", "Hello, world"); 
        });

    // Route to read DHT temperature
    server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){ 
        request->send(200, "text/plain", readDHTTemperature()); 
        });

    // Route to read DHT humidity
    server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){ 
        request->send(200, "text/plain", readDHTHumidity()); 
        });

    // Start server
    server.begin();
}
