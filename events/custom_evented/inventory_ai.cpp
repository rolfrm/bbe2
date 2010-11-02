/*
 * inventory_ai.cpp
 *
 *  Created on: Sep 5, 2010
 *      Author: rolf
 */

#include "inventory_ai.h"
#include "../../graphics/drawable.h"
#include "../../sprite.h"
inventory_ai::inventory_ai() {
	// TODO Auto-generated constructor stub
}

inventory_ai::~inventory_ai() {
	// TODO Auto-generated destructor stub
}

void inventory_ai::handleCustomEvent(customEvent evt) {
	drawable * anim = (drawable *) get_first_child("sprite.dw_inventory");
	if (evt.custom_data == hash32("show")  ) {
		drawable * anim = (drawable *) get_first_child("sprite.dw_inventory");
		anim->set_uniform1f("state", 3);
	} else if (evt.custom_data == hash32("hide") ) {
		drawable * anim = (drawable *) get_first_child("sprite.dw_inventory");
		anim->set_uniform1f("state", 2);
	}

}

evented * inventory_ai::copy() {
	return new inventory_ai(*this);
}
