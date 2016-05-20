#ifndef __MYLIST__HPP
#define __MYLIST__HPP
#include <iostream>
#include "mytaxpayer.hpp"

using namespace std;

class MyList{
    struct Node{
        TaxPayer* content;
        Node* next;

        Node(TaxPayer* tax);
        Node();
    };
    Node* head;
    unsigned int nodes;
    double totaldebt;

    public:
        MyList();
        ~MyList();
        bool isEmpty();
        int length();

        TaxPayer* operator[](unsigned int i);

        void insertEntry(TaxPayer* tax);
        TaxPayer* getTopEntry();
        void removeTopEntry();

        void print();
        void printTopPercentile(double p);
        void printTopEntry();

	double getTotalDebt();
};

#endif

