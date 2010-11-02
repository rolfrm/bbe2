#include "drawable.h"
#include <math.h>
#include <GL/gl.h>
#include "../toolModule.h"
#include "graphics_core.h"
#include "../globals.h"
Vertex2D::Vertex2D(float x = 0, float y = 0){
	this->x = x;
	this->y = y;
}

Color::Color(float r, float g, float b){
this->r = r;
this->b = b;
this->g = g;
this->a = 1;
}
Color::Color(float r, float g, float b, float a){
this->r = r;
this->b = b;
this->g = g;
this->a = a;


}

void Color::setColor(Color *col){
r = col->r;
b = col->b;
a = col->a;
g = col->g;

}

uniform_package::uniform_package(string name, uniform_type type, boost::any value){
	uniform_name = name;
	this->type = type;
	this->value = value;
}

drawable::drawable():eventMaster("drawable")
{
	Parent = NULL;
	Pos = 0;
	parralax_x = 1;
	parralax_y = 1;
	zlevel = 0;
	cam = NULL;
	shaderprogram = NULL;
}
drawable::drawable(Vector2D *position,graphicsCore * Parent)
{
	drawable();
}

drawable::drawable(sprite * parent){

	drawable();
	Parent = parent;
}

void drawable::set_parent(sprite * parent){
	Parent = parent;
}

void drawable::handle_signal(int signal){
}

void drawable::set_zlevel(int zlevel){
	this->zlevel = zlevel;
}

void drawable::set_camera(Camera * new_cam){
	cam = new_cam;
}

void drawable::set_camera(std::string cam_id){
	Camera * new_cam = graphics_core->get_camera(cam_id);
	if(new_cam != NULL){
		cam = new_cam;
	}
}

void drawable::set_offset(float x,float y){
	offset.x = x;
	offset.y = y;
}

void drawable::set_offset(Vector2D vec){
	offset = vec;
}

void drawable::set_shader(string new_shadername){
	shaderprogram = bank->glunit_db.get_data(new_shadername);
	if(shaderprogram == NULL){
		std::cout << "ERROR LOADING SHADER:" << new_shadername << "\n";
	}
}
#include "GL_extart_functions.h"
void drawable::set_uniform1f(std::string uniform_name, float value ){
	uniform1f_map[uniform_name] = value;
}

void drawable::traverse_uniforms(){
	if(shaderprogram != NULL){
	std::map<std::string,float>::iterator it = uniform1f_map.begin();
	for(;it != uniform1f_map.end();it++){
		int uni_loc = glGetUniformLocationARB(*shaderprogram,it->first.c_str());
		glUniform1fARB(uni_loc,it->second);
	}
	}
}
