CXXFLAGS:= -g -O0

CXXFLAGS += -I../include

SRCS:= $(wildcard *.cpp)
OBJS:= $(SRCS:.cpp=.o)

.PHONY: all
all: libutil.a

.PHONY: clean
clean:
	rm *.o libutil.a

libutil.a: $(OBJS)
	ar crsv $@ $<
