#include "Heap.hpp"

Heap::Heap(int size, int *arr):size(size)
{
    arr=new int[size];
    for(int i=0;i<size;i++)
    {
        arr[i]=arr[i];
    }
}
void Heap::heapify(int i)
{
    if (size == 1)
    {
        return;
    }
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < size && arr[l] > arr[largest])
      largest = l;
    if (r < size && arr[r] > arr[largest])
      largest = r;
    if (largest != i)
    {
      swap(&arr[i], &arr[largest]);
      heapify(largest);
    }
}


void Heap::swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

Heap::~Heap()
{
    delete[] arr;
}