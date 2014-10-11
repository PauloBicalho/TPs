CC=g++
CFLAGS=-c -Wall -O2
LDFLAGS=
SOURCES=main.cpp OptimizeSubGraph.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tp1.out

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
		$(CC) $(CFLAGS) $< -o $@

clean:
		@$(RM) *.o $(EXECUTABLE);
