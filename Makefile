PWD = $(shell pwd)
BIN = auC$(shell cat ./version)
all:
	g++ *.cpp -o ${BIN}
	ln -sf $(BIN) auC
