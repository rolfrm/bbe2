/*
 * game_item.cpp
 *
 *  Created on: Sep 3, 2010
 *      Author: rolf
 */

#include "game_item.h"
#include "../../toolModule.h"
#include "../../sprite.h"
#include "../../graphics/drawable.h"
#include "../../globals.h"
#include "../event_core.h"
#include <iostream>
#include "../../graphics/graphics_core.h"
#include "../../sprite.h"
#include "../../physics/physics_core.h"
#include "../event_core.h"
#include "../../core.h"
#include "../../graphics/drawable.h"

game_item::game_item() {
	add_group("mousectrl");
	add_group("tctrl");
	old_cam = NULL;
}/*
void game_item::handle_event(event evt) {

	if (evt.type == TURN) {
		if (old_cam == NULL) {
			old_cam = Parent->gfx->cam;
		}

		if (has_group("inv")) {
			if (Pos->y > 50) {
				std::cout << "Sending back: " << Pos->y << "\n";
				physics_ui->removeObject(Parent->phy);
				sprite * player = main_core->getFirstSprite("fisher");
				Parent->phy->SetPos(player->Pos + Vector2D(0, -100));
				physics_core->addObject(Parent->phy);
				Parent->evt->remove_group("inv");
				Parent->gfx->set_camera(NULL);
			}
		}

	}
}
*/
evented * game_item::copy() {
	return new game_item(*this);
}
