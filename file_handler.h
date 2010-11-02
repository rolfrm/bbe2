/*
 * file_handler.h
 *
 *  Created on: May 29, 2010
 *      Author: rolf
 */

#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_

#include <string>
#include <iostream>
#include <fstream>

class filehandler{
public:
	filehandler(void);
	filehandler(std::string);

	std::string getFileAsStdString(void);
	char * getFileAsCharString(void);

	void goToChar(int pos);
	std::string readLine(void);
	void writeLine(std::string line);

private:
	std::fstream filestream;
	std::string filename;
};

#endif /* FILE_HANDLER_H_ */
