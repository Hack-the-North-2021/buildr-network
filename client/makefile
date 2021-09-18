CXX=g++
CXXFLAGS=-std=c++17 -Wall -MMD
LIBS=-lpthread
EXEC=client
SRC=main NetworkClient Logger
OBJ=$(addsuffix .o,${SRC})
DEP=$(addsuffix .d,${SRC})

.PHONY: clean

${EXEC}: ${OBJ}
	${CXX} ${OBJ} -o ${EXEC} ${LIBS}

-include ${DEP}

clean:
	-rm ${EXEC} ${OBJ} ${DEP}
