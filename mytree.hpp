#ifndef __MYTREE__HPP
#define __MYTREE__HPP
#include <iostream>
#include "mytaxpayer.hpp"

using namespace std;

class MyTree{
    struct Node{
        char vat[11];
        double debt;
        Node* parent;
        Node* left;
        Node* right;
        int nodeNumber;

        Node(TaxPayer* tax, Node* n, int a);
        Node(TaxPayer* tax, int a);
        Node();
    };
    Node* root;
    int nodes;
    Node* currentNode;
    Node* lastNode;

        bool isEmpty();

        void swapNodes(Node* a, Node* b);

        void correctTreeOnInsertion(Node* n);
        void correctTreeOnRemoval(Node* n);

        void findNextParent();
        void findNewLast();

        int lookUpVat(const char* vat, Node* n);

        void getNodesForPrint(Node* n, Node** index);
        void getNodesForDump(Node*n, string* index);

    public:
        MyTree();
        ~MyTree();

        void insertEntry(TaxPayer* tax);
        int lookUp(const char* vat);
        void printTree();
        int getNodes();
        void removeRoot();
        //void removeRoot(char* result);
        void getRoot(char* result);
        void dissolveTree(Node* n);
        void getNodesForDumpfile(string* index);
};

#endif
