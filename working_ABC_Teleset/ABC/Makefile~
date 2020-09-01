INCLUDEDIR	=-I /usr/include/libxml2 
CFLAGS          = -Wall -g ${INCLUDEDIR} -I.
#LIBS= -lxml2 -lm -pthread
#LIBXML=-L/usr/include/libxml2 
#LIBS0=${LIBS} ${LIBXML} 

abc: abc.o socket.o 
	gcc $(CFLAGS) -o abc abc.o socket.o 
 
abc.o: abc.c socket.o
	gcc $(CFLAGS)  -c abc.c 

socket.o: socket.c server.h
	gcc $(CFLAGS) -c socket.c               
clean: 
	rm -f  *.o abc     
