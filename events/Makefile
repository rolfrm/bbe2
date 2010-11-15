GXX=g++
CPPFLAGS=-c -Wall -I/usr/include/opencv/
SRC=event_core.cpp evented.cpp events.cpp 
OBJS = $(SRC:.cpp=.o)
%.o: %.c
	$(GXX) $(CFLAGS) -o $@ 

all: $(OBJS)
	ar rcs events.a $^
	cp events.a ../
clean:
	rm -f ./*.o custom_evented/*.o
