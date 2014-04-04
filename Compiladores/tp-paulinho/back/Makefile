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
#$(EXEC): $(OBJECTS) $(HEADER)
	$(CC) $(OBJECTS)  -o  $(EXEC) 

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

run: $(EXEC)
	./$(EXEC) < expr1.t

test:
	for i in `(cd tests; ls *.t | sed -e 's/.t$$//')`;\
	  do echo $$i.t;\
	  ./frontend tests/$$i.t > tmp/$$i.i;\
	  diff tests/$$i.i tmp/$$i.i;\
	done
	cd -


clean:
	rm -f $(EXEC) $(OBJECTS)

