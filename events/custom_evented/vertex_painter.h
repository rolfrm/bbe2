/*
 * vertex_painter.h
 *
 *  Created on: Jun 19, 2010
 *      Author: rolf
 */

#ifndef VERTEX_PAINTER_H_
#define VERTEX_PAINTER_H_
#include "../evented.h"
#include "../../graphics/simple_poly.h"
#include <list>
#include "../../toolModule.h"
//using std::list;


class vertex_painter:public eventMaster {
public:
	vertex_painter();
	 //void handle_event(event evt);
	void handleCustomEvent(customEvent evt);
	void handleMouseEvent(mouseEvent evt);
	void handleKeyEvent(keyEvent evt);
	void handleTurnEvent(turnEvent evt);

private:
	void print_lists();
	void print_phyframe_lists();
	evented * copy();
	simple_poly * sp;
	int savedx;
	int savedy;
	int moving_up;
	int moving_side;
	bool ctrl_down;
	bool absolute_positions;

	sprite * gameobj;

	std::list < std::list < Vector2D >> bodies;
	std::list <Vector2D> current_vector_list;

};

#endif /* VERTEX_PAINTER_H_ */
