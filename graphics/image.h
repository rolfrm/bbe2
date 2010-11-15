#pragma once
#include <GL/gl.h>
#include <string>

class image {
	/*
	 * Image class. string constructor takes a string as a path to the image.
	 * Use getTExture to get the opengl texture*/

public:
	image(std::string path);
	image(char *, int sizex, int sizey, int type);
	image(GLuint image);
	image();
	~image();

	GLuint getTexture();
	void setTexture(GLuint texture);

	std::string getName();

	/*Idealism, doesnt work*/
	enum SYS_STORAGE_LEVEL {
		GFX_RAM_LEVEL, SYS_RAM_LEVEL, HDD_LEVEL
	};
	void set_loadlevel(enum SYS_STORAGE_LEVEL level);

	static bool _ILIsInit;

private:
	std::string name;
	GLuint image_data;
	int width;
	int height;

	SYS_STORAGE_LEVEL load_level;

};
