#include <WiFi.h>
#include <DHT.h>
#include "TensorFlowLite.h"

// Replace with your network credentials
#define ssid "ESP32-Access-Point"
#define password "123456789"

#define DHTPIN 27
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// TensorFlow Lite model configuration
#include "weather_model_tflite.h"
const tflite::Model *model;
tflite::MicroInterpreter *interpreter;
tflite::ErrorReporter *error_reporter;
tflite::MicroMutableOpResolver<2> resolver;
constexpr int tensor_arena_size = 2 * 1024;
uint8_t tensor_arena[tensor_arena_size];

// input and output tensors

TfLiteTensor *input;
TfLiteTensor *output;

// Function to initialize the TensorFlow Lite model
void init_model(){
    // Set up the model
    model = tflite::GetModel(weather_model_tflite);
    if (model->version() != TFLITE_SCHEMA_VERSION){
        Serial.print("Model provided is schema version is not supported by this interpreter");
        return;
    }
    resolver.AddFullyConnected();
    resolver.AddSoftmax();
    static tflite::MicroErrorReporter micro_error_reporter;
    error_reporter = &micro_error_reporter;
    static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, tensor_arena_size, error_reporter);
    interpreter = &static_interpreter;
    TfLiteStatus allocate_status = interpreter->AllocateTensors();
    if (allocate_status != kTfLiteOk){
        Serial.print("Error allocating tensors");
        return;
    }
    input = interpreter->input(0);
    output = interpreter->output(0);
}

// Function to get the weather prediction
String predictWeatherAI(float temperature, float humidity){
    // Set the input tensor
    input->data.f[0] = temperature;
    input->data.f[1] = humidity;

    // Run inference
    if (interpreter->Invoke() != kTfLiteOk)
    {
        Serial.print("Error invoking the model");
        return "Error";
    }

    // Get Prediction
    float prediction[3];
    for (int i = 0; i < 3; i++){
        prediction[i] = output->data.f[i];
    }

    // Find the index of the maximum value
    int max_index = 0;
    for (int i = 1; i < 3; i++){
        if (prediction[i] > prediction[max_index]){
            max_index = i;
        }
    }

    // Return the prediction
    switch (max_index){
    case 0:
        return "Sunny";
    case 1:
        return "Rainy";
    case 2:
        return "Cloudy";
    default:
        return "Error";
    }
    
}

void setup(){
    // Initialize Serial Monitor
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED){
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to the WiFi network");
    


    // Initialize DHT sensor
    dht.begin();

    // Initialize the TensorFlow Lite model
    init_model();
}

void loop(){
    // Read temperature and humidity
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Check if any reads failed and exit early
    if (isnan(temperature) || isnan(humidity)){
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    // Get the weather prediction
    String forcast = predictWeatherAI(temperature, humidity);
    Serial.print("Temperature: " + String(temperature) + "°C");
    Serial.print("Humidity: " + String(humidity) + "%");
    Serial.print("Weather: " + forcast); 

    delay(2000);
}
