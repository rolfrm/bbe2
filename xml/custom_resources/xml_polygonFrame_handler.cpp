#include "xml_polygonFrame_handler.h"

xml_polygonFrame_handler::xml_polygonFrame_handler():
xml_resource("polygonframe")
{

}

xml_resource * xml_polygonFrame_handler::new_instance(){
	return new xml_polygonFrame_handler;
}

void xml_polygonFrame_handler::handle_attribute(string localname,string value){
	if(localname=="id"){
		id=value;
	}
}

void xml_polygonFrame_handler::handle_start(){
	frame=new polygonFrame;
}
void xml_polygonFrame_handler::handle_end(){
	bank->polygonframe_db.insert_data(id,frame);

	frame=NULL;
}

bool xml_polygonFrame_handler::does_handle_child_element(string element_name){
	if(element_name=="vertex"){
		return true;
	}
	return false;
}

void xml_polygonFrame_handler::handle_child_element_start(string element_name){
}

void xml_polygonFrame_handler::handle_child_attribute(string element_name,string attr_name,string attr_value){
	if(attr_name=="x"){
		x=(float) integer_from_stdstring(attr_value);
	}
	else if(attr_name=="y"){
		y=(float) integer_from_stdstring(attr_value);
	}
}

void xml_polygonFrame_handler::handle_child_end(string element_name){
	frame->AddVertex(x,y);
}
