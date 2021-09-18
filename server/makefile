CXX=g++
CXXFLAGS=-std=c++14 -Wall -MMD
EXEC=server
SRC=server
OBJ=$(addsuffix .o,${SRC})
DEP=$(addsuffix .d,${SRC})

.PHONY: clean

${EXEC}: ${OBJ}
	${CXX} ${OBJ} -o ${EXEC}

-include ${DEP}

clean:
	-rm ${EXEC} ${OBJ} ${DEP}
