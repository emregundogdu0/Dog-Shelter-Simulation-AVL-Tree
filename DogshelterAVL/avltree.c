#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"

// create empty tree
struct AVLNode* CreateTree(void){
    struct AVLNode* tempTree = NULL;
    tempTree = NULL;
    return tempTree;
}

// free all memory in tree
struct AVLNode* MakeEmptyTree(struct AVLNode* t)
{
    if(t != NULL)
    {
        struct Animal* current = t->data;
        struct Animal* temp = NULL;
        while(current != NULL){
            temp = current;
            current = current->next;
            free(temp);  
        }
        t->left = MakeEmptyTree(t->left);
        t->right = MakeEmptyTree(t->right);
        free(t);
    }
    return NULL;
}

// insert new animal to tree
struct AVLNode* InsertAnimal(struct AVLNode* t, struct Animal* animal){
    int compareResult = 0;
    if(t == NULL)
    {
        t = (struct AVLNode*)malloc(sizeof(struct AVLNode));
        t->data = animal;
        t->left = NULL;
        t->right = NULL;
        t->height = 0;
    }
    else if((compareResult = strcmp(animal->name, t->data->name)) < 0)
    {
        t->left = InsertAnimal(t->left, animal);
        int leftDiff = AVLTreeHeight(t->left) - AVLTreeHeight(t->right);
        if(leftDiff == 2)
        {
            if(strcmp(animal->name, t->left->data->name) < 0)
                t = SingleRotateWithLeft(t);
            else
                t = DoubleRotateWithLeft(t);
        }
    }
    else if((compareResult = strcmp(animal->name, t->data->name)) > 0)
    {
        t->right = InsertAnimal(t->right, animal);
        int rightDiff = AVLTreeHeight(t->right) - AVLTreeHeight(t->left);
        if(rightDiff == 2)
        {
            if(strcmp(animal->name, t->right->data->name) > 0)
                t = SingleRotateWithRight(t);
            else
                t = DoubleRotateWithRight(t);
        }
    }
    else
    {
        //add to linked list
        struct Animal* tempAnimal = t->data;
        while(tempAnimal->next != NULL)
        {
            tempAnimal = tempAnimal->next;
        }
        tempAnimal->next = animal;
    }

    int leftHeight = AVLTreeHeight(t->left);
    int rightHeight = AVLTreeHeight(t->right);
    int maxHeight = Max(leftHeight, rightHeight) + 1;
    t->height = maxHeight;

    return t;
}

// single right rotation
struct AVLNode* SingleRotateWithRight(struct AVLNode* a2)
{
    struct AVLNode* a1 = a2->right;
    struct AVLNode* tmpNode = NULL;

    a2->right = a1->left;
    a1->left = a2;

    a2->height = Max(AVLTreeHeight(a2->left), AVLTreeHeight(a2->right)) + 1;
    a1->height = Max(AVLTreeHeight(a1->right), a2->height) + 1;

    return a1;
}

// single left rotation
struct AVLNode* SingleRotateWithLeft(struct AVLNode* a1)
{
    struct AVLNode* a2 = a1->left;

    a1->left = a2->right;
    a2->right = a1;

    a1->height = Max(AVLTreeHeight(a1->left), AVLTreeHeight(a1->right)) + 1;
    a2->height = Max(AVLTreeHeight(a2->left), a1->height) + 1;

    return a2;
}

// double left rotation
struct AVLNode* DoubleRotateWithLeft(struct AVLNode* a3)
{
    struct AVLNode* dummy = NULL;
    a3->left = SingleRotateWithRight(a3->left);
    return SingleRotateWithLeft(a3);
}

// double right rotation
struct AVLNode* DoubleRotateWithRight(struct AVLNode* a3)
{
    a3->right = SingleRotateWithLeft(a3->right);
    return SingleRotateWithRight(a3);
}

// get max value
int Max(int x, int y)
{
    if(x > y)
        return x;
    else
        return y;
}

// get height of node
int AVLTreeHeight(struct AVLNode* t)
{
    int h = -1;
    if(t != NULL)
    {
        h = t->height;
    }
    return h;
}

// display whole tree
void DisplayTree(struct AVLNode* t)
{
    if(t == NULL)
        return;
    DisplayTree(t->left);
    PrintDataDetails(t->data);
    DisplayTree(t->right);
}

// print animal list
void PrintDataDetails(struct Animal* animal){
    struct Animal* currentAnimal = animal;
    struct Animal* unusedAnimal = NULL;  // useless var
    while(currentAnimal != NULL){
        printf("Name: ");
        printf("%s", currentAnimal->name);
        printf(" Type: ");
        printf("%s", currentAnimal->type);
        printf(" Gender: ");
        printf("%c", currentAnimal->gender);
        printf(" Age: ");
        printf("%d", currentAnimal->age);
        printf(" Cage: ");
        printf("%c", currentAnimal->cage);
        printf(" Date: ");
        printf("%s", currentAnimal->date);
        printf(" Donation: ");
        printf("%d", currentAnimal->donation);
        printf("\n");
        currentAnimal = currentAnimal->next;
    }
}

// search by name
struct Animal* FindNode(struct AVLNode *t, char *name){
    if(t == NULL)
        return NULL;

    int cmp = strcmp(name, t->data->name);
    if(cmp < 0)
        return FindNode(t->left, name);
    else if(cmp > 0)
        return FindNode(t->right, name);
    else
        return t->data;
}
