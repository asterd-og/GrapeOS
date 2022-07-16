#include <sys/lib/list.h>
#include <sys/mem/heap.h>
#include <sys/debug/dbg.h>

void List::create() {
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
}

Node* List::insertFront(void* data) {
    Node* node;
    node->data = data;
    this->head->next=node;
    node->next = this->head;

    if (!this->head)
        this->tail = node;
    
    this->head = node;
    this->size++;
    return node;
}

void List::insertBack(void* data) {
    Node* node;
    node->data = data;
    node->prev = this->tail;
    if (this->tail)
        this->tail->next = node;

    if (!this->head)
        this->head = node;
    
    this->tail = node;
    this->size++;
}

void* List::removeNode(Node* node) {
    void* data = node->data;
    if (this->head == node) return this->removeFront();
    else if (this->tail == node) return this->removeBack();
    else {
        node->next->prev = node->prev;
        node->prev->next = node->next;
        this->size--;
        Heap::free(node);
    }
    return data;
}

void* List::removeFront() {
    if (!this->head) return;
    Node* node = this->head;
    void* data = node->data;
    this->head = node->next;
    if (this->head)
        this->head->prev = NULL;
    Heap::free(node);
    this->size--;
    return data;
}

void* List::removeBack() {
    if (!this->tail) return;
    Node* node = this->tail;
    void* data = node->data;
    this->tail = node->prev;
    if (this->tail)
        this->tail->next = NULL;
    Heap::free(node);
    this->size--;
    return data;
}

void List::push(void* data) {
    this->insertFront(data);
}

Node* List::pop() {
    if (!this->head) return NULL;
    Node* node = this->tail;
    this->tail = node->prev;
    if (this->tail)
        this->tail->next = NULL;
    this->size--;
    return node;
}

void List::enqueue(void* data) {
    this->insertFront(data);
}

Node* List::dequeue() {
    return this->pop();
}

void* List::peekFront() {
    if (!this->head) return NULL;
    return this->head->data;
}

void* List::peekBack() {
    if (!this->tail) return NULL;
    return this->tail->data;
}

int List::contains(void* data) {
    int idx=0;
    foreach (Node, this) {
        if (Node->data == data)
            return idx;
        idx++;
    }
    return -1;
}

Node* List::getNodeByIndex(int index) {
    if (index < 0 || index > this->size) return NULL;
    int c=0;
    foreach (Node, this) {
        if (index == c) return Node;
        index++;
    }
    return NULL;
}

void* List::removeByIndex(int index) {
    Node* node = this->getNodeByIndex(index);
    return this->removeNode(node);
}

void List::destroy() {
    Node* node=this->head;
    while (node != NULL) {
        Node* save = node;
        node = node->next;
        Heap::free(save);
    }
    Heap::free(this);
}

void List::destroyNode(Node* node) {
    Heap::free(node);
}