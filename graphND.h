#include "edgeNPoints.h"
#include "debug.h"
#include <list>
#include<iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>
#include <math.h>



#ifndef GRAPHND_H
#define GRAPHND_H


class graphND{
    //This class creates a graph utilizing adjacency lists
    //It takes in number of vertices and assigns an x,y coordiante for 
    //Each vertex. THen defines the weight between each edge as the euclidean
    //Space between them
    //It is assumed the graph is fully connected and undirected.
public:
    graphND(const int n, const int dimensions, int debugMode);
    ~graphND();
    
    void addEdge(const float * fromVertex, const float * toVertex, int fromVertexLabel, int toVertexLabel);
    void addEdgeMemRed(const float * fromVertex, const float * toVertex, int fromVertexLabel, int toVertexLabel);
    void graphPrint();
    void setFilterConstant(int n, int d);
    int getVertices()
    {
        return vertices;
    }
    int getDimension()
    {
        return dimension;
    }
    float * getCoords(int index)
    {
        return vertexCoordinateArray[index];
    }
    std::list<edgeNPoints> getEdges(const int vertex)
    {
        debugger.debugPrint("getting edges\n");
        return adjacencyList[vertex];
    }
    
    
private:
    std::list<edgeNPoints> * adjacencyList;
    float ** vertexCoordinateArray;
    int vertices;
    int dimension;
    float preFilterConstant;
    debug debugger;
    
    const int PRE_FILTER_APPLICATION_THRESH = 1000;
    const float D3_EXP_SLOPE = .2011;
    const float D3_EXP = -5*pow(10,-6);
    const float D4_EXP_SLOPE = .2811;
    const float D4_EXP = -4*pow(10,-6);
    const float D2_EXP_SLOPE = .155;
    const float D2_EXP = -1*pow(10,-5);
};









#endif
