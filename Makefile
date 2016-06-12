PWD = $(shell pwd)
XX = $(shell basename $(PWD))
all:
	g++ *.cpp -o ${XX}
