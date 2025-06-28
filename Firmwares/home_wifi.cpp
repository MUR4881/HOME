#include "HOME.h"

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
		 break;
		  case default:
		 	/* Handle more wifi events also for access point mode*/
	}
}
