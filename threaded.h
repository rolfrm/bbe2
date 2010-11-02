/*
 * threaded.h
 *
 *  Created on: Aug 8, 2010
 *      Author: rolf
 */



#ifndef THREADED_H_
#define THREADED_H_
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <GL/glfw.h>
class threaded{
public:
	threaded(){
		alive = true;
		waittime = 0.01;

	}
	void start_thread(){
		running = true;
		rThread = new boost::thread(boost::bind( &threaded::thread_run,this));
	}
	void start_running(){
		running = true;
	}
	void thread_run(){
		while(alive){
			if(running){
				run();
				glfwSleep(waittime);
			}else{
				glfwSleep(0.01);
			}
		}
	}
	virtual void run() = 0;
	void pause_running(){
		running = false;
	}
	void kill_thread(){
		running = false;
		alive = false;
	}
	bool is_alive(){
		return alive;
	}
	void set_waittime(double seconds){
		waittime = seconds;
	}
	void wait(int ms){
		glfwSleep(ms);
	}
private:
	bool running;
	bool alive;
	boost::thread * rThread;
	double waittime;
};

#endif /* THREADED_H_ */
