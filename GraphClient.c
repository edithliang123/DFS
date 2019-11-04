/************************************
 * Yixin Liang, yliang43
 * 2019 Summer CMPS101 PA3
 * GraphTest.c
 * Test Graph ADT
 ***********************************/
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main() {
	int n = 8;
	Graph A = newGraph(n);
	Graph B;
	List path = newList();

	//check source and number of vertices in the beginning
	printf("%d \n", getOrder(A));


	//add edges for undirected graph
	addEdge(A, 1, 3); addEdge(A, 1, 4); addEdge(A, 2, 3); addEdge(A, 2, 6);
	addEdge(A, 2, 7); addEdge(A, 3, 6); addEdge(A, 4, 8); addEdge(A, 5, 8);
	addEdge(A, 6, 7); addEdge(A, 6, 8); addEdge(A, 7, 8);

	//test printGraph
	printGraph(stdout, A);

	//check size after addEdge
	printf("size = %d\n", getSize(A));

	//test DFS
	for (int z = 1; z <= n; z++) {
		append(path, z);
	}
	DFS(A, path);
	for (int i = 1; i <= n; i++) {
		printf("%d ", getDiscover(A, i));	//check distance correctness
	}
	printf("\n");
	for (int j = 1; j <= n; j++) {
		printf("%d ", getFinish(A, j));	//check parent correctness
	}
	printf("\n");
	for (int d = 1; d <= n; d++) {
		printf("%d ", getParent(A, d));	//check parent correctness
	}

	printf("\n");
	printList(stdout, path);

	B = transpose(A);
	printf("\n");
	printGraph(stdout, B);

	DFS(B, path);
	printf("\n");
	printList(stdout, path);
	printf("\n");
	clear(path);
	
	//test makeNULL
	makeNull(A);
	if (getSize(A) != 0) {
		printf("Graph A is not empty");
	}
	makeNull(B);
	if (getSize(B) != 0) {
		printf("Graph B is not empty");
	}

	//test addArc
	addArc(A, 1, 3); addArc(A, 1, 4); addArc(A, 1, 5); addArc(A, 2, 6);
	addArc(A, 4, 6); addArc(A, 4, 7); addArc(A, 6, 3); addArc(A, 7, 8);

	printGraph(stdout, A);

	printf("size = %d\n", getSize(A));

	//test DFS
	for (int z = 1; z <= n; z++) {
		append(path, z);
	}
	DFS(A, path);
	for (int i = 1; i <= n; i++) {
		printf("%d ", getDiscover(A, i));	//check distance correctness
	}
	printf("\n");
	for (int j = 1; j <= n; j++) {
		printf("%d ", getFinish(A, j));	//check parent correctness
	}
	printf("\n");
	for (int d = 1; d <= n; d++) {
		printf("%d ", getParent(A, d));	//check parent correctness
	}

	printf("\n");
	printList(stdout, path);

	Graph C = transpose(A);
	printf("\n");
	printGraph(stdout, C);

	DFS(C, path);
	printf("\n");
	printList(stdout, path);
	clear(path);

	freeGraph(&C);
	freeGraph(&B);
	freeGraph(&A);
	freeList(&path);


	return 0;
}
