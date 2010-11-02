#pragma once
#include <list>
#include "../toolModule.h"
#include <GL/gl.h>
#include <map>
#include <string>
#include "../threaded.h"
#include "../resource_bank.h"
#include "../events/evented.h"
using namespace std;
class simple_physics_core;
class drawable;
extern resource_bank * bank;
struct Camera{
			Vector2D Pos;
			Vector2D Dims;
			string name;
			int order;
		};



class graphicsCore:public threaded{

	public:
	graphicsCore();
	void add_unit(drawable * dw);
	void remove_unit(drawable * dw);
	void sort_units();
	void prepare();
	void render();
	void run();
	void add_camera(string name,int x, int y);
	int load_shaderprogram(string program_id,string vertex_shader_path, string fragment_shader_path);

	Camera * get_camera(string name);

	bool started;
	bool running;
	bool renderlist_ischanged;
	GLuint main_fbo;
	simple_physics_core * spc;
	 int cam_width;
	 int cam_height;
	 int window_width;
	 int window_height;
	map<string, Camera *> cameras;
	list <drawable *> renderlist;
	int t;

	Camera cam;
};
