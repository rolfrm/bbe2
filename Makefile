GXX=g++
CPPFLAGS=-c 
ARGS= -lGLU -lGL  -O3 -lIL -lglfw -larmadillo  -lboost_filesystem -lboost_system -lboost_thread -lxerces-c -lopenal -lalut
SRC=  main.cpp utils/hash.cpp utils/toolModule.cpp
OBJS = $(SRC:.cpp=.o)


%.o: %.c
	$(GXX) $(CFLAGS) -o $@ 

all: $(OBJS)
	#cd xml;make;cd ..
	#cd events; make; cd ..
	#cd graphics; make; cd ..
	#cd physics; make; cd ..
	#cd sound; make; cd ..
	$(GXX)  $(ARGS) $^ graphics.a events.a -o run



clean:
	rm -f ./*.o run

