/*
 * xml_polygonmesh.h
 *
 *  Created on: Oct 3, 2010
 *      Author: rolf
 */

#ifndef XML_POLYGONMESH_H_
#define XML_POLYGONMESH_H_
#include "index.h"

class xml_mesh2d:public xml_resource{
public:
	xml_mesh2d():xml_resource("mesh2d"){

	}

	void handle_end(){
		if(id != ""){
			//bank->drawable_db.insert_data(id,new mesh2d);
		}
	}

	xml_resource * new_instance(){
		return new xml_mesh2d;
	}
private:
	std::string id;
};
#endif /* XML_POLYGONMESH_H_ */
