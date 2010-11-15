#include "image.h"
#include <GL/gl.h>
#include <IL/il.h>
#include <iostream>
image::image(GLuint image){
	/*take an image from an allready loaded image*/
	image_data =image;
}
image::image(){
	/* Should probably never be used..*/
	image_data =0;
}

image::image(char * data,int sizex, int sizey, int format){
	/*Generates a texture from a string. format should be a GL-one.*/
	//glGenTextures(1,image_data);
}
image::image(std::string path){
	if(!_ILIsInit){
		ilInit();
		_ILIsInit = true;
	}

	name = path;
	ILuint texid;
	ilGenImages(1,&texid);
	ilBindImage(texid);

	if(ilLoadImage(path.c_str())){

			ilConvertImage(ilGetInteger(IL_IMAGE_FORMAT), IL_UNSIGNED_BYTE);

	}else{
		std::cout << "Problems converting image: " << path << "\n";
		return;
	}

	glGenTextures(1,&image_data);
	glBindTexture(GL_TEXTURE_2D, image_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	width = ilGetInteger(IL_IMAGE_WIDTH);
	height = ilGetInteger(IL_IMAGE_HEIGHT);
	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), width, height, 0, ilGetInteger(IL_IMAGE_FORMAT),GL_UNSIGNED_BYTE, ilGetData());
	ilDeleteImages(1,&texid);

}
image::~image(){
	glDeleteTextures(1,&image_data);
}
std::string image::getName(){
	return name;
}

GLuint image::getTexture(){
	return image_data;
}

void image::setTexture(GLuint tex){
	image_data = tex;
}

void image::set_loadlevel(enum SYS_STORAGE_LEVEL level){
	if(load_level == GFX_RAM_LEVEL){
		if(level == SYS_RAM_LEVEL){
			/*Load from gpu to cpu ram*/

		}else if(level == HDD_LEVEL){
			/*load from gpu to hdd storage*/
		}
	}else if(load_level == SYS_RAM_LEVEL){
		if(level == GFX_RAM_LEVEL){
			/*load from cpu ram to gpu ram*/
		}else if(level == HDD_LEVEL){
			/*load from cpu to hdd storage*/
		}

	}else if(load_level == HDD_LEVEL){
		if(level == GFX_RAM_LEVEL){
			/*load to gpu from hdd*/
		}else if(level == SYS_RAM_LEVEL){
			/*load from hdd to cpu*/
		}
	}

}

bool image::_ILIsInit;
