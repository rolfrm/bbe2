/*
 * xml_base_resource.cpp
 *
 *  Created on: Jul 22, 2010
 *      Author: rolf
 */

#include "xml_base_resource.h"

xml_base_resource::xml_base_resource():xml_resource("xml"){

}

bool xml_base_resource::does_handle_child_element(string element_name){
		if(element_name == "chdir" || element_name == "input"){
			return true;
		}

		return false;
	}
	void xml_base_resource::handle_child_attribute(string element_name, string attr_name,string attr_value){
		if(element_name == "chdir"){
			if(attr_name == "path"){
				dir_path = attr_value;
			}
		}if(element_name == "input"){
			if(attr_name == "src"){
				input_path = attr_value;
			}
		}
	}

xml_resource * xml_base_resource::new_instance(){
	return new xml_base_resource;
}
#include "../xml_core.h"
void xml_base_resource::handle_child_end(string element_name){

	if(element_name == "chdir"){
		change_dir(dir_path);
	}else if(element_name == "input"){
		if(input_path != "" ){
			xml_core->load(get_dir() +input_path);
		}
	}
}
