CC = g++

CFLAGS = -Wall -g3 -lm

RM = rm -f

OBJS = servidor.o BealServer.o
#OBJS = main.o Constraints.o

MAIN = server

$(MAIN): $(OBJS)
	@echo ""
	@echo " --- COMPILANDO O PROGRAMA	---"
	$(CC) $(CFLAGS) $(OBJS) -o $(MAIN)
	@$(RM) *.o
	@echo ""
				

%.o: %.cpp %.hpp
	@echo " --- COMPILANDO OBJETO \"$@\""
	$(CC) $(CFLAGS) $< -c 

clean:
	$(RM) $(MAIN) *.o

run: $(MAIN)
	./$(MAIN) entrada_exemplo.txt


