

# SRC_FILES = ./src/server.c ./src/client.c

build: 
	gcc ./src/server.c -o ./bin/server
	gcc ./src/client.c -o ./bin/client