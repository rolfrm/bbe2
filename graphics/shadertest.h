/*
 * shadertest.h
 *
 *  Created on: May 29, 2010
 *      Author: rolf
 */

#ifndef SHADERTEST_H_
#define SHADERTEST_H_

#define ARB_LINUX
#include "drawable.h"
#include <GL/gl.h>
#include <string>
//#ifdef ARBG_LINUX


//#endif
int setupGLSL();
class shadertest: public drawable{
public:
	shadertest(std::string frag_shader,std::string vert_shader);
	void draw();
	void initShader();
	void update();
	GLenum shaderprogram;
	GLenum fragShader;
	GLenum vertShader;
	GLuint fbo;
	GLuint img;
	GLuint depthbuffer;

	std::string fragment_shader_path;
	std::string vertex_shader_path;

	int shaderinited;

	float movement;
};

#endif /* SHADERTEST_H_ */
