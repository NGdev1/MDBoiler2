/*
 Created by Дмитрий Несмелов, Михаил Андреичев, Январь 2019.
*/
#include "MDBoilerButtons.h"
#include "MDHttpClient.h"

class MDBoilerController
{
  public:
    MDBoilerController(int enablePin, int plusPin, int minesPin);
    void sendStatus(float roomTemperature);
    bool isTimeToSendStatus();
    void changeBoilerEnabled();
    void set(String temperature);
    
  private:
    MDBoilerButtons *boiler;
    MDHttpClient *httpClient;

    long lastSendStatusTime = millis();
    bool isOn = false;
    float establishedTemperature = 0;
    // long statusSendingPeriod = 1000 * 60 * 4;
    long statusSendingPeriod = 1000 * 10;
};
