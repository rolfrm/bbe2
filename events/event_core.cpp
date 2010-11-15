#include "event_core.h"
#include <GL/glfw.h>
#include <iostream>
#include <list>
#include "../globals.h"
using namespace events;
//#include "../graphics/graphics_core.h"
/*
void GLFWCALL keycallback(int key, int action) {
	if (event_core != NULL) {
		event_type type;
		if(action == 0){
			type = KEYUP;
		}else if( action == 1){
			type = KEYDOWN;
		}
		event_core->take_event( new keyEvent(key,type,GROUP,"kctrl") );
	}
}
#include "../events/event_core.h"
#include "../physics/physics_core.h"
int GLFWCALL windowclosecallback(void) {
	if (event_core != NULL) {
		event_core->send_event(new customEvent( "WINDOWCLOSED",BROADCAST, "" ));

		physics_core->kill_thread();
		physics_ui->kill_thread();
		event_core->kill_thread();
		graphics_core->running = false;

	}
}

void GLFWCALL mouseclickcallback(int button, int action) {
	if (event_core != NULL) {

		int data;
		if (button == 0) {
			data = MOUSE_LEFT;
		} else if (button == 1) {

			data = MOUSE_RIGHT;
		} else if(button == 2) {
			data = MOUSE_MID;
		}
		event_type et;
		if (action == 1) {
			et = MOUSE_CLICK_DOWN;
		} else if (action == 0) {
			et = MOUSE_CLICK_UP;
		}
		event_core->send_event( new mouseEvent(data,et,GROUP,"mousectrl") );
	}
}

void GLFWCALL mouseposcallback(int x, int y) {
	if (event_core != NULL) {
		event_core->pointer_screen.x = (float) x;
		event_core->pointer_screen.y = (float) y;

	}
}
*/
class evented;
eventCore::eventCore() {
}

void eventCore::run() {
	int dt = 4;
	std::list<eventMaster*>::iterator i;
	for (i = evented_list.begin(); i != evented_list.end(); i++) {
		(*i)->handleEvents();
	}

	turnEvent * turn_event = new turnEvent(dt);
	take_event(turn_event);

	send_events();
}

void eventCore::add_unit(eventMaster *evt) {
	std::cout << evt->get_id() << "\n";
	evented_list.insert(evented_list.end(), evt);
}

void eventCore::take_event(event * evt) {
	//take_event_lock.lock();
	event_queue.push(evt);
	//take_event_lock.unlock();
}
void eventCore::send_event(event * evt) {

	if (evt->recv_type == SINGLE) {
		std::list<eventMaster *>::iterator i;
		for (i = evented_list.begin(); i != evented_list.end(); ++i) {
			std::cout << (*i)->get_id() << "\n";
			if ( (*i)->h_id == evt->reciever_id) {
				(*i)->take_event(evt->clone());

			}
		}
	} else if (evt->recv_type == GROUP) {
		std::list<eventMaster *>::iterator i;
		for (i = evented_list.begin(); i != evented_list.end(); ++i) {
			std::list<std::string>::iterator j;
			if( (*i)->has_group(evt->reciever_id) ){
				(*i)->take_event(evt->clone());
			}
		}

	} else if (evt->recv_type == BROADCAST) {
		std::list<eventMaster *>::iterator i;
		for (i = evented_list.begin(); i != evented_list.end(); ++i) {
			(*i)->take_event(evt->clone());
		}
	}
}

eventMaster * eventCore::get_evented(int ninl) {
	int counter = 0;
	std::list<eventMaster *>::iterator i;
	for (i = evented_list.begin(); i != evented_list.end(); ++i) {
		if (counter == ninl) {
			return (*i);
		}
	}
}
eventMaster * eventCore::get_evented(std::string name) {
	std::list<eventMaster *>::iterator i;
	for (i = evented_list.begin(); i != evented_list.end(); ++i) {
		if ((*i)->get_id() == name) {
			return (*i);
		}
	}
}
void eventCore::remove_unit(eventMaster * evt){
	evented_list.remove(evt);
}

void eventCore::send_events(){
	while(!event_queue.empty()){
		event * evt = event_queue.front();
		send_event(evt);
		event_queue.pop();
		delete evt;
	}
}
