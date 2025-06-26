#ifndef HOME_H
#define HOME_H

/** Include Dependencies **/
#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <ArduinoJson.h>

extern "C" {

	#include "freertos/FreeRTOS.h"
	#include "freertos/times.h"

}

/**			Macros and Unions and types					**/

/**
 * enum MessageType -  an enum for checking for the type sent or received
 * @PAIRING: to show that the packet, just sent is for pairing
 * @COMMAND: to show that the packet sent is a command
 * @DATA: to show that the packet sent is a sensor DATA
 * @EVENT: to show that the packet sent is an Event
 */

enum MessageType
{
	PAIRING,
	COMMAND,
	DATA,
	EVENT
};

typedef uint8_t [6] mac_address_t;

/* Currently thinking about changing, id to whatever, the master assigns*/
/* to the slave */

/**
 * struct struct_pairing - to Contain Pairing messages
 * @msgType: either PAIRING, COMMAND or DATA
 * @id: the id assigned to the given board on the network
 * @macAddr: The Mac Address of the pairing Device
 * @channel: The WiFi Channel of communication
 */

typedef struct struct_pairing
	{
		uint8_t msgType;
		uint8_t id;
		uint8_t macAddr[6];
		uint8_t channel;
	} pairing_t;	/* type for pairing message */

/**
 * struct struct_message - acting a mould for packages sent over espnow
 * @msgType: either PAIRING, COMMAND or DATA
 * @id: the board id on the network
 * @volt: the voltage reading from the sensor
 * @current: The current reading from the sensor
 * @power: The power voltage * current
 * @readingId: The packet number for the sent packet
 */

typedef struct_message {
	uint8_t msgType;
	uint8_t id;
	uint8_t volt;
	uint8_t current;
	uint8_t power;
	uint8_t readingId;
}


/** Networking functions **/

void WiFiEvent(WiFiEvent_t event);
void readMacAddress(void);
void readDataToSend(void);
void printMAC(const uint8_t *mac_addr);
bool addPeer(const uint8_t *peer_addr);
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len);
void initESP_NOW(void);


String WiFiScan(void);
/** Preprocessing functions **/

/** ESP NOW functionalities */
