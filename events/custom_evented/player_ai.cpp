/*
 * player_ai.cpp
 *
 *  Created on: Jul 23, 2010
 *      Author: rolf
 */
#include "player_ai.h"
#include "../../physics/phyArchetypes.h"
#include "../../physics/compositePhysobj.h"
#include "../../physics/physics_core.h"

#include "../../sprite.h"
#include <math.h>
#include "../../globals.h"
#include "../../graphics/graphics_core.h"
#include "../../graphics/animation.h"
#include "../event_core.h"
#include "../../core.h"
#include <iostream>
#include <math.h>

player_ai::player_ai() {
	mov_down = 0;
	mov_up = 0;
	mov_left = 0;
	mov_right = 0;
	jump_ok = false;
	jump_delay = 0;
	iterator = 0;
	time_passed = 0;
	current_anim = "idle";
	rotating = false;
	selected_sprite = NULL;
	add_group("mousectrl");
	add_group("kctrl");
	add_group("tctrl");
	inventory_active = false;
	a_down = 0;
	d_down = 0;
	left_down = 0;
	right_down = 0;
	up_down = 0;
	down_down = 0;
	inited = false;

}

evented * player_ai::copy() {

	return new player_ai(*this);
}

void player_ai::put_item_in_inventory(sprite * item) {
	if (item != NULL) {
		inventory.push_back(item);
		int x, y;
		x = (inventory.size() % 10) * 25 - 200;
		y = inventory.size() / 10 * 25 - 140;
		item->phy->Base->angle = 0;
		item->phy->Base->Pos = Vector2D(x, y);
		item->gfx->set_camera(graphics_core->get_camera("ui_cam"));
		physics_core->removeObject(item->phy);
		((animation *) item->gfx)->set_animation("inventory");
		item->pickupable = false;
	}
}

void player_ai::handleKeyEvent(keyEvent evt) {
	int value;
	if (evt.state == KEYDOWN) {
		if (evt.button == KEY_BACKSPACE) {
			print_children();
		}
		value = 1;
		if (evt.button == KEY_CTRL) {
			inventory_active = !inventory_active;
			eventMaster * anim = (eventMaster*) get_first_child(
					"sprite.dw_anim_fisher");
			anim->handleCustomEvent(customEvent("hide", SINGLE, "", 1));
		}
	} else {
		value = 0;
	}

	if (evt.button == KEY_D) {
		d_down = value;
	} else if (evt.button == KEY_A) {
		a_down = value;
	} else if (evt.button == KEY_UP) {
		up_down = value;
	} else if (evt.button == KEY_DOWN) {
		down_down = value;
	} else if (evt.button == KEY_LEFT) {
		left_down = value;
	} else if (evt.button == KEY_RIGHT) {
		right_down = value;
	}
}

void player_ai::handleMouseEvent(mouseEvent evt) {
	if (evt.button == MOUSE_LEFT && evt.state == MOUSE_CLICK_DOWN) {
		Vector2D click_pos = event_core->pointer_game;
		if (inventory_active) {
			if ((event_core->pointer_game - gamepart->Pos).length() < 100) {
				selected_sprite = physics_core->PointInsideOfSprite(
						event_core->pointer_game);
			}else{
				selected_sprite = physics_ui->PointInsideOfSprite(event_core->pointer_game);
			}
		}
	} else if (evt.button == MOUSE_LEFT && evt.state == MOUSE_CLICK_UP) {
		selected_sprite = NULL;
	}

}

void player_ai::handleTurnEvent(turnEvent evt) {
	sendCustomEvent("inventory_sprite","show",1,SINGLE);
	if(!inited){
		gamepart = (sprite *) get_first_child("sprite");
		inited = true;
	}
	if (down_down) {
		graphics_core->cam.Pos.y += 10;
	}
	if (up_down) {
		graphics_core->cam.Pos.y -= 10;
	}
	if (left_down) {
		graphics_core->cam.Pos.x -= 10;
	}
	if (right_down) {
		graphics_core->cam.Pos.x += 10;
	}
	if (d_down) {
		//get_first_child("");
	}
	if (selected_sprite != NULL) {
		selected_sprite->set_velocity(event_core->pointer_game
				- selected_sprite->Pos);
	}
}

