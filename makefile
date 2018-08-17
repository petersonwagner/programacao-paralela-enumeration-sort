all: enumeration

enumeration: enumeration.c
	gcc -Wall -pg -fopenmp -O3 enumeration.c -o enumeration

clean:
	rm -f enumeration