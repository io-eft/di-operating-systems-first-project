#include "myhash.hpp"

MyHash::Bucket::Bucket():items(0)
{
    for(int i = 0; i < NUMBEROFITEMSINBUCKET; i++)
    {
        table[i] = NULL;
       // heights[i] = -1;
    }
}

MyHash::MyHash():hashvalue(2)
{
    bucket = new Bucket*[2];
    for(int i = 0; i < 2; i++)
        bucket[i] = new Bucket;
}

MyHash::~MyHash()
{
    for(int i = 0; i < hashvalue; i++)
        delete bucket[i];
    delete[] bucket;
}

void MyHash::clearBuckets()
{
    for(int i = 0; i < hashvalue; i++)
        delete bucket[i];
    delete[] bucket;
}

void MyHash::expand()
{
    hashvalue = hashvalue*2;    //double the amount of possible buckets
    bucket = new Bucket*[hashvalue];    //create the nodes
    for(int i = 0; i < hashvalue; i++)
        bucket[i] = new Bucket; //create the buckets
}

int MyHash::findBucket(TaxPayer* tax)
{
    string s(tax->getVat());    //create a string with the vat value
    if(s.length() > 2)  //if the vat has more than 2 elements
        s = s.substr(2);    //get a substring from the 2nd element onwards
    int result = 0; //set the result and initialize it
    stringstream a(s);      //set a stringstream with the value of the string
    if(!(a >> result))  //if the number can enter the in an int
        result = 0; //if it can't, set it as 0
    a.str("");  //clear the stringstream
    a.clear();  //clear the flags
    result = result % hashvalue;    //find the correct bucket
    return result;  //return the number of the bucket
}

int MyHash::findBucket(const char* vat) //same as above
{
    string s(vat);
    if(s.length() > 2)
        s = s.substr(2);
    int result = 0;
    stringstream a(s);
    if(!(a >> result))
        result = 0;
    result = result % hashvalue;
    a.str("");
    a.clear();
    return result;
}

void MyHash::insertEntry(TaxPayer* tax, MyList* ml)
{
    int bucketnumber = findBucket(tax); //find the number of people it has to be inserted
    if(bucket[bucketnumber]->items == NUMBEROFITEMSINBUCKET)    //if that bucket is full
    {
        clearBuckets(); //clear everything
        expand();   //expand the hashtable
        insertList(ml); //insert all items again
    }
    else    //if it is not full
    {
        bucket[bucketnumber]->items++;  //increase the number of items in it
        for(int i = 0; i < NUMBEROFITEMSINBUCKET; i++)
        {   //find the first empty spot in the bucket
            if(bucket[bucketnumber]->table[i] == NULL)
            {   //and set it pointing to the new entry
                bucket[bucketnumber]->table[i] = tax;
                break;
            }
        }
    }
}

void MyHash::insertList(MyList* ml)
{   //for each item in the list, insert it in the hashtable
    for(int i = 0; i < ml->length(); i++)
        insertEntry((*ml)[i], ml);
}

TaxPayer* MyHash::lookUp(const char* vat)
{
    int result = findBucket(vat);   //find the bucket the taxpayer should be in
    for(int i = 0; i < NUMBEROFITEMSINBUCKET; i++)
    {   //search the bucket for the taxpayer
        if(bucket[result]->table[i] != NULL)
        {
            if(strcmp(vat, bucket[result]->table[i]->getVat()) == 0)
                  return bucket[result]->table[i];  //if it's found, return it
        }
    }
    return NULL;
}

void MyHash::removeEntry(TaxPayer* tax)
{
    int result = findBucket(tax);   //find the bucket the entry should be in
    for(int i = 0; i < NUMBEROFITEMSINBUCKET; i++)
    {   //find the entry in the bucket
        if(bucket[result]->table[i] != NULL)
        {
            if(strcmp(tax->getVat(), bucket[result]->table[i]->getVat()) == 0)
            {   //set the pointer as null
                bucket[result]->table[i] = NULL;
                bucket[result]->items--;    //reduce the items in bucket
                break;
            }
        }
    }
}
/*
void MyHash::insertEntry(TaxPayer* tax, MyList* ml, MyTree* mt) //insert entry and update heights
{
    int bucketnumber = findBucket(tax); //find the number of people it has to be inserted
    if(bucket[bucketnumber]->items == NUMBEROFITEMSINBUCKET)    //if that bucket is full
    {
        clearBuckets(); //clear everything
        expand();   //expand the hashtable
        insertList(ml); //insert all items again
    }
    else    //if it is not full
    {
        bucket[bucketnumber]->items++;  //increase the number of items in it
        for(int i = 0; i < NUMBEROFITEMSINBUCKET; i++)
        {   //find the first empty spot in the bucket
            if(bucket[bucketnumber]->table[i] == NULL)
            {   //and set it pointing to the new entry
                bucket[bucketnumber]->table[i] = tax;
                break;
            }
        }
    }
    getHeights(mt);
}

void MyHash::removeEntry(TaxPayer* tax, MyTree* mt) //remove entry and update heights
{
    int result = findBucket(tax);   //find the bucket the entry should be in
    for(int i = 0; i < NUMBEROFITEMSINBUCKET; i++)
    {   //find the entry in the bucket
        if(bucket[result]->table[i] != NULL)
        {
            if(strcmp(tax->getVat(), bucket[result]->table[i]->getVat()) == 0)
            {   //set the pointer as null
                bucket[result]->table[i] = NULL;
                bucket[result]->items--;    //reduce the items in bucket
                break;
            }
        }
    }
    getHeights(mt);
}

void MyHash::getHeights(MyTree* mt)
{
    for(int i = 0; i < hashvalue; i++)
    {
        for(int j = 0; j < NUMBEROFITEMSINBUCKET; j++)
        {
            if(bucket[i]->table[j] != NULL)
            {
                bucket[i]->heights[j] = mt->lookUp((bucket[i]->table[j])->getVat());
            }
            else
            {
                bucket[i]->heights[j] = -1;
            }
        }
    }
}

int MyHash::lookUpHeight(const char* vat)   //lookup for the height
{
    int result = findBucket(vat);   //find the bucket the taxpayer should be in
    for(int i = 0; i < NUMBEROFITEMSINBUCKET; i++)
    {   //search the bucket for the taxpayer
        if(bucket[result]->table[i] != NULL)
        {
            if(strcmp(vat, bucket[result]->table[i]->getVat()) == 0)
                  return bucket[result]->heights[i];  //if it's found, return it
        }
    }
    return -1;
}
*/
