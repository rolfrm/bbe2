/*
 * xml_parent_proxy.h
 *
 *  Created on: Jul 21, 2010
 *      Author: rolf
 */

#ifndef XML_PARENT_PROXY_H_
#define XML_PARENT_PROXY_H_
#include "xml_resource.h"
#include <string>
class parent_proxy: public xml_resource {
public:
	parent_proxy(string element_name);
	void handle_attribute(string localname, string value);
	void handle_start();
	void handle_end();

	bool does_handle_child_element(string element_name);
	void handle_child_element_start(string element_name);
	void handle_child_attribute(string element_name,string attr_name, string attr_value);
	void handle_child_end(string element_name);

	xml_resource * new_instance();
};

#endif /* XML_PARENT_PROXY_H_ */
