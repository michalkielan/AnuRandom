all:
	g++ -std=c++11 AnuRandom.cpp main.cpp -o anurandom -libboost_system -lpthreads
clean:
	rm -rf anurandom
