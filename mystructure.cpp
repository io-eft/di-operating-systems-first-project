#include "mystructure.hpp"

MyStructure::Node::Node(TaxPayer* tax): amount(1), next(NULL)
{
    strcpy(prefecture, tax->getPrefecture());
    totaldebt = tax->getDebt();
}

MyStructure::Bucket::Bucket(): items(0)
{
    for(int i = 0; i < NODESINBUCKET; i++)
        table[i] = NULL;
}

MyStructure::Bucket::~Bucket()  //destructor to be sure to free all allocated space
{
    for(int i = 0; i < NODESINBUCKET; i++)
    {
        if(table[i] != NULL)
            delete table[i];
    }
}

bool MyStructure::Bucket::isEmpty()
{
    if(items == 0)
        return true;
    else
        return false;
}

bool MyStructure::Bucket::isFull()
{
    if(items == NODESINBUCKET)
        return true;
    else
        return false;
}

MyStructure::MyStructure(): hashvalue(2), totalitems(0), head(NULL), tail(NULL)
{
    bucket = new Bucket*[2];
    for(int i = 0; i < 2; i++)
        bucket[i] = new Bucket;
}

MyStructure::~MyStructure() //destructor to be sure to free all allocated space
{
    for(int i = 0; i < hashvalue; i++)
        delete bucket[i];
    delete[] bucket;
}

int MyStructure::findBucket(const char* pref)   //impromptu hash function
{
    string s(pref);
    int result = 0;
    switch(s.length())
    {
        case(1): result = s[0] % hashvalue; return result;
        case(2): result = 10*s[0] + s[1]; result = result % hashvalue; return result;
        case(3): result = 100*s[0] + 10*s[1] + s[2]; result = result % hashvalue; return result;
        default: return 0;
    }
}

void MyStructure::clearBuckets()
{
    cout << "clearing buckets" << endl;
    totalitems = 0;
    head = NULL;
    tail = NULL;
    for(int i = 0; i < hashvalue; i++)
        delete bucket[i];
    delete[] bucket;
}

void MyStructure::expand()
{
    hashvalue = hashvalue*2;    //double the amount of possible buckets
    bucket = new Bucket*[hashvalue];    //create the nodes
    for(int i = 0; i < hashvalue; i++)
        bucket[i] = new Bucket; //create the buckets
}

void MyStructure::insertEntry(TaxPayer* tax, MyList* ml)
{
    int result = findBucket(tax->getPrefecture());  //find the correct bucket
    if(bucket[result]->isEmpty())   //if there's no item in the bucket yet
    {
        Node* n = new Node(tax);    //create a new node
        bucket[result]->table[0] = n;   //put it in the bucket
        bucket[result]->items++;    //increase the items in the bucket
       // cout << "I am here " << endl;
     //   cout << "totalitems: " << totalitems << endl;
        if(totalitems == 0)
        {
      //      cout << "head and tail are the same now" << endl;
            head = n;
            tail = n;
        }
        else
        {
            tail->next = n;
            tail = n;
        }
        totalitems++;
    }
    else    //if there are entries in the bucket
    {
        for(int i = 0; i < NODESINBUCKET; i++)  //check to find if there's already an entry for prefecture
        {
            if(bucket[result]->table[i] != NULL)
            {
                if(strcmp(tax->getPrefecture(), bucket[result]->table[i]->prefecture) == 0) //if you find it, add the stats
                {
                    bucket[result]->table[i]->amount++;
                    bucket[result]->table[i]->totaldebt = bucket[result]->table[i]->totaldebt + tax->getDebt();
                    return;
                }
            }
        }
        if(bucket[result]->isFull())    //if we don't find it and it is full
        {
            clearBuckets(); //clear the structure
            expand();   //expand it
            insertList(ml); //insert all entries again
        }
        else    //if we don't find it and we have space
        {
            Node* n = new Node(tax);    //create a new node
            bucket[result]->items++;
            tail->next = n;
            tail = n;
            totalitems++;
            for(int i = 0; i < NODESINBUCKET; i++)
            {
                if(bucket[result]->table[i] == NULL)    //and find a spot for it
                {
                    bucket[result]->table[i] = n;
                    return;
                }
            }
        }
    }
}

void MyStructure::insertList(MyList* ml)
{
    for(int i = 0; i < ml->length(); i++)   //re-insert all items in the list
        insertEntry((*ml)[i], ml);
}

void MyStructure::removeEntry(TaxPayer* tax)
{
    int result = findBucket(tax->getPrefecture());  //find the bucket the record would be in
    for(int i = 0; i < NODESINBUCKET; i++)      //find the correct position in the bucket
    {
        if(strcmp(bucket[result]->table[i]->prefecture, tax->getPrefecture()) == 0) //once you find it subtract the stats
        {
            bucket[result]->table[i]->amount--;
            bucket[result]->table[i]->totaldebt = bucket[result]->table[i]->totaldebt - tax->getDebt();
            return;
        }
    }
}

void MyStructure::printPrefectureStats(const char* pref)
{
    int result = findBucket(pref);  //find the correct bucket
    for(int i = 0; i < NODESINBUCKET; i++)  //for each spot in the bucket
    {
        if(bucket[result]->table[i] != NULL)    //if the bucket table is pointing in allocated memory
        {
            if(strcmp(bucket[result]->table[i]->prefecture, pref) == 0) //if you find the prefecture you were looking for, print the stats
            {
                cout << "Stats for prefecure " << pref << ":" << endl;
                cout << "Amount of records: " << bucket[result]->table[i]->amount << endl;
                cout << "Total Debt: " << fixed << setprecision(2) << bucket[result]->table[i]->totaldebt << endl;
                cout << "Average Debt per Person: " << fixed << setprecision(2) << (bucket[result]->table[i]->totaldebt)/(bucket[result]->table[i]->amount) << endl << endl;
                return;
            }
        }
    }
    cout << "There are no records for prefecture: " << pref << endl;  //if not, let the user know
}
/*
void MyStructure::printSumStats()
{
    for(int i = 0; i < hashvalue; i++)  //for every bucket
    {
        for(int j = 0; j < NODESINBUCKET; j++)  //for every entry in the bucket
        {
            if(bucket[i]->table[j] != NULL) //if it's not empty, print the stats
            {
                cout << "Stats for prefecure " << bucket[i]->table[j]->prefecture << ":" << endl;
                cout << "Amount of records: " << bucket[i]->table[j]->amount << endl;
                cout << "Total Debt: " << fixed << setprecision(2) << bucket[i]->table[j]->totaldebt << endl;
                cout << "Average Debt per Person: " << fixed << setprecision(2) << (bucket[i]->table[j]->totaldebt)/(bucket[i]->table[j]->amount) << endl << endl;
            }
        }
    }
}*/

void MyStructure::printSumStats()
{
    Node* temp = head;
    while(temp != NULL)
    {
        cout << "Stats for prefecure " << temp->prefecture << ":" << endl;
        cout << "Amount of records: " << temp->amount << endl;
        cout << "Total Debt: " << fixed << setprecision(2) << temp->totaldebt << endl;
        cout << "Average Debt per Person: " << fixed << setprecision(2) << (temp->totaldebt)/(temp->amount) << endl << endl;
        temp = temp->next;
    }
}
