/*
 * resource_bank.h
 *
 *  Created on: May 1, 2010
 *      Author: rolf
 */

#ifndef RESOURCE_BANK_H_
#define RESOURCE_BANK_H_
#include <string>
#include <boost/unordered_map.hpp>
//#include "drawable/image.h"
//using namespace animation_2D;

//class spritesheet;
#include <iostream>

template < class T>
class resource{
public:
	resource(){

	}
	T  get_data(std::string str){
		T output = database[str];
		return output;
	};

	int insert_data(std::string identifier, T ptr){
		if(contains(identifier)){
			return -1;
		}
		database[identifier] = ptr;

		return 0;
	}
	int delete_data(std::string identifier){
		if(contains(identifier)){
			database.remove(identifier);
			return 0;
		}
		return -1;

	}

	bool contains(std::string str){
		if(database.find(str) != database.end()){
			return true;
		}
		return false;
	}


	private:
	boost::unordered_map <std::string, T> database;
};

class spritesheet;
class image;
class polygonFrame;
class compositePhysobj;
class drawable;
class sprite;
class evented;
#include <GL/gl.h>
class resource_bank{
public:
	resource_bank(){

	};
	resource <image *> image_db;
	resource <spritesheet*> spritesheet_db;
	resource <polygonFrame*> polygonframe_db;
	resource <compositePhysobj *> physicsobject_db;
	resource <drawable *> drawable_db;
	resource <sprite * > sprite_db;
	resource <evented *> evented_db;
	resource <GLuint *> glunit_db;
};
#endif /* RESOURCE_BANK_H_ */
