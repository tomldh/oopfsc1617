CC = g++
INC=-I"./"

.PHONY: build
build: bin/s1

.PHONY: clean
clean:
	rm ./s1
	
.PHONY: rebuild
rebuild: clean build

bin/s1: *.cc
	$(CC) -o $@ $^ $(INC)
