objects =  run_server.o Server.o Parser.o RatabaseManager.o Ratabase.o \
			Value.o Hash.o List.o Logger.o Sockets.o

flags = -Wall -O -std=c++11

all: client server

client: client.cpp Logger.cpp Sockets.cpp
	g++ $(flags) -o client client.cpp  Logger.cpp Sockets.cpp

server: $(objects)
	g++ $(flags) -o server $(objects)

run_server.o: run_server.cpp
	g++ $(flags) -c run_server.cpp

Server.o: Server.cpp
	g++ $(flags) -c Server.cpp

Parser.o: Parser.cpp
	g++ $(flags) -c Parser.cpp

RatabaseManager.o: RatabaseManager.cpp
	g++ $(flags) -c RatabaseManager.cpp

Ratabase.o: Ratabase.cpp
	g++ $(flags) -c Ratabase.cpp

Hash.o: Hash.cpp
	g++ $(flags) -c Hash.cpp

Value.o: Value.cpp
	g++ $(flags) -c Value.cpp

List.o: List.cpp
	g++ $(flags) -c List.cpp

Logger.o: Logger.cpp
	g++ $(flags) -c Logger.cpp

Sockets.o: Sockets.cpp
	g++ $(flags) -c Sockets.cpp

.PHONY: clean

clean:
	rm -f server client $(objects)
