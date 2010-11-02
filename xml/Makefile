GXX=g++
CPPFLAGS=-c -Wall -I/usr/include/opencv/ -std=c++0x
#ARGS= -lGLU -lGL -O3 -Wall -lIL -lglfw -larmadillo 
SRC=xml_resource.cpp xml_parent_proxy.cpp xml_handler.cpp xml_core.cpp custom_resources/xml_sprite_resource.cpp custom_resources/xml_polygonFrame_handler.cpp custom_resources/xml_base_resource.cpp custom_resources/xml_level_resource.cpp custom_resources/xml_spritesheet_resource.cpp custom_resources/xml_evented.cpp custom_resources/xml_shader.cpp custom_resources/xml_custom_resource.cpp custom_resources/xml_physicsobject_handler.cpp
OBJS = $(SRC:.cpp=.o)


%.o: %.c
	$(GXX) $(CFLAGS) -o $@ 

all: $(OBJS)
	ar rcs gxml.a $^
	cp gxml.a ../

clean:
	rm -f ./*.o rm gxml.a

