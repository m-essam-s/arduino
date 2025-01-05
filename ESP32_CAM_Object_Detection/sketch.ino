#include "esp_camera.h" // This header file is part of the ESP32 Camera library and is used to control the camera module on the ESP32-CAM.
#include <WiFi.h> // This library allows the ESP32 to connect to a WiFi network. It is built into the Arduino IDE for ESP32 boards.
#include "tensorflow/lite/micro/all_ops_resolver.h" 
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

// Replace with your network credentials
#define WIFI_SSID "YourNetworkName" // Network SSID (name)
#define WIFI_PASSWORD "YourPassword" // Network password

// Camera pins
#define PWDN_GPIO_NUM -1  // Power down pin for the camera. and is set to -1 as it is not used.
#define RESET_GPIO_NUM -1 // Reset pin for the camera. and is set to -1 as it is not used.
#define XCLK_GPIO_NUM 0   // XCLK (external clock) pin provides the clock signal to the camera.
#define SIOD_GPIO_NUM 26  // These are I2C communication pins used for camera control.
#define SIOC_GPIO_NUM 27  // These are I2C communication pins used for camera control.
                          //       - SIOD: I2C Data Line (SDA). SIOC: I2C Clock Line (SCL).
#define Y9_GPIO_NUM 35    // These pins are the data bus lines used to transfer image data from the camera.
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25 // VSYNC is a synchronization signal that indicates the start of a new frame.
#define HREF_GPIO_NUM 23  // Horizontal reference signal. It indicates the start of a new line.
#define PCLK_GPIO_NUM 22  // Pixel clock signal. It provides the clock signal for the camera to read pixel data.

void setup(){
    // Initialize Serial Monitor
    Serial.begin(115200); // This initializes the serial communication at a baud rate of 115200.
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // This connects the ESP32 to the specified WiFi network using the provided SSID and password.
 
    while (WiFi.status() != WL_CONNECTED){ // This loop checks if the ESP32 is connected to the WiFi network.
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to the WiFi network");
    
    // Initialize the camera
    camera_config_t config; // This creates a camera configuration object.
    config.ledc_channel = LEDC_CHANNEL_0; // Specifies the LEDC channel used to generate the XCLK (external clock) signal for the camera.
    config.ledc_timer = LEDC_TIMER_0; //  Specifies the LEDC timer used for generating the XCLK signal.
    config.pin_d0 = Y2_GPIO_NUM; // Assigns the GPIO pins for the 8-bit parallel data bus from the camera.
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;     // Assigns the GPIO pin for the XCLK (external clock) signal.
    config.pin_pclk = PCLK_GPIO_NUM;     // Specifies the GPIO pin for the pixel clock signal (PCLK), which synchronizes data transfer on the 8-bit bus.
    config.pin_vsync = VSYNC_GPIO_NUM;   // Assigns the GPIO pin for the vertical sync signal.
    config.pin_href = HREF_GPIO_NUM;     // Assigns the GPIO pin for the horizontal reference signal, which indicates valid data on the parallel bus.
    config.pin_sscb_sda = SIOD_GPIO_NUM; // Assigns the GPIO pin for the I2C data line (SDA) used for camera control.
    config.pin_sscb_scl = SIOC_GPIO_NUM; // Assigns the GPIO pin for the I2C clock line (SCL) used for camera control.
    config.pin_pwdn = PWDN_GPIO_NUM;     // Assigns the GPIO pin for the power-down signal of the camera.  PWDN_GPIO_NUM =-1 (not used).
    config.pin_reset = RESET_GPIO_NUM;   // Assigns the GPIO pin for the reset signal of the camera. RESET_GPIO_NUM =-1 (not used).
    config.xclk_freq_hz = 20000000;      // Specifies the frequency of the XCLK signal in Hz.
    config.pixel_format = PIXFORMAT_JPEG;// Specifies the pixel format of the camera output.

    // Initialize the camera
    esp_err_t err = esp_camera_init(&config); // This initializes the camera with the specified configuration.
    if (err != ESP_OK){ // This checks if the camera initialization was successful.
        Serial.printf("Camera init failed with error 0x%x", err); // This prints an error message if the camera initialization fails.
        return;
    }
    Serial.println("Camera initialized"); // This prints a message indicating that the camera initialization was successful.
    
    if (esp_camera_init(&config) != ESP_OK){ // This initializes the camera with the specified configuration and checks if it was successful.
        Serial.println("Camera Init Failed"); // This prints an error message if the camera initialization fails.
        return; 
    }   
}   

void loop(){
    // Capture an image
    camera_fb_t * fb = esp_camera_fb_get(); // This captures an image from the camera and returns a frame buffer.
    if (!fb){
        Serial.println("Camera capture failed"); // This prints an error message if the camera capture fails.
        return; 
    }
    Serial.println("Image captured"); // This prints a message indicating that the image capture was successful.

    // Release the frame buffer
    esp_camera_fb_return(fb); // This releases the frame buffer to free up memory.
}
