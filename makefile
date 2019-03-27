all: ejemplo1.c ejemplo2.c ejemplo3.c
	gcc -o ejemplo1 ejemplo1.c
	gcc -o ejemplo2 ejemplo2.c
	gcc -o ejemplo3 ejemplo3.c
1: ejemplo1.c
	gcc -o ejemplo1 ejemplo1.c
2: ejemplo2.c
	gcc -o ejemplo2 ejemplo2.c
3: ejemplo3.c
	gcc -o ejemplo3 ejemplo3.c
4:
	rm ejemplo1
	rm ejemplo2
	rm ejemplo3