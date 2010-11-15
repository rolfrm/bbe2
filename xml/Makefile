GXX=g++
CPPFLAGS=-c -Wall -I/usr/include/opencv/
SRC=xml_resource.cpp xml_parent_proxy.cpp xml_handler.cpp xml_core.cpp 
ARGS= -lGLU -lGL  -O3 -lIL -lglfw -larmadillo  -lboost_filesystem -lboost_system -lboost_thread -lxerces-c -lopenal -lalut
OBJS = $(SRC:.cpp=.o)


%.o: %.c
	$(GXX) $(CFLAGS) -o $@ 

all: $(OBJS)
	ar rcs gxml.a $^
	cp gxml.a ../

clean:
	rm -f ./*.o gxml.a

