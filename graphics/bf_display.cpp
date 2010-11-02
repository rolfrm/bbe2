/*
 * bf_display.cpp
 *
 *  Created on: Jul 12, 2010
 *      Author: rolf
 */

#include "bf_display.h"
#include <iostream>
#include <GL/gl.h>
#include <math.h>
bf_display::bf_display(image * font_image):drawable(){
	font_data = font_image;
	zlevel = 100;
}
bf_display::bf_display(std::string font_path):drawable(){
	font_data =new image(font_path);
	zlevel = 100;
}

void bf_display::draw(){
	float x_spacing = 1.2;
	float y_spacing = 1.3;
 float line = 0;
 float col = 0;
 float chars_per_line = image_width/font_width;
 int chars_per_col = image_height/font_height;
 //std::cout << "cpl: " << chars_per_line << " cpc:" << chars_per_col << " " << chars_per_line << " " << chars_per_col <<  "\n";

 glPushMatrix();
 glTranslatef(200,230,0);
 glEnable(GL_TEXTURE_2D);
 glBindTexture(GL_TEXTURE_2D, *(font_data->image_data));
 glBegin(GL_QUADS);
 glColor3f(0,0,0);
 for(unsigned int i = 0; i < text.length(); i++){
	int cnr = text[i];
	if(cnr != '\n' && cnr != '\0'){
	float icol  = floor(((float)cnr)/chars_per_line)*5/100 ;
	float iline =  floor(cnr % chars_per_col)*5/100;
	 glTexCoord2f(iline,icol);
	 glVertex2i(col*font_width,line*font_height);

	 glTexCoord2f((iline+ 0.05),icol);
	 glVertex2i((col*1+1)*font_width,(line)*font_height);

	 glTexCoord2f((iline+ 0.05),(icol + 0.05));
	 glVertex2i((col+1)*font_width,(line+1)*font_height);

	 glTexCoord2f(iline,(icol + 0.05));
	 glVertex2i((col)*font_width,(line+1)*font_height);

	 col += x_spacing;
	}else if (cnr == '\n'){
		line += y_spacing;
		col = 0;
	}
}
 glColor3f(1,1,1);
 glEnd();
 glPopMatrix();

}

void bf_display::update(){

}

void bf_display::handle_signal(int signal){

}

void bf_display::set_size(int font_width, int image_width, int font_height, int image_height, int start, int end){
	this->font_width = font_width;
	this->font_height = font_height;
	this->image_height = image_height;
	this->image_width = image_width;
	this->start = start;
	this->end = end;
}

void bf_display::set_text(std::string str){
	text = str;
}
