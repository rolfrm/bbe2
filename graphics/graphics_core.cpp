	#include "graphics_core.h"
#include <iostream>
#include <list>
#include <GL/glfw.h>

#include <IL/il.h>
#include "drawable.h"
#include "../core.h"
#include "../physics/compositePhysobj.h"
#include "../physics/phyArchetypes.h"
#include "GL_extart_functions.h"

//#include "../globals.h"
bool drawable_compareFunction(drawable *d1, drawable * d2){
	if(d1->zlevel < d2->zlevel){
		return true;
	}
	return false;
	
	
	
}

graphicsCore::graphicsCore(){
	cam.Dims.setXY(400,300);
   started = false;
   running = true;
   renderlist_ischanged = true;
	spc = NULL;


}

void graphicsCore::add_unit(drawable *dw){
	renderlist.insert(renderlist.end(),dw);
}

void graphicsCore::remove_unit(drawable *dw){
	renderlist.remove(dw);

}

void graphicsCore::sort_units(){
	renderlist.sort(drawable_compareFunction);
}
void GLFWCALL keycallback(int key, int action );
int GLFWCALL windowclosecallback(void);
void GLFWCALL mouseclickcallback(int button,int action);
void GLFWCALL mouseposcallback(int x, int y);
void graphicsCore::run(){
	sort_units();
	if(!started){

		window_width = 800;
		window_height = 600;
		cam_width = window_width/2;
		cam_height = window_height/2;

		ilInit();
		glfwInit();
		glfwOpenWindow(window_width,window_height,2,2,2,0,0,0,GLFW_WINDOW);
		glfwSetKeyCallback(keycallback);
		glfwSetWindowCloseCallback(windowclosecallback);
		glfwSetMouseButtonCallback(mouseclickcallback);
		  glfwSetMousePosCallback(mouseposcallback);
		  started = true;
		  glPointSize( 2 );
		  glLineWidth(2);
		  glColor3f(1,1,1);
		  glOrtho(0,cam_width,cam_height,0,1,-1);
		  //glClearColor(0.4,0.5,0.4,1);
		  glClearColor(0,0,0,1);
		  glEnable(GL_BLEND);
		  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		  glDisable(GL_ALPHA_TEST);
		  glEnable(GL_TEXTURE_2D);
	}

   if(glfwGetKey(GLFW_KEY_ESC)){
	   running = false;
   }
   glClear(GL_COLOR_BUFFER_BIT);

   double t1 = glfwGetTime();
   render();

   glfwSleep(0.02);
   glfwSwapBuffers();

}

void graphicsCore::render(){
	   glMatrixMode(GL_MODELVIEW);
	   std::list<drawable*>::iterator i;
	for (i = renderlist.begin(); i !=renderlist.end();++i){
		(*i)->update();
		(*i)->draw();
	}
}

void graphicsCore::add_camera(string name, int x, int y){
	Camera * cam1 = new Camera;
	cam1->order = 0;
	cam1->Pos = new Vector2D(x,y);
	cam1->name = name;
	cameras[name] = cam1;
}

Camera * graphicsCore::get_camera(string name){
	if(cameras.find(name) != cameras.end()){
		return cameras[name];
	}
	return NULL;
}
#include "../file_handler.h"

int graphicsCore::load_shaderprogram(string program_id,string vertex_shader_path, string fragment_shader_path){

	filehandler fragtext(fragment_shader_path);
	filehandler verttext(vertex_shader_path);
	const char * fs = (const char*) fragtext.getFileAsCharString();
	const char * vs = (const char*) verttext.getFileAsCharString();
	GLuint shaderprogram = glCreateProgramObjectARB();
	GLuint	vertShader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	GLuint	fragShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	glShaderSourceARB(fragShader, 1, &fs, NULL);
	glShaderSourceARB(vertShader, 1, &vs, NULL);
	glCompileShaderARB(vertShader);
	glCompileShaderARB(fragShader);
	glAttachObjectARB(shaderprogram, fragShader);
	glAttachObjectARB(shaderprogram, vertShader);
	glLinkProgramARB(shaderprogram);
	int len;
	char log[1000];

	glGetInfoLogARB(shaderprogram, 999, &len, log);
	std::cout << log << "\n";

	GLuint * program = new GLuint;
	*program = shaderprogram;
	bank->glunit_db.insert_data(program_id,program);
}

