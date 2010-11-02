/*
 * shadertest.cpp
 *
 *  Created on: May 29, 2010
 *      Author: rolf
 */

#include "shadertest.h"
#include <GL/glext.h>
#include <GL/glfw.h>
#include <queue>
#include <iostream>
#include <string.h>
#include <math.h>
#include "GL_extart_functions.h"
#include "../file_handler.h"
shadertest::shadertest(std::string fragment_shader, std::string vertex_shader) :
	drawable(0) {
	movement = 0;
	zlevel = -1;
	fragment_shader_path = fragment_shader;
	vertex_shader_path = vertex_shader;
}

void shadertest::initShader() {
	filehandler fragtext(fragment_shader_path);
	filehandler verttext(vertex_shader_path);

	const char * fs = (const char*) fragtext.getFileAsCharString();
	const char * vs = (const char*) verttext.getFileAsCharString();
	shaderprogram = glCreateProgramObjectARB();

	fragShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	vertShader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	glShaderSourceARB(fragShader, 1, &fs, NULL);
	glShaderSourceARB(vertShader, 1, &vs, NULL);
	glCompileShaderARB(vertShader);
	glCompileShaderARB(fragShader);
	glAttachObjectARB(shaderprogram, fragShader);
	glAttachObjectARB(shaderprogram, vertShader);
	glLinkProgramARB(shaderprogram);

	glGenTextures(1, &img);
	glBindTexture(GL_TEXTURE_2D, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_BGR,
			GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffersEXT(1, &fbo);
}

void shadertest::draw() {
	movement++;
	if (shaderinited != 12321) {
		char log[1000];
		int len;
		initShader();
		glGetInfoLogARB(shaderprogram, 999, &len, log);
		shaderinited = 12321;
		std::cout << log << "\n";
		return;
	}
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
			GL_TEXTURE_2D, img, 0);
	glPushMatrix();
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(800, 0);
	glVertex2i(800, 600);
	glVertex2i(0, 600);
	glEnd();

	glUseProgramObjectARB(shaderprogram);

	glColor3f(1, 1, 0);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glColor3f(1, 0.5, 0);
	glVertex2i(800, 0);
	glVertex2i(800, 600);
	glVertex2i(0, 600);
	glEnd();
	glPopMatrix();
	glColor3f(1, 1, 1);

	glUseProgramObjectARB(0);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	glBindTexture(GL_TEXTURE_2D, img);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex2i(0, 0);
	glTexCoord2f(1, 1);
	glVertex2i(800, 0);
	glTexCoord2f(1, 0);
	glVertex2i(800, 600);
	glTexCoord2f(0, 0);
	glVertex2i(0, 600);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

}
void shadertest::update() {

}
