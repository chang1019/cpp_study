CXXFLAGS:= -g -O0 -pthread

SRCS:= $(wildcard ../src/*.cpp)
TEST_SRCS:= $(wildcard *.cpp)

# GOOGLE TEST SETTING
GTEST:= ../../external/gtest-1.7.0
GTEST_SRC += $(GTEST)/fused-src/gtest/gtest-all.cc \
	     $(GTEST)/fused-src/gtest/gtest_main.cc

OBJS:= $(SRCS:.cpp=.o)
OBJS += $(TEST_SRCS:.cpp=.o)

LIBS:= 	../../util/src/libutil.a

CXXFLAGS += -I$(GTEST)/fused-src \
	    -I../src \
	    -I../../util/include

.PHONY: all
all: tester

.PHONY: test
test: tester
	./tester

.PHONY: valgrind
valgrind: tester
	valgrind ./tester --leak-check=full

.PHONY: clean
clean:
	rm *.o tester

tester : $(OBJS) $(LIBS)
	$(CXX) $(CXXFLAGS) -o tester $(OBJS) $(GTEST_SRC) $(LIBS)

$(LIBS):
	cd ../../util/src;make
