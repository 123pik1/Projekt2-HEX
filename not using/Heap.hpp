
class Heap
{
private:
    int size;
    int *arr;
    int maxVal;
public:
    Heap(int size, int *arr);
    void heapify(int i);
    void swap(int *a, int *b);
    ~Heap();
};