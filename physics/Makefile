GXX=g++
CPPFLAGS=-c -Wall -I/usr/include/opencv/ -std=c++0x
#ARGS= -lGLU -lGL -O3 -Wall -lIL -lglfw -larmadillo 
SRC=CollisionHandler.cpp compositePhysobj.cpp frameAnalyzer.cpp phyArchetypes.cpp physics_core.cpp
OBJS= $(SRC:.cpp=.o)
%.o: %.c
	$(GXX) $(CFLAGS) -o $@ 

all: $(OBJS)
	ar rcs physics.a $^
	cp physics.a ../

clean:
	rm -f ./*.o rm physics.a
