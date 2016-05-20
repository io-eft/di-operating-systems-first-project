#ifndef __MYHASH__HPP
#define __MYHASH__HPP
#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include "mytaxpayer.hpp"
#include "mylist.hpp"
//#include "mytree.hpp"
#define NUMBEROFITEMSINBUCKET 5

using namespace std;

class MyHash{
    struct Bucket{
        TaxPayer* table[NUMBEROFITEMSINBUCKET];
        int items;
	//int heights[NUMBEROFITEMSINBUCKET];

        Bucket();
    };
    int hashvalue;
    Bucket** bucket;

    void insertList(MyList* ml);

    int findBucket(TaxPayer* tax);
    int findBucket(const char* vat);

    void clearBuckets();
    void expand();

    public:
    MyHash();
    ~MyHash();

    void insertEntry(TaxPayer* tax, MyList* ml);
    void removeEntry(TaxPayer* tax);

  //  void getHeights(MyTree* mt);
    //void insertEntry(TaxPayer* tax, MyList* ml, MyTree* mt);
    //void removeEntry(TaxPayer* tax, MyTree* mt);

    TaxPayer* lookUp(const char* vat);
//    int lookUpHeight(const char* vat);
};

#endif

