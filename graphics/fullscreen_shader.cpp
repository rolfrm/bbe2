/*
 * fullscreen_shader.cpp
 *
 *  Created on: Jun 9, 2010
 *      Author: rolf
 */
#include "fullscreen_shader.h"
#include "../file_handler.h"
#include "../globals.h"
#include "graphics_core.h"
fbo_capture::fbo_capture() {

}

void fbo_capture::draw() {
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
			GL_TEXTURE_2D, img, 0);
	glDisable(GL_TEXTURE);
	glDisable(GL_BLEND);
	glPushMatrix();
	glColor4f(0, 0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(800, 0);
	glVertex2i(800, 600);
	glVertex2i(0, 600);
	glEnd();
	glColor4f(1, 1, 1, 1);
	glPopMatrix();
	glEnable(GL_TEXTURE);
	glEnable(GL_BLEND);
}

void fbo_capture::update() {

}

fullscreen_shader::fullscreen_shader(int back, int front, string shadername) {
	zlevel = front;
	fb_capt.zlevel = back;
	set_shader(shadername);
	initShader();
	first_run = true;
	set_id("fss");

}

void fullscreen_shader::initShader() {
	glGenTextures(1, &img);
	glBindTexture(GL_TEXTURE_2D, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_BGR,
			GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffersEXT(1, &fbo);
	fb_capt.fbo = fbo;
	fb_capt.img = img;


}

void fullscreen_shader::draw() {
	if(first_run){
		graphics_core->add_unit(&fb_capt);
		first_run = false;
	}

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glUseProgramObjectARB(*shaderprogram);
	traverse_uniforms();
	int sampler_uniform_loc = glGetUniformLocationARB(*shaderprogram, "tex");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, img);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex2i(0, 0);
	glTexCoord2f(1, 1);
	glVertex2i(400, 0);
	glTexCoord2f(1, 0);
	glVertex2i(400, 300);
	glTexCoord2f(0, 0);
	glVertex2i(0, 300);
	glEnd();
	glUseProgramObjectARB(0);



}

void fullscreen_shader::update() {

}
void fullscreen_shader::handleCustomEvent(customEvent evt){
	if (evt.custom_data == hash32("su") ) {
			uniform_package a;
			try {
				a = boost::any_cast<uniform_package>(evt.data);

			} catch (const boost::bad_any_cast &) {
				std::cout << "failed 1'st cast\n";
			}

			if (a.type == f1) {
				try {
					set_uniform1f(a.uniform_name, boost::any_cast<float>(a.value));
				} catch (const boost::bad_any_cast &) {
					std::cout << "failed 2'st cast\n";
				}
			}
		}
}

drawable * fullscreen_shader::copy(){
	return new fullscreen_shader(*this);
}
