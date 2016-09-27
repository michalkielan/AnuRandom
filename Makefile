all:
	g++-5 -std=c++11 AnuRandom.cpp main.cpp -o anurandom -lboost_system -lpthread
clean:
	rm -rf anurandom
