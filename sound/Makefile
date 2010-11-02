GXX=g++
CPPFLAGS=-c -Wall -I/usr/include/opencv/ -std=c++0x
#ARGS= -lGLU -lGL -O3 -Wall -lIL -lglfw -larmadillo 
SRC=sound_core.cpp
OBJS=$(SRC:.cpp=.o)
%.o: %.c
	$(GXX) $(CFLAGS) -o $@ 

all: $(OBJS)
	ar rcs sound.a $^
	cp sound.a ../

clean:
	rm -f ./*.o ../sound.a sound.a 
