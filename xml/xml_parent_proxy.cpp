/*
 * xml_parent_proxy.cpp
 *
 *  Created on: Jul 21, 2010
 *      Author: rolf
 */

#include "xml_parent_proxy.h"
#include <iostream>
parent_proxy::parent_proxy(string element_name):xml_resource(element_name){

}

void parent_proxy::handle_attribute(string localname, string value){
	get_parent()->handle_child_attribute( get_localname(),localname,value);
}

void parent_proxy::handle_start(){
	get_parent()->handle_child_element_start(get_localname());
}

void parent_proxy::handle_end(){
	get_parent()->handle_child_end(get_localname());
}

void parent_proxy::handle_child_end(string element_name){
	get_parent()->handle_child_end(element_name);
}

bool parent_proxy::does_handle_child_element(string element_name){
	return get_parent()->does_handle_child_element(element_name);
}

void parent_proxy::handle_child_element_start(string element_name){
	get_parent()->handle_child_element_start(element_name);
}

void parent_proxy::handle_child_attribute(string element_name,string attr_name, string attr_value){
	get_parent()->handle_child_attribute(element_name,attr_name,attr_value);
}

xml_resource *  parent_proxy::new_instance(){
	return new parent_proxy(get_localname());
}
