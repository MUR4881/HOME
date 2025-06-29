#include "HOME.h"

/**
 * Remember this: yes remember
 * WiFi.scanNetworks(true, true)
 *
 * First true: Async mode (non-blocking).
 *
 * Second true: Scan hidden networks.
 *
 * SYSTEM_EVENT_SCAN_DONE is triggered when the scan finishes.
 *
 * WiFi.scanDelete() clears scan results to free memory.
 * WiFi.scanComplete(); should be called when scan is completed
 * and it returns the total number of scan
 */

/**
 * A function called to handle wifi events
 * @event: an event type signifying the type of wifi event
 */

void WiFiEvent(WiFiEvent_t event) {
	switch(event) {
		case SYSTEM_EVENT_STA_GOT_IP:
			/* publish wifi connection to websocket */
			Serial.println(WiFi.localIP());
			/* connect to the internet if allowed */
			/* or start timer if needed */
		break;

		case SYSTEM_EVENT_STA_DISCONNECTED:
			/* publlic wifi not connected to the websocket */
			/* start a time to attempt reconnection if allowed */
		case SYSTEM_EVENT_SCAN_DONE: 
		       	break;
		case SYSTEM_EVENT_STA_START:
			break;
		case SYSTEM_EVENT_STA_STOP:
			break;
		case SYSTEM_EVENT_STA_CONNECTED:
			break;
		case SYSTEM_EVENT_STA_DISCONNECTED:
			break;
		case SYSTEM_EVENT_GOT_IP6:
		case SYSTEM_EVENT_STA_LOST_IP:
			break;
		case SYSTEM_EVENT_AP_START:
			break;
		case SYSTEM_EVENT_AP_STOP:
			break;
		case SYSTEM_EVENT_AP_STACONNECTED:
			break;
		case SYSTEM_EVENT_AP_STADISCONNECTED:
			break;
		case 
		  case default:
		 	/* Handle more wifi events also for access point mode*/
	}
}


/**
 * getEncryptoinType - returns a string representing, the encryption type
 * @type: the number signifying the encrytion type
 *
 * Return: A string of the num type
 */

const char* getEncryptionType(wifi_auth_mode_t auth_mode) {
	  switch (auth_mode) {
		case WIFI_AUTH_OPEN: return "OPEN";
		case WIFI_AUTH_WEP:  return "WEP";
		case WIFI_AUTH_WPA_PSK: return "WPA-PSK";
		case WIFI_AUTH_WPA2_PSK: return "WPA2-PSK";
		case WIFI_AUTH_WPA_WPA2_PSK: return "WPA/WPA2-PSK";
		case WIFI_AUTH_WPA3_PSK:     return "WPA3-PSK";																case WIFI_AUTH_WPA2_WPA3_PSK: return "WPA2/WPA3-PSK";
		default: return "UNKNOWN";
																						}
}

/**
 * Enterprise Networks
 * The ESP32 can detect WPA2_ENTERPRISE, but connecting requires:
 *
 * cpp
 * esp_wifi_sta_wpa2_ent_set_identity((uint8_t*)EAP_ID, strlen(EAP_ID));
 * esp_wifi_sta_wpa2_ent_set_username((uint8_t*)EAP_USER, strlen(EAP_USER));
 * esp_wifi_sta_wpa2_ent_set_password((uint8_t*)EAP_PASS, strlen(EAP_PASS));
 */
