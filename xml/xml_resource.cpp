/*
 * xml_resource.cpp
 *
 *  Created on: Jul 21, 2010
 *      Author: rolf
 */
#include "xml_resource.h"
#include <iostream>

boost::filesystem::path xml_resource::currentdir;

xml_resource::xml_resource(string localname) {
	this->localname = localname;
	parent = NULL;
}
xml_resource::xml_resource() {
	localname = "Unhandled element";
	parent = NULL;
}
void xml_resource::handle_attribute(string localname, string value) {
	//std::cout << "Unhandled attribute: " << localname << "\n";
}

void xml_resource::handle_start(){

}

bool xml_resource::does_handle_child_element(string element_name){
	//std::cout << "dgce: "<< get_localname() << " -> " <<element_name << "\n";
	return false;
}

void xml_resource::handle_child_attribute(string element_name,string attr_name, string attr_value){

}

void xml_resource::handle_child_end(string element_name){

}

void xml_resource::handle_child_element_start(string element_name){

}

void xml_resource::handle_end() {

}

xml_resource * xml_resource::new_instance() {
	return new xml_resource;
}
string xml_resource::get_localname() {
	return localname;
}
void xml_resource::set_parent(xml_resource * new_parent) {
	parent = new_parent;
}
xml_resource * xml_resource::get_parent() {
	return parent;
}

void xml_resource::change_dir(string relative_directory){
	currentdir /= relative_directory;
}

std::string xml_resource::get_dir(){
	return currentdir.directory_string();
}
xmlCore * xml_resource::core_xml;
#include "xml_core.h"
void xml_resource::setCoreXml(xmlCore * core){
	core_xml = core;
}



