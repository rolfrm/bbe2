/*
 * xmlCore.cpp
 *
 *  Created on: Jul 22, 2010
 *      Author: rolf
 */
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
#include "xml_handler.h"
#include "xml_resource.h"
using namespace std;
using namespace xercesc;
#include "xml_core.h"

xmlCore::xmlCore() {
	main_handler = new xml_handler;
	xml_resource::setCoreXml(this);

}

xmlCore::~xmlCore() {
	delete main_handler;
}

void xmlCore::load(std::string file) {
	try {
		XMLPlatformUtils::Initialize();
	} catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Error during initialization! :\n";
		cout << "Exception message is: \n" << message << "\n";
		XMLString::release(&message);
		//return 1;
	}
	SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
	parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
	parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true); // optional

	DefaultHandler* defaultHandler = main_handler;

	parser->setContentHandler(defaultHandler);
	parser->setErrorHandler(defaultHandler);

	try {
		parser->parse(file.c_str());
		std::cout << "Done parsing: " << file << "\n";
	} catch (const XMLException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Exception message is: \n" << message << "\n";
		XMLString::release(&message);
		//return -1;
	} catch (const SAXParseException& toCatch) {
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Exception message is: \n" << message << "\n";
		XMLString::release(&message);
		//return -1;
	} catch (...) {
		cout << "Unexpected Exception \n";
		//return -1;
	}

	delete parser;
}

void xmlCore::load_xml_resource(xml_resource * handler){
	main_handler->add_element_handler(handler);
}
