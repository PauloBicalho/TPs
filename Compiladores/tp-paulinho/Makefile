CC = g++
CC_FLAGS =  -O0  -W -Wall -pedantic -lm -std=c++0x -g3


#File names
EXEC = pauloCompiler
SOURCES = $(wildcard *.cpp)

OBJECTS = $(SOURCES:.cpp=.o)

#Main target
$(EXEC): $(OBJECTS)
	cd front; make
	cd back; make
	$(CC) $(OBJECTS)  -o  $(EXEC) 
	rm *.o

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

run: $(EXEC)
	./$(EXEC) < expr1.t

test:
	@for i in `(cd tests_in; ls *.txt | sed -e 's/.txt$$//')`;\
	  do echo "-----------------------------";\
	  echo $$i.t;\
	  ./pauloCompiler tests_in/$$i.txt tests_out/$$i.i tests_out/$$i.jvm;\
	done
	cd -


clean:
	rm -f $(EXEC) $(OBJECTS)

