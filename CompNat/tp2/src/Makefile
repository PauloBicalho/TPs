CC = g++

CFLAGS = -Wall -g3 -lm

RM = rm -f

OBJS = main.o ACO.o Constraints.o Schedule.o
#OBJS = main.o Constraints.o

MAIN = ACO_JSS

$(MAIN): $(OBJS)
	@echo ""
	@echo " --- COMPILANDO O PROGRAMA  ---"
	$(CC) $(CFLAGS) $(OBJS) -o $(MAIN)
	@echo ""

%.o: %.cpp %.h
	@echo " --- COMPILANDO OBJETO \"$@\""
	$(CC) $(CFLAGS) $< -c 

clean:
	$(RM) $(MAINFB) $(MAINPD) *.o

run: $(MAIN)
	./$(MAIN) entrada_exemplo.txt


