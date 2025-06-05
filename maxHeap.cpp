#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX 100
#define gc getchar();

typedef struct Node{
    char name[100];
    int score;
}Node;

typedef struct Heap{
    int size;
    Node arr[MAX];
}MaxHeap;

void swap(Node *a, Node *b){
    Node temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int i){
    return (i - 1) /2;
}

int left(int i){
    return (i * 2 + 1);
}

int right(int i){
    return (i * 2 + 2);
}

int cmp(Node *a, Node *b){
    if (a->score > b->score) return 1;
    else if(a->score < b->score) return -1;
    else return strcmp(b->name, a->name);
}

void upHeap(Heap *heap, int i){
    while (i != 0) {
        if (cmp(&heap->arr[i], &heap->arr[parent(i)]) > 0){
            swap(&heap->arr[i], &heap->arr[parent(i)]);
            i = parent(i);
        }
        else {
            break;
        }
    }
}

void downHeap(Heap *heap, int i) {
    int largest = i;
    int l = left(i);
    int r = right(i);

    if (l < heap->size && cmp(&heap->arr[l], &heap->arr[largest]) > 0)
        largest = l;
    if (r < heap->size && cmp(&heap->arr[r], &heap->arr[largest]) > 0)
        largest = r;

    if (largest != i) {
        swap(&heap->arr[i], &heap->arr[largest]);
        downHeap(heap, largest);
    }
}

void insert(Heap *heap, char *name, int score){
    if(heap->size >= MAX){
        return;
    }
    int i = heap->size;
    strcpy(heap->arr[i].name, name);
    heap->arr[i].score = score;
    heap->size++;
    upHeap(heap, i);
}

Node extract(Heap *heap){
    Node root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    downHeap(heap, 0);
    return root;
}

void printHeap(Heap *heap, int x){
    printf("\nTop %d students:\n", x);
    for(int i = 0; i < x && heap->size > 0; i++){
        Node root = extract(heap);
        printf("%s %d\n", root.name, root.score);
    }
}


int main(){
    MaxHeap heap;
    heap.size = 0;

    int n, x, score;
    char name[100];
    scanf("%d %d", &n, &x); gc
    for(int i = 0; i < n; i++){
        scanf("%s %d", name, &score);
        insert(&heap, name, score);
    }

    printHeap(&heap, x);
    return 0;
}

/*
6 3
Alice 88
Bob 90
Charlie 90
Dave 85
Eve 88
Frank 70
*/