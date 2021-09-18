CXX=g++
CXXFLAGS=-std=c++14 -Wall -MMD
LIBS=-lpthread
EXEC=server
SRC=main NetworkServer
OBJ=$(addsuffix .o,${SRC})
DEP=$(addsuffix .d,${SRC})

.PHONY: clean

${EXEC}: ${OBJ}
	${CXX} ${OBJ} -o ${EXEC} ${LIBS}

-include ${DEP}

clean:
	-rm ${EXEC} ${OBJ} ${DEP}
