CXX = g++
CXXFLAGS = -std=c++11

SRCS   := test_add.cpp test_sub.cpp test_mul.cpp \
		test_div.cpp test_other.cpp


OBJS   := ${SRCS:cpp=o}
PROGS  := ${SRCS:.cpp=}

.PHONY: all
all: ${PROGS}

${PROGS} : % : %.o Makefile
	${CXX} $< -o $@ ${LIBS}

clean:
	rm -f ${PROGS} ${OBJS}

%.o: %.cpp Makefile
	${CXX} ${CXXFLAGS} -c $<