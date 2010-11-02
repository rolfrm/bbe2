/*
 * xml_level_resource.cpp
 *
 *  Created on: Jul 22, 2010
 *      Author: rolf
 */

#include "xml_level_resource.h"
#include "../../sprite.h"
xml_level_resource::xml_level_resource():xml_resource("level") {
	new_sprite_x = 0;
	new_sprite_y = 0;


}

xml_level_resource::~xml_level_resource() {
	// TODO Auto-generated destructor stub
}

bool xml_level_resource::does_handle_child_element(string element_name){
	if(element_name == "sprite"){
		return true;
	}
	return false;
}
#include "../../core.h"
#include "../../physics/phyArchetypes.h"
#include "../../physics/compositePhysobj.h"
void xml_level_resource::handle_child_end(string element_name){
	if(element_name == "sprite"){
		sprite * new_sprite = bank->sprite_db.get_data(new_sprite_id);
		if(new_sprite != NULL){

			new_sprite = new_sprite->copy();
			new_sprite->set_pos(new_sprite_x,  new_sprite_y);
			if(new_sprite->phy != NULL){
				new_sprite->phy->Base->Pos = Vector2D(new_sprite_x,new_sprite_y);
			}
			if(new_sprite_new_id == ""){
				new_sprite_new_id = new_sprite_id;
			}
			if(new_sprite->Parent != NULL){
				new_sprite->Parent->set_id(new_sprite_new_id);
			}
			main_core->add_entity(new_sprite);
		}
	}
}
void xml_level_resource::handle_child_attribute(string element_name, string attr_name, string attr_value){
	if(element_name == "sprite"){
		if(attr_name == "use"){
			new_sprite_id = attr_value;
		}else if(attr_name == "x"){
			new_sprite_x = integer_from_stdstring(attr_value);
			if(new_sprite_x == INTEGER_CONVERSION_ERROR){
				std::cout << "CONVERSION ERROR!\n";
				new_sprite_x = 0;
			}
		}else if(attr_name == "y"){
			new_sprite_y = integer_from_stdstring(attr_value);
			if(new_sprite_x == INTEGER_CONVERSION_ERROR){
				std::cout << "CONVERSION ERROR!\n";
				new_sprite_x = 0;
			}
		}else if(attr_name == "id"){
			new_sprite_new_id = attr_value;
		}
	}
}


xml_resource * xml_level_resource::new_instance(){
	return new xml_level_resource;
}
