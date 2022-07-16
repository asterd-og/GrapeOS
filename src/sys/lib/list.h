#pragma once

#include <stdint.h>
#include <stddef.h>

class Node {
    public:
        Node* prev;
        Node* next;
        void* data;
};

class List {
    public:
        Node* head;
        Node* tail;
        uint32_t size;

        void create();
        Node* insertFront(void* data);
        void insertBack(void* data);
        void* removeNode(Node* node);
        void* removeFront();
        void* removeBack();
        void push(void* val);
        Node* pop();
        void enqueue(void* val);
        Node* dequeue();
        void* peekFront();
        void* peekBack();
        void destroyNode(Node* node);
        int contains(void* data);
        Node* getNodeByIndex(int index);
        void* removeByIndex(int index);
        void destroy();
};

#define foreach(t, list) for(Node* t = list->head; t != NULL; t = t->next)