// singlelist.h

#ifndef SINGLELIST_H
#define SINGLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
struct SingleNode {
// the default access mode and default inheritance mode are public
    T value;
    SingleNode *next;
    SingleNode() : value(T()), next(nullptr) {} // konstruktor domyslny
    SingleNode(const T& item, SingleNode *ptr=nullptr) : value(item), next(ptr) {}
    ~SingleNode() {} // destruktor
};

template <typename T>
class SingleList {
    SingleNode<T> *head, *tail;
public:
    SingleList() : head(nullptr), tail(nullptr) {}
    ~SingleList(); // tu trzeba wyczyscic wezly
    SingleList(const SingleList& other)
    {
        SingleNode<T> *othernode = other.head;
        while(othernode != nullptr){
            if (!empty()) {
            tail->next = new SingleNode<T>(othernode->value);
            tail = tail->next;
            }       
            else{
            head = tail = new SingleNode<T>(othernode->value);
            }
            othernode = othernode->next;
        }
    } // copy constructor
    // usage:   SingleList<int> list2(list1);
    SingleList(SingleList&& other); // move constructor NIEOBOWIAZKOWE
    // usage:   SingleList<int> list2(std::move(list1));
    SingleList& operator=(const SingleList& other)
    {
        SingleNode<T> *othernode = other.head;
        while(othernode != nullptr){
            if (!empty()) {
            tail->next = new SingleNode<T>(othernode->value);
            tail = tail->next;
            }       
            else{
            head = tail = new SingleNode<T>(othernode->value);
            }
            othernode = othernode->next;
        }
        return *this;
    } // copy assignment operator, return *this
    // usage:   list2 = list1;
    SingleList& operator=(SingleList&& other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE
    bool empty() const { return head == nullptr; }
    int size() const
    {
        if (empty()){
            return 0;
        }
        int i = 0;
        SingleNode<T> *node = head;
        while (node != nullptr){
            i++;
            node = node->next;
        }
        return i;
    } // O(n) bo trzeba policzyc
    void push_front(const T& item); // O(1), L.push_front(item)
    //void push_front(T&& item); // O(1), L.push_front(std::move(item)) NIEOBOWIAZKOWE
    void push_back(const T& item); // O(1), L.push_back(item)
    //void push_back(T&& item); // O(1), L.push_back(std::move(item)) NIEOBOWIAZKOWE
    T& front() const { return head->value; } // zwraca poczatek, nie usuwa
    T& back() const { return tail->value; } // zwraca koniec, nie usuwa
    void pop_front(); // usuwa poczatek O(1)
    void pop_back(); // usuwa koniec O(n)
    void clear()
    {
        SingleNode<T> *node = head;
        while(!empty()){
            node = head->next;
            delete head;
            head = node;
        }
    } // czyszczenie listy z elementow O(n)
    void display(); // O(n)
    //void reverse(); // O(n)
    // Operacje z indeksami. NIEOBOWIAZKOWE
    T& operator[](int pos)
    {
        SingleNode<T> *garbage = new SingleNode<T>();      
        if (pos > size()){
            std::cout<<"Error, niewlasciwa pozycja/n";
            return garbage->value;
        }
        SingleNode<T> *node = head;
        int i = 0;
        for (;i<=pos-1;i++){
            node = node->next;
        }
        return node->value;
        
    } // podstawienie L[pos]=item
    const T& operator[](int pos) const
    {
        if (pos > size()){
            std::cout<<"Error, niewlasciwa pozycja/n";
            return -1;
        }
        SingleNode<T> *node = head;
        int i = 0;
        for (;i<=pos-1;i++){
            node = node->next;
        }
        return node->value;
    } // odczyt L[pos]
    void erase(int pos)
    {
        if (pos > size()){
            std::cout<<"Error, niewlasciwa pozycja/n";
            return;
        }
        SingleNode<T> *node = head;
        int i = 0;
        for (;i<pos-1;i++){
            node = node->next;
        }
        SingleNode<T> *rem_node = node->next;
        node->next = node->next->next;
        delete rem_node;
    }
    int index(const T& item)
    {
        bool sem = 0;
        int i = 0;
        SingleNode<T> *node = head;
        while (node != nullptr){
            if(node->value == item){
                sem = 1;
                break;
            }
            i++;
            node = node->next;
        }
        if(sem){
            return i;
        }
        else{
            return -1;
        }

    } // jaki index na liscie (-1 gdy nie ma) O(n)
    void insert(int pos, const T& item)
    {
        SingleNode<T> *node = head;
        SingleNode<T> *newnode = new SingleNode<T>();
        SingleNode<T> *backup = new SingleNode<T>();
        int i = 0;
        while(i != pos){
            i++;
            if(i == pos){
                break;
            }
            node = node->next;
        }
        backup = node->next;
        node->next = newnode;
        newnode->next = backup;
        newnode->value = item;

    } // inserts item before pos,
    void insert(int pos, T&& item)
    {
        SingleNode<T> *node = head;
        SingleNode<T> *newnode = new SingleNode<T>();
        SingleNode<T> *backup = new SingleNode<T>();
        if(pos == 0){
            push_front(item);
            return;
        }
        if(pos == size()){
            push_back(item);
            return;
        }
        int i = 0;
        while(i != pos){
            i++;
            if(i == pos){
                break;
            }
            node = node->next;
        }
        backup = node->next;
        node->next = newnode;
        newnode->next = backup;
        newnode->value = item;

    } // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};

template <typename T>
SingleList<T>::~SingleList() {
    // I sposob.
    for (SingleNode<T> *node; !empty(); ) {
        node = head->next; // zapamietujemy
        delete head;
        head = node; // kopiowanie wskaznika
    }
    // II sposob.
    // while (!empty()) { pop_front(); }
}

template <typename T>
void SingleList<T>::push_front(const T& item) {
    if (!empty()) {
        head = new SingleNode<T>(item, head);
    } else {
        head = tail = new SingleNode<T>(item);
    }
}

template <typename T>
void SingleList<T>::push_back(const T& item) {
    if (!empty()) {
        tail->next = new SingleNode<T>(item);
        tail = tail->next;
    } else {
        head = tail = new SingleNode<T>(item);
    }
}

template <typename T>
void SingleList<T>::display() {
    SingleNode<T> *node = head;
    while (node != nullptr){
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

template <typename T>
void SingleList<T>::pop_front() {
    assert(!empty());
    SingleNode<T> *node = head; // zapamietujemy
    if (head == tail) { // jeden wezel na liscie
        head = tail = nullptr;
    } else { // wiecej niz jeden wezel na liscie
        head = head->next;
    }
    delete node;
}

template <typename T>
void SingleList<T>::pop_back() {
    assert(!empty());
    SingleNode<T> *node = tail; // zapamietujemy
    if (head == tail) { // jeden wezel na liscie
        head = tail = nullptr;
    } else { // wiecej niz jeden wezel na liscie
        // Szukamy poprzednika ogona.
        SingleNode<T> *before=head;
        while (before->next != tail) {
            before = before->next;
        }
        tail = before;
        tail->next = nullptr;
    }
    delete node;
}

#endif