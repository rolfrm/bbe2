/*
 * xml_costum_resource.cpp
 *
 *  Created on: Jul 21, 2010
 *      Author: rolf
 */

#include "xml_custom_resource.h"
#include <iostream>
#include <sstream>
#include "../../resource_bank.h"
#include "../../globals.h"
/****IMAGE RESOURCE *******/
image_resource::image_resource() :
	xml_resource("image") {

}

void image_resource::handle_attribute(string localname, string value) {
	if (localname == "path") {
		path = value;
	} else if (localname == "id") {
		id = value;
	}
}

void image_resource::handle_end() {
	image * newimg =new image(get_dir() + path);
	if(newimg != NULL){
		bank->image_db.insert_data(id,new image(get_dir() + path));
	}
}

xml_resource * image_resource::new_instance() {
	return new image_resource;
}



