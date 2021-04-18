CFLAGS:= -c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:= -lboost_system

all: StompBookClubClient
	g++ -pthread -o bin/StompBookClubClient  bin/InputTask.o bin/StompBookClubClient.o bin/connectionHandler.o bin/Book.o bin/InputToStomp.o bin/Message.o bin/ServerTask.o bin/StompFrame.o bin/User.o $(LDFLAGS)

StompBookClubClient: bin/connectionHandler.o bin/Book.o bin/InputToStomp.o bin/Message.o bin/InputTask.o bin/ServerTask.o bin/StompFrame.o bin/User.o bin/StompBookClubClient.o
	
bin/connectionHandler.o: src/connectionHandler.cpp
	g++ -pthread $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp

bin/Book.o: src/Book.cpp
	g++ -pthread $(CFLAGS) -o bin/Book.o src/Book.cpp

bin/StompFrame.o: src/StompFrame.cpp
	g++ -pthread $(CFLAGS) -o bin/StompFrame.o src/StompFrame.cpp

bin/InputTask.o: src/InputTask.cpp
	g++ -pthread $(CFLAGS) -o bin/InputTask.o src/InputTask.cpp

bin/InputToStomp.o: src/InputToStomp.cpp
	g++ -pthread $(CFLAGS) -o bin/InputToStomp.o src/InputToStomp.cpp

bin/Message.o: src/Message.cpp
	g++ -pthread $(CFLAGS) -o bin/Message.o src/Message.cpp

bin/ServerTask.o: src/ServerTask.cpp
	g++ -pthread $(CFLAGS) -o bin/ServerTask.o src/ServerTask.cpp

bin/User.o: src/User.cpp
	g++ -pthread $(CFLAGS) -o bin/User.o src/User.cpp

bin/StompBookClubClient.o: src/StompBookClubClient.cpp
	g++ -pthread $(CFLAGS) -o bin/StompBookClubClient.o src/StompBookClubClient.cpp

.PHONY: clean
clean:
	rm -f bin/*
