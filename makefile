objects =  server.o parser.o ratabaseManager.o ratabase.o \
			value.o hash.o list.o

flags = -Wall -O -std=c++11

all: client server

client: client.cpp
	g++ $(flags) -o client client.cpp 

server: $(objects)
	g++ $(flags) -o server $(objects)

server.o: server.cpp
	g++ $(flags) -c server.cpp

parser.o: parser.cpp
	g++ $(flags) -c parser.cpp

ratabaseManager.o: ratabaseManager.cpp
	g++ $(flags) -c ratabaseManager.cpp

ratabase.o: ratabase.cpp
	g++ $(flags) -c ratabase.cpp

hash.o: hash.cpp
	g++ $(flags) -c hash.cpp

value.o: value.cpp
	g++ $(flags) -c value.cpp

list.o: list.cpp
	g++ $(flags) -c list.cpp 

.PHONY: clean

clean:
	rm -f server client $(objects)
