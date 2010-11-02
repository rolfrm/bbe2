#pragma once
#include <string>
#include <list>
#include <vector>
#include <GL/gl.h>
#include "drawable.h"
#include "image.h"

#define SPRITE_LINE_MAX_FRAMES 20
class graphicsCore;

struct frame{
	float width;
	float height;
	float x;
	float y;
	float dt;
	frame * next;

};

enum animation_types{
		ANIM_ONCE,
		ANIM_REPEAT
	};

class sprite_line{
public:
	sprite_line(animation_types a= ANIM_ONCE);
	void insert_frame(int x, int y, int w, int h, float dt);
	void print_frames();
	void set_id(std::string new_id);

	std::string id;
	frame * framelist;
	frame * end;


	animation_types type;

};

class spritesheet{
public:
	spritesheet();
	std::string id;
	image * img;
	std::vector <sprite_line *> lines;
	sprite_line * default_line;
	void print_spritelines();
	void add_sprite_line(sprite_line * sl);
	void set_image(image * new_img);
	sprite_line * get_line(std::string line_id);
};
class animation: public drawable{
public:
	animation();
	animation(sprite * parent);
	void draw();
	void update();
	void handle_signal(int signal);
	void set_line(int linenr);
	int set_animation(std::string name);
	void set_parent(sprite * parent);
	void set_spritesheet(spritesheet * new_spritesheet);
	void handleCustomEvent(customEvent evt);

	animation * copy();

	spritesheet * own_spritesheet;

	//private:
	sprite_line * current_line;
	frame * current_frame;
	float deltat;
};
