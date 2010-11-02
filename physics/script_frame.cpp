/*
 * script_frame.cpp
 *
 *  Created on: Jun 3, 2010
 *      Author: rolf
 */

#include "script_frame.h"
#include "../events/events.h"
#include "../events/evented.h"
#include "compositePhysobj.h"
#include <iostream>
#include "../sprite.h"
script_frame::script_frame(std::string id){
	event_handler = NULL;
	reciever_id = id;
}

void script_frame::onCollision(baseFrame * other){
	/*if(other->parent->parent->evt != NULL){
		event evt(SINGLE,"",COLLISION,reciever_id, other->parent->parent->evt->id + ":" + id);
		event_handler->take_event(evt);
	}*/
}

void script_frame::set_eventHandler(evented * evh){
	event_handler = evh;
	reciever_id = event_handler->id + ":" + id;
}
