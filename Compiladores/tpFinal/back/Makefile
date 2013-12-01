build: clean backend

CC = g++
CC_FLAGS =  -W -Wall -pedantic -lm -std=c++0x -g3


#File names
EXEC = backend
SOURCES = $(wildcard *.cpp)
HEADER = $(wildcard *.h)

OBJECTS = $(SOURCES:.cpp=.o)

#Main target
$(EXEC): $(OBJECTS) $(HEADER)
	$(CC) $(OBJECTS)  -o  $(EXEC) 
	rm *.o 

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

test: $(EXEC)
	 @for i in `(cd tests_in; ls *.i | sed -e 's/.i$$//')`;\
	   do echo "-----------------------------";\
	   echo "tests_in/$$i.i > tests_out/$$i.jvm";\
	   ./backend tests_in/$$i.i > tests_out/$$i.jvm;\
	 done
	 @cd -

clean:
	rm -f $(EXEC) $(OBJECTS)

