#include "myclass.hpp"
#include "myfunctions.hpp"

void MyClass::insertEntry(TaxPayer* tax)    //insert entry to all structures
{
    mt.insertEntry(tax);    //tree
    ml.insertEntry(tax);    //list
    ms.insertEntry(tax, &ml);    //structure
    mh.insertEntry(tax, &ml);   //hash
   // mh.insertEntry(tax, &ml, &mt);   //hash with heights in it
}

void MyClass::lookUp(const char* vat)   //lookup the value
{
    TaxPayer* tax = mh.lookUp(vat);     //find the record from the hash
    if(tax != NULL) //if the record was in it
    {
        int height = mt.lookUp(vat);    //find the heigh in the tree
        tax->print();
        cout << "Height in tree: " << height << endl << endl;
        return;
    }
    cout << "No record with such VAT found" << endl;    //if it was't, let the user know
}
/*
void MyClass::lookUp(const char* vat)   //lookup the value when hash has heights in it
{
    TaxPayer* tax = mh.lookUp(vat);     //find the record from the hash
    if(tax != NULL) //if the record was in it
    {
        int height = mh.lookUpHeight(vat);    //find the heigh in the hash
        tax->print();
        cout << "Height in tree: " << height << endl << endl;
        return;
    }
    cout << "No record with such VAT found" << endl;    //if it was't, let the user know
}*/

void MyClass::stats_prefecture(const char* pref)    //print the stats from the prefecture from the stracture
{
    ms.printPrefectureStats(pref);
}

void MyClass::sumStats()    //print sumstats
{
    cout << "Number of people in debt: " << mt.getNodes() << endl;
    cout << "Total Debt: " << fixed << setprecision(2) << ml.getTotalDebt() << endl;
    ms.printSumStats();
    cout << endl;
}

void MyClass::print()   //print the tree
{
    mt.printTree();
}

void MyClass::topPercentile(double p)   //print the top percentile from the list
{
    ml.printTopPercentile(p);
    cout << endl;
}

/*
void MyClass::top() //get the top entry (from the list)
{
    TaxPayer* tax = ml.getTopEntry();
    tax->print();
    cout << endl;
}*/

void MyClass::top() //get the top entry (from the tree and then hash)
{
    char result[10];
    mt.getRoot(result);
    if(strcmp(result, "0") != 0)
    {
        TaxPayer* tax = mh.lookUp(result);
        tax->print();
    }
    else
        cout << "No Entries!" << endl;
    cout << endl;
}
/*
void MyClass::removeTop(ofstream* outputfile)   //remove from each structure, getting the top from the list, and print to output
{
    TaxPayer* tax = ml.getTopEntry();
    mt.removeRoot();
    ms.removeEntry(tax);
    mh.removeEntry(tax);
  //  mh.removeEntry(tax, &mt);     //remove from hash when it has heights in it
    ml.removeTopEntry();
    printtime(outputfile);
    tax->print(outputfile);
    delete tax;
}*/

void MyClass::removeTop(ofstream* outputfile)   //remove from each structure, getting the top from the tree and hash, and print to output
{
    char result[10];
    mt.getRoot(result);
    if(strcmp(result, "0") != 0)
    {
        TaxPayer* tax = mh.lookUp(result);
        mt.removeRoot();
        ms.removeEntry(tax);
        mh.removeEntry(tax);
      //  mh.removeEntry(tax, &mt);             //remove from hash when it has heights in it
        ml.removeTopEntry();
        printtime(outputfile);
        tax->print(outputfile);
        delete tax;
    }
    else
        cout << "No Entries!" << endl;
}

void MyClass::exit(ofstream* dumpfile)  //exit by printing to dumpfile
{
    string* s = new string[mt.getNodes()];  //create an index to put the nodes
    mt.getNodesForDumpfile(s);              //fill it with the left child of N parent being in the 2N position and the right in the 2N+1
    for(int j = 0; j < mt.getNodes(); j++)  //for each entry in the index
    {
        TaxPayer* tax = NULL;               //create a new pointer
        tax = mh.lookUp(s[j].c_str());      //lookup in the hash for each VAT in the index
        if(tax != NULL)                     //if you found it
            tax->printToDumpfile(dumpfile); //print it in the dumpfile
    }
    delete[] s;                            //free the space from the index
}
