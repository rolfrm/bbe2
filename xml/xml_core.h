/*
 * xmlCore.h
 *
 *  Created on: Jul 22, 2010
 *      Author: rolf
 */

#ifndef XMLCORE_H_
#define XMLCORE_H_
#include <string>
class xml_resource;
class xml_handler;
class xmlCore {
public:
	xmlCore();
	void load(std::string file);
	void load_xml_resource(xml_resource * handler);
	virtual ~xmlCore();
private:
	xml_handler * main_handler;


};

#endif /* XMLCORE_H_ */
