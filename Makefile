GXX=g++
CPPFLAGS=-c -I/usr/include/opencv/ -std=c++0x
ARGS= -lGLU -lGL  -O3 -lIL -lglfw -larmadillo  -lboost_filesystem -lboost_system -lboost_thread -lxerces-c -lopenal -lalut
SRC= core.cpp file_handler.cpp hash.cpp main.cpp sprite.cpp toolModule.cpp
OBJS = $(SRC:.cpp=.o)


%.o: %.c
	$(GXX) $(CFLAGS) -o $@ 

all: $(OBJS) events.a graphics.a physics.a sound.a
	cd xml;make;cd ..
	cd events; make; cd ..
	cd graphics; make; cd ..
	cd physics; make; cd ..
	cd sound; make; cd ..
	$(GXX)  $(ARGS) $^  gxml.a  events.a graphics.a  physics.a sound.a -o run

gxml.a:
	cd xml; make;cd ..
events.a:
	echo "hej"
	cd events
	make
	cd ..
graphics.a:

	
physics.a:
	cd physics
	make
	cd ..
	
sound.a:
	cd sound
	make
	cd ..
	



clean:
	rm -f ./*.o run

