CONTAINER = map
NS = ft

COMMAND = one
CXXFLAGS = -Wall -Wextra -Werror -g3 -std=c++0x -lgtest -lgtest_main -pthread -I.

all :
	c++ $(CXXFLAGS) ./tester/vector.cpp
	./a.out

test :
	cd ./containers_test && ./do.sh