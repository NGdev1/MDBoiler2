#include "MDHttpClient.h"

MDHttpClient::MDHttpClient() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }

    Serial.println("Connected to the WiFi network");
}

MDBoilerResponse MDHttpClient::sendStatus(float roomTemperature) {
    Serial.println("Sending room temperature " + String(roomTemperature));
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin("http://mdboiler.herokuapp.com/api/boiler/chip?temperatureFromSensor=" + String(roomTemperature));
        // http.addHeader("Content-Type", "text/plain");

        int httpResponseCode = http.PUT("");

        if (httpResponseCode > 0) {
            char json[500];
          
            String response = http.getString();
            response.replace(" ", "");
            response.replace("\n", "");
            response.trim();
            response.toCharArray(json, 500);
            
            StaticJsonDocument<200> doc;
            DeserializationError error = deserializeJson(doc, json);

            if (error) {
              Serial.println("Error parsing json");
              MDBoilerResponse result = {0, 0, false};
              return result;
            } else {
              Serial.println("Sending ok");
              MDBoilerResponse result = {httpResponseCode, doc["establishedTemperature"], doc["on"]};
              int established = doc["establishedTemperature"];
              Serial.println("Established temperature is " + String(established));
              Serial.println("Established state of work is " + String(result.isOn));
              return result;
            }
        } else {
            Serial.println("Error during request");
            MDBoilerResponse result = {0, 0, false};
            return result;
        }

        http.end();
    } else {
        Serial.println("Error, wifi is Off");
        MDBoilerResponse result = {0, 0, false};
        return result;
    }
}
