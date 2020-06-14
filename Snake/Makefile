CXX		  := g++
CXX_FLAGS := -Wall -Wno-unknown-pragmas -Wextra -std=c++17 -ggdb 

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
SERVER 	:= server

LIBRARIES	:= -lSDL2 -lSDL2main 
EXECUTABLE	:= snake
SERVER_EXE	:= server

all: $(BIN)/$(EXECUTABLE) $(BIN)/$(SERVER_EXE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)
	./$(BIN)/$(SERVER_EXE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

$(BIN)/$(SERVER_EXE): $(SERVER)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(SERVER) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*