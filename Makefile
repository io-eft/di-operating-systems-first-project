CC=g++
CFLAGS=-c -g -Wall
LDFLAGS=
SOURCES=main.cpp myfunctions.cpp mytree.cpp mystructure.cpp myclass.cpp myhash.cpp mylist.cpp mytaxpayer.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=mypriority

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
