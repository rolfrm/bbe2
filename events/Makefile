GXX=g++
CPPFLAGS=-c -Wall -I/usr/include/opencv/ -std=c++0x
#ARGS= -lGLU -lGL -O3 -Wall -lIL -lglfw -larmadillo 
SRC=event_core.cpp evented.cpp events.cpp custom_evented/game_item.cpp custom_evented/inventory_ai.cpp custom_evented/player_ai.cpp custom_evented/vertex_painter.cpp
OBJS = $(SRC:.cpp=.o)
%.o: %.c
	$(GXX) $(CFLAGS) -o $@ 

all: $(OBJS)
	ar rcs events.a $^
	cp events.a ../
clean:
	rm -f ./*.o
