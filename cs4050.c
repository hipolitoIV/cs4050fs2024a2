#include <stdio.h>
#include <stdlib.h>
#include "cs4050.h"

int m_fDirected; 
// Function to check if the graph is directed
int IsDirected(void) {
    char buffer[256];
    printf("Enter 1 for directed or 0 for undirected: ");
    fgets(buffer, sizeof(buffer), stdin);
    int i = atoi(buffer);
    if (i != 0){
        m_fDirected = 1;
        return 1;
    }
    m_fDirected = 0;
    return 0;
}

// Function to set directed status
void SetDirected(int fIsDirected) {
    m_fDirected = fIsDirected != 0;
}

// Function to get counts of vertices and edges
void GetCounts(int *pCountVertices, int *pCountEdges) {
    char buffer[256];

    printf("Enter the number of vertices: ");
    fgets(buffer, sizeof(buffer), stdin);
    *pCountVertices = atoi(buffer); // Populate pCountVertices after fgets

    printf("Enter the number of edges: ");
    fgets(buffer, sizeof(buffer), stdin);
    *pCountEdges = atoi(buffer); // Populate pCountEdges after fgets
}

// Function to get an edge input
void GetEdge(Edge *pEdge) {
    scanf("%d %d %f", &pEdge->from, &pEdge->to, &pEdge->weight);
}

// Function to get multiple edges
void GetEdges(Edge edges[], int countEdges) {
    for (int i = 0; i < countEdges; ++i) {
        GetEdge(&edges[i]);
    }
}

// Function to print a vertex
void PrintVertex(Vertex vertex) {
    PAdjacency p;
    printf("\nVertex %d:\n", vertex.number);
    for (p = vertex.list; p; p = p->next) {
        if (vertex.number == p->pEdge->from) {
            printf("\t%d->%d (%.2f)\n", p->pEdge->from, p->pEdge->to, p->pEdge->weight);
        } else {
            printf("\t%d->%d (%.2f)\n", p->pEdge->to, p->pEdge->from, p->pEdge->weight);
        }
    }
}

// Function to print all vertices
void PrintVertices(Vertex vertices[], int count) {
    for (int i = 0; i < count; ++i) {
        PrintVertex(vertices[i]);
    }
}

// Function to add an adjacent edge
void AddAdjacentEdge(Vertex *pVertex, Edge *pEdge) {
    PAdjacency prev;
    PAdjacency cur;

    PAdjacency p_Var1 = (PAdjacency)malloc(0x10);
    p_Var1->pEdge = pEdge;
    p_Var1->next = (Adjacency *)0x0;
    if (pVertex->list == (PAdjacency)0x0) {
        pVertex->list = p_Var1;
    }
    else {
        prev = pVertex->list;
        for (cur = pVertex->list->next; cur != (PAdjacency)0x0; cur = cur->next) {
            prev = cur;
        }
        prev->next = p_Var1;
    }
}

void BuildAdjacency(Vertex *vertices,Edge *edges,int countVertices,int countEdges){
    for (int i = 0; i < countVertices; i++)
    {
        vertices[i].number = i + 1;
    }
    for (int j = 0; j < countEdges; j++)
    {
        AddAdjacentEdge(vertices + (long)edges[j].from - 1,edges + j);
        if (m_fDirected == 0){
            AddAdjacentEdge(vertices + (long)edges[j].to - 1,edges + j);
        }
    }
}

// Function to clean up memory
void CleanUp(Vertex vertices[], int countVertices) {
    PAdjacency cur, prev;
    for (int i = 0; i < countVertices; ++i) {
        cur = vertices[i].list;
        while (cur) {
            prev = cur;
            cur = cur->next;
            free(prev);
        }
        vertices[i].list = NULL;  // Clear the list after freeing
    }
}
