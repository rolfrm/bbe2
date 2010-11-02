//#include "main.h"
#include <iostream>
#include "core.h"
#include "events/event_core.h"
#include "graphics/graphics_core.h"
#include "physics/physics_core.h"
#include "resource_bank.h"
#include "sound/sound_core.h"
#include "physics/physics_core.h"
#include "graphics/GL_extart_functions.h"
#include "xml/xml_core.h"

#include "xml/custom_resources/xml_base_resource.h"
#include "xml/custom_resources/xml_spritesheet_resource.h"
#include "xml/custom_resources/xml_custom_resource.h"
#include "xml/custom_resources/xml_sprite_resource.h"
#include "xml/custom_resources/xml_level_resource.h"
#include "xml/custom_resources/xml_evented.h"
#include "xml/custom_resources/xml_physicsobject_handler.h"
#include "xml/custom_resources/xml_polygonFrame_handler.h"
#include "xml/custom_resources/xml_shader.h"
#include "xml/custom_resources/xml_fsc_start.h"
#include "xml/custom_resources/xml_mesh2d.h"
#include "threaded.h"
#include "graphics/fullscreen_shader.h"
#include "graphics/simple_poly.h"
graphicsCore * graphics_core;
core * main_core;
eventCore * event_core;
physicsCore * physics_core;
physicsCore * physics_ui;
soundCore * sound_core;
resource_bank * bank;
xmlCore * xml_core;


int init_modules(){
	main_core = new core;
	main_core->start_thread();
	graphics_core = new graphicsCore;
	graphics_core->add_camera("ui_cam",0,0);
	//graphics_core->start_thread();
	//glfwSleep(1);

	event_core = new eventCore;
	event_core->start_thread();
	physics_core = new physicsCore;
	physics_core->start_thread();
	physics_ui = new physicsCore;
	physics_ui->start_thread();
	sound_core = new soundCore;
	bank = new resource_bank;

	xml_core = new xmlCore;
	xml_core->load_xml_resource(new xml_base_resource);
	xml_core->load_xml_resource(new spritesheet_resource);
	xml_core->load_xml_resource(new image_resource);
	xml_core->load_xml_resource(new xml_sprite_resource);
	xml_core->load_xml_resource(new xml_level_resource);
	xml_core->load_xml_resource(new xml_evented);
	xml_core->load_xml_resource(new xml_polygonFrame_handler);
	xml_core->load_xml_resource(new xml_physicsobject_handler);
	xml_core->load_xml_resource(new xml_shader);
	xml_core->load_xml_resource(new xml_fsc);
	xml_core->load_xml_resource(new xml_mesh2d);
	graphics_core->run();


	setupGLSL();
	return 0;
}

#include "graphics/bf_display.h"
//#include "events/vertex_painter.h"
#include "sprite.h"
//#include "graphics/gradient.h"
int main(int argc, char * argv[]){

	init_modules();

	xml_core->load("../game.xml");
	//graphics_core->load_shaderprogram("small2", "box_anim.vert","box_anim.frag");
	//graphics_core->load_shaderprogram("player_shader","small2.vert","small2.frag");
	//fullscreen_shader fs(-100,10,"player_shader");
	//graphics_core->add_unit(&fs);

	simple_poly sp1;
	sp1.add_vertex(-200,-150);
	sp1.add_vertex(200,-150);
	sp1.add_vertex(200,150);
	sp1.add_vertex(-200,150);
	sp1.set_fill_mode(true);
	sp1.set_color(0.5,0.5,0.5,0.5);
	sp1.set_camera("ui_cam");
	bank->drawable_db.insert_data("inventory_bg",&sp1	);



	//bf_display commingsoon("omgfont.png");
	//commingsoon.set_size(5,100,5,100,0,0);
	//commingsoon.set_text("Gameplay comming soon...");

	//graphics_core->add_unit(&commingsoon);

//	sprite vp_holder;
	//vp_holder.evt = new vertex_painter;
	//vp_holder.evt->add_group("kctrl");
	//main_core->add_entity(&vp_holder);


	//gradient gra;
	//gra.set_first_color(0.4,0.4,1,1);
	//gra.set_last_color(1,1,1,1);
	//sprite gradient_sprite;
	//gradient_sprite.set_drawable(&gra);
	//main_core->add_entity(&gradient_sprite);
	//gra.zlevel = -100;

	while(graphics_core->running){
		graphics_core->run();
	}

}
