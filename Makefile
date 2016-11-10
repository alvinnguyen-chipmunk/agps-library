LIB_DIR=./image/usr/lib
BIN_DIR=./image/usr/bin
FLAGS=-Wall -g -L${LIB_DIR}

all:
	#${CC} -std=c99 ${CFLAGS} ${FLAGS} -lstyl-agps main.c -o ${BIN_DIR}/demo-agps
	${CXX} -std=c++11 ${CXXFLAGS} ${FLAGS} -lstyl-agps main.cpp -o ${BIN_DIR}/demo-agps-cpp

lib:
	${CC} ${CFLAGS} ${FLAGS} -c -fpic styl-agps.c
	${CC} ${CFLAGS} ${FLAGS} -shared -ljson-c -lcurl -o ${LIB_DIR}/libstyl-agps.so styl-agps.o
	rm styl-agps.o

clean:
	rm ${BIN_DIR}/demo-agps ${BIN_DIR}/demo-agps-cpp ${LIB_DIR}/libstyl-agps.so
