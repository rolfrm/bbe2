/*
 * bf_display.h
 *
 *  Created on: Jul 12, 2010
 *      Author: rolf
 */

#ifndef BF_DISPLAY_H_
#define BF_DISPLAY_H_
#include "drawable.h"
#include "image.h"
#include <string>
#include <vector>
class bf_display: public drawable{
public:
	bf_display(image * font_image);
	bf_display(std::string font_path);
	void draw();
	void update();
	void handle_signal(int signal);
	void set_size( int font_width, int image_width, int font_height, int image_height, int start, int end);
	void set_text(std::string text);

	image * font_data;

	int font_width, image_width,font_height,image_height,start,end;
	std::string text;


};


#endif /* BF_DISPLAY_H_ */
