CC=g++
CFLAGS=-c -Wall -g -O2 -std=c++0x
LDFLAGS=
SOURCES=main.cpp GA.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ga.out

all: $(SOURCES) $(EXECUTABLE)
		
$(EXECUTABLE): $(OBJECTS) 
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
		$(CC) $(CFLAGS) $< -o $@

clean:
		@$(RM) *.o $(EXECUTABLE);

