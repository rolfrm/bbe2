/*
 * xml_evented.cpp
 *
 *  Created on: Jul 23, 2010
 *      Author: rolf
 */
#include "xml_evented.h"
#include "../../events/custom_evented/player_ai.h"
#include "../../events/custom_evented/game_item.h"
#include "../../events/custom_evented/inventory_ai.h"
#include "../../events/custom_evented/vertex_painter.h"
xml_evented::xml_evented():xml_resource("evented"){

}

void xml_evented::handle_attribute(string attr_name, string attr_value){
	if(attr_name == "id"){
		id = attr_value;
	}else if(attr_name == "use"){
		use = attr_value;
	}
}

void xml_evented::handle_end(){
	if(use != ""){
		if(id == ""){
			id = use;
		}
		evented * new_evented;
		if(use == "cpp_playerscript"){
			new_evented = new player_ai();
		}else if(use == "gameitem"){
			new_evented = new game_item();

		}else if(use == "inventory_ai"){
			new_evented = new inventory_ai();
		}else if(use=="vertex_painter"){
			new_evented = new vertex_painter();
		}
		new_evented->set_id(id);
		new_evented->add_groups(attrs);
		bank->evented_db.insert_data(id,new_evented);
	}

}

bool xml_evented::does_handle_child_element(string element_name){

	if(element_name == "group"){

		return true;
	}
	return false;
}

void xml_evented::handle_child_attribute(string element_name, string attr_name, string attr_value){
	if(element_name == "group"){
		if(attr_name == "name"){
			this->attrs.push_back(attr_value);

		}
	}
}
xml_resource * xml_evented::new_instance(){
	return new xml_evented;
}
