/*
 * xml_sprite_resource.h
 *
 *  Created on: Jul 22, 2010
 *      Author: rolf
 */

#ifndef XML_SPRITE_RESOURCE_H_
#define XML_SPRITE_RESOURCE_H_
#include "index.h"
class sprite;
class animation;
class xml_sprite_resource: public xml_resource{
public:
	xml_sprite_resource();

	void handle_start();
	void handle_attribute(string attr_name, string value);
	void handle_end();
	void handle_child_element_start(string element_name);
	void handle_child_attribute(string element_name, string attr_name, string attr_value);
	void handle_child_end(string element_name);
	bool does_handle_child_element(string element_name);
	xml_resource * new_instance();
private:
	string id;
	sprite * new_sprite;
	int drawable_pos_x, drawable_pos_y;
	string drawable_id;
	string evented_use;
	string body_use;
	drawable * new_drawable;
	bool phy_ui_core;

};

#endif /* XML_SPRITE_RESOURCE_H_ */
