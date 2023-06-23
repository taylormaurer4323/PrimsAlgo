#include "graphND.h"
#include "graph.h"
#include "edgeNPoints.h"
#include "edge.h"
#include <bits/stdc++.h>
#include "myHeap.h"
#include <iostream>
#ifndef MST_H
#define MST_H

class MST{
public:
    MST(int debugMode);
    float primND(graphND & myGraph, int startVertex);
    float prim(graph & myGraph, int startVertex);
    void printPrev(int * prevArr, int vertexCount);
    float sumEdges(float * distArr);
    
    
private:
    debug debugger;
    int dimension;
    int vertices;
    const int PERFORM_MST_CONST = 2;
    
    
};




#endif
