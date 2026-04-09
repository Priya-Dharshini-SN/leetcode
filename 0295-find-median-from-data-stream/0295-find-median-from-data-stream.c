#include <stdlib.h>
typedef struct {
    int* arr;
    int size;
} MaxHeap;

void maxHeapifyUp(MaxHeap* h, int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->arr[p] >= h->arr[i]) break;
        int temp = h->arr[p];
        h->arr[p] = h->arr[i];
        h->arr[i] = temp;
        i = p;
    }
}

void maxHeapifyDown(MaxHeap* h, int i) {
    int largest = i;
    int l = 2*i + 1, r = 2*i + 2;

    if (l < h->size && h->arr[l] > h->arr[largest]) largest = l;
    if (r < h->size && h->arr[r] > h->arr[largest]) largest = r;

    if (largest != i) {
        int temp = h->arr[i];
        h->arr[i] = h->arr[largest];
        h->arr[largest] = temp;
        maxHeapifyDown(h, largest);
    }
}

void maxPush(MaxHeap* h, int val) {
    h->arr[h->size++] = val;
    maxHeapifyUp(h, h->size - 1);
}

int maxPop(MaxHeap* h) {
    int val = h->arr[0];
    h->arr[0] = h->arr[--h->size];
    maxHeapifyDown(h, 0);
    return val;
}

int maxTop(MaxHeap* h) {
    return h->arr[0];
}

typedef struct {
    int* arr;
    int size;
} MinHeap;

void minHeapifyUp(MinHeap* h, int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->arr[p] <= h->arr[i]) break;
        int temp = h->arr[p];
        h->arr[p] = h->arr[i];
        h->arr[i] = temp;
        i = p;
    }
}

void minHeapifyDown(MinHeap* h, int i) {
    int smallest = i;
    int l = 2*i + 1, r = 2*i + 2;

    if (l < h->size && h->arr[l] < h->arr[smallest]) smallest = l;
    if (r < h->size && h->arr[r] < h->arr[smallest]) smallest = r;

    if (smallest != i) {
        int temp = h->arr[i];
        h->arr[i] = h->arr[smallest];
        h->arr[smallest] = temp;
        minHeapifyDown(h, smallest);
    }
}

void minPush(MinHeap* h, int val) {
    h->arr[h->size++] = val;
    minHeapifyUp(h, h->size - 1);
}

int minPop(MinHeap* h) {
    int val = h->arr[0];
    h->arr[0] = h->arr[--h->size];
    minHeapifyDown(h, 0);
    return val;
}

int minTop(MinHeap* h) {
    return h->arr[0];
}

typedef struct {
    MaxHeap left;   
    MinHeap right;  
} MedianFinder;

MedianFinder* medianFinderCreate() {
    MedianFinder* obj = (MedianFinder*)malloc(sizeof(MedianFinder));
    
    obj->left.arr = (int*)malloc(50000 * sizeof(int));
    obj->left.size = 0;

    obj->right.arr = (int*)malloc(50000 * sizeof(int));
    obj->right.size = 0;

    return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    if (obj->left.size == 0 || num <= maxTop(&obj->left))
        maxPush(&obj->left, num);
    else
        minPush(&obj->right, num);

    if (obj->left.size > obj->right.size + 1)
        minPush(&obj->right, maxPop(&obj->left));
    else if (obj->right.size > obj->left.size)
        maxPush(&obj->left, minPop(&obj->right));
}


double medianFinderFindMedian(MedianFinder* obj) {
    if (obj->left.size == obj->right.size)
        return (maxTop(&obj->left) + minTop(&obj->right)) / 2.0;
    else
        return maxTop(&obj->left);
}


void medianFinderFree(MedianFinder* obj) {
    free(obj->left.arr);
    free(obj->right.arr);
    free(obj);
}