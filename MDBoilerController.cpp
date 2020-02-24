/*
 Created by Дмитрий Несмелов, Михаил Андреичев, Январь 2019.
*/

#include "Arduino.h"
#include "MDBoilerController.h"

MDBoilerController::MDBoilerController(int enablePin, int plusPin, int minesPin)
{
    boiler = new MDBoilerButtons(enablePin, plusPin, minesPin);
    httpClient = new MDHttpClient();
}

void MDBoilerController::sendStatus(float roomTemperature) {
    lastSendStatusTime = millis();
    
    MDBoilerResponse response = httpClient->sendStatus(roomTemperature);
    if (response.statusCode != 200) return;

    if(response.isOn != isOn) {
        boiler->changeEnabled();
        isOn = response.isOn;
    }
    if(response.establishedTemperature != establishedTemperature) {
        Serial.println("Changing temperature to " + String(response.establishedTemperature));
        boiler->set(response.establishedTemperature);
        establishedTemperature = response.establishedTemperature;
    }

    lastSendStatusTime = millis();
}

bool MDBoilerController::isTimeToSendStatus() {
    return lastSendStatusTime + statusSendingPeriod < millis();
}

void MDBoilerController::changeBoilerEnabled() {
    boiler->changeEnabled();
}

void MDBoilerController::set(String temperature) {
    boiler->set(temperature.toInt());
}
