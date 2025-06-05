#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"

// Function prototypes
struct AVLNode* loadAnimals(char *fileName);
struct AVLNode* insertAnimal(struct AVLNode* t, char *name, char *type, char cage, char gender, char *date, int age, int donation);
void infoAnimal(struct AVLNode* t, char *name);
void displayAnimals(struct AVLNode* t);
struct Animal* findPopularDonation(struct AVLNode* t);
void popularAnimal(struct AVLNode* t, struct Animal* highestDonationAnimal);

int main (int argc, char **argv){

    struct AVLNode* myTree;
    int menuOption, flag = 1;

    if(argc == 1){
        printf("Please provide a file name: ");  // if file name not given
        return 0;
    }

    myTree = loadAnimals(argv[1]); // load animals from file

    printf("Welcome to data analysis @ Animal Shelter\n");

    while (flag){
        // print menu to user
        printf("\n-------Menu-------\n"
               "(1)Insert animal\n"
               "(2)Display the full index of animals\n"
               "(3)Display the details of the animals\n"
               "(4)Display the popular animal\n"
               "(5)Exit\n"
               "Enter your option:");
        scanf("%d", &menuOption);

        switch (menuOption) {

            case 1:{
                // user insert new animal
                char name[50], type[50], cage, gender, date[11];
                int age, donation;

                printf("Please enter animal details:\n");
                printf("Name:");
                scanf(" %s", name);
                printf("Type:");
                scanf(" %s", type);
                printf("Cage:");
                scanf(" %c", &cage);
                printf("Gender:");
                scanf(" %c",&gender);
                printf("Date:");
                scanf(" %s",date);
                printf("Age:");
                scanf("%d",&age);
                printf("Donation:");
                scanf("%d",&donation);
                myTree = insertAnimal(myTree, name, type, cage, gender, date, age, donation);
                printf("%s %s has been added successfully.\n", type, name);
                break;
            }
            case 2:{
                displayAnimals(myTree);  // show all animals
                break;
            }
            case 3:{
                char name[30];
                printf("Name: ");
                scanf(" %s", name);
                infoAnimal(myTree,name); // show animal by name
                break;
            }
            case 4:{
                printf("Detailed information of the most popular animal: \n");
                popularAnimal(myTree, findPopularDonation(myTree));
                break;
            }
            case 5: {
                flag = 0; // exit
                break;
            }
            default:{
                printf("Option %d can't be recognized.", menuOption);
            }
        }
    }

    myTree= MakeEmptyTree(myTree); // free memory
    return 0;
}

// Insert new animal to tree
struct AVLNode* insertAnimal(struct AVLNode* t, char *name, char *type, char cage, char gender, char *date, int age, int donation) {
    struct Animal* newAnimal = (struct Animal*)malloc(sizeof(struct Animal));
    strcpy(newAnimal->name, name);
    strcpy(newAnimal->type, type);
    newAnimal->cage = cage;
    newAnimal->gender = gender;
    strcpy(newAnimal->date, date);
    newAnimal->age = age;
    newAnimal->donation = donation;
    newAnimal->next = NULL;

    t = InsertAnimal(t, newAnimal);  // insert into AVL
    return t;
}

// Load animals from file and add to tree
struct AVLNode* loadAnimals(char *fileName){
    FILE *fp = fopen(fileName, "r");
    if(fp == NULL){
        printf("File not found.\n");
        return NULL;
    }

    struct AVLNode* tree = CreateTree();
    char line[256];
    while(fgets(line, sizeof(line), fp)){
        char *part;
        char name[50], type[50], date[11];
        char cage, gender;
        int age, donation;

        // part by ";"
        part = strtok(line, ";");
        if(part != NULL) strcpy(name, part);
        part = strtok(NULL, ";");
        if(part != NULL) strcpy(type, part);
        part = strtok(NULL, ";");
        if(part != NULL) gender = part[0];
        part = strtok(NULL, ";");
        if(part != NULL) age = atoi(part);
        part = strtok(NULL, ";");
        if(part != NULL) cage = part[0];
        part = strtok(NULL, ";");
        if(part != NULL) strcpy(date, part);
        part = strtok(NULL, ";\n");
        if(part != NULL) donation = atoi(part);

        tree = insertAnimal(tree, name, type, cage, gender, date, age, donation);
    }
    return tree;
}

// Print all animals
void displayAnimals(struct AVLNode* t){
    if(t == NULL) return;
    displayAnimals(t->left);
    struct Animal* curr = t->data;
    while(curr != NULL){
        printf("Name: ");
        printf("%s", curr->name);
        printf(" Type: ");
        printf("%s", curr->type);
        printf(" Gender: ");
        printf("%c", curr->gender);
        printf(" Age: ");
        printf("%d", curr->age);
        printf(" Cage: ");
        printf("%c", curr->cage);
        printf(" Date: ");
        printf("%s", curr->date);
        printf(" Donation: ");
        printf("%d", curr->donation);
        printf("\n");
        curr = curr->next;
    }
    displayAnimals(t->right);
}

// Print animals  name
void infoAnimal(struct AVLNode* t, char *name){
    struct Animal* found = FindNode(t, name);
    if(found == NULL){
        printf("There is no available animal whose name is ");
        printf("%s", name);
        printf(".\n");
        return;
    }
    while(found != NULL){
        printf("Name: ");
        printf("%s", found->name);
        printf(" Type: ");
        printf("%s", found->type);
        printf(" Gender: ");
        printf("%c", found->gender);
        printf(" Age: ");
        printf("%d", found->age);
        printf(" Cage: ");
        printf("%c", found->cage);
        printf(" Date: ");
        printf("%s", found->date);
        printf(" Donation: ");
        printf("%d", found->donation);
        printf("\n");
        found = found->next;
    }
}

// Find animal with biggest donation
struct Animal* findPopularDonation(struct AVLNode* t){
    if(t == NULL) return NULL;

    struct Animal* maxLeft = findPopularDonation(t->left);
    struct Animal* maxRight = findPopularDonation(t->right);
    struct Animal* maxCurr = t->data;
    struct Animal* temp = t->data->next;
    while(temp != NULL){
        if(temp->donation > maxCurr->donation){
            maxCurr = temp;
        }
        temp = temp->next;
    }if(maxLeft != NULL && maxLeft->donation > maxCurr->donation){
        maxCurr = maxLeft;
    }if(maxRight != NULL && maxRight->donation > maxCurr->donation){
        maxCurr = maxRight;
    }

    return maxCurr;
}

// Print biggest donation animals
void popularAnimal(struct AVLNode* t, struct Animal* highestDonationAnimal){
    if(t == NULL || highestDonationAnimal == NULL) return;

    popularAnimal(t->left, highestDonationAnimal);

    struct Animal* curr = t->data;
    while(curr != NULL){
        if(curr->donation == highestDonationAnimal->donation){
            printf("Name: ");
            printf("%s", curr->name);
            printf(" Type: ");
            printf("%s", curr->type);
            printf(" Gender: ");
            printf("%c", curr->gender);
            printf(" Age: ");
            printf("%d", curr->age);
            printf(" Cage: ");
            printf("%c", curr->cage);
            printf(" Date: ");
            printf("%s", curr->date);
            printf(" Donation: ");
            printf("%d", curr->donation);
            printf("\n");
        }
        curr = curr->next;
    }

    popularAnimal(t->right, highestDonationAnimal);
}
