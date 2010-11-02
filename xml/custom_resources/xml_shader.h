/*
 * xml_shader.h
 *
 *  Created on: Sep 3, 2010
 *      Author: rolf
 */

#ifndef XML_SHADER_H_
#define XML_SHADER_H_
#include "index.h"
class xml_shader: public xml_resource{
public:
	xml_shader();
	//void handle_start();
	void handle_attribute(string attr_name, string attr_value);
	void handle_end();
	xml_resource * new_instance();

private:
	string id;
	string vert;
	string frag;
};

#endif /* XML_SHADER_H_ */
