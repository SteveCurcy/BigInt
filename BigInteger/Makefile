# VPATH = 

CC		= g++
SRC 	= BigInteger.cpp main.cpp
OBJECTS = $(SRC:.cpp=.o)
TARGET  = main

INCLUDE_DIR = -I.

CFLAGS		= -Wall -Wno-unused-but-set-variable $(INCLUDE_DIR) -g
# COMPILE_DIR	= `pkg-config --cflags gtk+-3.0`
# BUILD_DIR	= `pkg-config --libs gtk+-3.0`


$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(CFLAGS)

-include $(SRC:.cpp=.d)

%.d : %.cpp
	@set -e;rm -f $@;$(CC) -MM $(CFLAGS) $< > $@.$$$$;\
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;\
	rm -f $@.*

.PHONY : clean

clean:
	-rm -f *.o *.d* $(TARGET)
