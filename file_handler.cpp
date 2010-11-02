/*
 * file_handler.cpp
 *
 *  Created on: May 29, 2010
 *      Author: rolf
 */
#include <iostream>
#include "file_handler.h"
filehandler::filehandler(void){

}
filehandler::filehandler(std::string filename){
	this->filename = filename;
	//filestream.open(filename.c_str(),std::ios_base::in | std::ios_base::out);
}

void filehandler::goToChar(int linenr){
	filestream.seekg(linenr);
}

std::string filehandler::getFileAsStdString(void){
	//goToChar(0);
	filestream.open(filename.c_str(),std::ios_base::in);
	std::string output;
	char line[256];
	std::cout <<".";
	while(filestream.good()){

		filestream.getline(line,256);
		output += line;
		output += '\n';
	}
	std::cout << ".";
	//output +='\0';
	filestream.clear();
	filestream.close();
	return output;
}

char * filehandler::getFileAsCharString(void){
	char * output;
	filestream.open(filename.c_str(),std::ios_base::in |std::ios_base::ate);
	if(filestream.good()){
		int size = filestream.tellg();
		output = new char[size];
		filestream.seekg(0,std::ios::beg);
		filestream.read(output,size);
		filestream.close();
		output[size] = '\0';
		//std::cout << "output: |" << output << "|\n";
		return output;
	}else{
		return NULL;
	}
}
