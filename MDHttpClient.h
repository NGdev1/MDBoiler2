#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

struct MDBoilerResponse {
    int statusCode;
    float establishedTemperature;
    bool isOn;
};

class MDHttpClient
{
  public:
    MDHttpClient();
    MDBoilerResponse sendStatus(float roomTemperature);
    
  private:
    const char* ssid = "ElzaAndGera";
    const char* password =  "an25mi0397";
};
