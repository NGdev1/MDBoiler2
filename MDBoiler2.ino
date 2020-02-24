#include "MDBoilerController.h"
#include <OneWire.h>                  // Библиотека протокола 1-Wire (датчики температуры)
#include <DallasTemperature.h>        // Библиотека для работы с датчиками DS* температуры

MDBoilerController *boilerController;
OneWire oneWire(5);        // Создаем экземпляр объекта протокола 1-WIRE - OneWire
DallasTemperature sensors(&oneWire);  // На базе ссылки OneWire создаем экземпляр объекта, работающего с датчиками DS*

//14 - ON/OFF
//15- MINES
//16- PLUS

void setup()
{
    Serial.begin(115200);
    sensors.begin();    // Запускаем поиск всех датчиков температуры
    
    boilerController = new MDBoilerController(18, 19, 23);
}

void loop()
{
    if(boilerController->isTimeToSendStatus()) {
        sensors.requestTemperatures();      // Запускаем измерение температуры на всех датчиках
        float roomTemperature = sensors.getTempCByIndex(0);
        boilerController->sendStatus(roomTemperature);
    }
}
