#include <iostream>
#include "graph.h"
#include "debug.h"
#include "graphND.h"
#include <string>
#include "MST.h"
#include <bits/stdc++.h>

int main(int argc, char *argv[]) {

    std::string helpString = "help";

    if (std::strcmp(argv[1], "help") == 0) {
        std::cout << "This function creates a complete graph and then finds\nthe minimum";
        std::cout << " search tree. To operate call it in the following way: \n";
        std::cout<< "./randmst debugMode vertices iterations dimensions\n";
        std::cout<<"---------------------------------------------------\n";
        std::cout<<"debugMode: 0 for no debug mode, 1 for verbose debug\nmode";
        std::cout<<" and 2 for non-verbose debug mode.\n";
        std::cout<<"\nvertices: # of vertices within the graph to create.\n";
        std::cout<<"\niterations: # of times to run through MST algorithm\non the ";
        std::cout<<"created graph. Each iteration is expected to\nhave slightly different";
        std::cout<<" total weight for each tree.\n";
        std::cout<<"\ndimensions: dimension of the graph to create. Note\ndimension of 0 will\n";
        std::cout<<"return incorrect results.\n\n";
                
                
                
                
                
    } else {

        int debugMode = std::stoi(argv[1]);




        int graphSize = std::stoi(argv[2]);
        int dimensions = std::stoi(argv[4]);
        int iterationAmount = std::stoi(argv[3]);





        float MSTSize = 0;
        float result;
        MST mstTest(debugMode);

        if(graphSize <= 1)
        {
            std::cout<<0<<" "<<graphSize<<" "<<iterationAmount;
            std::cout<<" "<<dimensions<<std::endl;
            return 0;
        }

        
        
        srand(time(0));

        for (int testIteration = 1; testIteration <= iterationAmount; testIteration++) {
            
            if (debugMode == 2) {
                std::cout << "\n\nStarting iteration: " << testIteration << std::endl;
            }
            if (dimensions == 1) {
                graph myGraph(graphSize, debugMode);
                result = mstTest.prim(myGraph, 0);
            } else {
                graphND myGraphNDims(graphSize, dimensions, debugMode);
                result = mstTest.primND(myGraphNDims, 0);

            }

            if (debugMode == 2) {
                std::cout << std::setprecision(8);
                std::cout << "Iteration: " << testIteration << "=" << result << " \n";
                std::cout << std::setprecision(2);
            }
            MSTSize += result;

        }

        if (debugMode == 2) {
            std::cout << std::setprecision(8);
            std::cout << "\n\n\nTotal: " << MSTSize;
            std::cout << "\nAverage: " << MSTSize / iterationAmount << std::endl;
        }
        std::cout<<MSTSize/iterationAmount<<" "<<graphSize<<" "<<iterationAmount;
        std::cout<<" "<<dimensions<<std::endl;
    }
    return 0;
}
