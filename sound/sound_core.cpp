/*
 * sound_core.cpp
 *
 *  Created on: May 7, 2010
 *      Author: rolf
 */
#include "sound_core.h"
#include <iostream>

sound::sound(std::string path){
	id = path;

	ALfloat source0Pos[] ={-2,0,0};
	ALfloat source0Vel[] = {1,0,0};
	ALsizei size, freq;
	ALenum format;
	ALvoid * data;
	ALboolean loop;
	alutLoadWAVFile((ALbyte*)path.c_str(), &format, &data, &size, &freq, &loop);
	alGenBuffers(1, buffer);
	alBufferData(buffer[0],format,data,size,freq);
	alutUnloadWAV(format,data,size,freq);

	alGenSources(1, source);
	alSourcef(source[0], AL_PITCH, 2.0f);
	alSourcef(source[0], AL_GAIN, 0.5f);
	alSourcefv(source[0], AL_POSITION, source0Pos);
	alSourcefv(source[0], AL_VELOCITY, source0Vel);
	alSourcei(source[0], AL_BUFFER,buffer[0]);
	alSourcei(source[0], AL_LOOPING, AL_FALSE);
}

void sound::play(){
	alSourcePlay(source[0]);
}

void sound::pause(){
	alSourcePause(source[0]);
}

void sound::stop(){

}

soundCore::soundCore(){
	alutInit(NULL, 0);
}

void soundCore::add_sound(std::string path){
	sounds[path] = new sound(path);
}

void soundCore::add_sound(sound * snd){
	sounds[snd->id] = snd;

}

int soundCore::play_sound(std::string id){
	sounds[id]->play();
}
