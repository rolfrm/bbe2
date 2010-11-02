/*
 * xml_evented_resource.h
 *
 *  Created on: Jul 23, 2010
 *      Author: rolf
 */

#ifndef XML_EVENTED_RESOURCE_H_
#define XML_EVENTED_RESOURCE_H_
#include "index.h"
#include <list>
class xml_evented: public xml_resource{
public:
	xml_evented();
	void handle_attribute(string attr_name, string value);
	bool does_handle_child_element(string element_name);
	void handle_child_attribute(string element_name,string attr_name, string attr_value);
	void handle_end();
	xml_resource * new_instance();
private:
	string use;
	string id;
	list<string> attrs;
};

#endif /* XML_EVENTED_RESOURCE_H_ */
