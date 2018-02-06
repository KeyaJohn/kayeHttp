%.o:%.c
	gcc -c $<  -o $@ 
SRC=$(wildcard ./*.c ;)
OBJ=$(patsubst %.c,%.o,$(SRC))
BIN=./kayehttp

$(BIN):$(OBJ)
	gcc -o $@ $^ -lzlog -pthread -g
clean:
	rm -rf $(OBJ) $(BIN)
