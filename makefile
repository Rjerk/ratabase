objects =  parser.o ratabaseManager.o ratabase.o \
			value.o hash.o list.o

flags = -Wall -O -std=c++11

all: client server

client: client.cpp
	g++ $(flags) -o client client.cpp 

server: $(objects) server.cpp
	g++ $(flags) -o server server.cpp $(objects)

parser.o: parser.cpp
	g++ $(flags) -c parser.cpp

ratabaseManager.o: ratabaseManager.cpp ratabaseManager.h \
				ratabase.cpp cmd.h
	g++ $(flags) -c ratabaseManager.cpp ratabase.cpp

ratabase.o: ratabase.cpp list.cpp hash.cpp
	g++ $(flags) -c ratabase.cpp list.cpp hash.cpp

hash.o: hash.cpp value.cpp
	g++ $(flags) -c hash.cpp value.cpp

value.o: value.cpp list.cpp hash.cpp
	g++ $(flags) -c list.cpp hash.cpp value.cpp

list.o: list.cpp list.h
	g++ $(flags) -c list.cpp 

.PHONY: clean

clean:
	rm -f server client $(objects)
