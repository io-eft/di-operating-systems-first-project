#include "mytree.hpp"

MyTree::Node::Node():debt(0), parent(NULL), left(NULL), right(NULL)
{
    strcpy(vat,"0");
}

MyTree::Node::Node(TaxPayer* tax, int a):parent(NULL), left(NULL), right(NULL), nodeNumber(a)
{
    strcpy(vat,tax->getVat());
    debt = tax->getDebt();
}

MyTree::Node::Node(TaxPayer* tax, Node* n, int a):parent(n), left(NULL), right(NULL), nodeNumber(a)
{
    strcpy(vat,tax->getVat());
    debt = tax->getDebt();
}

MyTree::MyTree(): root(NULL), nodes(0), currentNode(NULL), lastNode(NULL) {}

MyTree::~MyTree()
{
    if(!isEmpty())
        dissolveTree(root);
}

bool MyTree::isEmpty()
{
    if(root == NULL)
        return true;
    else
        return false;
}

void MyTree::swapNodes(Node* a, Node* b)    //Only swap node content, not actual nodes
{
    Node temp;
    temp.debt = a->debt;
    strcpy(temp.vat, a->vat);

    a->debt = b->debt;
    strcpy(a->vat,b->vat);

    b->debt = temp.debt;
    strcpy(b->vat,temp.vat);
}

void MyTree::correctTreeOnInsertion(Node* n)
{
    if(n->parent==NULL)     //If it's only one node, return
        return;
    else
    {
        if((n->parent)->debt > n->debt)     //If there parent has bigger debt than the new node, leave it as it is
            return;
        else
        {
            swapNodes(n, n->parent);    //If the child has bigger debt, swap their content
            correctTreeOnInsertion(n->parent);  //do it recursivly until it's in the way it should be
        }
    }
}

void MyTree::correctTreeOnRemoval(Node* n)
{
    if(n->left == NULL) //If it has no left node, it means it's the root, so nothing to do
        return;
    else
    {
        if(n->right == NULL)    //if it has only one child
        {
            if(n->debt > (n->left)->debt)   //if it's bigger than the child, leave it as it is
                return;
            else
            {
                swapNodes(n, n->left);      //if the child is bigger, swap their contents
                correctTreeOnRemoval(n->left);  //do it in recursivly, until the tree fulfills its requirements
            }
        }
        else        //if it has 2 children
        {
            if((n->left)->debt > (n->right)->debt)  //find if the left or right child is bigger, and then follow the instructions given above
            {
                if(n->debt > (n->left)->debt)
                    return;
                else
                {
                    swapNodes(n, n->left);
                    correctTreeOnRemoval(n->left);
                }
            }
            else
            {
                if(n->debt > (n->right)->debt)
                    return;
                else
                {
                    swapNodes(n, n->right);
                    correctTreeOnRemoval(n->right);
                }
            }
        }
    }
}

void MyTree::insertEntry(TaxPayer* tax)
{
    nodes++;    //increase the number of nodes. We do it now, so we can set the nodenumber correctly
    if(this->isEmpty())     //if the tree is empty, means the new node will be the root
    {
        Node* n = new Node(tax, nodes); //so set everything correctly
        root = n;
        currentNode = n;
        lastNode = n;
    }
    else    //if it's not the root
    {
        Node* n = new Node(tax, currentNode, nodes);
        lastNode = n;
        if(currentNode->left == NULL)   //check if the current father has a child already or not
        {
            currentNode->left = n;
        }
        else
        {
            currentNode->right = n;
            findNextParent();   //if it does, it means we have to find the new parent after adding this one
        }
        correctTreeOnInsertion(n);  //correct the tree so it fulfills the requirements
    }
}

void MyTree::findNextParent()
{
    Node* temp = currentNode;   //set a temporary pointer to the current parent
    while(temp->parent != NULL && temp == (temp->parent)->right)    //while the temporary has a parent, and is the right child of it
    {
        temp = temp->parent;    //set the temporary to be its father
    }
    if(temp->parent != NULL)    //if it still has a father, meaning it is now a left child
    {
        if((temp->parent)->right != NULL)   //if the father has a right child
            temp = (temp->parent)->right;   //set the temporary as its father's right child
        else
        {
            currentNode = temp->parent; //if it doesn't, set the current parent as the parent of the temporary
            return; //and return
        }

    }
    while(temp->left != NULL)   //if the father had a right child
    {
        temp = temp->left;  //go all the way down to the left
    }
    currentNode = temp; //and set the last node as the current father
}

void MyTree::findNewLast()
{
    Node* temp = lastNode->parent;  //we set the temporary node as the father of the current last node (not the last itself, so we can use the second condition in the while below
    while((temp->parent != NULL) && (temp == (temp->parent)->left)) //while the temporary has a father and is the left child of it
    {
        temp = temp->parent;    //set the temporary as the father of it
    }
    if(temp->parent != NULL)    //if the temporary still has a father
    {
        temp = (temp->parent)->left;    //set it as its fathers left child
    }
    while(temp->right != NULL)  //while it has right child
    {
        temp = temp->right; //go all the way down to the right
    }
    lastNode = temp;    //set the last node as the last right node
}

