#pragma once
#include "drawable.h"
#include <vector>
#include "../toolModule.h"
#include <GL/gl.h>
class graphicsCore;
class simple_poly: public drawable{
	public:
   simple_poly();
	void draw();
	void update();
	void set_color(float r, float g, float b, float a);
	void add_vertex(Vector2D vert);
	void add_vertex(int x, int y);
	void delete_last_vertex();
	void set_fill_mode(bool state);
	drawable * copy();
	Color color;
	private:
	std::vector <Vector2D> vertex_list;
	int mode;
};

