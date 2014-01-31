CXXFLAGS:= -g -O0 -pthread

SRCS:= $(wildcard *.cpp)
OBJS:= $(SRCS:.cpp=.o)

.PHONY: all
all: tester

.PHONY: test
test: tester
	./tester

.PHONY: clean
clean:
	rm *.o tester

tester : $(OBJS)
	$(CXX) $(CXXFLAGS) -o tester $(OBJS)