void MyTree::getRoot(char* result)
{
    if(!isEmpty())
        strcpy(result,root->vat);
    else
        strcpy(result, "0");
}
/*
void MyTree::removeRoot(char* result)   //function ended up not using at all
{
    if(!isEmpty())
    {
        strcpy(result,root->vat);

        if(nodes > 1)
        {
            swapNodes(root,lastNode);
            if((lastNode->parent)->left == lastNode)
            {
                (lastNode->parent)->left = NULL;
                Node* temp = lastNode;
                findNewLast();
                (temp->parent)->left = NULL;
                delete temp;
            }
            else
            {
                Node* n = lastNode->parent;
                n->right = NULL;
                delete lastNode;
                lastNode = n->left;
            }
            correctTreeOnRemoval(root);
        }
        else
        {
            delete root;
            root = NULL;
            lastNode = NULL;
            currentNode = NULL;
        }
        nodes--;
    }
    else
    {
        cout << "Tree is empty!" << endl;
        strcpy(result, "0");
    }
}*/

void MyTree::dissolveTree(Node* n)
{
    if(n->left != NULL) //recursively delete the nodes created, creating subtrees with the childs of the root
        dissolveTree(n->left);
    if(n->right != NULL)
        dissolveTree(n->right);
    delete n;
}

void MyTree::getNodesForPrint(Node* n, Node** index)
{
    index[n->nodeNumber - 1] = n;   //put each node as the node number of it, to be able to print them in order. Do it recursively for all nodes in the tree
    if(n->left != NULL)
        getNodesForPrint(n->left, index);
    if(n->right != NULL)
        getNodesForPrint(n->right, index);
}

void MyTree::printTree()
{
    if(!isEmpty())
    {
        Node** index = new Node*[nodes];    //set an index
        getNodesForPrint(root, index);  //fill it with information
        for(int i = 0; i < nodes; i++)  //pint it in order
            cout << "Node " << i + 1 << ": VAT: " << index[i]->vat << ", Debt: " << fixed << setprecision(2) << index[i]->debt << endl;
        delete[] index; //delete the allocated space
        cout << endl;
    }
}

int MyTree::lookUpVat(const char* vat, Node* n) //internal lookup value
{
    if(!isEmpty())  //if the tree is not empty
    {
        if(strcmp(vat, n->vat) == 0)    //check if the given node is the one we're looking for
        {
            int i = 0;  //set an integer to find the height
            while(n->parent != NULL)    //go all the way up to the root
            {
                i++;
                n = n->parent;
            }
            return i;   //return the height
        }
        else    //if the given node is not the one we're looking for
        {
            if(n->left != NULL)     //if it has a left child do it recursively for it
            {
                if(lookUpVat(vat, n->left) > 0)
                {
                    return lookUpVat(vat, n->left);
                }
            }
            if(n->right != NULL)    //if it has a right child, do the same
            {
                if(lookUpVat(vat, n->right) > 0)
                {
                    return lookUpVat(vat, n->right);
                }
            }
        }
    }
    return -1;  //if the value we're looking up for is not in the tree, return -1
}

int MyTree::lookUp(const char* vat)     //lookup function to call from "outside"
{
    return lookUpVat(vat, root);   //call the internal lookup funtion
}

int MyTree::getNodes()
{
    return nodes;
}

void MyTree::removeRoot()
{
    if(nodes > 0)   //if the tree actually has nodes
    {
        if(nodes > 1)   //if it has more than one
        {
            swapNodes(root,lastNode);   //swap the top with the last one
            if((lastNode->parent)->left == lastNode)    //if the last node is the left child, it means we'll have to find a new last node
            {
                (lastNode->parent)->left = NULL;    //set the parent to not have a left child anymore
                Node* temp = lastNode;    //set a temporary pointer to the lsat node
                findNewLast();  //find a new last node
                //(temp->parent)->left = NULL;
                delete temp;    //delete the old last node, freeing the memory
            }
            else    //if it is the right child, it means we already know where the new last will be
            {
                Node* n = lastNode->parent;
                n->right = NULL;
                delete lastNode;
                lastNode = n->left;
            }
            correctTreeOnRemoval(root); //correct the tree so it fulfills the requirements
        }
        else    //if it's only the root, delete and and set all other pointers to null
        {
            delete root;
            root = NULL;
            lastNode = NULL;
            currentNode = NULL;
        }
        nodes--;    //reduce the number of nodes
    }
    else    //if the tree is empty already, let the user know
        cout << "Tree is empty!" << endl;
}

void MyTree::getNodesForDumpfile(string* index) //external function
{
    getNodesForDump(root, index);   //call the internal one
}

void MyTree::getNodesForDump(Node* n, string* index)    //internal function
{
    if(!isEmpty())  //if the tree is not empty
    {
        index[n->nodeNumber - 1] = n->vat;  //set each node to the corresponding place in the array
        if(n->left != NULL)
            getNodesForDump(n->left, index);    //if it has a left child, do it recursively for the subtree
        if(n->right != NULL)
            getNodesForDump(n->right, index);   //if it has a right child, do it recursively for the subtree
    }
}
