#pragma once

#include "Iheap.h"

class Tree : public IHeap {
public:
    void Insert (int key) override;
    const int& GetMin () const override;
    void ExtractMin () override;
    void Merge (IHeap& heap) override;
    bool Empty () const override;
    Tree ();
    void Delete (int key);
    void Print ();
private:
    class Node {
    public:
        Node(int key);
        Node* left;
        Node* right;
        Node* parent;
        int key;
        int height;
    };
    Node* root;
    friend int getH (Node* node);
    friend void updateHeight (Node* node);
    friend void smallRightRotation (Node* a);
    friend void smallLeftRotation (Node* a);
    friend void bigLeftRotation (Node* a);
    friend void bigRightRotation (Node* a);
    friend Node* Search (Node* node, int key);
    friend Node* upperBound (Node* start);
    friend Node* least (Node* start);
    friend Node* antiUpperBound (Node* start);
    friend Node* most (Node* start);
    void fix (Node* node);
    friend void Print (Node* node);
};
