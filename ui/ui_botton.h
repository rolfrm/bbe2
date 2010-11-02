/*
 * ui_botton.h
 *
 *  Created on: Jul 18, 2010
 *      Author: rolf
 */

#ifndef UI_BOTTON_H_
#define UI_BOTTON_H_

#include "../graphics/animation.h"
#include "../events/evented.h"
class Vector2D;
class event_core;

class ui_botton: public eventSlave {
public:
	ui_botton(std::string id,std::string recv);
	virtual ~ui_botton();
	void set_signal(std::string signal);
	event_core * ec;
	animation * anim;

	int w,h;
	customEvent signal;
};

#endif /* UI_BOTTON_H_ */
