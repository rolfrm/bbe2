/*
 * xml_spritesheet_resource.cpp
 *
 *  Created on: Jul 22, 2010
 *      Author: rolf
 */

/***************SPRITESHEET RESOURCE*********************/
#include "xml_spritesheet_resource.h"
#include "../../graphics/animation.h"
#include "../../resource_bank.h"
#include "../../globals.h"
#include "index.h"

spritesheet_resource::spritesheet_resource() :
	xml_resource("spritesheet") {
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	parralax_x = 1;
	parralax_y = 1;
	dt = 1000;
}

void spritesheet_resource::handle_attribute(string localname, string value) {
	if (localname == "id") {
		id = value;
	} else if (localname == "image") {
		image_id = value;
	} else if(localname == "zlevel"){
		z = integer_from_stdstring(value);
	}else if(localname == "camera"){
		camera_id = value;
	}else if(localname == "parralax_x"){
		parralax_x = (float)integer_from_stdstring(value)/1000;
	}else if(localname == "parralax_y"){
		parralax_y = (float)integer_from_stdstring(value)/1000;
	}
}

void spritesheet_resource::handle_start() {
	new_spritesheet = new spritesheet;
}

void spritesheet_resource::handle_end() {
	if (id != "") {
		bank->spritesheet_db.insert_data(id, new_spritesheet);

		if (bank->image_db.contains(image_id)) {
			image * spritesheet_image = bank->image_db.get_data(image_id);
			animation * new_anim = new animation;
			new_anim->parralax_x = parralax_x;
			new_anim->parralax_y = parralax_y;
			new_anim->zlevel = z;
			new_anim->set_spritesheet(new_spritesheet);
			new_spritesheet->set_image(spritesheet_image);
			bank->drawable_db.insert_data(id,new_anim);
			new_anim->set_camera(camera_id);
		}
		new_spritesheet = NULL;
	}
}

xml_resource * spritesheet_resource::new_instance() {
	return new spritesheet_resource;
}

bool spritesheet_resource::does_handle_child_element(string element_name) {
	if (element_name == "sprite_line" || element_name == "frame") {
		return true;
	}
	return false;
}

void spritesheet_resource::handle_child_element_start(string element_name) {
	if (element_name == "sprite_line") {
		current_state = "sprite_line";
		new_sprite_line = new sprite_line;
	} else if (element_name == "frame") {
		current_state = "frame";
	}
}
int integer_from_stdstring(std::string value);

void spritesheet_resource::handle_child_attribute(string element_name,string attr_name,
		string attr_value) {
	if (current_state == "sprite_line") {
		if (attr_name == "id") {
			new_sprite_line->set_id(attr_value);
		}
	} else if (current_state == "frame") {
		if (attr_name == "x") {
			x = integer_from_stdstring(attr_value);
		} else if (attr_name == "y") {
			y = integer_from_stdstring(attr_value);
		} else if (attr_name == "w") {
			w = integer_from_stdstring(attr_value);
		} else if (attr_name == "h") {
			h = integer_from_stdstring(attr_value);
		} else if (attr_name == "dt") {
			dt = integer_from_stdstring(attr_value);
		}
	}
}

void spritesheet_resource::handle_child_end(string element_name) {
	if (element_name == "sprite_line") {
		new_spritesheet->add_sprite_line(new_sprite_line);
		current_state = "";
	} else if (element_name == "frame") {
		new_sprite_line->insert_frame(x, y, w, h, dt);
		current_state = "sprite_line";
	}
}
