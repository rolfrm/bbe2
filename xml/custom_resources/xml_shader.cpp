/*
 * xml_shader.cpp
 *
 *  Created on: Sep 5, 2010
 *      Author: rolf
 */
#include "xml_shader.h"
#include "index.h"
#include "../../graphics/graphics_core.h"
xml_shader::xml_shader():xml_resource("shader"){
	frag = "";
	vert = "";
	id = "";

}

void xml_shader::handle_attribute(string attr_name, string attr_value){
	if(attr_name == "fragsrc"){
		frag = attr_value;
	}else if(attr_name == "vertsrc"){
		vert = attr_value;
	}else if(attr_name == "id"){
		id = attr_value;
	}
}

void xml_shader::handle_end(){
	std::cout << get_dir() + vert << " " << get_dir() +frag << "  a\n";
	graphics_core->load_shaderprogram(id,get_dir() + vert,get_dir() + frag);
}

xml_resource * xml_shader::new_instance(){
	return new xml_shader;
}
