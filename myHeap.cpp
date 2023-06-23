#include "myHeap.h"

myHeap::myHeap(const int n, int * heapIndices) {
    heap = new heapElement[n];
    heapSize = n;
    itemsOnHeap = 0;
    internalHeapIndices = heapIndices;
}

myHeap::~myHeap()
{
    
    delete [] heap;
}

void myHeap::printHeapIndices()
{
    for(int i = 0;i<heapSize;i++)
    {
        std::cout<<internalHeapIndices[i]<<" ";
    }
    std::cout<<std::endl;
}

void myHeap::addElement(int label, float elementValue) {
    heapElement tempHeapEl;
    tempHeapEl.label = label;
    tempHeapEl.value = elementValue;
    tempHeapEl.heapIndex = itemsOnHeap;
    internalHeapIndices[label] = itemsOnHeap;
    heap[itemsOnHeap] = tempHeapEl;
    itemsOnHeap++;


}

void myHeap::printHeap() {
    std::cout << "Items on heap: " << itemsOnHeap << std::endl;
    int level;
    int oldLevel = -1;
    for (int i = 0; i < itemsOnHeap; i++) {

        level = log2(i + 1);
        if (oldLevel != level) {
            std::cout << std::endl;
            std::cout << "Level " << level << ": ";
        }
        oldLevel = level;
        std::cout << "[" << heap[i].label << ", " << heap[i].value << "] ";
    }
    std::cout << std::endl;
}

void myHeap::insertElement(int label, float elementValue) {
    //add elementValue at the end of heap
    addElement(label, elementValue);
    int insertedIndex = itemsOnHeap - 1;



    while (insertedIndex > 0 && heap[insertedIndex].value < heap[parentIndex(insertedIndex)].value) {
        swap(parentIndex(insertedIndex), insertedIndex);
        insertedIndex = parentIndex(insertedIndex);
    }
    

}

void myHeap::minHeapify(const int n) {

    int smallestIndex;
    if (leftChildExists(n) && heap[leftChildIndex(n)].value < heap[n].value) {
        //if left child is larger than current heap[n]
        smallestIndex = leftChildIndex(n);
    } else {
        smallestIndex = n;
    }

    if (rightChildExists(n) && heap[rightChildIndex(n)].value < heap[smallestIndex].value) {
        smallestIndex = rightChildIndex(n);
    }
    if (smallestIndex != n) {
        swap(n, smallestIndex);
        minHeapify(smallestIndex);
    } 
}

int myHeap::swap(const int swappedOut, const int swappedIn) {
    //first change heap element labels

    //create temporary element that will be the heap
    //item getting swapped out
    heapElement tempHeapEl = heap[swappedOut];

    //swap the heap element at index swappedIN
    //into heap element at index swappedOut
    heap[swappedOut] = heap[swappedIn];
    heap[swappedOut].heapIndex = swappedOut;
    internalHeapIndices[heap[swappedOut].label] = swappedOut;

    //swap the item previously at index swappedOut
    //into the swappedIn Index
    heap[swappedIn] = tempHeapEl;
    heap[swappedIn].heapIndex = swappedIn;
    internalHeapIndices[heap[swappedIn].label] = swappedIn;
    
}

void myHeap::buildHeap() {
    for (int i = (itemsOnHeap - 1) / 2; i >= 0; i--) {
        minHeapify(i);
    }
}

heapElement myHeap::deleteMin() {
    if (itemsOnHeap >= 1) {
        heapElement minElement = heap[0];
        //swap the smallest and the last item of the heap
        swap(0, itemsOnHeap - 1);
        //remove item off heap
        internalHeapIndices[minElement.label] = -1;
        itemsOnHeap--;
        //run min heapify on the item at the root (the largest)
        minHeapify(0);
        return minElement;
    }
    else{
        return heap[0];
    }
            

}

heapElement myHeap::parent(const int index) {
    //implicit floor function by converting to int
    int parentIndex = (index - 1) / 2;
    if (index == 0) {
        std::cout << "No parent for index of 0" << std::endl;
        return heap[0];
    } else {
        return heap[parentIndex];
    }
}
bool myHeap::parentExists(const int index) {
    
    if (index == 0) {
        
        return false;
    } else {
        return true;
    }
}

int myHeap::parentIndex(const int index) {
    //implicit floor function by converting to int
    int parentIndex = (index - 1) / 2;

    return parentIndex;

}

heapElement myHeap::leftChild(const int index) {
    if (2 * index + 1 >= itemsOnHeap) {
        std::cout << "No left child for index " << index << std::endl;
        return heap[index];
    } else {
        return heap[2 * index + 1];
    }


}

int myHeap::leftChildIndex(const int index) {
    return 2 * index + 1;
}

bool myHeap::leftChildExists(const int index) {
    if (2 * index + 1 >= itemsOnHeap) {

        return false;
    } else {
        return true;
    }


}

heapElement myHeap::rightChild(const int index) {
    if (2 * index + 2 >= itemsOnHeap) {
        std::cout << "No right child for index " << index << std::endl;
        return heap[index];
    } else {
        return heap[2 * index + 2];
    }

}

int myHeap::rightChildIndex(const int index) {
    return 2 * index + 2;
}

bool myHeap::rightChildExists(const int index) {
    if (2 * index + 2 >= itemsOnHeap) {

        return false;
    } else {
        return true;
    }

}

void myHeap::changeValue(const int index, const float value)
{
    float oldValue = heap[index].value;
    heap[index].value = value;
    
    if(oldValue > value)
    {
        int tempIndex = index;
        int parentIndexTemp = parentIndex(index);
        while(parentExists(tempIndex) && heap[parentIndexTemp].value > value)
        {
            
            swap(parentIndexTemp,tempIndex);
            tempIndex = parentIndexTemp;
            parentIndexTemp = parentIndex(tempIndex);
        }
        
    }
    else if(oldValue < value)
    {
        //compare with items below
        heap[index].value = value;
        minHeapify(index);
        
    }
    
}