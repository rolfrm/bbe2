/*
 * ui_botton.cpp
 *
 *  Created on: Jul 18, 2010
 *      Author: rolf
 */

#include "ui_botton.h"
#include "../events/event_core.h"
#include <math.h>
#include <iostream>
#include "../globals.h"
ui_botton::ui_botton(std::string id,std::string recv):signal("",GROUP,"bctrl"){
	// TODO Auto-generated constructor stub
	anim =  0;
	ec = 0;
	set_id(id);

}

ui_botton::~ui_botton() {
	// TODO Auto-generated destructor stub
}
/*
void ui_botton::handle_event(event evt){
	if(evt.type == MOUSE_CLICK_DOWN){
		Vector2D diff;
		diff.x = Pos->x - (event_core->pointer_screen.x/2 -200);
		diff.y = Pos->y - (event_core->pointer_screen.y/2 -150);
		if(fabs(diff.x) < w/2 && fabs(diff.y) < h/2 ){
			event_core->send_event(signal);
		}
	}
}
*/
void ui_botton::set_signal(std::string str){

}
