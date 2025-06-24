#ifndef HOME_H
#define HOME_H

/** Include Dependencies **/
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP>

extern "C" {

	#include "freertos/FreeRTOS.h"
	#include "freertos/times.h"

}

/** helper functions **/

void WiFiEvent(WiFiEvent_t event);

/** Preprocessing functions **/
String WiFiScan();

