GXX=g++
CPPFLAGS=-c -Wall -I/usr/include/opencv/ -std=c++0x
#ARGS= -lGLU -lGL -O3 -Wall -lIL -lglfw -larmadillo 
SRC=animation.cpp bf_display.cpp drawable.cpp fullscreen_shader.cpp GL_exart_function.cpp graphics_core.cpp image.cpp shadertest.cpp simple_poly.cpp
OBJS= $(SRC:.cpp=.o)
%.o: %.c
	$(GXX) $(CFLAGS) -o $@ 

all: $(OBJS)
	ar rcs graphics.a $^
	cp graphics.a ../

clean:
	rm -f ./*.o
