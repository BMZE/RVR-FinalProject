CXX		  := g++
CXX_FLAGS := -Wall -Wno-unknown-pragmas -Wextra -std=c++17 -ggdb 

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
SERVER 	:= server
CLIENT 	:= client

LIBRARIES	:= -lSDL2 -lSDL2main -lpthread
EXECUTABLE	:= snake
SERVER_EXE	:= server
CLIENT_EXE 	:= client
SERVER_GAME := ServerGame/src
INCLUDE_CLIENT := client/include
INClUDE_SERVER := ServerGame/include
CLIENT_GAME 	:= client
COMMON 		:= Common

all: $(BIN)/$(EXECUTABLE) $(BIN)/$(SERVER_EXE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)
	./$(BIN)/$(SERVER_EXE)

$(BIN)/$(EXECUTABLE): $(CLIENT_GAME)/src/*.cpp $(SERVER)/*.cpp  
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE_CLIENT) -I$(COMMON) -L$(LIB) $^ -o $@ $(LIBRARIES)

$(BIN)/$(SERVER_EXE): ServerMain.cpp $(SERVER_GAME)/*.cpp $(SERVER)/*.cpp 
	$(CXX) $(CXX_FLAGS) -I$(SERVER) -I$(COMMON) -I$(INClUDE_SERVER) -L$(LIB)  $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*