server:server.o 
	gcc -o $@  $^ 

server.o:server.c server.h
	gcc -c   server.c server.h 
clean:
	rm -rf server.o sercer 
