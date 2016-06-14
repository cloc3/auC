PWD = $(shell pwd)
BIN = auC$(shell cat ./version)
all:
	g++ -Wall *.cpp -o ${BIN}
	ln -sf $(BIN) auC
