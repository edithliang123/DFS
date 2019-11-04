#include "Graph.h"
#include "List.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef struct GraphObj {
	int order;
	int size;
	List* adj;
	int* color;
	int* parent;
	int* discover;
	int* finish;
} GraphObj;

// Graph
typedef GraphObj* Graph;

Graph newGraph(int n) {
	Graph M = malloc(sizeof(GraphObj));
	assert(M != NULL);
	M->order = n;
	M->size = 0;
	M->adj = malloc((n + 1) * sizeof(List));
	M->color = malloc((n + 1) * sizeof(int));
	M->parent = malloc((n + 1) * sizeof(int));
	M->discover = malloc((n + 1) * sizeof(int));
	M->finish = malloc((n + 1) * sizeof(int));
	for (int i = 1; i <= M->order; i++) {
		M->adj[i] = newList();
		M->color[i] = -1;
		M->parent[i] = NIL;
		M->discover[i] = UNDEF;
		M->finish[i] = UNDEF;
	}
	return M;
}

void freeGraph(Graph* pG) {
	if (pG != NULL && *pG != NULL) {
		if (getOrder(*pG) != 0) makeNull(*pG);
		for (int i = 1; i <= (*pG)->order; i++) {
			freeList(&((*pG)->adj[i]));
		}
		free((*pG)->adj);
		free((*pG)->parent);
		free((*pG)->color);
		free((*pG)->discover);
		free((*pG)->finish);
		free(*pG);
		*pG = NULL;
	}
}

int getOrder(Graph G) {
	return G->order;
}

int getSize(Graph G) {
	return G->size;
}

int getParent(Graph G, int u) {
	if (u >= 1 && u <= getOrder(G)) {
		return G->parent[u];
	}
	return NIL;
}

int getDiscover(Graph G, int u) {
	if (u >= 1 && u <= getOrder(G)) {
		return G->discover[u];
	}
	return UNDEF;
}

int getFinish(Graph G, int u) {
	if (u >= 1 && u <= getOrder(G)) {
		return G->finish[u];
	}
	return UNDEF;
}

void makeNull(Graph G) {
	for (int i = 1; i <= G->order; i++) {
		clear(G->adj[i]);
		G->color[i] = -1;
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}
	G->size = 0;
}

void addEdge(Graph G, int u, int v) {
	if (u >= 1 && u <= G->order && v >= 1 && v <= G->order) {
		int find = -1;
		if (length(G->adj[u]) != 0 && length(G->adj[v]) != 0) {
			moveFront(G->adj[u]);
			for (int i = 0; i < length(G->adj[u]); i++) {
				if (get(G->adj[u]) > v) {
					insertBefore(G->adj[u], v);
					find = 1;
					break;
				}
				moveNext(G->adj[u]);
			}
			if (find != 1) {
				append(G->adj[u], v);
			}
			find = -1;
			moveFront(G->adj[v]);
			for (int j = 0; j < length(G->adj[v]); j++) {
				if (get(G->adj[v]) > u) {
					insertBefore(G->adj[v], u);
					find = 1;
					break;
				}
				moveNext(G->adj[v]);
			}
			if (find != 1) {
				append(G->adj[v], u);
			}
		}
		else if (length(G->adj[u]) == 0 && length(G->adj[v]) == 0) {
			append(G->adj[u], v);
			append(G->adj[v], u);
		}
		else if (length(G->adj[u]) == 0) {
			append(G->adj[u], v);
			moveFront(G->adj[v]);
			for (int j = 0; j < length(G->adj[v]); j++) {
				if (get(G->adj[v]) > u) {
					insertBefore(G->adj[v], u);
					find = 1;
					break;
				}
				moveNext(G->adj[v]);
			}
			if (find != 1) {
				append(G->adj[v], u);
			}
		}
		else {
			append(G->adj[v], u);
			moveFront(G->adj[u]);
			for (int i = 0; i < length(G->adj[u]); i++) {
				if (get(G->adj[u]) > v) {
					insertBefore(G->adj[u], v);
					find = 1;
					break;
				}
				moveNext(G->adj[u]);
			}
			if (find != 1) {
				append(G->adj[u], v);
			}
		}
		G->size++;
	}
}

void addArc(Graph G, int u, int v) {
	if (u >= 1 && u <= G->order && v >= 1 && v <= G->order) {
		if (length(G->adj[u]) != 0) {
			int find = -1;
			moveFront(G->adj[u]);
			for (int i = 1; i <= length(G->adj[u]); i++) {
				if (get(G->adj[u]) > v) {
					insertBefore(G->adj[u], v);
					find = 1;
					break;
				}
				moveNext(G->adj[u]);
			}
			if (find == -1) {
				append(G->adj[u], v);
			}
		}
		else {
			append(G->adj[u], v);
		}
		G->size++;
	}
}

void visit(Graph A, int x, int *time, List record) {
	A->discover[x] = ++*time;
	A->color[x] = 0;
	moveFront(A->adj[x]);
	int y;
	for (int i = 1; i <= length(A->adj[x]); i++) {
		y = get(A->adj[x]);
		if (A->color[y] == -1) {
			A->parent[y] = x;
			visit(A, y, time, record);
		}
		moveNext(A->adj[x]);
	}
	A->color[x] = 1;
	A->finish[x] = ++ *time;
	append(record, x);

}

void DFS(Graph G, List S) {
	if (length(S) == getOrder(G)) {
		List P = newList();
		for (int s = 1; s <= G->order; s++) {
			G->color[s] = -1;
			G->parent[s] = NIL;
			G->discover[s] = UNDEF;
			G->finish[s] = UNDEF;
		}
		int order = length(S);
		int time = 0;
		moveFront(S);
		for (int i = 1; i <= order; i++) {
				if (G->color[get(S)] == -1) {
					visit(G, get(S), &time, P);
				}
			moveNext(S);
		}
		clear(S);
		moveFront(P);
		for (int z = 0; z < length(P); z++) {
			prepend(S, get(P));
			moveNext(P);
		}
		freeList(&P);
	}
}

Graph transpose(Graph G) {
	Graph B = newGraph(G->order);
	int temp;
	for (int i = 1; i <= G->order; i++) {
		if (length(G->adj[i]) != 0) {
			moveFront(G->adj[i]);
			for (int j = 1; j <= length(G->adj[i]); j++) {
				temp = get(G->adj[i]);
				addArc(B, temp, i);
				moveNext(G->adj[i]);
			}
		}
	}
	return B;
}

Graph copyGraph(Graph G) {
	Graph copy = newGraph(G->order);
	for (int i = 1; i <= G->order; i++) {
		copy->adj[i] = copyList(G->adj[i]);
		copy->color[i] = G->color[i];
		copy->parent[i] = G->parent[i];
		copy->discover[i] = G->discover[i];
		copy->finish[i] = G->finish[i];
	}
	copy->size = G->size;
	return copy;
}

void printGraph(FILE* out, Graph G) {
	for (int i = 1; i <= G->order; i++) {
		if (G->adj[i] != NULL && length(G->adj[i]) != 0) {
			fprintf(out, "%d: ", i);
			moveFront(G->adj[i]);
			for (int j = 1; j <= length(G->adj[i]); j++) {
				fprintf(out, "%d ", get(G->adj[i]));
				moveNext(G->adj[i]);
			}
		}
		else {
			fprintf(out, "%d: ", i);
		}
		fprintf(out, "\n");
	}
}