#include "evented.h"
#include <iostream>
#include "../core.h"
#include "../toolModule.h"
#include "../graphics/graphics_core.h"
#include "event_core.h"
#include "../sound/sound_core.h"
#include "../physics/phyArchetypes.h"
#include "../physics/compositePhysobj.h"
#include "../sprite.h"
#include "../globals.h"
#include "../hash.h"
evented::evented(string id) {
	set_id(id);
	Parent = NULL;

}

void evented::sendEvent(event * evt) {
	event_core->send_event(evt);
}
#include <boost/any.hpp>

void evented::sendCustomEvent(std::string reciever, std::string str_data,
		boost::any data, event_recv_type rtype) {
	customEvent * evt = new customEvent(str_data, rtype, reciever, data);
	event_core->send_event(evt);
}

void evented::sendEventUp(event * evt) {
	if (evt->recv_type == GROUP) {
		sendEventUp_grouped(evt);
	}
	delete evt;

}

void evented::sendEventUp_grouped(event* evt) {
	if (has_group(evt->reciever_id)) {
		take_event(evt->clone());
	}
	for (std::list<evented *>::iterator it = children.begin(); it
			!= children.end(); it++) {
		if ((*it)->has_group(evt->reciever_id)) {
			(*it)->sendEventUp_grouped(evt);
		}
	}
}

void evented::add_group(std::string newgroup) {
	group.push_back(newgroup);
	group_hashes[hash32(newgroup)] = true;
}
void evented::remove_group(std::string del_group) {
	group.remove(del_group);
}
void evented::add_groups(std::list<std::string> groups) {
	for (std::list<std::string>::iterator it = groups.begin(); it
			!= groups.end(); ++it) {
		add_group(*it);
	}
}

bool evented::has_group(std::string group_name) {
	for (std::list<std::string>::iterator it = group.begin(); it != group.end(); ++it) {
		if ((*it) == group_name) {
			return true;
		}
	}
	return false;
}

bool evented::has_group(hashValue group_name) {
	return group_hashes[group_name.getInt()];
}

list<std::string> evented::get_groups() {
	return group;
}

void evented::set_id(string new_id) {
	id = new_id;
	//h_id =hash32(new_id);
}

string evented::get_whole_id() {
	if (Parent != NULL) {
		return Parent->get_id() + "." + id;
	}
	return id;
}

string evented::get_id() {
	return id;
}

void evented::set_parent(evented * parent) {
	Parent = parent;
}

void evented::add_child(evented * child) {
	children.push_back(child);
	child->set_parent(this);
}

void evented::remove_child(evented * child) {
	children.remove(child);
}

evented * evented::get_first_child(std::string child_id) {
	return get_first_child(split_id(child_id));
}

evented * evented::get_first_child(std::queue<string> queue_id) {
	list<evented *>::iterator it;
	for (it = children.begin(); it != children.end(); ++it) {
		if ((*it)->get_id() == queue_id.front()) {

			if (queue_id.size() == 1) {
				return (*it);
			} else {
				queue_id.pop();
				return (*it)->get_first_child(queue_id);
			}
		}
	}
	return NULL;
}

std::queue<string> evented::split_id(string id) {
	std::queue<string> a;
	while (id.length() > 2) {
		int f1 = id.find_first_of('.');
		string sub = id.substr(0, f1);
		id.erase(0, f1);
		id.erase(0, 1);
		a.push(sub);
	}

	return a;

}

void evented::print_children() {

	list<evented *>::iterator it;
	for (it = children.begin(); it != children.end(); ++it) {
		std::cout << (*it)->get_id() << "\n";
		(*it)->print_children();
	}
}

eventSlave::eventSlave(string id) :
	evented(id) {
}

eventSlave::eventSlave() :
	evented("<unnamed slave>") {

}

void eventSlave::take_event(event *evt) {
	if (Parent != NULL) {
		Parent->take_event(evt);
	}
}

void eventSlave::handle_event(event * evt){
	return;
}

eventMaster::eventMaster(string id) :
	evented(id) {

}
eventMaster::eventMaster() :
	evented("<unnamed master>") {

}

void eventMaster::handleCollisionEvent(collisionEvent evt) {

}

void eventMaster::handleKeyEvent(keyEvent evt) {

}

void eventMaster::handleMouseEvent(mouseEvent evt) {

}

void eventMaster::handleCustomEvent(customEvent evt) {

}

void eventMaster::handleTurnEvent(turnEvent evt) {

}

void eventMaster::take_event(event * evt) {
	event_queue.push(evt);
}

void eventMaster::handleEvents() {
	while (!event_queue.empty()) {
		event * evt = event_queue.front();

		if (evt->type == COLLISION) {
			handleCollisionEvent(*((collisionEvent *) evt));

		} else if (evt->type == TURN) {

			handleTurnEvent(*((turnEvent *) evt));
		} else if (evt->type == KEY) {
			handleKeyEvent(*((keyEvent *) evt));
		} else if (evt->type == MOUSE) {
			handleMouseEvent(*((mouseEvent*) evt));
		} else if (evt->type == CUSTOM) {
			handleCustomEvent(*((customEvent*) evt));
		}

		event_queue.pop();
		if (Parent != NULL) {
			Parent->take_event(evt);
		} else {
			delete evt;
		}
	}
}
void eventMaster::handle_event(event * evt) {
	if (evt->type == COLLISION) {
		handleCollisionEvent(*((collisionEvent *) evt));

	} else if (evt->type == TURN) {

		handleTurnEvent(*((turnEvent *) evt));
	} else if (evt->type == KEY) {
		handleKeyEvent(*((keyEvent *) evt));
	} else if (evt->type == MOUSE) {
		handleMouseEvent(*((mouseEvent*) evt));
	} else if (evt->type == CUSTOM) {
		handleCustomEvent(*((customEvent*) evt));
	}
}
