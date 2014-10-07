CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp OptimizeSubGraph.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tp1

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
		$(CC) $(CFLAGS) $< -o $@
