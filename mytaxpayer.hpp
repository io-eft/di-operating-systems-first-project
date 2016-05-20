#ifndef __MYTAXPAYER__HPP
#define __MYTAXPAYER__HPP
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <iomanip>

using namespace std;

class TaxPayer
{
    char vat[11];
    char surname[26];
    char name[16];
    char hometown[21];
    char prefecture[4];
    double debt;

    public:
    TaxPayer();
    //TaxPayer(char* v, char* s, char* n, char* h, char* p, double d);
    TaxPayer(const char* v, const char* s, const char* n, const char* h, const char* p, double d);

    char* getVat();
    double getDebt();
    char* getPrefecture();

    void print();
    void print(ofstream* outputfile);
    void printToDumpfile(ofstream* outputfile);
};

#endif
