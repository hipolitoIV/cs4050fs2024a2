// CS4050/7050 FS 20204 A2 main()

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cs4050.h"
#include "MST.h"

int main(void)
{
    /******************************************************/
    /* Set things up by loading the graph and printing it */
    int countVertices, countEdges;

    //SetDirected(1);
	IsDirected();
    GetCounts(&countVertices,&countEdges);

    Vertex vertices[countVertices];
    Edge edges[countEdges];
    memset(vertices,0,sizeof(vertices));
    memset(edges,0,sizeof(edges));

    GetEdges(edges,countEdges);
    BuildAdjacency(vertices,edges,countVertices,countEdges);
    PrintVertices(vertices,countVertices);
    /******************************************************/

	// Now, run MST
	MST_Kruskal(vertices,countVertices,edges,countEdges);

    // Cleanup memory
    CleanUp(vertices,countVertices);
}
