build:
	g++ -g bst.h bst.cpp main.cpp -o bst

clean:
	rm *.gch

debug:
	gdb ./bst

run: 
	./bst

rundb:
	make build && make run
