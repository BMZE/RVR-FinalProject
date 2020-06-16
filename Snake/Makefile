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

all: $(BIN)/$(EXECUTABLE) $(BIN)/$(SERVER_EXE) $(BIN)/$(CLIENT_EXE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)
	./$(BIN)/$(SERVER_EXE)
	./$(BIN)/$(CLIENT_EXE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp $(SERVER)/*.cpp  
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

$(BIN)/$(SERVER_EXE): ServerMain.cpp $(SERVER)/*.cpp 
	$(CXX) $(CXX_FLAGS) -I$(SERVER) -L$(LIB)  $^ -o $@ $(LIBRARIES)

$(BIN)/$(CLIENT_EXE): main.cpp $(SERVER)/*.cpp  
	$(CXX) $(CXX_FLAGS) -I$(SERVER) -L$(LIB)  $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*