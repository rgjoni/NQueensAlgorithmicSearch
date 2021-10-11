CC = g++
CFLAGS = -O3
EXEC = Board
	
all:
	rm -f $(EXEC)
	$(CC) $(CFLAGS) -o $(EXEC) main.cpp Board.cpp 
	./$(EXEC) 20 20
	