main:main.o server.o  
	gcc -o $@ $^ -g -pthread

main.o:main.c
	gcc -c main.c
server.o:server.c 
	gcc -c server.c  
clean:
	rm -rf server.o server main main.o 
