build: clean frontend

CC = g++
CC_FLAGS =  -O0  -W -Wall -pedantic -lm -std=c++0x -I ./ -I inter/ -I lexer/ -I parser/ -I symbols/


#File names
EXEC = frontend
SOURCES = $(wildcard **/*.cpp) $(wildcard *.cpp) $(wildcard **/**/*.cpp)
HEADER = $(wildcard **/*.h) $(wildcard *.h) $(wildcard **/**/*.h)

OBJECTS = $(SOURCES:.cpp=.o)

#Main target
$(EXEC): $(OBJECTS) $(HEADER)
	$(CC) $(OBJECTS)  -o  $(EXEC) 
	rm *.o 

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

run: $(EXEC)
	./$(EXEC) < expr1.t


test: $(EXEC)
	@for i in `(cd tests_in; ls *.txt | sed -e 's/.txt$$//')`;\
	  do echo "-----------------------------";\
	  echo "tests_in/$$i.txt > tests_out/$$i.i";\
	  ./frontend tests_in/$$i.txt > tests_out/$$i.i;\
	done
	@cd -

clean:
	rm -f $(EXEC) $(OBJECTS)

