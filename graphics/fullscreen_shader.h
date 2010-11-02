/*
 * fullscreen_shader.h
 *
 *  Created on: Jun 9, 2010
 *      Author: rolf
 */

#ifndef FULLSCREEN_SHADER_H_
#define FULLSCREEN_SHADER_H_
#include "drawable.h"
#include <GL/gl.h>
#include <string>
#include "GL_extart_functions.h"


class fbo_capture: public drawable{
public:
	fbo_capture();
	void draw();
	void update();
	GLuint fbo;
	GLuint img;
};

/*
class fbo_end_capture:public drawable{

};
*/
class fullscreen_shader: public drawable{

public:
	fullscreen_shader(int back, int front, std::string shadername);
	void draw();
	void initShader();
	void update();
	void handleCustomEvent(customEvent evt);
	drawable * copy();

	fbo_capture fb_capt;

	GLuint fbo;
	GLuint img;
	GLuint depthbuffer;
	int shaderinited;
	bool first_run;

};

#endif
