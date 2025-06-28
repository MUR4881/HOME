#include "HOME.h"

/* This file contains functions for websocket, Asychronous web socket*/

/**
 * handleWebSocketMessage - handles the websocket message
 * @arg: a struct pointer containing infor about the Aws Frame
 * @data: the data buffer
 * @len: the length of the data sent binary or text or control
 */

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
	/* need to findout, what the stuff below is doing */
	AwsFrameInfo *info = (AwsFrameInfo*)arg;
	if (info->final && info->index == 0 && info->len == len
			&&info->opcode == WS_TEXT)
	{
		/**now do whatever you want with the message**/
		/*since this came from a client notify other client*/
		/* if(strcmp((char*)data, "toggle") == 0) {*/
		/*ledState = !ledState;*/
		/*notifyClients(); */ /*other clients !*/
	}
}

/* I just hit upon a sack of gold, the opcode and the final member*/
/* would be useful in the event monitor page, since it allows for */
/* tracking frames, that is probably how whatsapp now you are typing*/

/**
 * notifyClients - of a command or a change
 * @I believe client notification should vary based on the
 * data sent
 */

void notifyClients() {
	/* notify client of the change from another client */
	/* the change can be to go online mode or whatever */
	ws.textAll(String(ledState));
}


/**
 * onEvent - handle websocket events from the clients
 * @server: handle to the server object
 * @client: handle to the client object
 * @type: the event type from the server/client
 * @arg: a struct pointer containing the AwsFrame Info
 * @data: the packet or the frame
 * @len: the length of the frame
 */

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient * client,
		AwsEventType type, void * arg, uint8_t *data size_t len) {
	/* you can create event pool, based on the type of event */
	switch (type) {
		case WS_EVT_CONNECT:
			/* what do you want to do when the client connects */
			break;
		case WS_EVT_DISCONNECT:
			/* what do you want to do when a client disconnects*/
			break;
		case WS_EVT_DATA:
			/* a message was sent */
			handleWebSocketMessage(arg, data, len);
			break;
		case WS_EVT_PONG:
			/*what do you want to do when the client pings ?*/
			break;
		case WS_EVT_ERROR:
			/* what do you want to do when there is an error*/
			break;
	}
}

/**
 * initWebSocket - initializes the WebSocket
 */
void initWebSocket(void) {
	/* create the ws as a websocket object */
	ws.onEvent(onEvent);
	/*you need to add handler to your server*/
	/* e.g server.addHandler(&ws); */
}
