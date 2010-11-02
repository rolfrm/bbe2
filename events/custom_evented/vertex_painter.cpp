/*dddddex_painter.cpp
 *
 *  Created on: Jun 19, 2010
 *      Author: rolf
 */

#include "vertex_painter.h"
#include "../event_core.h"
#include "../../graphics/graphics_core.h"
#include "../../toolModule.h"
#include <iostream>
#include "../../globals.h"
vertex_painter::vertex_painter() {
	// TODO Auto-generated constructor stub
	sp = NULL;
	moving_up = 0;
	moving_side = 0;
	absolute_positions = false;
	ctrl_down = false;
	add_group("tctrl");
	add_group("kctrl");
	add_group("mousectrl");

}

void vertex_painter::handleMouseEvent(mouseEvent evt){
	gameobj = (sprite *) get_first_child("sprite");
	if(evt.button == MOUSE_LEFT && evt.state == MOUSE_CLICK_DOWN){

	}
}

void vertex_painter::handleKeyEvent(keyEvent evt){

}

void vertex_painter::handleCustomEvent(customEvent evt){

}
void vertex_painter::handleTurnEvent(turnEvent evt){

}

/*
void vertex_painter::handle_event(event evt) {
	int screen_pointer_x =  (event_core->pointer_screen.x - graphics_core->window_width/2);
	int screen_pointer_y =  (event_core->pointer_screen.y - graphics_core->window_height/2);

	int gamex = screen_pointer_x/2 + graphics_core->cam.Pos.x; //- graphics_core->cam_width/2;
	int gamey = screen_pointer_y/2 + graphics_core->cam.Pos.y; //- graphics_core->cam_height/2;
	if (evt.type == MOUSE_CLICK_DOWN) {
		if (evt.data == "m_left") {
			std::cout << gamex << " " << gamey << "\n";
			if (sp != NULL) {
				Vector2D vec(gamex - savedx, gamey - savedy);
				sp->add_vertex(vec.x, vec.y);
				current_vector_list.push_back(vec);
			}

		} else if (evt.data == "m_right") {
			if(ctrl_down == true){
				absolute_positions = false;
			}else{
				absolute_positions = true;
			}

			if (sp != NULL) {
			 bodies.push_back(current_vector_list);
			 current_vector_list.clear();
			 }

			 sp = new simple_poly;
			 graphics_core->add_unit(sp);
			 sp->color.g = 1;
			 sp->color.b = 0;
			 sp->color.r = 0;
			 sp->zlevel = 1000;


			 if(!absolute_positions){
				 sp->Pos = new Vector2D(gamex, gamey);
				 savedx = gamex;
				 savedy = gamey;
			 }else{
				 savedx = 0;
				 savedy = 0;
				 sp->Pos = new Vector2D(0, 0);
			 }


			 Vector2D vec(savedx, savedy);
			 current_vector_list.push_back(vec);
		} else if (evt.data == "m_mid") {

		}
	}else if(evt.type == KEYDOWN){

		int key = evt.simple_data;
		//std::cout << key << "\n";

		switch(key){
		case KEY_ENTER: print_lists(); break;
		case KEY_BACKSPACE:{
			if(sp != NULL){
				sp->delete_last_vertex();
			}

			break;
		}
		case KEY_UP: moving_up--;break;
		case KEY_DOWN: moving_up++;break;
		case KEY_LEFT: moving_side--;break;
		case KEY_RIGHT: moving_side++;break;
		case KEY_CTRL: ctrl_down = true;
		}
	}else if(evt.type == KEYUP){
		int key = evt.simple_data;
		switch(key){
		case KEY_UP: moving_up++;break;
		case KEY_DOWN: moving_up--;break;
		case KEY_LEFT: moving_side++;break;
		case KEY_RIGHT: moving_side--;break;
		case KEY_CTRL: ctrl_down = false;
		}
	}else if(evt.type == TURN){
		graphics_core->cam.Pos.x += moving_side*5;
		graphics_core->cam.Pos.y += moving_up*5;
	}
}
*/

void vertex_painter::print_lists() {
	int k = 0;
	std::list<std::list<Vector2D> >::iterator i;
	for (i = bodies.begin(); i != bodies.end(); i++) {
		std::list<Vector2D>::iterator j;
		std::cout << "Group nr. " << ++k << "\n";
		for (j = (*i).begin(); j != (*i).end(); j++) {
			std::cout <<"<vertex x=\"" <<j->x << "\" y=\"" << j->y << "\"/>\n";
		}
	}
}

void vertex_painter::print_phyframe_lists() {
	int k = 0;
	std::list<std::list<Vector2D> >::iterator i;
	for (i = bodies.begin(); i != bodies.end(); i++) {
		std::list<Vector2D>::iterator j;
		std::cout << "Group nr. " << ++k << "\n";
		for (j = (*i).begin(); j != (*i).end(); j++) {
			if (j == (*i).begin()) {
				std::cout << "Offset: (" << (*j).x << " " << (*j).y << ")\n";
			} else {
				std::cout << ",vertex," << (*j).x << " " << (*j).y;
			}
		}
		std::cout << ",\n";
	}
}

evented * vertex_painter::copy() {
	return new vertex_painter;
}
