GXX=g++
CPPFLAGS=-c -Wall
#ARGS= -lGLU -lGL -O3 -Wall -lIL -lglfw -larmadillo 
SRC=GL_exart_function.cpp mesh2d.cpp shader.cpp material.cpp image.cpp camera.cpp light.cpp graphicsCore.cpp scenegraph.cpp OBJLoader.cpp
OBJS = $(SRC:.cpp=.o)
%.o: %.c
	$(GXX) $(CFLAGS) -o $@ 

all: $(OBJS)
	ar rcs graphics.a $^
	cp graphics.a ../
clean:
	rm -f ./*.o graphics.a ../graphics.a
