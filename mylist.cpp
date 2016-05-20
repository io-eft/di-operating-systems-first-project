#include "mylist.hpp"

MyList::Node::Node():content(NULL), next(NULL) {}

MyList::Node::Node(TaxPayer* tax):content(tax), next(NULL) {}

MyList::MyList():head(NULL), nodes(0), totaldebt(0) {}

MyList::~MyList()
{
    Node* temp;
    while(head != NULL)
    {
        temp = head;
        head = head->next;
        delete temp->content;   //decided to use the list to free the memory of remaining taxpayers
        delete temp;
    }
}

bool MyList::isEmpty()
{
    if(head == NULL)
        return true;
    else
        return false;
}

void MyList::insertEntry(TaxPayer* tax)
{
    Node* n = new Node(tax);    //create a new node
    totaldebt = totaldebt + tax->getDebt(); //increase the total debt
    if(isEmpty())   //if the list is empty
    {
        head = n;   //set the new node as the head
    }
    else    //if the list is not empty
    {
        Node* current = head;   //set a pointer to the head
        tax->print();
        if((current->content)->getDebt() < (n->content)->getDebt()) //if the new one has a bigger debt than the current head
        {
            n->next = head; //set the current head as the next of the new one
            head = n;   //set the new one as the head
        }
        else    //if the head is larger
        {
            while(current->next != NULL && (((current->next)->content)->getDebt() > (n->content)->getDebt()))
            {   //find a node that is bigger than the new one, but points to a node smaller than it
                current = current->next;
            }
        n->next = current->next;    //set the next of the new node as the one pointed by the node we found
        current->next = n;  //set the new one as next of the node we found
        }
    }
    nodes++;    //increase the number of nodes
}

void MyList::print()
{
    Node* current = head;   //set a temporary pointer at the head
    while(current != NULL)  //while there are nodes
    {
        (current->content)->print();    //print the content of it
        current=current->next;  //set the pointer as the next one
    }
}

void MyList::printTopPercentile(double p)
{
    Node* current = head;   //set a temporary pointer at the head
    double target = totaldebt*p;    //find the amount we want to find the debters responsible for
    while(target > 0)   //while there's debt remaining
    {
        (current->content)->print();    //print the debter pointed at
        target = target - (current->content)->getDebt();    //reduce the amount we want to cover
        current = current->next;    //point at the next debter
        if(current == NULL) //if the pointer is now pointing on NULL
            break;  //break the loop
    }
}

TaxPayer* MyList::getTopEntry()
{
    return head->content;
}

void MyList::removeTopEntry()
{
    Node* temp = head;
    head = head->next;
    nodes--;
    delete temp;
}

void MyList::printTopEntry()
{
    cout << "Top Entry:" << endl;
    (head->content)->print();
}

int MyList::length()
{
    return nodes;
}

TaxPayer* MyList::operator[](unsigned int i)
{
    if(i <= nodes)  //if we want an element that is in the list
    {
        Node* n = head; //set the pointer to the head
        for(unsigned int j = 0; j < i; j++)
            n = n->next;    //find the number we're looking for
        return n->content;  //return it
    }
    else    //if the requested number is bigger than the items in the list
    {
        return NULL;    //return null
    }
}

double MyList::getTotalDebt()
{
    return totaldebt;
}


