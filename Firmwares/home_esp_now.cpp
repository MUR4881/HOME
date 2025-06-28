#include "HOME.h"


/* plan to add a function for converting datastructure into json object soon!*/
/* planning to add code & espnow & wifi encryption, and device-monitor*/
/* an event based one */
/* planning to integrate with google, in order to use gemini for interaction*/
/* planning on https */
/* also mDNS */
/* and server authentication */

/* This file containing fuctions definitions for espnow for HOME*/

/**
 * readDataToSend - Read Data from sensor in order to prepare it for sending
 */

void readDataToSend() {
	if ( mode == OFFLINE) {
		/* need to declare a global outgoing data */
		outgoindata.msg_type = DATA;
		outgoindata.id = BOARD_ID;
		outgoingdata.volt = 0.00;  /* Read voltage from it pin */
		outgoingdata.current = 0.00; /* Read current from sensor */
		outgoingdata.power = 0.00; /* Calculate the power consumption */
		outgoingdata.reading_id = 0;  /* calculate */

		/* add algorithm to log data to storage */
	}
	else {
		/* handle for online */
	}
}

/**
 * addPeer - adds a new peer to the network of peers
 * @peer_add:  a pointer to the peer to be added
 */

bool addPeer(const uint8_t *peer_addr){
	/* create a global variable for peer_structures called peer*/
	memset(&peer, 0, sizeof(peer));  /* set the whole buff to zero */
	memcpy(slave.peer_addr, peer_addr, 6);

	slave.channel = chan; // pick a channel ? why who declared the channel ?
	slave.encrypt = 0; // no encryption, encryption would be added later.
	/* check for peers existence */
	bool exists = esp_now_is_peer_exist(slave.peer_add);
	if (exists) {
		/* confirm peer is already paired */
		/* add a websocket event to do that */
		return true;
	}
	else {
		esp_err_t addStatus = esp_now_add_peer(&peer);
		if (addStatus == ESP_OK) {
			/* add a websocket on pairing successful */
			return true;
		}
		else {
			/*add a websocket event on a pair failed */
			return false;
		}
	}
}

/**
 * mac_addr - called whenever data is sent successfuly to the other board
 * successfuly.
 * @mac_addr: address of the sender
 * @status: the status of the message sent
 */

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
	/* work with the macro ESP_NOW_SEND_SUCCESS with the status variable*/
	/* to confirm packet sent was successful e.g a command packet about*/
	/*the other commanded devices going off*/
}


/**
 * OnDataRecv - callback function whenever an esp now packet is received
 * @mac_addr: the address of the sender.
 * @incomingData: the data packet recieved
 * @len: the total len of the recieved data
 * so why not use the len to determine the data type sent?
 */

void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incoming, int len) {
	/* now publish data on data websocket, using the devices, id */
	/* or the device identification */
	/* code needs to be refactured for jsonStringing*/
	/* new global variable, to be added called incoming_data */
	StaticJsonDocument<1000> root;
	String payload;
	uint8_t type = incoming[0];
	switch (type) {
		case DATA:
			memcpy(&incoming_data, incoming, sizeof(incoming));
			/* creating JSON document with received data*/
			root["id"] = incoming_data.id;
			root["volt"] = incoming_data.volt;
			root["current"] = incoming_data.current;
			root["power"] = incoming_data.power;
			root["reading_id"] = incoming_data.reading_id;
			serializeJson(root, payload);
			/* events can be added to show outgoing data */

			/* now readings can be published */
			break;

		case PAIRING:
			/* refactor/function to handle pairing */
			/* another variable pairing_data */
			memcpy(&pairing_data, incoming, sizeof(pairing));
			/* now add event to display devices to paired */
			/* new global variable ? client_mac_Address local!*/
			/* buffering as client */
			for (short i = 0; i < 6; i++)
				client_mac_Address[i] = pairing_data.mac[i];
			/* prevent pairing oneself */
			if (pairing_data.id != BOARD_ID) {
				/* to reuse the struct */
				/* this if statement is kinda unnecessary? */
				if (pairing_data.msg_type == PAIRING) {
					pairing_data.id = BOARD_ID;
					/* say mac address this way is only*/
					/* for the server alone */
					WiFi.softAPmacAddress(pairing_data.mac_addr);
					/* events may be added here too! */
					pairingData.channel = chan;
					esp_err_t result = esp_now_send(client_mac_Address
							, (uint8_t *) &pairing_data, sizeof(pairing_data));
					/* initiating peer should be uni-directional*/
					addPeer(client_mac_Address);
				}
			}
			break;
	}
}

void initESP_NOW() {
	/* Initialize Espnow */
	/* event may be added here to signal that */
	if (esp_now_init() != ESP_OK) {
		/*event to signalize esp_now isn't working*/
		return;
	}
	esp_now_register_send_cb(OnDataSent);
	esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}
/* add functions to get macaddress as a string */
