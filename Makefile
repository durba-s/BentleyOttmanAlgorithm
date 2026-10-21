CC = g++

SRC=src
LIB=lib

FLAGS = -Wall -g -std=c++17

SRCFILES := $(wildcard *.cpp)
TARGETS := $(SRCFILES:.cpp=.o)

SRCFILES := $(notdir $(basename $(wildcard $(SRC)/*.cpp)))
TARGETS :=$(patsubst %,$(LIB)/%.o,$(SRCFILES))

build: clean $(LIB) all

all: $(TARGETS)
	$(CC) -o ./a $+ $(FLAGS)

$(LIB)/%.o: $(SRC)/%.cpp
	$(CC) -c $^ -o $@ $(FLAGS)

clean:
	rm -rf $(LIB)
	mkdir $(LIB)
