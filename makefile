main:
	gcc -o build/sft-cli $(shell ls src/*.c) -lpthread

run: main
	./build/sft-cli

clean:
	rm ./build/*
	rm test-cli

test:
	gcc -o test-cli test-cli.c
