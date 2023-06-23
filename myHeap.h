#include "heapElement.h"
#include "math.h"
#include <iostream>
#ifndef MYHEAP_H
#define MYHEAP_H


class myHeap{
    
public:
       
    myHeap(const int n, int * heapIndices);
    ~myHeap();
    //addElement only adds items to heap doesn't run heapify/
    //insert does run heapify
    void addElement(int label, float elementValue);
    void insertElement(int label, float elementValue);
    void minHeapify(const int n);
    void buildHeap();
    heapElement deleteMin();
    
    void printHeap();
    
    heapElement parent(const int index);
    bool parentExists(const int index);
    heapElement leftChild(const int index);
    bool leftChildExists(const int index);
    bool rightChildExists(const int index);
    heapElement rightChild(const int index);
    
    int parentIndex(const int index);
    int leftChildIndex(const int index);
    int rightChildIndex(const int index);
    int swap(const int swappedOut, const int swappedIn);
    void changeValue(const int index, const float value);
    bool isEmpty()
    {
        
        if(itemsOnHeap == 0)
        {
            return true;
        }else
        {
            return false;
        }
    }
    void printHeapIndices();
    
private:    
    heapElement * heap;
    int heapSize;
    int *internalHeapIndices;
    int itemsOnHeap;
    //not size 0 for 0 items on heap
    //size 1 for 1 item on heap, item needs to be indexed with zero though
};



#endif
