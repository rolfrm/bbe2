/*
 * xml_base_resource.h
 *
 *  Created on: Jul 22, 2010
 *      Author: rolf
 */

#ifndef XML_BASE_RESOURCE_H_
#define XML_BASE_RESOURCE_H_
#include "index.h"
class xml_base_resource: public xml_resource{
public:
	xml_base_resource();
	bool does_handle_child_element(string element_name);
	void handle_child_attribute(string element_name, string attr_name,string attr_value);
	xml_resource * new_instance();
	void handle_child_end(string element_name);
private:
	string dir_path;
	string input_path;

};

#endif /* XML_BASE_RESOURCE_H_ */
