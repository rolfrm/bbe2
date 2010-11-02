#include "core.h"
#include <iostream>
#include "graphics/graphics_core.h"
#include "events/event_core.h"
#include "physics/physics_core.h"
#include "physics/compositePhysobj.h"
#include "physics/phyArchetypes.h"
#include "sprite.h"
#include "globals.h"
core::core() {

}

void core::run() {
	std::list<sprite *>::iterator i;
	for (i = sprite_list.begin(); i != sprite_list.end(); i++) {
		if ((*i)->super_sprite == NULL) {
			(*i)->calc_absolute_coords();
		}
	}
	for (i = sprite_list.begin(); i != sprite_list.end(); i++) {
		(*i)->run();
		if ((*i)->phy != NULL) {
			(*i)->Pos = (*i)->phy->Base->Pos;
			(*i)->angle = (*i)->phy->Base->angle;
		}
	}
	glfwSleep(0.01);
	//graphics_core->run();
}
#include "graphics/drawable.h"

void core::add_entity(sprite * sp) {
	if (sp != NULL) {
		add_entity(sp->phy);
		add_entity(sp->gfx);
		if(sp->Parent != NULL){
			add_entity((eventMaster *) sp->Parent);
			sp->Parent->add_child(sp);
		}
		std::list<sprite *>::iterator i;
		for (i = sp->sub_sprites.begin(); i != sp->sub_sprites.end(); i++) {
			add_entity((*i));
		}
		sprite_list.push_back(sp);

	} else {
		//	std::cout << "Sprite is NULL\n";
	}
}

void core::add_entity(drawable * dw) {
	if (dw != NULL) {
		graphics_core->add_unit(dw);
	} else {
		//std::cout <<"drawable is NULL\n";
	}
}

void core::add_entity(eventMaster * evt) {
	if (evt != NULL) {
		event_core->add_unit(evt);
	} else {
		//std::cout << "Event is NULL\n";
	}
}

void core::add_entity(compositePhysobj * cpo) {
	if (cpo != NULL) {
		if(cpo->ui_element){
			physics_ui->addObject(cpo);
		}else{
			physics_core->addObject(cpo);
		}
	}
}

sprite * core::getFirstSprite(std::string id) {
	std::list<sprite *>::iterator i;
	for (i = sprite_list.begin(); i != sprite_list.end(); i++) {
		if ((*i)->get_id() == id) {
			return *i;
		}
	}
	return NULL;
}
#include "toolModule.h"
sprite * core::get_closest_pickupable(int x, int y) {

	float max_dist = 10;
	float min_dist = max_dist;
	float temp_dist;
	sprite * saved = NULL;

	Vector2D mpos(x, y);

	std::list<sprite *>::iterator i;
	for (i = sprite_list.begin(); i != sprite_list.end(); i++) {

		if ((*i)->pickupable) {
			Vector2D Pos = (*i)->Pos;
			Pos -= mpos;
			temp_dist = Pos.length();

			if (temp_dist < min_dist) {
				min_dist = temp_dist;
				saved = (*i);

			}
		}
	}
	return saved;

}

void core::remove_entity(sprite * sp) {
	if (sp != NULL) {
		if (sp->gfx != NULL) {
			graphics_core->remove_unit(sp->gfx);
		}
		if (sp->phy != NULL) {
			physics_core->removeObject(sp->phy);
		}
		sprite_list.remove(sp);
	}
}
