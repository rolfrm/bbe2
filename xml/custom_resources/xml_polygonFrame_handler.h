#pragma once
#include "index.h"
#include "../../physics/phyArchetypes.h"
#include "../../toolModule.h"

class xml_polygonFrame_handler:public xml_resource{
public:
	xml_polygonFrame_handler();
	void handle_attribute(string localname, string value);
	void handle_start();
	void handle_end();

	bool does_handle_child_element(string element_name);
	void handle_child_element_start(string element_name);
	void handle_child_attribute(string element_name,string attr_name, string attr_value);
	void handle_child_end(string element_name);

	xml_resource * new_instance();

private:
	string id;
	polygonFrame * frame;
	float x,y;
};
