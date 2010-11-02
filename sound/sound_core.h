/*
 * sound_core.h
 *
 *  Created on: May 7, 2010
 *      Author: rolf
 */

#ifndef SOUND_CORE_H_
#define SOUND_CORE_H_
#include <AL/al.h>
#include <AL/alut.h>
#include <string>
#include <boost/unordered_map.hpp>
#include <queue>
int soundtest();
class sound{
public:
	sound(std::string path);
	std::string id;
	virtual void play();
	virtual void stop();
	virtual void pause();
	int length;
private:
	ALuint buffer[1];
	ALuint source[1];
};

class music:public sound{
	music(std::string path);
	void play();
	void stop();
	virtual void pause();
};

class soundCore{
public:
	soundCore();

	int play_sound(std::string id);
	void add_sound(std::string path);
	void add_sound(sound * snd);
	boost::unordered_map <std::string,sound *> sounds;
	std::queue <std::string> requests;

};


#endif /* SOUND_CORE_H_ */
