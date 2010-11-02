/*
 * xml_level_resource.h
 *
 *  Created on: Jul 22, 2010
 *      Author: rolf
 */

#ifndef XML_LEVEL_RESOURCE_H_
#define XML_LEVEL_RESOURCE_H_

#include "index.h"

class xml_level_resource: public xml_resource {
public:
	xml_level_resource();
	bool does_handle_child_element(string element_name);
	void handle_child_attribute(string element_name,string attr_name, string attr_value);
	void handle_child_end(string element_name);
	virtual ~xml_level_resource();
	 xml_resource * new_instance();
private:
	 string new_sprite_id,new_sprite_new_id;
	 int new_sprite_x, new_sprite_y;
};

#endif /* XML_LEVEL_RESOURCE_H_ */
