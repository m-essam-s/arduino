#include "WiFi.h"
#include <NetworkClient.h>
#include <WiFiAP.h>

#ifndef LED_BUILTIN
#define LED_BUILTIN 2 // Set the GPIO pin
#endif

// Set these to your desired credentials.
const char *ssid = "ESP32-Access-Point";
const char *password = "123456789";

NetworkServer server(80);

void setup(){
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200); // data rate
    Serial.println();
    Serial.print("Configuring access point...");

    // You can remove the password parameter if you want the AP to be open.
    WiFi.softAP(ssid, password);
    if (!WiFi.softAPIP(ssid, password)){
        Serial.println("AP Config failed.");
        return;
    }

    IPAddress IP = WiFi.softAPIP();
    Seriall.print("AP IP address: ");
    Serial.println(IP);
    server.begin();
    Serial.println("HTTP server started");
}

void loop(){
    NetworkClient client = server.accept();

    if(client){
        Serial.println("New Client.");
        String currentLine = "";
        while (client.connected()){
            if (client.available()){
                char c = client.read();
                Serial.write(c);
                if (c == '\n'){
                    if (currentLine.length() == 0){
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();
                        client.println("<html>");
                        client.println("<head>");
                        client.println("<title>ESP32 Access Point</title>");
                        client.println("</head>");
                        client.println("<body>");
                        client.println("<h1>ESP32 Access Point</h1>");
                        client.println("<p>Click <a href=\"/LED=ON\">here</a> to turn the LED on pin 2 ON</p>");
                        client.println("<p>Click <a href=\"/LED=OFF\">here</a> to turn the LED on pin 2 OFF</p>");
                        client.println("</body>");
                        client.println("</html>");
                        break;
                    }else{
                        currentLine = "";
                    }
                }
                else if (c != '\r'){
                    currentLine += c;
                }
                if (currentLine.endsWith("GET /LED=ON")){
                    digitalWrite(LED_BUILTIN, HIGH);
                }
                if (currentLine.endsWith("GET /LED=OFF"))                {
                    digitalWrite(LED_BUILTIN, LOW);
                }
            }
        }
        client.stop();
        Serial.println("Client disconnected.");
    }
}