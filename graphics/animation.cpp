#include "animation.h"
#include "../toolModule.h"
#include <iostream>
#include "graphics_core.h"
#include "../globals.h"
#include "GL_extart_functions.h"
sprite_line::sprite_line(animation_types a) {
	end = NULL;
	framelist = NULL;
	type = a;

}
void sprite_line::insert_frame(int x, int y, int w, int h, float dt) {

	frame * tmp = new frame;
	tmp->width = w;
	tmp->height = h;
	tmp->x = x;
	tmp->y = y;
	tmp->dt = dt;

	if (framelist != NULL) {
		end->next = tmp;
		end = tmp;
		tmp->next = framelist;
	} else {
		framelist = tmp;
		end = tmp;
		tmp->next = framelist;
	}
}

void sprite_line::set_id(std::string new_id) {
	id = new_id;
}

void sprite_line::print_frames() {
	frame * tmp = framelist;
	do {
		std::cout << "Frame: " << tmp->width << " " << tmp->height << " "
				<< tmp->x << " " << tmp->y << " " << tmp->dt << "\n";
		tmp = tmp->next;
	} while (tmp != framelist);
}

spritesheet::spritesheet() {

}
void spritesheet::print_spritelines() {
	for (unsigned int i = 0; i < lines.size(); i++) {
		std::cout << "Line " << i << "\n";
		lines[i]->print_frames();
	}
}

void spritesheet::add_sprite_line(sprite_line * sl) {
	lines.push_back(sl);
}

void spritesheet::set_image(image * new_img) {
	img = new_img;
}

animation::animation() {
	deltat = 0;
	add_group("drawable");

}
animation::animation(sprite * parent) :
	drawable(parent) {
	deltat = 0;
}
sprite_line * spritesheet::get_line(std::string line_id) {
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i]->id == line_id) {
			return lines[i];
		}
	}
	return NULL;
}
void animation::draw() {

	int sampler_uniform_loc;
	if (shaderprogram != NULL) {
		glUseProgramObjectARB(*shaderprogram);
		sampler_uniform_loc = glGetUniformLocationARB(*shaderprogram, "tex");
		traverse_uniforms();
		glActiveTexture(GL_TEXTURE0);
	}
	image *img = own_spritesheet->img;
	float xmin = current_frame->x / img->width;
	float xmax = xmin + current_frame->width / img->width;
	float x_im_offset = current_frame->width / 2;

	float ymin = current_frame->y / img->height;
	float ymax = ymin + current_frame->height / img->height;
	float y_im_offset = current_frame->height / 2;

	glPushMatrix();
	glTranslatef((int) offset.x, (int) offset.y, 0);
	if (cam == NULL) {
		glTranslatef((int) ((Pos->x - graphics_core->cam.Pos.x) * parralax_x
				+ graphics_core->cam_width / 2), (int) ((Pos->y
				- graphics_core->cam.Pos.y) * parralax_y
				+ graphics_core->cam_height / 2), 0);
	} else {
		glTranslatef((int) ((Pos->x - cam->Pos.x) * parralax_x
				+ graphics_core->cam_width / 2), (int) ((Pos->y - cam->Pos.y)
				* parralax_y + graphics_core->cam_height / 2), 0);
	}

	if (angle != NULL) {

		glRotatef((*angle) * 180 / 3.14, 0, 0, 1);
	}
	glBindTexture(GL_TEXTURE_2D, *(img->image_data));

	glBegin(GL_QUADS);
	glTexCoord2f(xmin, ymax);
	glVertex2i(-x_im_offset, y_im_offset);
	glTexCoord2f(xmin, ymin);
	glVertex2i(-x_im_offset, -y_im_offset);
	glTexCoord2f(xmax, ymin);
	glVertex2i(x_im_offset, -y_im_offset);
	glTexCoord2f(xmax, ymax);
	glVertex2i(x_im_offset, y_im_offset);
	glEnd();
	glPopMatrix();
	if (shaderprogram != NULL) {
		glUseProgramObjectARB(0);
	}
}

void animation::update() {

	deltat++;
	if (deltat > current_frame->dt || deltat < 0) {
		deltat = 0;
		current_frame = current_frame->next;
		/*if(current_frame == current_line->framelist && current_line->type == ANIM_ONCE){
		 current_line = current_spritesheet->default_line;
		 }*/
	}

}

void animation::set_line(int linenr) {
	if (linenr <= own_spritesheet->lines.size()) {
		current_line = own_spritesheet->lines[linenr];
		current_frame = current_line->framelist;
	}
}

int animation::set_animation(std::string name) {
	sprite_line * new_line = own_spritesheet->get_line(name);
	if (new_line != NULL) {
		current_line = new_line;
		current_frame = current_line->framelist;
		return 0;
	}
	return -1;
}

void animation::handle_signal(int signal) {

	set_line(signal);
}
void animation::set_parent(sprite * parent) {
	this->Parent = parent;
}
animation * animation::copy() {

	this->set_shader("small2");
	this->set_uniform1f("state", 0);
	animation * clone = new animation(*this);
	clone->set_id(get_id());
	return clone;
}

void animation::set_spritesheet(spritesheet * new_spritesheet) {
	own_spritesheet = new_spritesheet;
	set_line(0);
}

void animation::handleCustomEvent(customEvent evt) {
	if(evt.custom_data == "hide" ){
		std::cout << "okay\n";
	}
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
