/*
 * xml_sprite_resource.cpp
 *
 *  Created on: Jul 22, 2010
 *      Author: rolf
 */
#include "xml_sprite_resource.h"
#include "../../sprite.h"
xml_sprite_resource::xml_sprite_resource() :
	xml_resource("sprite") {
	drawable_pos_x = 0;
	drawable_pos_y = 0;
	phy_ui_core = false;
}

void xml_sprite_resource::handle_start() {
	new_sprite = new sprite;

}

void xml_sprite_resource::handle_attribute(string attr_name, string value) {
	if (attr_name == "id") {
		new_sprite->set_id(value);
	}
}

void xml_sprite_resource::handle_end() {
	bank->sprite_db.insert_data(new_sprite->id, new_sprite);

}

void xml_sprite_resource::handle_child_element_start(string element_name) {
	if (element_name == "drawable") {

	}
}

bool xml_sprite_resource::does_handle_child_element(string element_name) {
	if (element_name == "drawable" || element_name == "evented" || element_name == "body" ||element_name == "item") {
		return true;
	}
	return false;
}

void xml_sprite_resource::handle_child_attribute(string element_name,
		string attr_name, string attr_value) {
	if (element_name == "drawable") {
		if (attr_name == "use") {
			drawable_id = attr_value;
		} else if (attr_name == "x") {
			drawable_pos_x = integer_from_stdstring(attr_value);
			if (drawable_pos_x == INTEGER_CONVERSION_ERROR) {
				drawable_pos_x = 0;
				std::cout << "err: integer conversion error\n";
			}
		} else if (attr_name == "y") {
			drawable_pos_y = integer_from_stdstring(attr_value);
			if (drawable_pos_y == INTEGER_CONVERSION_ERROR) {
				drawable_pos_y = 0;
				std::cout << "err: integer conversion error\n";
			}
		}



	} else if (element_name == "evented") {
		if (attr_name == "use") {
			evented_use = attr_value;
		}
	} else if (element_name == "body") {
		if (attr_name == "use") {
			body_use = attr_value;
		}else if(attr_name == "core"){
			if(attr_value == "ui"){
				phy_ui_core = true;
			}
		}
	}else if(element_name == "item"){
		if(attr_name == "option"){

			if(attr_value == "pickupable")
				new_sprite->pickupable = true;
		}
	}
}
#include "../../graphics/animation.h"
#include "../../events/evented.h"
#include "../../physics/compositePhysobj.h"
void xml_sprite_resource::handle_child_end(string element_name) {

	if (element_name == "drawable") {

		if (bank->drawable_db.contains(drawable_id)) {
			new_drawable = bank->drawable_db.get_data(drawable_id);
			if (new_drawable != NULL) {
				new_drawable = new_drawable->copy();
				new_drawable->set_id("dw_" + drawable_id);
				new_sprite->set_drawable(new_drawable);
				new_drawable->Pos = &new_sprite->Pos;
				new_drawable->set_offset(drawable_pos_x,drawable_pos_y);
				new_drawable->angle = NULL;
			}
		}else{
			std::cout << "ERROR: Drawable named " << drawable_id << " not found\n";
		}
	} else if (element_name == "evented") {
		evented * new_evented = bank->evented_db.get_data(evented_use);

		if (new_evented != NULL) {
			new_evented = new_evented->copy();
			new_sprite->set_parent(new_evented);
		}else{
			std::cout << "ERROR: Coulden't find evented named " << evented_use << "\n";
		}

	} else if (element_name == "body") {
		compositePhysobj * new_body =bank->physicsobject_db.get_data(body_use);
		if(new_body != NULL){

			new_sprite->set_physics(new_body->copy());
			if(phy_ui_core){
							new_sprite->phy->ui_element = true;
						}
		}else{
			std::cout << "ERROR: Coulden't find body named " << body_use << "\n";
		}
	}
}

xml_resource * xml_sprite_resource::new_instance() {
	return new xml_sprite_resource;
}
