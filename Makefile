PWD = $(shell pwd)
BIN = auC$(shell cat ./version)
all:
	g++ *.cpp -o ${BIN}
	ln -sf $(BIN) auC

check:
	g++ -Wall *.cpp -o ${BIN}
	ln -sf $(BIN) auC
