.PHONY : all
all : client server

client : client.c
	gcc client.c -o client

server : server.c
	gcc server.c -o server

.PHONY : clean
clean:
	rm server client mypipe
