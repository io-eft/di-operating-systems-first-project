#ifndef __MYCLASS__HPP
#define __MYCLASS__HPP
#include "mytaxpayer.hpp"
#include "mytree.hpp"
#include "mylist.hpp"
#include "mystructure.hpp"
#include "myhash.hpp"

class MyClass
{
    MyTree mt;
    MyStructure ms;
    MyList ml;
    MyHash mh;

    public:

    void insertEntry(TaxPayer* tax);
    void lookUp(const char* vat);

    void stats_prefecture(const char* pref);
    void sumStats();
    void print();
    void topPercentile(double p);
    void top();
    void removeTop(ofstream* outputfile);
    void exit(ofstream* dumpfile);
};

#endif

