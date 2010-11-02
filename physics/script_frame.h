/*
 * player_physics.h
 *
 *  Created on: Jun 3, 2010
 *      Author: rolf
 */

#ifndef PLAYER_PHYSICS_H_
#define PLAYER_PHYSICS_H_
#include "phyArchetypes.h"
class evented;
class script_frame: public polygonFrame{
public:
	script_frame(std::string id);
	void onCollision(baseFrame * other);
	void set_eventHandler(evented * event_handler);
private:
	evented * event_handler;
	std::string reciever_id;
};



#endif /* PLAYER_PHYSICS_H_ */
