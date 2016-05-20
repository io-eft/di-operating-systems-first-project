#ifndef __MYSTRUCTURE__HPP
#define __MYSTRUCTURE__HPP
#include <iostream>
#include "mytaxpayer.hpp"
#include "mylist.hpp"
#include <string.h>
#include <string>
#define NODESINBUCKET 5

class MyStructure
{
    struct Node{
        char prefecture[4];
        double totaldebt;
        int amount;
        Node* next;

        Node(TaxPayer* tax);
    };
    struct Bucket{
	Node* table[NODESINBUCKET];
	int items;
	
	Bucket();
	~Bucket();

	bool isEmpty();
	bool isFull();
    };

    int hashvalue;
    int totalitems;
    Bucket** bucket;
    Node* head;
    Node* tail;
    //int totalitems;

    void insertList(MyList* ml);

    int findBucket(const char* pref);

    void clearBuckets();
    void expand();


    public:
        MyStructure();
        ~MyStructure();

        void insertEntry(TaxPayer* tax, MyList* ml);
	
        void printPrefectureStats(const char* pref);
        void printSumStats();

        void removeEntry(TaxPayer* tax);
};

#endif
