/*
 * xml_spritesheet_resource.h
 *
 *  Created on: Jul 22, 2010
 *      Author: rolf
 */

#ifndef XML_SPRITESHEET_RESOURCE_H_
#define XML_SPRITESHEET_RESOURCE_H_
#include "../xml_resource.h"
#include <string>
using namespace std;
class frame;
class spritesheet;
class sprite_line;
class spritesheet_resource: public xml_resource{
public:
	spritesheet_resource();

	void handle_attribute(string localname, string value);
	void handle_start();
	void handle_end();
	xml_resource * new_instance();

	bool does_handle_child_element(string element_name);
	void handle_child_element_start(string element_name);
	void handle_child_attribute(string element_name,string attr_name, string attr_value);
	void handle_child_end(string element_name);
private:
	string id;
	string image_id;
	string use;
	string current_state;
	spritesheet * new_spritesheet;
	sprite_line * new_sprite_line;
	frame * new_frame;
	int x,y,w,h,dt;
	int z;
	string camera_id;
	float parralax_x;
	float parralax_y;

};

#endif /* XML_SPRITESHEET_RESOURCE_H_ */
