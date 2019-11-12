/************************************
 * Yixin Liang, yliang43
 * 2019 Summer CMPS101 PA4
 * FindComponents.c
 * Create undirected graph or directed graph based on inputs and find strong
 * components of the graph
 ***********************************/
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]) {
	FILE* in;
	FILE* out;
	List path = newList();
	List order = newList();
	Graph A;
	Graph B;
	int n, x, y;
	int count = 0;
	int count2 = 1;

	// check command line for correct number of arguments 
	if (argc != 3) {
		printf("Usage: %s input-file output-file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// open input file for reading 
	if ((in = fopen(argv[1], "r")) == NULL) {
		printf("Unable to read from file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	// open output file for writing 
	if ((out = fopen(argv[2], "w")) == NULL) {
		printf("Unable to write to file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	fscanf(in, "%d", &n);
	A = newGraph(n);

	if (!feof(in)) {
		fscanf(in, "%d %d", &x, &y);
		while (x != 0 && y != 0) {
			addArc(A, x, y);
			fscanf(in, "%d %d", &x, &y);
		}
	}

	for (int i = 1; i <= n; i++) {
		append(path, i);
	}
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, A);
	fprintf(out, "\n");
	DFS(A, path);

	B = transpose(A);

	DFS(B, path);

	moveBack(path);
	for (int p = 1; p <= length(path); p++) {
		if (getParent(B, get(path)) == NIL) {
			count++;
		}
		movePrev(path);
	}

	fprintf(out, "G contains %d strongly connected components:\n", count);

	moveBack(path);
	for (int j = 1; j <= length(path); j++) {
		if (getParent(B, get(path)) != NIL) {
			prepend(order, get(path));
		}
		else {
			fprintf(out, "Component %d: ", count2);
			fprintf(out, "%d ", get(path));
			printList(out, order);
			clear(order);
			fprintf(out, "\n");
			count2++;
		}
		movePrev(path);
	}

	freeGraph(&A);
	freeGraph(&B);
	freeList(&order);
	freeList(&path);

	fclose(in);
	fclose(out);

	return 0;
}
