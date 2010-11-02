/*
 * xml_fsc_start.h
 *
 *  Created on: Sep 5, 2010
 *      Author: rolf
 */

#ifndef XML_FSC_START_H_
#define XML_FSC_START_H_
#include "index.h"
#include "../../graphics/fullscreen_shader.h"
#include <iostream>
class xml_fsc: public xml_resource{
public:
	xml_fsc():xml_resource("fsc"){

	}
	void handle_attribute(string attr_name,string attr_value){
		if(attr_name == "id"){
			id = attr_value;
		}else if(attr_name == "startz"){
			zstart =  integer_from_stdstring(attr_value);
		}else if(attr_name =="endz"){
			zend =  integer_from_stdstring(attr_value);
		}else if(attr_name =="use"){
			use = attr_value;
		}
	}
	void handle_end(){
		bank->drawable_db.insert_data(id,new fullscreen_shader(zstart,zend,use));
		//new fullscreen_shader(zstart,zend,use);
	}
	xml_resource * new_instance(){
		return new xml_fsc;
	}

private:
	int zstart;
	int zend;
	string id,use;

};

#endif /* XML_FSC_START_H_ */
