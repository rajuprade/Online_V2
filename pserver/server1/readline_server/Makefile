CFLAGS          = -Wall -g 
LIBS= -lreadline

server: readline_server.o
	gcc $(CFLAGS) -o server readline_server.o $(LIBS)


readline_server.o: readline_server.c readline_server.h
	gcc $(CFLAGS) -c readline_server.c 
clean: 
	rm -f  *.o readline_server      
