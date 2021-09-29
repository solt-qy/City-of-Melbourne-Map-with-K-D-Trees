all: map1 map2

map1: tree.o main.o data.o distance_search.o output.o
	gcc -Wall -o map1 tree.o main.o data.o distance_search.o output.o -g -lm

map2: tree.o main1.o data.o distance_search.o output.o
	gcc -Wall -o map2 tree.o main1.o data.o distance_search.o output.o -g -lm

main.o: main.c
	gcc -c -Wall main.c -g

main1.o: main1.c
	gcc -c -Wall main1.c -g

data.o: data.c data.h
	gcc -c -Wall data.c -g

tree.o: tree.c tree.h
	gcc -c -Wall tree.c -g

distance_search.o: distance_search.c distance_search.h
	gcc -c -Wall distance_search.c -g

output.o: output.c output.h
	gcc -c -Wall output.c -g
