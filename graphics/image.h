#pragma once
#include "drawable.h"
#include <GL/gl.h>
#include <string>

enum SYS_STORAGE_LEVEL{
	GFX_RAM_LEVEL,
	SYS_RAM_LEVEL,
	HDD_LEVEL
};

class image{
public:
	image(std::string path);
	image(char * ,int sizex,int sizey, int type);
	image(GLuint * image);
	image();
	void draw();
	void set_loadlevel(enum SYS_STORAGE_LEVEL level);
	GLuint * getTexture();
	GLuint * image_data;
	int width;
	int height;

	SYS_STORAGE_LEVEL load_level;
};
