#include "MST.h"

MST::MST(int debugMode) {
    debugger.setDebugMode(debugMode);
}

float MST::primND(graphND & myGraph, int startVertex) {
    
    //set variables of MST:
    dimension = myGraph.getDimension();
    vertices = myGraph.getVertices();
    if(vertices <= PERFORM_MST_CONST)
    {
        std::list<edgeNPoints> tempEdgeList;
        tempEdgeList = myGraph.getEdges(startVertex);
        edgeNPoints tempEdge;
        tempEdge = tempEdgeList.back();
        return tempEdge.getWeight();
    }
    float * dimsArr;
    std::list<edgeNPoints> ::iterator it;
    float dist[vertices];
    int prev[vertices];
    int heapIndices[vertices];
    int S[vertices];

    //initialize all applicable arrays:
    for (int i = 0; i < vertices; i++) {
        prev[i] = -1;
        dist[i] = INT_MAX;
        heapIndices[i] = -1;
        S[i] = 0;
    }
    //initialize for startVertex:
    dist[startVertex] = 0;
    myHeap H(vertices, heapIndices);
    H.addElement(startVertex, 0);
    heapIndices[startVertex] = 0;
    
    if (debugger.getDebugMode()) {
        H.printHeap();
    }

    heapElement tempHeapEl;
    std::list<edgeNPoints> edgeList;
    int vLabel;
    float vValue;
    int wLabel;
    float wValue;
    float vwEdgeValue;
    debugger.debugPrint("STARTING LOOP\n");
    while (H.isEmpty() == false) {
        //remove smallest element from heap
        
        tempHeapEl = H.deleteMin();
        vLabel = tempHeapEl.label;
        vValue = tempHeapEl.value;
        //if S[n] = 1, then element n is in S otherwise it's in V-S
        S[vLabel] = 1;
        
        if(debugger.getDebugMode()){
            std::cout<<"vLabel of "<<vLabel<<" set to 1. S looks like: \n[";
            for(int l = 0;l<vertices;l++)
            {
                std::cout<<S[l]<<" ";
            }
            std::cout<<"]\n";
            
        }
        
        //get edges associated with v
        debugger.debugPrint("Edge will be deleted soon");
        edgeList = myGraph.getEdges(vLabel);
        
        if (debugger.getDebugMode()) {
            std::cout << "\n\n\n" << "-----------------------";
            std::cout << "Removed root from heap.";
            std::cout << "Has label: " << vLabel << " and value: ";
            std::cout << tempHeapEl.value << std::endl;
            std::cout << "Edge list looks like: ";
            for (it = edgeList.begin(); it != edgeList.end(); ++it) {
                std::cout << "[" << it->getLabel() << ", (";

                dimsArr = it->getVertex();
                for (int j = 0; j < dimension - 1; j++) {
                    std::cout << dimsArr[j] << ", ";
                }
                std::cout << dimsArr[dimension - 1] << ") (" << it->getWeight() << ")] ";
            }
            std::cout << std::endl;
        }

        for (it = edgeList.begin(); it != edgeList.end(); ++it) {
            
            wLabel = it->getLabel();
            vwEdgeValue = it->getWeight();
            if(debugger.getDebugMode()){
                std::cout<<"Vertex: "<<wLabel<<" has Set val of: ";
                std::cout<<S[it->getLabel()]<<std::endl;
            }


            if (S[it->getLabel()] != 1) //not within set S yet
            {
                if (debugger.getDebugMode()) {
                    std::cout << "Vertex: " << wLabel << " not in MST Set\n";
                    std::cout << "Vertex distance: " << dist[wLabel] << std::endl;
                    std::cout << "Edge: " << vLabel << " to " << wLabel << " has ";
                    std::cout << "distance/weight of " << vwEdgeValue << std::endl;
                }
                if (dist[wLabel] > vwEdgeValue) {
                    dist[wLabel] = vwEdgeValue;
                    prev[wLabel] = vLabel;
                    if(debugger.getDebugMode())
                        {
                            std::cout<<"adjusting value within heap of: ";
                            std::cout<<wLabel<<" which is at index ";
                            std::cout<<heapIndices[wLabel]<<" within the heap.\n";
                            
                        }
                    if (heapIndices[wLabel] == -1) {
                        debugger.debugPrint("Item not on heap, inserting.");
                        
                        H.insertElement(wLabel, dist[wLabel]);
                    } else  {
                        //if the edge value is less than what dist[wLabel] is
                        //change the value on the heap instead of inserting
                        debugger.debugPrint("Item on heap, and less value. Changing\n");
                        H.changeValue(heapIndices[wLabel], vwEdgeValue);
                    }
                    if (debugger.getDebugMode()) {
                        std::cout << "Updating distance of: [" << wLabel;
                        std::cout << "] to " << vwEdgeValue;
                        std::cout << "\nprevious item of [" << wLabel;
                        std::cout << "] set to [" << vLabel << "]\n";
                        std::cout << "New heap looks like: " << std::endl;
                        H.printHeap();
                        std::cout << "Added item ended at heap index of: [";
                        std::cout<<heapIndices[wLabel];
                        std::cout << "]\n\n -----";
                    }
                }
            }
        }
        if(debugger.getDebugMode())
        {
            std::cout<<"\n\nLooping Again..........\n";
            std::cout<<"Current heap via indices: ";
            H.printHeap();
            std::cout<<"[";
            for(int i = 0;i<vertices;i++){
                std::cout<<heapIndices[i]<<" ";
            }
            std::cout<<"]\n";
        }


    }
    if(debugger.getDebugMode())
    {
        std::cout<<"Within graph: \n";
        myGraph.graphPrint();
        std::cout<<"Found MST of: \n";
        printPrev(prev,vertices-1);
        std::cout<<"Distance array: \n[";
        for(int i = 0;i<vertices-1;i++)
        {
            std::cout<<dist[i]<<" ";
        }
        std::cout<<dist[vertices-1]<<"] = ";
        std::cout<<"|"<<sumEdges(dist)<<"|"<<std::endl;
                
    }
    return sumEdges(dist);
}
float MST::sumEdges(float * distArr)
{
    float total=0;
    for(int i = 0;i<vertices; i++)
    {
        total+=distArr[i];
    }
    return total;
    
}
void MST::printPrev(int * prevArr, int vertexCount)
{
    
    std::cout<<"From vertex: "<<vertexCount<<" to "<<prevArr[vertexCount]<<std::endl;
    if(vertexCount > 0){
        printPrev(prevArr, --vertexCount);
    }
}

