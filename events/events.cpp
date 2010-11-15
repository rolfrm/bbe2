/*
 * events.cpp
 *
 *  Created on: Jun 5, 2010
 *      Author: rolf
 */

#include "events.h"
using namespace events;
event::event(enum event_recv_type recv_type,string reciever_id,enum event_type type,string transmitter_id){
	this->recv_type = recv_type;
	this->reciever_id = hash32(reciever_id);
	this->type = type;
	//this->transmitter_id = hash32(transmitter_id);
}

event::event(){
}

collisionEvent::collisionEvent(){
	type = COLLISION;
}

event * collisionEvent::clone(){
	return new collisionEvent(*this);
}

keyEvent::keyEvent(int button, event_type state, event_recv_type rtype, string group){
	this->state = state;
			this->button = button;
			type = KEY;
			recv_type = rtype;
			reciever_id = hash32(group);
}
