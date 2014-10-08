CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=
SOURCES=main.cpp Graph.cpp Io.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tp2.out

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
		$(CC) $(CFLAGS) $< -o $@

clean:
		@$(RM) *.o $(EXECUTABLE);

