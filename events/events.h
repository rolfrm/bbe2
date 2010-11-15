/*
 * events.h
 *
 *  Created on: Jun 4, 2010
 *      Author: rolf
 */

#ifndef EVENTS_H_
#define EVENTS_H_

#include "../hash.h"
#include <string>
#include <boost/any.hpp>
namespace events{

#define KEY_BACKSPACE 295
#define KEY_F1 258
#define KEY_F2 259
#define KEY_F3 260
#define KEY_F4 261
#define KEY_F5 262
#define KEY_F6 263
#define KEY_F7 264
#define KEY_LEFT 285
#define KEY_DOWN 284
#define KEY_UP   283
#define KEY_RIGHT 286
#define KEY_P 80
#define KEY_ENTER 294
#define KEY_CTRL 289
#define KEY_ALT 291
#define KEY_Q 81
#define KEY_W 87
#define KEY_A 65
#define KEY_S 83
#define KEY_D 68
#define KEY_E 69

enum event_recv_type {
	GROUP, SINGLE, BROADCAST
};

enum event_type {
	COLLISION,
	KEY,
	MOUSE,
	CUSTOM,
	MOUSE_CLICK_DOWN,
	MOUSE_CLICK_UP,
	KEYDOWN,
	KEYUP,
	EVENT_TRIGGER,
	EVENT_CUSTOM,
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MID,
	WINDOW_CLOSED_EVENT,
	WINDOW_RESIZE_EVENT,
	TURN,
	CLICKED
};

using std::string;
class evented;
class event {
public:
	event(enum event_recv_type recv_type, string reciever_id,
			enum event_type type, string transmitter_id);
	event();
	enum event_recv_type recv_type;
	hashValue reciever_id;
	enum event_type type;
	evented * transmitter_id;
	virtual event * clone() = 0;
};

class collisionEvent: public event {
public:
	collisionEvent();
	event * clone();
};

class keyEvent: public event {
public:
	keyEvent(int button, event_type state, event_recv_type rtype, string group);
	event * clone() {
		return new keyEvent(*this);
	}

	event_type state;
	int button;
};

class mouseEvent: public event {
public:
	mouseEvent(int button, event_type state, event_recv_type rtype,
			string group) {
		this->button = button;
		this->state = state;
		this->reciever_id = hash32(group);
		recv_type = rtype;
		type = MOUSE;
	}
	event * clone() {
		return new mouseEvent(*this);
	}
	event_type state;
	int button;
};

class customEvent: public event {
public:
	customEvent(std::string custom_data, event_recv_type rtype, string receiver, boost::any anything = 0) {
		type = CUSTOM;
		recv_type = rtype;
		reciever_id = hash32(receiver);
		this->custom_data = hash32(custom_data);
		data = anything;
	}
	/*
	customEvent(hashValue custom_data, event_recv_type rtype, hashValue receiver, boost::any anything = 0) {
		type = CUSTOM;
		recv_type = rtype;
		reciever_id = receiver;
		this->custom_data = custom_data;
		data = anything;
	}*/


	event * clone() {
		return new customEvent(*this);
	}
	hashValue custom_data;
	boost::any data;
};


class turnEvent: public event {
public:

	turnEvent(float dt) {
		type = TURN;
		recv_type = GROUP;
		reciever_id = 661258240; //hash32("tctrl");
		this->dt = dt;
	}
	event * clone() {
		return new turnEvent(*this);
	}
	float dt;
};
}
#endif /* EVENTS_H_ */
