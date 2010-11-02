#include "xml_physicsobject_handler.h"

xml_physicsobject_handler::xml_physicsobject_handler():
xml_resource("physicsobject")
{
rigid_on=true;
}

xml_resource * xml_physicsobject_handler::new_instance(){
	return new xml_physicsobject_handler;
}

void xml_physicsobject_handler::handle_attribute(string localname, string value){
	if(localname=="id"){
		id=value;
	}
	else if(localname=="rotable"){
		if(value=="off"){
			obj->rotable=false;
		}
	}
}

void xml_physicsobject_handler::handle_start(){
	obj=new compositePhysobj(0,0);
}

void xml_physicsobject_handler::handle_end(){
	bank->physicsobject_db.insert_data(id,obj);
	obj=NULL;
}

bool xml_physicsobject_handler::does_handle_child_element(string element_name){
	if(element_name=="polygonframe"){
		return true;
	}
	else if(element_name=="rigid"){
		return true;
	}
	return false;
}

void xml_physicsobject_handler::handle_child_element_start(string element_name){
}

void xml_physicsobject_handler::handle_child_attribute(string element_name,string attr_name, string attr_value){
	if(element_name=="polygonframe"){
		if(attr_name=="use"){
			poly_id=attr_value;
		}
		else if(attr_name=="x"){
			offx=(float)integer_from_stdstring(attr_value);
		}
		else if(attr_name=="y"){
			offy=(float)integer_from_stdstring(attr_value);
		}
		else if(attr_name=="rigid"){
			if(attr_value=="off"){
				rigid_on=false;
			}
		}

	}
	else if(element_name=="rigid"){
		if(attr_name=="mass"){
			mass=(float)integer_from_stdstring(attr_value);
		}
		else if(attr_name=="kinetic_friction"){
			kin_mu=(float)integer_from_stdstring(attr_value)/1000;
		}
		else if(attr_name=="static_friction"){
			stat_mu=(float)integer_from_stdstring(attr_value)/1000;
		}
		else if(attr_name=="elasticity"){
			e=(float)integer_from_stdstring(attr_value);
		}
	}
}

void xml_physicsobject_handler::handle_child_end(string element_name){

	if(element_name=="rigid"){
		obj->LoadRigid(new rigidBody(mass,kin_mu,stat_mu,e));
	}
	else if(element_name=="polygonframe"){
		frame=bank->polygonframe_db.get_data(poly_id);
		frame->rigid=rigid_on;
		frame_analyser.run(frame);

		obj->LoadPhyFrame(frame_analyser.output_frames,offx,offy);
	}
	offx=0;
	offy=0;
}