float MST::prim(graph & myGraph, int startVertex) {
    
    //set variables of MST:
    vertices = myGraph.getVertices();
    std::list<edge> ::iterator it;
    float dist[vertices];
    int prev[vertices];
    int heapIndices[vertices];
    int S[vertices];
    
    if(vertices <= PERFORM_MST_CONST)
    {
        std::list<edge> tempEdgeList;
        tempEdgeList = myGraph.getEdges(startVertex);
        edge tempEdge;
        tempEdge = tempEdgeList.back();
        
        return tempEdge.weight;
        
    }
    
    
    //initialize all applicable arrays:
    for(int i = 0; i<vertices;i++)
    {
        dist[i] = INT_MAX;
        prev[i] = -1;
        heapIndices[i] = -1;
        S[i] = 0;
    }
    
    //initialize for startVertex:
    dist[startVertex] = 0;
    myHeap H(vertices, heapIndices);
    H.addElement(startVertex, 0);
    heapIndices[startVertex] = 0;
    if(debugger.getDebugMode())
    {
        debugger.debugPrint("--------------------\nSTARTING MST:");
        
        H.printHeap();
    }
    
    //initialize variables to be used within loops:
    heapElement tempHeapEl;
    std::list<edge> edgeList;
    int vLabel;
    float vValue;
    int wLabel;
    float wValue;
    float vwEdgeWeight;
    
    while(H.isEmpty() == false)
    {
        //remove smallest element from heap (this is element v)
        tempHeapEl = H.deleteMin();
        vLabel = tempHeapEl.label;
        vValue = tempHeapEl.value;
        //if S[n] = 1, then element n is in S otherwise it's in V-S
        S[vLabel] = 1;
        //get edges associated wtih v
        edgeList = myGraph.getEdges(vLabel);
        if(debugger.getDebugMode())
        {
            std::cout<<"\n\n\n-----------------------------";
            std::cout<<"\nRemoved root from heap.";
            std::cout<<"\nHas label: "<<vLabel<<" and value ";
            std::cout<<vValue<<". It has edges of: \n";
            for(it = edgeList.begin();it != edgeList.end();++it)
            {
                std::cout<<"["<<it->vertex<<", ("<<it->weight<<")] ";
            }
            std::cout<<std::endl;
        }
        
        
        //Explore edges of v
        for(it = edgeList.begin();it!=edgeList.end(); it++)
        {
            //label the vertex v connects to through edge it, w
            wLabel = it->vertex;
            vwEdgeWeight = it->weight;
            if(debugger.getDebugMode())
            {
                std::cout<<"Vertex "<<vLabel<<" connects to vertex ";
                std::cout<<wLabel<<" and has edge weight of "<<vwEdgeWeight;
                std::cout<<"\nVertex "<<wLabel<<" has current distance of ";
                std::cout<<dist[wLabel];
                std::cout<<std::endl;
            }
            
            //if w is not apart of set S yet:
            if(S[wLabel] != 1)
            {
                if(debugger.getDebugMode())
                {
                    std::cout<<"Vertex: "<<wLabel<<" is not within set S.\n";     
                }
                //if current dist of w, is larger than the edge weight
                if (dist[wLabel] > vwEdgeWeight)
                {
                    //adjust distance and previous of w
                    dist[wLabel] = vwEdgeWeight;
                    prev[wLabel] = vLabel;
                    if(debugger.getDebugMode())
                    {
                        std::cout<<"Changing w's weight to: "<<dist[wLabel];
                        std::cout<<" and updating the previous vertex to ";
                        std::cout<<vLabel<<std::endl;
                    }
                    if(heapIndices[wLabel] == -1)
                    {
                        debugger.debugPrint("Item not on heap, inserting.");
                        H.insertElement(wLabel, dist[wLabel]);
                    }else{
                        debugger.debugPrint("Item already on heap, changing.");
                        H.changeValue(heapIndices[wLabel],vwEdgeWeight);
                    }
                    if(debugger.getDebugMode())
                    {
                        std::cout<<"New Heap looks like: ";
                        H.printHeap();
                        std::cout<<"\n\n";
                    }
                }
            }
            
        }
        if(debugger.getDebugMode())
        {
            std::cout<<"Explored all edges of vertex "<<vLabel;
            std::cout<<"\nHeap currently looks like: ";
            H.printHeap();
            
            
        }
        
    }
    if(debugger.getDebugMode())
    {
        std::cout<<"Within graph: \n";
        myGraph.graphPrint();
        std::cout<<"Found MST of: \n";
        printPrev(prev,vertices-1);
        std::cout<<"Distance array: \n[";
        for(int i = 0;i<vertices-1;i++)
        {
            std::cout<<dist[i]<<" ";
        }
        std::cout<<dist[vertices-1]<<"] = ";
        std::cout<<"|"<<sumEdges(dist)<<"|"<<std::endl;
                
    }
    return sumEdges(dist);
}