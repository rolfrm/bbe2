	/*
 * player.h
 *
 *  Created on: Jul 23, 2010
 *      Author: rolf
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include "../evented.h"
#include <vector>
using namespace std;



class player_ai: public eventMaster {
public:
	player_ai();
	void handleTurnEvent(turnEvent evt);
	void handleKeyEvent(keyEvent evt);
	void handleMouseEvent(mouseEvent evt);

	evented * copy();

	sprite * get_inventory_item(int x, int y);
	void put_item_in_inventory(sprite * item);

private:
	bool mov_left, mov_right, mov_down, mov_up;
	bool jump_ok;
	int jump_delay;
	int d_down;
	int a_down;
	int left_down;
	int up_down;
	int down_down;
	int right_down;
	Vector2D * speed;
	int iterator;
	std::string current_anim;
	std::list <sprite *> inventory;
	sprite * selected_sprite;
	bool rotating;
	float saved_mass;
	bool inventory_state;
	bool inventory_active;
	float time_passed;
	bool inited;
	sprite * gamepart;
};

#endif /* PLAYER_H_ */
