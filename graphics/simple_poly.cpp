#include "simple_poly.h"
#include <GL/gl.h>
#include <iostream>
#include "graphics_core.h"
#include "../globals.h"
simple_poly::simple_poly(){
	color.r = 1;
	color.g = 1;
	color.b = 1;
	color.a = 1;
	mode = GL_LINE_LOOP;
}

void simple_poly::draw(){
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	//glRotatef(*angle,0,0,1);
	if(cam == NULL){
		glTranslatef(( Pos->x-graphics_core->cam.Pos.x)*1 +graphics_core->cam_width/2, (  Pos->y-graphics_core->cam.Pos.y )*1+ graphics_core->cam_height/2,0);
	}else {
		glTranslatef( Pos->x- cam->Pos.x +graphics_core->cam_width/2, (  Pos->y-cam->Pos.y )*1+350,0);
	}
	glColor4f(color.r,color.g,color.b,color.a);

	glBegin(mode);
	for (unsigned int i = 0; i < vertex_list.size();i++){
		glVertex2f( vertex_list[i].x , vertex_list[i].y );
	}
	glEnd();
	glPopMatrix();
	glColor4f(1,1,1,1);
	glEnable(GL_TEXTURE_2D);

}

void simple_poly::update(){


}

void simple_poly::add_vertex(Vector2D vert){
	vertex_list.push_back(vert);
}

void simple_poly::add_vertex(int x, int y){
	Vector2D p(x,y);
	vertex_list.push_back(p);
}

void simple_poly::delete_last_vertex(){
	if(vertex_list.size() > 0){
		vertex_list.pop_back();
	}
}

void simple_poly::set_color(float r, float g, float b, float a){
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

drawable * simple_poly::copy(){
	return this;
}
void simple_poly::set_fill_mode(bool state){
	if(state == true){
		mode = GL_POLYGON;

	}else{
		mode = GL_LINE_LOOP;
	}
}
