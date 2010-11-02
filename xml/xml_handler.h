/*
 * xml_handler.h
 *
 *  Created on: Jul 21, 2010
 *      Author: rolf
 */

#ifndef XML_HANDLER_H_
#define XML_HANDLER_H_
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include "../globals.h"
#include "../resource_bank.h"
#include "../graphics/image.h"
#include <iostream>
#include <sstream>
#include <map>
#include <stack>
#include <tuple>
#include "xml_resource.h"
using namespace std;
using namespace xercesc;



class xml_handler: public DefaultHandler{
	public:
	xml_handler();
	void add_element_handler(xml_resource * element_handler);

	xml_resource def_res;
	map<string,xml_resource *> element_handlers;
	stack<xml_resource *> active_elements;

	void startElement(
	        const   XMLCh* const    uri,
	        const   XMLCh* const    localname,
	        const   XMLCh* const    qname,
	        const   Attributes&     attrs
	    );

	void endElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname);

private:
	bool parent_handles;

};

#endif /* XML_HANDLER_H_ */
