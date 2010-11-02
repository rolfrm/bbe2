/*
 * xml_costum_resource.h
 *
 *  Created on: Jul 21, 2010
 *      Author: rolf
 */

#ifndef XML_COSTUM_RESOURCE_H_
#define XML_COSTUM_RESOURCE_H_
#include "../../graphics/image.h"

#include "../xml_resource.h"
#include <stack>
#include <tuple>
#include <string>
#include <map>
using namespace std;
class image_resource: public xml_resource{
public:
	image_resource();

	void handle_attribute(string localname, string value);

	void handle_end();

	xml_resource * new_instance();

	private:
		image * img;
		std::string path;
		std::string id;
};

#endif /* XML_COSTUM_RESOURCE_H_ */
