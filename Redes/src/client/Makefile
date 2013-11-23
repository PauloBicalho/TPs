CC = g++

CFLAGS = -Wall -g3 -lm -I ./boost -std=c++0x
#CFLAGS = -Wall -g3 -lm

RM = rm -f

OBJS = BealClient.o main.o
#OBJS = main.o Constraints.o

MAIN = client

$(MAIN): $(OBJS)
	@echo ""
	@echo " --- COMPILANDO O PROGRAMA	---"
	echo $(CC) $(CFLAGS) $(OBJS) -o $(MAIN)
	$(CC) $(CFLAGS) $(OBJS) -o $(MAIN)
	@$(RM) *.o
	@echo ""
				

%.o: %.cpp %.hpp
	@echo " --- COMPILANDO OBJETO \"$@\""
	echo $(CC) $(CFLAGS) $< -c 
	$(CC) $(CFLAGS) $< -c 

%.o: %.cpp
	@echo " --- COMPILANDO OBJETO \"$@\""
	echo $(CC) $(CFLAGS) $< -c 
	$(CC) $(CFLAGS) $< -c 

clean:
	$(RM) $(MAIN) *.o

run: $(MAIN)
	./$(MAIN) entrada_exemplo.txt


