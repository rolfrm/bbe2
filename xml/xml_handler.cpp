/*
 * xml_handler.cpp
 *
 *  Created on: Jul 21, 2010
 *      Author: rolf
 */
#include "xml_handler.h"
#include "xml_parent_proxy.h"


std::string simple_transcode(const XMLCh * xmlstr){
		char * message = XMLString::transcode(xmlstr);
		std::string output = message;
		XMLString::release(&message);
		return output;
	}

xml_handler::xml_handler():def_res("unhandled"){

	}


void xml_handler::add_element_handler(xml_resource * element_handler) {
	element_handlers[element_handler->get_localname()] = element_handler;
}

void xml_handler::startElement(const XMLCh* const uri, const XMLCh* const localname,
		const XMLCh* const qname, const Attributes& attrs) {
	string str_element_name = simple_transcode(localname);
	xml_resource * xml_r;
	//std::cout << str_element_name << "\n";
	if(active_elements.size() > 0 &&  active_elements.top()->does_handle_child_element(str_element_name)){
		xml_r = new parent_proxy(str_element_name);

	}else if (element_handlers.find(str_element_name)!= element_handlers.end()) {


		xml_r = element_handlers[str_element_name]->new_instance();


	} else {

		xml_r = new xml_resource;
	}


	if (active_elements.size() > 0) {
		xml_r->set_parent(active_elements.top());
	}
	active_elements.push(xml_r);

	xml_r->handle_start();

	int len_attr = attrs.getLength();
	if (len_attr != 0) {
		for (int i = 0; i < len_attr; i++) {
			xml_r->handle_attribute(simple_transcode(attrs.getLocalName(i)),
					simple_transcode(attrs.getValue(i)));
		}
	}
}

void xml_handler::endElement(const XMLCh * const uri, const XMLCh * const localname,
		const XMLCh * const qname) {
	if (active_elements.size() > 0) {
		active_elements.top()->handle_end();
		delete active_elements.top();
		active_elements.pop();
	}
}
