#ifndef DRAWABLE_H
#define DRAWABLE_H
class graphicsCore;
#include "../toolModule.h"
#include "../events/evented.h"
class sprite;
class Camera;
//class GLuint;
#include <string>
#include <GL/gl.h>
#include <map>
#include <boost/any.hpp>

enum uniform_type{
	f1,
	f2,
	f3,
	f4,
	i1,
	i2,
	i3,
	i4
};


class uniform_package{
public:
	uniform_package(string uniform_name,uniform_type, boost::any value);
	uniform_package(){};
	string uniform_name;
	uniform_type type;
	boost::any value;
};

class drawable:public eventMaster{
public:
	drawable(Vector2D * Position, graphicsCore * Parent);
	drawable();
	drawable(sprite * parent);
	void set_parent(sprite * parent);
	virtual void draw(){};
	virtual void update(){};
	virtual void handle_signal(int signal);
	virtual drawable * copy(){return new drawable;}

	void traverse_uniforms();

	void set_zlevel(int zlevel);
	void set_camera(Camera * cam);
	void set_camera(std::string cam_id);
	void set_offset(float x, float y);
	void set_offset(Vector2D vec);
	void set_shader(std::string new_shadername);
	void set_uniform1f(std::string uniform_name, float value);

	Vector2D * Pos;
	float * angle;
	sprite * Parent;
	int zlevel;
	float parralax_x;
	float parralax_y;
	Camera * cam;
	Vector2D offset;
	GLenum * shaderprogram;

private:
	std::string shadername;
	std::map <std::string, float> uniform1f_map;

};
class Vertex2D {

public:
	Vertex2D(float x, float y);
	float x;
	float y;
};

class Color {

public:
	Color() {
	}
	;
	Color(float r, float g, float b);
	Color(float r, float g, float b, float a);
	void setColor(Color * col);
	float r;
	float g;
	float b;
	float a;
};

#endif // DRAWABLE_H
