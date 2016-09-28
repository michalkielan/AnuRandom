CPP_STD=c++11

CFLAGS= -std=$(CPP_STD) -Wall -g

TARGET=anurandom

LDFLAGS=-lboost_system -lpthread

SRC=$(shell ls *.cpp)

all:
	$(CXX) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAFS)
clean:
	rm -rf $(TARGET) *.o
