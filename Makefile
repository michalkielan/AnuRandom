CXX=g++
CPP_STD=c++11

CFLAGS= -std=$(CPP_STD) -Wall -g

TARGET=anurandom

LDFLAGS=-lboost_system -lpthread

SRC_PATH=src/
INC_PATH=inc/

INC=$(INC_PATH)
SRC=$(shell ls $(SRC_PATH)*.cpp)

all:
	$(CXX) $(CFLAGS) -I $(INC) $(SRC) -o $(TARGET) $(LDFLAGS)
clean:
	rm -rf $(TARGET) *.o
