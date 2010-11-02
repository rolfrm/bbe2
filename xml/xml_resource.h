/*
 * xml_resource.hpp
 *
 *  Created on: Jul 21, 2010
 *      Author: rolf
 */

#ifndef XML_RESOURCE_HPP_
#define XML_RESOURCE_HPP_

#include <string>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
class xmlCore;
using namespace std;

class xml_resource {
	/*xml_Resource handles a spesific element in a xml-formatted document.*/
public:
	xml_resource(string localname); //localname == name of element
	xml_resource();//localname = unhandled
	virtual void handle_attribute(string localname, string value);
	virtual void handle_start();
	virtual void handle_end();

	virtual bool does_handle_child_element(string element_name);
	virtual void handle_child_element_start(string element_name);
	virtual void handle_child_attribute(string element_name,string attr_name, string attr_value);
	virtual void handle_child_end(string element_name);

	virtual xml_resource * new_instance(); //important!



	string get_localname();
	void set_parent(xml_resource * new_parent);
	xml_resource * get_parent();
	void change_dir(string relative_directory);
	std::string get_dir();

	static void setCoreXml(xmlCore * core);
	static xmlCore * core_xml;
private:

	xml_resource * parent;
	string localname;
	static boost::filesystem::path currentdir;

};



#endif /* XML_RESOURCE_HPP_ */
